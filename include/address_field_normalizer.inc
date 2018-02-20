<?php

use \Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Implements a normalizer for the addressfield.
 */
class GDPRExportAddressFieldNormalizer implements NormalizerInterface {
  public function normalize($object, $format = NULL, array $context = array()) {
    $address = $object->raw();

    // Remove empty values and the data key, added by the
    // addressfield_autocomplete module.
    $address = array_filter($address, function ($value, $key) {
      return !empty($value) && $key != 'data';
    }, ARRAY_FILTER_USE_BOTH );

    return $address;
  }

  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityStructureWrapper
      && $data->info()['type'] == 'addressfield';
  }
}
