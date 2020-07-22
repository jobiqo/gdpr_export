<?php

/**
 * @file
 * Provides the addressfield normalizer
 */

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Implements a normalizer for the addressfield.
 */
class GDPRExportAddressFieldNormalizer implements NormalizerInterface {
  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    try {
      $address = $object->raw();
    }
    catch (EntityMetadataWrapperException $exception) {
      // If there is some problem with retrieving the address just ignore
      // the exception and return NULL.
      return NULL;
    }

    // Remove empty values and the data key, added by the
    // addressfield_autocomplete module.
    if (!empty($address)) {
      $address = array_filter($address, function ($value, $key) {
        return !empty($value) && $key != 'data';
      }, ARRAY_FILTER_USE_BOTH);
    }

    return $address;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper
      && $data->info()['type'] == 'addressfield';
  }
}
