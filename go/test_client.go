package main

import "fmt"

const host = "localhost"
const port = "9999"

func main() {
	conn := InitTCP(host, port)

	_, data := Recv(conn)
	fmt.Print("recv : ")
	fmt.Println(data)
	Send(conn, data.(int64))

	_, data = Recv(conn)
	fmt.Print("recv : ")
	fmt.Println(data)
	Send(conn, data.(float64))

	_, data = Recv(conn)
	fmt.Print("recv : ")
	fmt.Println(data)
	Send(conn, data.(string))

	ExitTCP(conn)
}
