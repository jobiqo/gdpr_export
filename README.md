GDPR Export module
==================
This module allows a user to export all his data, so that your site is
compatible with the General Data Protection Regulation (Art. 15 & 20).

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

## Usage

The module currently adds a button to the user edit page, which will initialize
the export and provide the data zipped for download. This might change in the
future if we decide that there's a better place.

## Extending

The module comes with several symfony serializers for different entities and
field types, so that the most common uses are supported. You might have to 
implement additional hooks or normalizers if your data depends on extra modules 
like profile2. It comes with normalizers for 
[field collections](https://www.drupal.org/project/field_collection), 
[date](https://www.drupal.org/project/date) and the 
[address field](https://www.drupal.org/project/addressfield) modules
See the gdpr_export.api.php file for more information on how to implement 
additional normalizers and exports.
