<?php

/**
 * Provides a normalizer for user objects.
 */
class GDPRExportUserNormalizer extends GDPRExportEntityNormalizer {
  /**
   * Returns the normalized basic user properties, i.e. the basic user columns.
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
  protected function getBasicProperties($object, $format = NULL, array $context = array()) {
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
      $normalized[$property] = $this->normalizer->normalize($object->$property, $format, $context);
    }

    // Export the ip log if the uiplog is enabled.
    if (module_exists('uiplog')) {
      $log = db_select('uiplog', 'uip')
        ->fields('uip', [])
        ->condition('uid', $object->getIdentifier())
        ->execute()
        ->fetchAllAssoc('lid');

      $log = array_map(function($entry) {
        $time = new DateTime();
        $time->setTimestamp($entry->timestamp);

        return [
          'ip' => $entry->ip,
          'time' => $time->format(DateTime::ISO8601),
        ];
      }, $log);

      $normalized['ips'] = array_values($log);
    }

    return $normalized;
  }

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $result = $this->getBasicProperties($object, $format, $context);
    $result += $this->getNormalizedFields($object, $format, $context);

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
