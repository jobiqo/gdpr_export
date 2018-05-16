<?php

/**
 * @file
 * Hooks provided by the gdpr export module
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allows you to register new normalizers.
 *
 * The function should return an array with the class name as key, the
 * normalizers weight as value. The Lower the weight is, the higher it will
 * prioritized.
 * If you want to override for example the default User normalizer
 * (GDPRExportUserNormalizer), which has a weight of 5, your specialized
 * normalizer need a weight < 5.
 *
 * Normalizers can either implement the Symfony NormalizerInterface or be based
 * on one of the existing Normalizers. For fieldable entity you can for example
 * use the GDPRExportEntityNormalizer, which has helper functions to check the
 * entity type & bundle, to retrieve the normalized fields.
 * For an example take a look at the GDPRExportFieldCollectionItemNormalizer.
 *
 * @return array
 *   An array with the normalizers class name as key and its weight as value.
 *
 * @see gdpr_export_gdpr_export_normalizer_info()
 * @see \Symfony\Component\Serializer\Normalizer\NormalizerInterface
 * @see GDPRExportEntityNormalizer
 * @see GDPRExportFieldCollectionItemNormalizer
 */
function hook_gdpr_export_normalizer_info() {
  return [
    'SpecialUserNormalizer' => -10,
  ];
}

/**
 * Alter the list of normalizers.
 *
 * @param array $normalizers
 *   An array with the normalizers class name as key and its weight as value.
 *
 * @see \hook_gdpr_export_normalizer_info()
 */
function hook_gdpr_export_normalizer_info_alter(&$normalizers) {
  unset($normalizers['GDPRExportUserNormalizer']);
}

/**
 * Alter if the field of an entity should be exported.
 *
 * @param bool $should_export
 *   True if the field should be exported, false if not.
 * @param array $context
 *   An array containing the name of the field to be exported in the key
 *  'field_name' and the entity that contains this field in the key 'entity'
 */
function hook_gdpr_export_entity_should_export_field_alter(&$should_export, $context) {
  if ($context['entity']->type == 'user'
    && $context['field_name'] == 'field_user_contacts')
  {
    $should_export = FALSE;
  }
}

/**
 * Alter the fields that the field collection normalizer should return.
 *
 * @param array $fields
 *   An array with the normalized fields, keyed by the field names.
 *
 * @param EntityDrupalWrapper $field_collection_wrapper
 *   A EntityDrupalWrapper containing the field collection to be normalized.
 */
function hook_gdpr_export_field_collection_item_normalizer_alter(&$fields, $field_collection_wrapper) {
  unset($fields['field_something']);
}


/**
 * Alter the fields that the field collection normalizer should return.
 *
 * @param array $properties
 *   An array with the normalized $properties, keyed by the property names.
 *
 * @param EntityDrupalWrapper $user_wrapper
 *   A EntityDrupalWrapper containing the user object to be normalized.
 */
function hook_gdpr_export_user_normalizer_alter(&$properties, $user_wrapper) {
  unset($properties['uid']);
}

/**
 * Allows to export files with the gdpr user export.
 *
 * If additional data should be exported, for example a profile or a node
 * related to the account, then modules should implement this hook.
 * New entities can be exported using gdpr_export_serialize_entity() and have to
 * be saved to the directory given in $context['gdpr_export_dir'] using
 * file_unmanaged_save_data(). The function gdpr_export_user_export() will then
 * zip all the files in $context['gdpr_export_dir'], send it to the client and
 * remove the directory afterwards.
 *
 * @param object $account
 *   The user account for which the data should be exported.
 * @param string $format
 *   The format which should be used for the export. Currently only 'xml' and
 *   'json' are supported.
 * @param array $context
 *   An array of contexts. The default context gdpr_export_dir contains the temp
 *   directory to which files copied or exported for zipping.
 */
function hook_gdpr_export_user_export($account, $format, $context) {
  // Export a certain profile from the profile2 module. An appropriate profile2
  // normalizer would have to be implemented though.
  // @see GDPRExportEntityNormalizer.
  $profile = profile2_load_by_user($account, 'user_profile');
  $meta = entity_metadata_wrapper('profile2', $profile);
  $data = gdpr_export_serialize_entity($meta, $format);
  file_unmanaged_save_data($data, $context['gdpr_export_dir'] . "/user_profile.$format");
}

/**
 * Change the format used for the exports.
 *
 * @param string $format
 *   Either json or xml (default).
 */
function hook_gdpr_export_user_export_format_alter(&$format) {
  $format = 'json';
}

/**
 * Alter the contexts passed to the hook_gdpr_export_user_export()
 * implementations and serializations. Encoders and normalizers will therefore
 * be able to access those options.
 *
 * @param array $context
 *   An array of contexts to alter. The default context gdpr_export_dir contains
 *   the temp directory to which files copied or exported for zipping.
 */
function hook_gdpr_export_user_export_context_alter(&$context) {
  $context['gdpr_export_dir'] = 'some_other_dir';
}

/**
 * @} End of "addtogroup hooks".
 */
