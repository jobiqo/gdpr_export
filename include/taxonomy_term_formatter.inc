<?php

/**
 * A basic taxonomy term formatter, which simply outputs the referenced terms
 * name.
 */
class GDPRExportTaxonomyTermFormatter implements GDPRExportDataFormatter {
  /**
   * @inheritdoc
   */
  public function format($meta_data) {
    return $meta_data->name->value();
  }
}
