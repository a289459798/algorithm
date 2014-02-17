<?php
	/**
	 * 插入排序
	 * @auther zhangzy
	 * @date 2014-02-17
	 */

	 function insert_sort($arr = array())
	 {
		$len = count($arr);
		$j = 0;
		for($i = 1; $i < $len; $i++){
			$j = $i - 1;
			$t = $arr[$i];
			while($j >= 0 && $arr[$j] > $t){
				$arr[$j+1] = $arr[$j];
				$j--;
			}
			$arr[$j+1] = $t;
		}
		return $arr;
	 }

	 $arr = array(2, 1, 5, 4,  3, 7, 6);
	 print_r(insert_sort($arr));
