<?php

/**
 * @file
 * Integration with Views.
 */

/**
 * Invoke hook_views_data().
 */
function views_phpexcel_views_data() {
  $data['views']['phpexcel'] = array(
    'title' => t('PHP Excel'),
    'help' => t('Exports items to excel file using PHPExcel library'),
    'area' => array(
      'help' => t('Expose form that allows to export data to excel files'),
      'handler' => 'views_phpexcel_handler_area',
      'path' => drupal_get_path('module', 'views_phpexcel') . '/plugins/viewa',
    ),
  );
  return $data;
}
