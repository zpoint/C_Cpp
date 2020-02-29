package main

import "fmt"

func main() {
	var a []int
	a = append(a, 1) // 追加1个元素
	a = append(a, 1, 2, 3) // 追加多个元素, 手写解包方式
	a = append(a, []int{1,2,3}...) // 追加一个切片, 切片需要解包

	var numbers []int
	for i := 0; i < 10; i++ {
		numbers = append(numbers, i)
		fmt.Printf("len: %d  cap: %d pointer: %p\n", len(numbers), cap(numbers), numbers)
	}
}