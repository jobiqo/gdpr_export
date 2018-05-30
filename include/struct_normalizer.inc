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
 * A normalizer for struct fields used by for example date durations or
 * intervals.
 */
class GDPRExportStructNormalizer implements NormalizerInterface, NormalizerAwareInterface {
  use NormalizerAwareTrait;

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    // The possible values are stored in the property info.
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
