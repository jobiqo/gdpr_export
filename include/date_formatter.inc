<?php

/**
 * A data formatter for date columns.
 */
class GDPRExportDateFormatter implements GDPRExportDataFormatter {
  // Use the default parameter of format_date as the default date format.
  private $format = 'medium';

  public function __construct($format = null) {
    if (!empty($format)) {
      $this->format = $format;
    }
  }

  public function format($meta_data) {
    return format_date($meta_data->value(), $this->format);
  }
}
