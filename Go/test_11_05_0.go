package main

import (
	"fmt"
	"time"
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
}
