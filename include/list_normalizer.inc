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
    $result = [];
    try {
      foreach ($object as $item) {
        $result[] = $this->normalizer->normalize($item, $format, $context);
      }
    }
    catch (EntityMetadataWrapperException $exception) {
      // If there is some problem with retrieving the list values just ignore
      // the exception and return what we have so far in the list.
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
