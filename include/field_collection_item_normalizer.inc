<?php

/**
 * @file
 * Provides a normalizer for field collection items.
 */


/**
 * Implements a normalizer for field collection items.
 */
class GDPRExportFieldCollectionItemNormalizer extends GDPRExportEntityNormalizer {

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    // In most cases it will be enough to export the fields of a field
    // collection item.
    $result = $this->getNormalizedFields($object);

    // Allow modules to alter the fields to export based on the entity meta data
    // wrapper.
    drupal_alter('gdpr_export_field_collection_item_normalizer', $result,
      $object);

    return $result;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $this->isEntityType($data, 'field_collection_item');
  }
}
