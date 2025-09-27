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

## matlab 폴더(내부 quanser simulation 아래)
해당 폴더는 quanser 장비를 구동하기 위한 원점에서 선형화된 연속시간 상태공간 모델 파일인 'plant_continous_model.mat' 이 존재하고, 매트랩 코드 파일인 'system_load.m' 을 통하여 이산시간 제어기 설계를 진행할 수 있습니다. 또한 'system_sim' 이름의 시뮬링크 파일을 이용하여 가시적으로 모델의 출력을 생성하고 확인 가능합니다.

## interface 폴더
### plant_py
해당 폴더는 퀀서 장비를 이용할 수 있는 python 코드가 구성되어 있으며 다음과 같은 파일 이름과 작동 방식을 갖습니다.

1. plant_quanser.py
   가장 기본적인 퀀서 장비를 이용할 수 있는 코드입니다. 아래 설명된 "ctrl_py" 폴더 내부의 'system.py' 와 한 쌍이되어 'plant_quanser.py'를 구동하고 'system.py'를 구동할 수 있습니다.
      
3. plant_quanser_delayed.py
   암호화된 제어기는 제어기의 연산에서 발생하는 지연을 포함한은 작동을 위한 코드입니다. 아래 설명된 "ctrl_py" 폴더 내부의 'system_delayed.py' 와 한 쌍이되어 구동됩니다.
   
5. plant_sim_original.py
   퀀서 장비를 이용하기 전에 "ctrl_py" 폴더의 'system.py' 의 작동과 통신이 잘 되는지 확인하기 위한 시뮬레이션 코드입니다. 암호화된 제어기를 구동하기 위한 지연을 생각하지 않는 작동을 확인할 수 있고, 시뮬레이션이 끝나면 작동 데이터를 'plant output as sim.png' 로 저장합니다.
   
7. plant_sim_delayed.py
   퀀서 장비를 이용하기 전에 "ctrl_py" 폴더의 'system_delayed_for_sim.py' 의 작동과 통신이 잘 되는지 확인하기 위한 시뮬레이션 코드입니다. 암호화된 제어기를 구동하기 위한 지연을 생각하는 작동을 확인할 수 있고, 시뮬레이션이 끝나면 작동 데이터를 'plant output with delayed control input as sim.png' 로 저장합니다.
   
### ctrl_py
해당 폴더는 퀀서 장비의 제어기와 입력과 출력을 전달 하고/받는 python 코드가 구현되어 있습니다.

1. controller.py
   해당 파일은 작동의 위한 관측기 기반 설계의 제어기의 상태공간 모델을 포함합니다. 두 가지의 클래스가 구현되어 있는데, 한 가지는 제어기의 연산 지연이 없는 Controller 클래스와 지연이 존재하여 상태변수 계산 이후에 제어 입력을 생성하는 Controller_delayed 클래스가 포함됩니다. "matlab" 폴더의 매트랩 코드를 이용한 상태공간 모델을 시험하거나 혹은 다른 제어기를 생성하려면 해당 파일에 생성을 할 수 있습니다.

2. system.py
   "plant_py" 폴더의 'plant_quanser.py'와 상호작용을 위한 코드입니다. 'controller.py' 의 Controller 클래스를 이용하며 제어기의 지연이 없는 퀀서 장비의 시뮬레이션을 진행할 수 있습니다.

3. system_delay.py
   "plant_py" 폴더의 'plant_quanser_delayed.py' 와 상호작용을 위한 코드입니다. 'controller.py' 의 Controller_delayed 클래스를 이용합니다.

4. system_delayed_for_sim.py
   "plant_py" 의 'plant_sim_origianl.py' 는 'system.py' 와 같이 돌릴 수 있지만 지연이 있는 제어기의 경우 샘플링 시간 만큼 지연을 포함하고 있어 시뮬레이션을 위한 특수 코드가 필요합니다. 'system_delayed_for_sim.py' 가 해당 역할을 합니다.

# 실행해보기
