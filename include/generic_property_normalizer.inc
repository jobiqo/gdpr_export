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
    return $object->value();
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    // @todo: Add additional formats like float
    return $data instanceof EntityValueWrapper
      && in_array($data->info()['type'],
        ['text', 'integer', 'text_formatted', 'boolean', 'uri']);
  }
}
