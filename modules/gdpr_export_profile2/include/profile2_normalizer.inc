<?php

/**
 * Provides a normalizer for profile2 objects.
 */
class GDPRProfileNormalizer extends GDPRExportEntityNormalizer {

  /**
   * Normalize Profile object.
   *
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $result = $this->getNormalizedFields($object, $format, $context);
    return $result;
  }

  /**
   * Determines if this normalizer matches the object type supplied.
   *
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $this->isEntityType($data, 'profile2');
  }

}
