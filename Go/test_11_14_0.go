package main

// // 大写公开，小写私有
// import (
// 	structls "c_and_cplusplus/Go/lib/struct"
// 	"fmt"
// )

// type Man struct {
// 	structls.Person
// 	Level  int
// 	Gender string
// }

// func (Thisman *Man) Print() {
// 	fmt.Println("Man Print")
// 	fmt.Println("Name:", Thisman.Name, "Age:", Thisman.Age, "Gender:", Thisman.Gender, "Level:", Thisman.Level)
// }

// func (Thisman *Man) Set(name string, age int, gender string, level int) Man {
// 	Thisman.Name = name
// 	Thisman.Age = age
// 	Thisman.Gender = gender
// 	Thisman.Level = level

// 	return *Thisman
// }

// type Cat struct {
// 	Namestring        string
// 	Getcategorystring string
// 	Sleepstring       string
// }

// func (c *Cat) Getcategory() string {
// 	return c.Getcategorystring
// }

// func (c *Cat) Sleep() {
// 	fmt.Println(c.Namestring, "is sleeping")
// }

// func (c *Cat) Print() {
// 	fmt.Println("Cat Print")
// 	fmt.Println("Name:", c.Namestring, "Getcategory:", c.Getcategorystring, "Sleep:", c.Sleepstring)
// }

// // 万能类型
// func Prints(a any) {
// 	value, ok := a.(string)
// 	if ok {
// 		fmt.Println(value)
// 	} else {
// 		fmt.Println("not string")
// 	}
// }

// func main() {

// 	// {
// 	// 	var test1 Man
// 	// 	test1.Name = "wang"
// 	// 	test1.Age = 18
// 	// 	test1.Gender = "male"
// 	// 	test1.Level = 10
// 	// 	test1.Person.Print()
// 	// 	test1.Print()
// 	// 	fmt.Println(test1)
// 	// 	fmt.Println(test1.Set("li", 20, "female", 20))
// 	// 	fmt.Println(test1)
// 	// }
// 	{
// 		var test Cat
// 		test.Namestring = "mimi"
// 		test.Getcategorystring = "cat"
// 		test.Sleepstring = "sleeping"
// 		structls.Print(&test)
// 		fmt.Println("-------------")
// 		fmt.Println(test.Getcategory())
// 		test.Sleep()
// 	}
// 	{
// 		// 接口类型可以存储实现了该接口的任何类型的变量
// 		var test structls.Animal = &Cat{Namestring: "mimi", Getcategorystring: "cat", Sleepstring: "sleeping"}
// 		structls.Print(test)
// 		fmt.Println("-------------")
// 		fmt.Println(structls.Getcategory(test))
// 		test.Sleep()
// 	}
// 	{
// 		Prints("hello")
// 	}
// }
