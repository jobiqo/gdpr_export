<?php

/**
 * Provides a normalizer for user objects.
 */
class GDPRExportUserNormalizer extends GDPRExportEntityNormalizer {
  /**
   * Returns the normalized basic user properties, i.e. the basic user columns.
   */
  protected function getBasicProperties($object) {
    // @todo: Check that this are really the default drupal core properties.
    // @todo: Add language as the appropriate normalizer is ready.
    $properties = [
      'uid',
      'name',
      'mail',
      'url',
      'last_access',
      'last_login',
      'created',
    ];

    $normalized = [];
    foreach ($properties as $property) {
      $normalized[$property] = $this->normalizer->normalize($object->$property);
    }

    return $normalized;
  }

  public function normalize($object, $format = NULL, array $context = array()) {
    $result = $this->getBasicProperties($object);
    $result += $this->getNormalizedFields($object);

    // Allow modules to add or remove properties
    drupal_alter('gdpr_export_user_normalizer', $result, $object);

    return $result;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $this->isEntityType($data, 'user');
  }
}
