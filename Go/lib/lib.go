package lib

import (
	"fmt"
)

func Lib() {
	fmt.Println("当前是lib包的Lib函数")

}
func init() {
	fmt.Println("当前是lib包的init函数")
}
