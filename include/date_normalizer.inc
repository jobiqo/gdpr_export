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
    // Export the date in the ISO 8601 format.
    try {
      return date('c', $object->value());
    }
    catch (EntityMetadataWrapperException $exception) {
      // If there is some problem with retrieving the date just ignore
      // the exception and return NULL.
      return NULL;
    }
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityValueWrapper &&
      $data->info()['type'] == 'date';
  }
}
