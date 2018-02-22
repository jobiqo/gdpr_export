GDPR Export module
==================
This module allows a user to export all his data, so that your site is
compatible with the General Data Protection Regulation (Art. 15 & 20).

It comes with some usefull defaults, but if a site is using additional fields or
entities, which save user data, you'll have to implement additional code to
export it. See gdpr_export.api.php for more information on that.

## Setup

The module requires the [Entity API](https://www.drupal.org/project/entity)
module as well as the [Symfony 3.x Serializer](https://symfony.com/doc/3.4/serializer.html).

It is up to you how to add the Symfony Serializer as a dependency. You either
use either the [composer manager](https://www.drupal.org/project/composer_manager)
or just add a vendors directory to your repo and require composers autoload.php
file in a `hook_boot()` (this is the way we do it at jobiqo):
```php
/**
 * Implements hook_boot().
 */
function your_module_boot() {
  // include the composer autoload file.
  require_once DRUPAL_ROOT . '/sites/all/vendor/autoload.php';
}
```

The important thing is that the Symfony Serializer classes are available for
the GDPR Export module to use.
