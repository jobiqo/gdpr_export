<?php

/**
 * A data formatter for date columns.
 */
class GDPRExportDateFormatter implements GDPRExportDataFormatter {
  // Use the default parameter of format_date as the default date format.
  private $type;
  private $format;

  /**
   * Constructs a new GDPRExportDateFormatter with the given type and formatter,
   * similar to format_date().
   *
   * @see \format_date()
   */
  public function __construct($type = 'medium', $format = '') {
    $this->type = $type;
    $this->format = $format;
  }

  public function format($meta_data) {
    return format_date($meta_data->value(), $this->type, $this->format);
  }
}
