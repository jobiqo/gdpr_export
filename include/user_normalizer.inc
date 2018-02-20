<?php

/**
 * Provides a normalizer for user objects.
 */
class GDPRExportUserNormalizer extends GDPRExportEntityNormalizer {
  /**
   * @inheritdoc
   */
  protected function getProperties() {
    // @todo: Check that this are really the default drupal core properties.
    $properties = [
      'uid',
      'name',
      'mail',
      'url',
      'last_access',
      'last_login',
      'created',
      'language',
    ];

    drupal_alter('gdpr_export_user_normalizer_fields', $properties);

    return $properties;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityDrupalWrapper && $data->type() == 'user';
  }
}
