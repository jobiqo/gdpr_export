<?php

/**
 * @file
 * Provides the date normalizer
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareTrait;
use Symfony\Component\Serializer\Exception\NotNormalizableValueException;

/**
 * A data formatter for date columns.
 */
class GDPRExportStructNormalizer implements NormalizerInterface, NormalizerAwareInterface {
  use NormalizerAwareTrait;

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $properties = $object->info()['property info'];

    $normalized = [];
    foreach ($properties as $name => $property) {
      try {
        $normalized[$property['label']] = $this->normalizer->normalize($object->$name);
      }
      catch (NotNormalizableValueException $exception) {
        watchdog_exception('gdpr_export', $exception);
      }
    }

    // Export the date in the ISO 8601 format.
    return $normalized;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper &&
      $data->info()['type'] == 'struct';
  }
}
