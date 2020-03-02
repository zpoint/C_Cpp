package main

import "log"

// 一个服务需要满足能够开启和写日志的功能
type Service interface {
Start()  // 开启服务
Log(string)  // 日志输出
}
// 日志器
type Logger struct {
}
// 实现Service的Log()方法
func (g *Logger) Log(l string) {
	log.Print(l)
}
// 游戏服务
type GameService struct {
	Logger  // 嵌入日志器
}
// 实现Service的Start()方法
func (g *GameService) Start() {
}

func main() {
	var s Service = new(GameService)
	s.Start()
	s.Log("hello")
}
