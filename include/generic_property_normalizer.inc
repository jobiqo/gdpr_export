<?php

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;
/**
 * A data formatter the formats generic field types.
 */
class GDPRExportGenericDataNormalizer implements NormalizerInterface {
  public function normalize($object, $format = NULL, array $context = array()) {
    return $object->value();
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityValueWrapper
      && in_array($data->info()['type'], ['text', 'integer', 'text_formatted']);
  }
}
