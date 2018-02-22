<?php

/**
 * @file
 * Provides the image field normalizer.
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Implements a normalizer for image fields.
 */
class GDPRExportImageFieldNormalizer implements NormalizerInterface {
  public function normalize($object, $format = NULL, array $context = array()) {
    $file = $object->value();

    gdpr_export_register_file_for_export($file['fid']);

    return [
      'title' => $file['title'],
      'filename' => $file['filename'],
      'path' => file_uri_target($file['uri']),
    ];
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper
      && $data->info()['type'] == 'field_item_image';
  }

}
