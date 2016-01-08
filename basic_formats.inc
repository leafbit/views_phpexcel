<?php
/*
* Function trade_xls_formats()
*/
function phpexcel_xls_formats (){

	$style=new stdClass();

	$style->title = array(
			'font' => array(
				'bold' => true
			),
			'alignment'=>array(
				'horizontal'=>PHPExcel_Style_Alignment::HORIZONTAL_CENTER,
				'vertical'=>PHPExcel_Style_Alignment::VERTICAL_CENTER,
			),
		 'borders' => array(
				'allborders'=>array('style' => PHPExcel_Style_Border::BORDER_THIN),
			),
			'fill' => array(
				'type' => PHPExcel_Style_Fill::FILL_SOLID,
				'startcolor' => array(
						'argb' => 'CCCCCCCC',
					),
			),
	);

	$style->vertical_center=array(
		'alignment'=>array(
				'vertical'=>PHPExcel_Style_Alignment::VERTICAL_CENTER,
			),
	);
	$style->horizontal_center=array(
		'alignment'=>array(
				'horizontal'=>PHPExcel_Style_Alignment::HORIZONTAL_CENTER,
			),
  );
	$style->vertical_top=array(
		'alignment'=>array(
				'vertical'=>PHPExcel_Style_Alignment::VERTICAL_TOP,
			),
	);

	$style->total = array(
			'font' => array(
				'bold' => true
			),
			'alignment'=>array(
				'vertical'=>PHPExcel_Style_Alignment::VERTICAL_CENTER,
			),
			'borders' => array(
				'allborders'=>array('style' => PHPExcel_Style_Border::BORDER_THIN),
			),
	);

	//stype of product refused to supply line
	$style->refused = array(
			'fill' => array(
				'type' => PHPExcel_Style_Fill::FILL_SOLID,
				'startcolor' => array(
						'argb' => 'FFFFDDDD',
					),
			),
			'font'=>array(
				'color'=> array(
					'argb'=>'FFFF0000',
				),
			),
	);

	$style->no_offer = array(
			'fill' => array(
				'type' => PHPExcel_Style_Fill::FILL_SOLID,
				'startcolor' => array(
						'argb' => 'FFF0E68C',
					),
			),
			'font'=>array(
				'color'=> array(
					'argb'=>'FF8B0000',
				),
			),
	);

	$style->min_q=array(
			'fill' => array(
				'type' => PHPExcel_Style_Fill::FILL_SOLID,
				'startcolor' => array(
						'argb' => 'FFAFEEEE',
					),
			),
			'font'=>array(
				'color'=> array(
					'argb'=>'FF191970',
				),
			),
	);
	$style->borders = array(
			'alignment'=>array(
				'vertical'=>PHPExcel_Style_Alignment::VERTICAL_CENTER,
			),
			'borders' => array(
				'allborders'=>array('style' => PHPExcel_Style_Border::BORDER_THIN),
			),
	);

	return $style;
}
