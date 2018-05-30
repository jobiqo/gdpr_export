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
    $info = $object->info();
    $properties = $info['property info'];

    $normalized = [];
    foreach ($properties as $name => $property) {
      try {
        // To be able to use the properties label as tag, we need to preprocess
        // it, to remove spaces and make them a bit cleaner.
        $filter = [
          ' ' => '_',
          '-' => '_',
          '/' => '_',
          '[' => '_',
          ']' => '',
        ];
        $key = drupal_clean_css_identifier(drupal_strtolower($property['label']), $filter);
        $normalized[$key] = $this->normalizer->normalize($object->$name);
      }
      catch (NotNormalizableValueException $exception) {
        watchdog('gdpr_export', "Could not normalize the property @property of @type in struct @struct with name @name. No supporting normalizer found.", [
          '@property' => $property['label'],
          '@type' => $property['type'],
          '@struct' => $info['label'],
          '@name' => $info['name'],
        ], WATCHDOG_WARNING);
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
