<?php

/**
 * @file
 * Provides a generic normalizer
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;
/**
 * A data formatter the formats the generic property types, text, integer,
 * text_formatted, boolean and uri.
 */
class GDPRExportGenericDataNormalizer implements NormalizerInterface {

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    try {
      return $object->value();
    }
    catch (EntityMetadataWrapperException $exception) {
      // If there is some problem with retrieving the value just return NULL.
      return NULL;
    }
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    // @todo: Add additional formats like float
    return $data instanceof EntityMetadataWrapper
      && in_array($data->info()['type'],
        ['text', 'integer', 'text_formatted', 'boolean', 'uri' , 'decimal']);
  }
}
