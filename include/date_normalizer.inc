<?php

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;
/**
 * A data formatter for date columns.
 */
class GDPRExportDateNormalizer implements NormalizerInterface {
  public function normalize($object, $format = NULL, array $context = array()) {
    return format_date($object->value());
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityValueWrapper &&
      $data->info()['type'] == 'date';
  }
}
