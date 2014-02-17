<?php
/**
 * 分治法
 * @auther zhangzy
 * @date 2014-02-17
 */

 //1、分割
 function merge_sort(&$arr, $s, $e)
 {
		if($s < $e){
			$m = floor(($s + $e) / 2);
			merge_sort($arr, $s, $m);
			merge_sort($arr, $m+1, $e);
			merge($arr, $s, $m, $e);
		}
 }
 //2、解决
 function merge(&$arr, $s, $m, $e)
 {
	$lArr = array();
	$rArr = array();
	for($i = 1; $i <= $m-$s+1; $i++){
		$lArr[$i] = $arr[$s+$i-1];
	}	
	for($i = 1; $i <= $e-$m; $i++){
		$rArr[$i] = $arr[$m+$i];
	}
	$i = 1;
	$j = 1;
	for($k = $s; $k <= $e; $k++){
		if(!isset($rArr[$j]) || (isset($lArr[$i]) && $lArr[$i] < $rArr[$j])){
			$arr[$k] = $lArr[$i];
			$i++;
		}else{
			$arr[$k] = $rArr[$j];
			$j++;
		}
	}
 }
 $arr = array(2, 5, 3, 7, 1, 9, 8, 4);
 merge_sort($arr, 0, 7);
 print_r($arr);
