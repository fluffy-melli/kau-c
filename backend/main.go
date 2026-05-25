package main

import (
	"backend/protocol"
	"net"
)

func main() {
	addr, err := net.ResolveUDPAddr("udp", ":12700")
	if err != nil {
		panic(err)
	}

	conn, err := net.ListenUDP("udp", addr)
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	service := protocol.NewService()

	buf := make([]byte, 1024)

	for {
		n, addr, err := conn.ReadFromUDP(buf)
		if err != nil {
			panic(err)
		}

		response := service.Handle(buf[:n])
		if response == nil {
			continue
		}

		_, err = conn.WriteToUDP(response, addr)
		if err != nil {
			panic(err)
		}
	}
}
