<?php

/**
 * A data formatter the formats generic field types.
 */
class GDPRExportGenericDataFormatter implements GDPRExportDataFormatter {
  /**
   * @inheritdoc
   */
  public function format($meta_data) {
    return $meta_data->value();
  }
}
