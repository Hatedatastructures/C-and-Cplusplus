// package main

// import (
// 	"fmt"
// 	"time"
// )

// func test_time() {
// 	time_object := time.Now()
// 	time_string := time_object.Format("2006-01-02 15:04:05")
// 	fmt.Println(time_object)
// 	fmt.Println(time_string)
// }

// // 创建一个定时器任务
// func test_time2() {
// 	// ticker := time.NewTicker(time.Second)
// 	// n := 30
// 	// for i := range ticker.C {
// 	// 	fmt.Println(i.Format("2006-01-02 15:04:05")) // 每秒打印一次当前时间
// 	// 	n--
// 	// 	if n == 0 {
// 	// 		break
// 	// 	}
// 	// }
// 	start := time.Now()
// 	time.Sleep(time.Second * 2)
// 	end := time.Now()
// 	fmt.Println("2秒后时间:", end.Sub(start).Nanoseconds())
// }
// func main() {

//		test_time()
//		test_time2()
//	}
package main

import (
	"c_and_cplusplus/Go/lib"
	"c_and_cplusplus/Go/lib/stringt"
	"c_and_cplusplus/Go/lib/vector"
)

//	func test_func(val int) {
//		fmt.Println("test func", val)
//		// time.Sleep(time.Millisecond * 100)
//		// fmt.Println("test func", val)
//	}
func main() {

	// for i := range 1000000 {
	// 	go test_func(i)
	// }
	// time.Sleep(time.Second * 10)
	lib.Lib()
	stringt.Stringcount()
	vector.Vector()

}
