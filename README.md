Python 서버와 Python, Golang, Cpp 의 클라이언트를 구동하는 간단한 코드.

python 폴더 내부에 tcp_protocol_server.py 는 python 에서 서버를 구동하는 코드, 같은 폴더 내부에 tcp_protocol_client.py 는 python 에서 클라이언트를 구동하는 코드이다.
go 폴더 내부에 tcp_protocol_client.go 는 go 에서 클라이언트를 구동하는 코드, cpp 폴더 내부에 tcp_protocol_client.h 는 cpp 에서 클라이언트를 구동하는 코드이다.


python, go, cpp 폴더 내부에 test_client 를 돌려보는 방법

1. python 폴더에서 "python3 -m venv venv" 명령어를 통하여 가상환경을 구축한다.
2. 같은 폴더에서 "source ./venv/bin/activate"를 이용하여 가상환경을 실행한다.
3. "pip install numpy" 와 "pip install matplotlib"을 이용하여 두가지 라이브러리를 설치한다.
4. "python ./test_server.py"를 이용하여 파이썬 서버를 구동한다.
5. 구동하고하 하는 클라이언트를 다음과 같이 구동한다.
	python : "python ./test_client.py"
	go	   : "go run test_client.go"
	cpp	   : "./test_client"
6. 서버와 클라이언트에서 데이터 전달이 이루어지고 커맨드창에 전달된 데이터가 입력되는 것을 확인한다.
