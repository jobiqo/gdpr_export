<?php

/**
 * @file
 * Provides a helper class to implement normalizers based on entities.
 */

use Symfony\Component\Serializer\Normalizer\NormalizerInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareTrait;
use Symfony\Component\Serializer\Exception\NotNormalizableValueException;


/**
 * Helper class to implement normalizers based on entities.
 */
abstract class GDPRExportEntityNormalizer implements NormalizerInterface, NormalizerAwareInterface {
  use NormalizerAwareTrait;

  /**
   * Returns whether the given object is an entity of the given type.
   *
   * @param object $data
   *   The object which should be checked.
   * @param string $type
   *   The type the entity should be.
   *
   * @return bool
   *   TRUE if the given object is an entity of the correct type, FALSE if else.
   */
  protected function isEntityType($data, $type) {
    return $data instanceof EntityDrupalWrapper
      && $data->type() == $type;
  }

  /**
   * Returns whether the given object is an entity of the given type and bundle.
   *
   * @param object $data
   *   The object which should be checked.
   * @param string $type
   *   The type the entity should be.
   * @param $bundle
   *   The bundle the entity should be.
   *
   * @return bool
   *   TRUE if the given object is an entity of the correct type & bundle, FALSE
   *   if else.
   */
  protected function isEntityBundle($data, $type, $bundle) {
    return $this->isEntity($data, $type) && $data->getBundle() == $bundle;
  }

  /**
   * Returns all normalized fields of the given entity
   * @param object $object
   *   Object to normalize
   * @param string $format
   *   Format the normalization result will be encoded as
   * @param array $context
   *   Context options for the normalizer
   *
   * @return array|scalar
   *   An array containing the the normalized field values, keyed by the field
   *   names.
   */
  protected function getNormalizedFields($object, $format = NULL, array $context = array()) {
    // Get all fields names.
    $field_names = array_keys(field_info_instances($object->type(),
      $object->getBundle()));

    $result = [];
    // Normalize and save it to the results array keyed by the field name.
    foreach ($field_names as $field_name) {
      try {
        $result[$field_name] = $this->normalizer->normalize($object->$field_name, $format, $context);
      }
      catch (NotNormalizableValueException $exception) {
        watchdog_exception('gdpr_export', $exception);
      }
      catch (EntityMetadataWrapperException $exception) {
        watchdog_exception('gdpr_export', $exception);
      }
    }

    return $result;
  }
}
