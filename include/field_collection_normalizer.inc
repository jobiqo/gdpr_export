<?php
/**
 * @file
 * Provides a normalizer for field collection items.
 */

use Symfony\Component\Serializer\Normalizer\NormalizerInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareInterface;
use Symfony\Component\Serializer\Normalizer\NormalizerAwareTrait;
use Symfony\Component\Serializer\Exception\NotNormalizableValueException;


/**
 * Implements a normalizer for field collection items.
 */
class GDPRExportFieldCollectionItem implements NormalizerInterface, NormalizerAwareInterface {
  use NormalizerAwareTrait;

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $info = $object->info();

    // For field collections we only want to export fields . Therefore get all
    // field names and only normalize the those.
    $field_names = array_keys(field_info_instances($info['type'], $info['bundle']));

    $result = [];
    foreach ($field_names as $field_name) {
      try {
        $result[$field_name] = $this->normalizer->normalize($object->$field_name);
      } catch (NotNormalizableValueException $exception) {
        watchdog_exception('gdpr_export', $exception, t(''));
      } catch (EntityMetadataWrapperException $exception) {
        watchdog_exception('gdpr_export', $exception);
      }
    }

    return $result;
  }

  /**
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $data instanceof EntityDrupalWrapper
      && $data->info()['type'] == 'field_collection_item';
  }

}
