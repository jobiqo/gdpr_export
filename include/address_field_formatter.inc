<?php

/**
 * Implements a formatter for the addressfield.
 */
class GDPRExportAddressFieldFormatter implements GDPRExportDataFormatter {
  public function format($meta_data) {
    $address = $meta_data->raw();

    $render = addressfield_generate($address, ['address'], ['mode' => 'render']);
    $render = drupal_render($render);
    // Add line breaks at the end divs, otherwise line breaks in the markup
    // won't be preserved.
    $render = str_replace('</div>',  "</div>\n", $render);

    return drupal_html_to_text($render);
  }
}
