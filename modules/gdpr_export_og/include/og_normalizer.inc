<?php

/**
 * Provides a normalizer for organic groups.
 */
class GDPRExportOGNormalizer extends GDPRExportEntityNormalizer {

  /**
   * Normalize Profile object.
   *
   * @inheritdoc
   */
  public function normalize($object, $format = NULL, array $context = array()) {
    $membership = $object->raw();

    $group_entity = entity_metadata_wrapper($membership->group_type, $membership->gid);

    $result['label'] = $group_entity->label();
    $result['type'] = $membership->type;
    $result['state'] = $membership->state;

    try {
      $result['created'] = $this->normalizer->normalize($object->created, $format, $context);
    }
    catch (NotNormalizableValueException $exception) {
      watchdog('gdpr_export', "Could not normalize the field @field_name with type @field_type in entity @entity with bundle @bundle. No supporting normalizer found.", [
        '@field_name' => 'created',
        '@field_type' => $object->created->info()['type'],
        '@entity' => $object->type(),
        '@bundle' => $object->getBundle(),
      ], WATCHDOG_WARNING);
    }
    catch (EntityMetadataWrapperException $exception) {
      watchdog_exception('gdpr_export', $exception);
    }

    $result += $this->getNormalizedFields($object, $format, $context);
    return $result;
  }

  /**
   * Determines if this normalizer matches the object type supplied.
   *
   * @inheritdoc
   */
  public function supportsNormalization($data, $format = NULL) {
    return $this->isEntityType($data, 'og_membership');
  }

}
