# 프로젝트 설명
## 목적
해당 코드는 quanser 의 큐브 서보 3 제품의 python 라이브러리의 입출력 데이터를 TCP/IP 를 이용하여 python, cpp, golang 으로 데이터 전송을 지원하는 코드입니다. 
## 사용 방향
TCP/IP로 구현된 데이터 전송 함수를 이용하여 python, cpp, golang 으로 데이터를 전송하여 해당 언어로 구현된 **암호화된 제어기**를 작동시켜보는 것이 사용 방향입니다.

# 프로젝트 구성
## python 폴더
python 폴더 내부에는 'tcp_protocol_server.py' 파일과 'tcp_protocol_client.py' 파일이 존재합니다.

1. tcp_protocol_server.py
  해당 파일은 python 에서 TCP를 이용하기 위한 서버를 구동하는 바인딩 코드와 INT, FLOAT, STR 을 전송할 수 있는 함수를 구성하는 클래스가 존재합니다. 해당 파일의 작동은 같은 폴더 내부의 'test_server.py' 파일을 잠조하실 수 있습니다.

2. tcp_protocol_cilent.py
  해당 파일을 python 에서 TCP 서버가 구동 중일때 해당 서버와 상호작용을 할 수 있도록 하는 함수 클래스가 존재합니다. 해당 파일의 작동은 같은 폴더 내부의 'test_client.py' 파일을 참조하실 수 있습니다.

## cpp 폴더
cpp 폴더 내부에는 'tcp_protocol_client.h' 파일이 존재합니다.

1. tcp_protocol_client.h
   해당 파일은 python 에서 TCP 서버가 구동 중일때 클라이언트로 상호작용을 위한 함수를 구현한 헤더 파일입니다. 해당 파일은 헤더 파일로 작동을 위한 cpp 코드의 예시는 같은 폴더의 'test_client.cpp'를 참조하실 수 있습니다.

## go 폴더
go 폴더 내부에는 'tcp_protocol_client.go' 파일이 존재합니다.

1. tcp_protocol_client.go
   해당 파일은 python 에서 TCP 서버가 구동 중일때 클라이언트로 상호작용을 위한 함수를 구현한 go 파일입니다. 해당 파일의 작동을 위한 go 코드의 예시는 같은 폴더의 'test_client.go'를 참조하실 수 있습니다. golang 특성상 'tcp_protocol_client.go' 파일과 작동을 위한 코드는 go.mod 가 있는 같을 폴더에서 작동해야 합니다.


