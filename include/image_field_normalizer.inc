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

    // Check if the export directory was passed to the context and if that
    // directory exists.
    if (!empty($context['gdpr_export_dir']) && file_prepare_directory($context['gdpr_export_dir'])) {
      // Copy the file to the export dir, so that it gets zipped with the
      // export.
      // The target directory should be the directory with out the scheme, so
      // that we don't accidentally replace files, or have to handle suffixes on
      // the filename.
      $target = $context['gdpr_export_dir'] . "/" . file_uri_target($file['uri']);
      $dir = dirname($target);
      file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
      file_unmanaged_copy($file['uri'], $target);
    }

    return [
      'title' => $file['title'],
      'filename' => file_uri_target($file['uri']),
      'path' => file_uri_target($file['uri']),
    ];
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper
      && $data->info()['type'] == 'field_item_image';
  }
}
