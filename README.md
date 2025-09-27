# 코드 설명


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

example 폴더는 제어시스템의 시뮬레이션이다. 내부 파일은 sim_cpp, sim_go, sim_py로 되어있으며 각각 서버는 python으로 클라이언트가 cpp, go, python으로 구성되어 있는것을 확인할 수 있다. 해당 폴더에서 실행은 위 순서와 마찬가지로 이루어지고 잘 돌아갔는지 확인하는 방법은 "plant output.png" 파일이 정상적으로 생성이 되었으며, 내부 그림이 0으로 수렴하는 형태임을 확인한다.
