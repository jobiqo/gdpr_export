<?php

/**
 * Provides a class to normalize comments.
 */

/**
 * Normalizes comments.
 */
class GDPRExportComment extends GDPRExportEntityNormalizer {
  /**
   * Returns the normalized basic user properties, i.e. the basic comment
   * columns.
   *
   * @param object $object
   *   Object to normalize
   * @param string $format
   *   Format the normalization result will be encoded as
   * @param array $context
   *   Context options for the normalizer
   *
   * @return array|scalar
   *   The normalized $object.
   */
  public function getBasicProperties($object, $format = NULL, array $context = array()) {
    $properties = [
      'created',
      'hostname',
      'status',
      'name',
      'mail',
      'homepage',
      'subject',
    ];

    $normalized = [];
    foreach ($properties as $property) {
      $normalized[$property] = $this->normalizer->normalize($object->$property, $format, $context);
    }

    return $normalized;
  }

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $result = $this->getBasicProperties($object, $format, $context);
    $result += $this->getNormalizedFields($object, $format, $context);

    return $result;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $this->isEntityType($data, 'comment');
  }
}
