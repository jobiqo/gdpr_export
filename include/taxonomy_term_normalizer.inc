<?php

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * A basic taxonomy term formatter, which simply outputs the referenced terms
 * name.
 */
class GDPRExportTaxonomyTermNormalizer implements NormalizerInterface {
  public function normalize($object, $format = NULL, array $context = array()) {
    try {
      return $object->name->value();
    } catch (EntityMetadataWrapperException $exception) {
      watchdog_exception('gdpr_export', $exception);
      return '';
    }
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityDrupalWrapper
      && $data->info()['type'] == 'taxonomy_term';
  }
}
