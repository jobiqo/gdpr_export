<?php

use Symfony\Component\Serializer\Normalizer\NormalizerInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareTrait;

class GDPRExportListNormalizer implements NormalizerInterface, NormalizerAwareInterface {
  use NormalizerAwareTrait;

  public function normalize($object, $format = NULL, array $context = array()) {
    $info = $object->info();
    $type = entity_property_list_extract_type($info['type']);

    $result = [];
    foreach ($object as $item) {
      $result[] = $this->normalizer->normalize($item);
    }
    return $result;
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityListWrapper;
  }
}
