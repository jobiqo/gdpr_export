<?php

use Symfony\Component\Serializer\Normalizer\NormalizerInterface;

/**
 * Provides a generic entity normalization using the formatter system.
 */
abstract class GDPRExportEntityNormalizer implements NormalizerInterface {

  /**
   * Returns an array of properties that should be exported.
   *
   * @return array
   *   An array of properties that should be exported.
   */
  abstract protected function getProperties();

  /**
   * @inheritdoc
   */
  public function normalize($object, $format = null, array $context = array()) {
    $property_names = $this->getProperties();
    $normalization = [];

    foreach ($property_names as $name) {
      $formatter = gdpr_export_get_data_formatter($object->$name);
      if (gdpr_export_property_is_list($object->$name)) {
        $normalization[$name] = [];
        foreach ($object->$name as $item) {
          $normalization[$name][] = $formatter->format($item);
        }
      } else {
        $normalization[$name] = $formatter->format($object->$name);
      }
    }

    return $normalization;
  }
}
