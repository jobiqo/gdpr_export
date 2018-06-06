<?php

/**
 * Provides a class to normalize Privatemsg messages.
 */

/**
 * Normalizes Privatemsg messages.
 */
class GDPRExportPrivatemsgMessage extends GDPRExportEntityNormalizer {
  public function normalize($object, $format = NULL, array $context = array()) {
    $properties = [
      'timestamp',
      'subject',
      'body',
    ];

    $export = [];
    foreach ($properties as $property) {
      $export[$property] = $this->normalizer->normalize($object->$property, $format, $context);
    }

    // Non serializable properties.
    $plain_properties = [
      'format',
      'is_new',
    ];
    foreach ($plain_properties as $property) {
      $export[$properties] = $this->$property;
    }

    return $export;
  }

  public function supportsNormalization($data, $format = NULL) {
    return $this->isEntityType($data, 'privatemsg_message');
  }
}
