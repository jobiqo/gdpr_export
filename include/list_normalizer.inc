<?php

/**
 * @file
 * Provides a normalizer for entity list wrappers.
 */

use Symfony\Component\Serializer\Normalizer\NormalizerInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareTrait;

/**
 * Implements a normalizer for property lists.
 */
class GDPRExportListNormalizer implements NormalizerInterface, NormalizerAwareInterface {
  use NormalizerAwareTrait;

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $info = $object->info();
    $type = entity_property_list_extract_type($info['type']);

    $result = [];
    foreach ($object as $item) {
      $result[] = $this->normalizer->normalize($item, $format, $context);
    }
    return $result;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityListWrapper;
  }
}
