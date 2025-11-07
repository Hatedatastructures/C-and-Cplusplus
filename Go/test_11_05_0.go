package main

import (
	"fmt"
	"math"
	"strings"
	"time"
	"unsafe"
)

// import "net/http"

//	func test() {
//		string_value := "string type"
//		fmt.Println("string :", string_value)
//		fmt.Printf("string type = %T \n", string_value)
//		// fmt.Println("我是一个函数" + "我会打印函数")
//	}
func returnVlaue() (string, int) {
	return "hello world", 100
}

func main() {
	// test()
	// var html_string string = `
	// <html>
	// 	<head>
	// 		<title>hello world</title>
	// 	</head>
	// 	<body>
	// 		<h1>hello world</h1>
	// 	</body>
	// </html>
	// `
	// fmt.Println(html_string)

	// fmt.Println("hello world")
	// var a string // 定义一个字符串变量a
	// // fmt.Scanln(&a)
	// fmt.Println("请输入一个字符串")
	// fmt.Scanf("%s", &a)
	// fmt.Println("你输入的字符串是：" + a)
	{
		var username, _ = returnVlaue() // 忽略第二个返回值
		var _, age = returnVlaue()      // 忽略第一个返回值
		fmt.Println(username)
		fmt.Println(age)
		t := time.Date(2023, time.Month(11), 5, 10, 0, 0, 0, time.Local)
		fmt.Println(t.Month())
		fmt.Println(t)
	}
	{
		const (
			n1 int = iota
			n2
			n3
		)
		fmt.Println(n1, n2, n3)
	}
	const name string = "hello world"
	fmt.Println(name)
	{
		var value int64 = 10000000000
		fmt.Printf("value = %d \n", value)
		fmt.Println(unsafe.Sizeof(value))
	}
	{
		a1 := int64(math.Round(float64(10000000000) / 1000000000))
		fmt.Println(a1)
		fmt.Println(unsafe.Sizeof(name))
	}
	{
		test_string := "hello Go"
		if test_string == "hello Go" {
			fmt.Println("hello world")
		} else {
			fmt.Println("hello go")
		}
		test_value := test_string
		fmt.Println(test_value)

	}
	{
		// 字符串长度
		string_test := "nihao"
		fmt.Println(len(string_test))
		// 拼接字符串
		str1 := "你好" //只有Printf支持格式化
		fmt.Printf("%s", fmt.Sprintf("%s %s", string_test, str1))
		// fmt.Scanf("%s", &str2)
		// fmt.Println(str2)
		// fmt.Println(strings.Count(str1, "你")) // 统计字符串中某个字符出现的次数
		{
			// 字符串切分
			str := "127157161521171251671"
			string_arr := strings.Split(str, "1")
			fmt.Print("源字符串：", str, "分割完成->")
			fmt.Print(string_arr)
			fmt.Print("Join 函数操作：\n")
			value := strings.Join(string_arr, "->")
			fmt.Print("Join 函数操作结果：", value, "\n")
		}
		{
			// 切片定义
			arr := []string{"C++", "Java", "Go", "Python", "JavaScript"}
			fmt.Println("切片打印->", arr)
			// 和strings包联动
			value := strings.Join(arr, "-")
			fmt.Println("Join 函数操作结果：", value, "value长度大小:", len(value))
		}
	}
}
