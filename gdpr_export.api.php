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
 * Allows to register new files to be exported with the user data.
 *
 * If additional data should be exported, for example a profile or a node
 * related to the account, then modules should implement this hook.
 * New entities can be exported using gdpr_export_serialize_entity() and should
 * be saved to the $directory parameter using file_unmanaged_save_data(),
 * so that data is cleared after the files where zipped and downloaded.
 * If an existing file should be added to the export, than just return the path
 * to it.
 *
 *
 * @param object $account
 *   The user account for which the data should be exported.
 * @param string $directory
 *   The directory where new files should be saved to.
 *
 * @return bool|string
 *   A string with the path of the file to export, or FALSE on error.
 */
function hook_gdpr_export_user_export($account, $directory) {
  // Export the basic user account data.
  $meta = entity_metadata_wrapper('user', $account);
  $data = gdpr_export_serialize_entity($meta);
  return file_unmanaged_save_data($data, "$directory/user.xml");
}

/**
 * @} End of "addtogroup hooks".
 */
