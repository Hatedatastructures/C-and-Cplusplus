package main

import (
	"fmt"
	"reflect"
)

// go 中的反射

type Person struct {
	Name string `info:"name" doc:"姓名"`
	Sex  string `info:"sex"` // Tag 标签 方便解析
}

func TagFind(value any) {
	t := reflect.TypeOf(value)
	fmt.Println("当前是函数传进来的类型：", t) // 当前是函数传进来的类型： main.Person

	// fmt.Println("当前是函数传进来的类型的元素：", t.Elem()) // 当前是函数传进来的类型的元素： main.Person
	fmt.Println("当前是函数传进来的类型的元素：", t.Elem().Field(0).Tag.Get("info"))
}

func main() {
	// var str string = "hello world"
	// var anytest any = &str
	// fmt.Println(reflect.TypeOf(str), reflect.ValueOf(str))
	// fmt.Println(reflect.TypeOf(anytest), reflect.ValueOf(anytest.(*string)))
	// fmt.Println(reflect.TypeOf(anytest), reflect.ValueOf(anytest).Elem())
	// // json.Marshal(anytest)
	// time.Date(2023, time.Month(11), 14, 10, 0, 0, 0, time.UTC)
	var Test Person
	TagFind(&Test)
}
