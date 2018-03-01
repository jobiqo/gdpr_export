<?php

/**
 * @file
 * Provides the date normalizer
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * A data formatter for date columns.
 */
class GDPRExportDateNormalizer implements NormalizerInterface {
  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    return format_date($object->value());
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityValueWrapper &&
      $data->info()['type'] == 'date';
  }
}
