package main

import (
	"fmt"
	"math"
	"strconv"
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
			// 字符串拼接
			fmt.Print("Join 函数操作：\n")
			value := strings.Join(string_arr, "->")
			fmt.Print("Join 函数操作结果：", value, "\n")
			// 检查字符串包含  Contains 函数 调用
			test_str1 := "hello world"
			test_str2 := "hello"
			if strings.Contains(test_str1, test_str2) {
				fmt.Print("找到了，里面包含", test_str2, "字符串")
			} else {
				fmt.Print("没有找到，里面不包含", test_str2, "字符串")
			}
		}
		fmt.Println("")
		{
			// 切片定义
			arr := []string{"C++", "Java", "Go", "Python", "JavaScript"}
			fmt.Println("切片打印->", arr)
			// 和strings包联动
			value := strings.Join(arr, "-")
			fmt.Println("Join 函数操作结果：", value, "value长度大小:", len(value))
		}
		{
			string_t := "192.168.127.1"
			print(string_t) // go 内置函数
		}
		{
			fmt.Println("\n字符串转切片")
			chin_string := "你好"
			str := []rune(chin_string)
			fmt.Printf("%s", string(str))
		}
		{
			fmt.Println()
			value, _ := strconv.ParseInt("123", 10, 64) // 字符串转int
			test_value := 123
			fmt.Println("数字转换为字符串：", strconv.FormatInt(int64(test_value), 10))
			fmt.Println("value = ", value)
		}
		{
			number := 1234
			number++ // ++ 只能单独使用
			fmt.Println(number)
			// fmt.Println(number--) // 错误
		}
		{
			// 循环
			var sum uint64 = 0
			j := uint64(1000000000)
			for i := uint64(0); i <= j; i++ {
				sum += i
			}
			fmt.Println(j, "连续相加结果：", sum)
		}
		{
			name_test := "这是个中文字符串,hello,world"
			for k, value := range name_test {
				fmt.Printf("字符位置：%d,字符值：%c\n", k, value)
			}
		}
		{
			// switch
			switch string_test {
			case "nihao":
				fmt.Println("nihao world")
				fmt.Println("nihao world")
				fallthrough // case 穿透 能继续执行 并且只能穿透一层
			case "hello":
				fmt.Println("hello world")
			default:
				fmt.Println("default")
			}
		}
		{
			// 数组
			arrtest := [...]string{"hello", "world", "nihao", "hello"}
			for k, value := range arrtest {
				fmt.Printf("数组位置：%d,数组值：%s\n", k, value)
			}
			for i := 0; i < len(arrtest); i++ {
				fmt.Println(arrtest[i])
			}
		}
		{
			// 多维数组
			arrtest := [...][2]string{
				{"hello", "world"},
				{"nihao", "hello"},
			}
			// 按数组遍历
			fmt.Println("按数组遍历")
			for k, v := range arrtest {
				fmt.Println("二维数组位置：", k, "二维数组值：", v)
			}
			fmt.Println("按值遍历")
			for k, v := range arrtest {
				for i, value := range v {
					fmt.Printf("二维数组位置：%d,%d,二维数组值：%s\n", k, i, value)
				}
			}
		}
		{
			// 切片
			arrstring := []string{"hello", "world", "nihao", "hello"}
			test_arr_string := [5]string{"hello", "world", "nihao", "hello", "test"}
			fmt.Println("切片打印->", arrstring)
			// 从切片构建切片
			arr1_string := arrstring[1:3] // 从1开始到3结束 “world" ~ "nihao" 左闭右开
			fmt.Println("从切片构建的切片打印->", arr1_string)
			// 从数组构建切片
			arr2_string := test_arr_string[1:4] // 构建切片，同上
			fmt.Println("从数组构建切片打印：->", arr2_string)
		}
	}
	{
		{
			// 切片的追加
			var arr []string
			arr = append(arr, "nihao")
			fmt.Println("切片扩容：", arr)
			// 切片和切片的追加
			arr1 := []string{"hello", "world"}
			arr = append(arr, arr1...)
			fmt.Println("切片和切片的追加：", arr)
		}
		{
			// 切片创建和声明
			arr := make([]string, 8, 18)
			fmt.Println("切片创建和声明：", arr)
			// 切片修改
			fmt.Println("切片修改前：", arr)
			arr[0] = "nihao"
			arr[7] = "world"
			// arr = append(arr, "hello")
			fmt.Println("切片修改后：", arr)

		}
	}
}
