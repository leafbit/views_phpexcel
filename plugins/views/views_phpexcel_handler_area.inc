<?php
/**
 * @file
 * Contains class to expend view to export its fields to excel file.
 */

/**
 * Plugin that extend view to export content to excel file.
 **/
class views_phpexcel_handler_area extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();
    $options['views_phpexcel_fields'] = array('default' => array());
    $options['file_name'] = "Date(Ymd)_[view]_[display]_!0";
    $options['on_image_set_height'] = 150;
    $options['format'] = array('totals' => '', 'header' => '', 'body' =>  '//<' . "?\n\$format = array(
  // Alignment
  'alignment' => array(
    'vertical' => PHPExcel_Style_Alignment::VERTICAL_CENTER,
    'wrap' => true
  ),
  'borders' => array(
    'allborders' => array(
      'style' => PHPExcel_Style_Border::BORDER_THIN,
    ),
  ),
);");
    $options['start_at_row'] = 1;
    $options['alter_code'] = array(
      'page_process' => '',
      'file_build' => '',
    );
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $key = 'views_phpexcel_fields';

    $form[$key] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );

    $path = drupal_get_path('module', 'views_phpexcel');


    $v = $this->options[$key];
    $fields = $this->view->display_handler->get_field_labels();
    foreach ($fields as $field_key => $field_label) {

      $vals = isset($v[$field_key]) ? $v[$field_key] : array(
        'export' => FALSE,
        //'rewrite_label' => FALSE,
        //'new_label' => '',
        'formula' => '',
        'width' => 30,
        'format' => '',
      );

      $form[$key][$field_key] = array(
        '#type' => 'fieldset',
        '#title' => $field_label,
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => !$vals['export'],
      );
      $form[$key][$field_key]['export'] = array(
        '#type' => 'checkbox',
        '#title' => t('Export this field'),
        '#default_value' => $vals['export'],
      );
      $form[$key][$field_key]['width'] = array(
        '#type' => 'textfield',
        '#title' => t('Col width'),
        '#default_value' => $vals['width'],
        '#description' => t('Column width in exported file'),
      );
      $form[$key][$field_key]['formula'] = array(
        '#type' => 'textfield',
        '#title' => t('Formula'),
        '#default_value' => $vals['formula'],
        '#description' => t('Leave empty if only the vlaue of this field shall be exported.'
        . ' Instead of excel form cell names use [field_name] style.'),
      );

      $form[$key][$field_key]['format'] = array(
        '#type' => 'textarea',
        '#title' => t('Format'),
        '#default_value' => $vals['format'],
        '#description' => t('Set $format variable to a PHPExcel format style array to use for the table cells for this column in exported file.'),
      );

      $form[$key][$field_key]['total'] = array(
        '#type' => 'select',
        '#title' => t('Totals'),
        '#options' => array(
          'none' => t('-- No totals --'),
          'sum' => t('Sum'),
          'average' => t('Average'),
        ),
        '#default_value' => $vals['total'],
      );
    }

    $form['format_help'] = array(
      '#type' => 'fieldset',
      '#title' => t('Cells Format Help'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'help' => array (
        '#markup' => file_get_contents($path . '/format_help.html'),
      ),
    );

    $form['fields_info'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available fields'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'data' => array(
        '#markup' => '[' . implode(']<br>[', array_keys($fields)) . ']',
      ),
    );

    $form['file_name'] = array(
      '#title' => t('File Name Pattern'),
      '#type' => 'textfield',
      '#size' => 12,
      '#required' => TRUE,
      '#default_value' => $this->options['file_name'],
      '#description' => t('Definition of way for file name to be built. use %0..%x for path arguments and !0...!x for view arguments. Date() processes date formats. Keys [view], [display], [uid], [username] inject view and user relevant keys.'),
    );

    $form['on_image_set_height'] = array(
      '#type' => 'textfield',
      '#title' => t('On image set height'),
      '#size' => 5,
      '#default_value' => $this->options['on_image_set_height'],
      '#required' => FALSE,
      '#description' => t('If row contains image set the height to given value'),
    );

    $form['start_at_row'] = array(
      '#type' => 'textfield',
      '#title' => t('Start ar row'),
      '#size' => 5,
      '#default_value' => $this->options['start_at_row'] ? $this->options['start_at_row'] : 1 ,
      '#required' => FALSE,
      '#description' => t('Number of row to start to print the table in the exported file. Note that first row is 1.'),
    );

    $form['format'] = array(
      '#type' => 'fieldset',
      '#title' => t('Format'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['format']['header'] = array(
      '#type' => 'textarea',
      '#title' => t('Table header format'),
      '#default_value' => $this->options['format']['header'],
      '#description' => t('Set $format variable to a PHPExcel format style array to use for the table header in exported file.'),
    );

    $form['format']['header_template'] = array(
      '#type' => 'fieldset',
      '#title' => t('Template'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'data' => array(
        '#markup' => '<pre>' . htmlentities(file_get_contents($path . '/tpl/format_header.inc')) . '</pre>',
      ),
    );

    $form['format']['body'] = array(
      '#type' => 'textarea',
      '#title' => t('Table body format'),
      '#default_value' => $this->options['format']['body'],
      '#description' => t('Set $format variable to a PHPExcel format style array to use for the table body in exported file.'),
    );
    $form['format']['body_template'] = array(
      '#type' => 'fieldset',
      '#title' => t('Template'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'data' => array(
        '#markup' => '<pre>' . htmlentities(file_get_contents($path . '/tpl/format_body.inc')) . '</pre>',
      ),
    );

    $form['format']['totals'] = array(
      '#type' => 'textarea',
      '#title' => t('Total totals format'),
      '#default_value' => $this->options['format']['totals'],
      '#description' => t('Set $fromat variable to a PHPExcel format style array to use for the table cells in exported file that show totals'),
    );
    $form['format']['totals_template'] = array(
      '#type' => 'fieldset',
      '#title' => t('Template'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'data' => array(
        '#markup' => '<pre>' . htmlentities(file_get_contents($path . '/tpl/format_totals.inc')) . '</pre>',
      ),
    );

    $templates = file($path . '/tpl/templates.list');
    $content = '';
    foreach ($templates as $fn) {
      $fn = trim($fn);
      $fln = $path . '/tpl/' . $fn . '.inc';
      if (file_exists($fln)) {
        $content .= '<pre>' . htmlentities(file_get_contents($fln)) . '</pre>';
      }
    }
    if ($content) {
      $form['format']['more_template'] = array(
        '#type' => 'fieldset',
        '#title' => t('More Templates'),
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        'data' => array(
          '#markup' => $content,
        ),
      );
    }

    $form['alter_code'] = array(
      '#type' => 'fieldset',
      '#title' => t('PHP Alter Code'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['alter_code']['page_process'] = array(
      '#type' => 'textarea',
      '#title' => t('PHP Code for Page Process'),
      '#default_value' => $this->options['alter_code']['page_process'],
      '#description' => t('Code to run and alter one batch operation of gathering data for the final file from each page of the view. During this process $view, $pagenr, $nr (current row number), $params variables are available.'),
    );

    $form['alter_code']['file_build'] = array(
      '#type' => 'textarea',
      '#title' => t('PHP Code for File Build'),
      '#default_value' => $this->options['alter_code']['page_build'],
      '#description' => t('Alters the run of the code that builds excel file. Variables $view, $results, $params, $objPHPExcel and $objSheet are available.'),
    );
  }

  function render($empty = FALSE) {
    if (!$empty) {
      $form = drupal_get_form('views_phpexcel_form_export', $this);
      return drupal_render($form);
    }
  }
}
