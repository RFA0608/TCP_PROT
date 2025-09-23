package main

import "fmt"

const host = "localhost"
const port = "9999"

func main() {
	conn := InitTCP(host, port)

	for i := 0; i < 10; i++ {
		_, data := Recv(conn)
		fmt.Println(data)
		Send(conn, "go 인덱스:"+fmt.Sprintf("%d", i))
	}

	ExitTCP(conn)
}
