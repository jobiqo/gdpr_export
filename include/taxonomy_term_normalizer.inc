<?php

/**
 * @file
 * Provides a normalizer for taxonomy term references.
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Implements a basic normalizer for taxonomy terms, which will simply return
 * the name of the term.
 */
class GDPRExportTaxonomyTermNormalizer implements NormalizerInterface {
  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    try {
      return $object->name->value();
    }
    catch (EntityMetadataWrapperException $exception) {
      // If there is some problem with retrieving the value just return NULL.
      return NULL;
    }
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityDrupalWrapper
      && $data->info()['type'] == 'taxonomy_term';
  }
}
