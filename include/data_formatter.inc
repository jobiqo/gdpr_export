<?php

/**
 * Interface GDPRExportDataFormatter
 */
interface GDPRExportDataFormatter {

  /**
   * Format the given meta data.
   *
   * @param \EntityMetadataWrapper $meta_data
   *   The data that should be formatted.
   *
   * @return string|array
   *   a string or an array of strings.
   */
  public function format($meta_data);
}
