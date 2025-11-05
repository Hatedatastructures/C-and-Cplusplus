package main

import "fmt"

// import "net/http"

func test() {
	string_value := "string type"
	fmt.Println("string :", string_value)
	fmt.Printf("string type = %T \n", string_value)
	// fmt.Println("我是一个函数" + "我会打印函数")
}

func main() {
	test()
	var html_string string = `
	<html>
		<head>
			<title>hello world</title>
		</head>
		<body>
			<h1>hello world</h1>
		</body>
	</html>
	`
	fmt.Println(html_string)

	// fmt.Println("hello world")
	// var a string // 定义一个字符串变量a
	// // fmt.Scanln(&a)
	// fmt.Println("请输入一个字符串")
	// fmt.Scanf("%s", &a)
	// fmt.Println("你输入的字符串是：" + a)
}
