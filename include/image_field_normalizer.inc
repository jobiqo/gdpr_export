<?php

/**
 * @file
 * Provides the image field normalizer.
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Implements a normalizer for image fields, based on the
 * GDPRExportFileFieldNormalizer, adding the 'title' property if available.
 */
class GDPRExportImageFieldNormalizer extends GDPRExportFileFieldNormalizer {
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

    $result = parent::normalize($object, $format, $context);

    // Add the title if not empty.
    if (!empty($result['title'])) {
      $result['title'] = $file['title'];
    }

    return $result;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper
      && $data->info()['type'] == 'field_item_image';
  }
}
