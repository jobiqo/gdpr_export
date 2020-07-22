<?php

/**
 * @file
 * Provides the file field normalizer.
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Implements a normalizer for file fields, which also copies to the
 * gdpr_export_dir if it was given in the context.
 */
class GDPRExportFileFieldNormalizer implements NormalizerInterface {
  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    try {
      $file = $object->value();
    }
    catch (EntityMetadataWrapperException $exception) {
      // If there is some problem with retrieving the file just ignore
      // the exception and return NULL.
      return NULL;
    }

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
      'filename' => $file['filename'],
      'path' => file_uri_target($file['uri']),
    ];
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper
      && $data->info()['type'] == 'field_item_file';
  }
}
