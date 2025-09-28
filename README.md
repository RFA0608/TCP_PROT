# 프로젝트 개발 단계
1. ✅️[100%] TCP 통신을 위한 서버와 클라이언트 코드 구현
2. ✅️[100%] quanser qube servo 3 개별 구동
3. ✅️[80%] TCP 통신과 servo 3 연결 후 제어기 동작 확인

➡️[이유] 제어기에서 발생하는 딜레이를 고려한 설계 필요, python 이 아닌 cpp, golang 으로 구성된 제어기 코드 설계 필요

4. ☑️[0%] 스윙업을 통한 초기 진자 자동으로 스탠딩업
5. ☑️[10%] 암호화된 제어기 작동

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
## 실행 순서
### 공통
해당 코드는 대부분 WSL 위에서 작동을 보장하지만, python 의 경우 윈도우에서도 작동됩니다. 
1. 윈도우에서 가상환경을 쓰지 않을 경우
  TCP 통신이 필요한 코드들에 파일 import를 위하여
  ```
  sys.path.append(r"./python")
  ```
  이 삽입되어 있는데 이것을 
  ```
  sys.path.append(r"../../python")
  ```
  으로 변경해야합니다.
  
2. WSL에서 가상환경을 써야하는 경우
해당 깃허브 파일을 다운받아 가장 상단(아무 폴더도 들어가지 않은 cpp, example, go ... 등의 파일이 보이는 위치)에서 다음의 명령어를 이용하여 파이썬 가상환경을 실행합니다.
```bash
python3 -m venv venv
source ./venv/bin/activate
pip install numpy
pip install matplotlib
```

---

➤ 퀀서 장비를 돌리는 경우
TCP 서버의 주소를 모든 아이피를 허용할 수 있게 "0.0.0.0" 로 설정하고 포트 넘버 9999 를 윈도우 상에서 방화벽 해지를 해야합니다. 방화벽 해지 후 WSL의 커맨드창에 다음 명령어를 입력합니다.
```bash
sudo apt install net-tools
ifconfig
```

WSL 의 설정을 변경하지 않았을 경우 네트워킹 모드가 Nat 으로 구성되어 있습니다. 따라서 TCP 클라이언트는 위 명령어를 쳐서 나오는 커맨드 결과 중 eth0 의 inet 주소를 그대로 이용합니다. 포트는 서버와 같은 것을 이용하시면 됩니다.

➤ 시뮬레이션만 하는 경우
시뮬레이션만 하는 경우 해당 코드를 그대로 작동하실 수 있습니다.

---
    
⇨이후 작동 인터프리터를 (venv)가 붙은 것을 이용하시면 됩니다.

### simulation
폴더 "interface/plant_py" 에서 ?_sim_.py 로 구성된 파일을 실행하고, 폴더 "interface/ctrl_py" 에서 위의 설명에 대응되는 system_?.py 를 실행하면 시뮬레이션 결과가 "interface/plnat_py" 폴더에 png 파일로 생성됩니다.
### quanser test
퀀서 장비를 키고 "interface/plnat_py" 에서 plant_?.py 로 구성된 파일을 실행하고, 폴더 "interfasce/ctrl_py" 에서 위에 설명에 대응되는 system_?.py 를 실행하고 퀀서 장비의 진자를 위로 올려서 기다려주면 작동이 됩니다.

## quanser 실행 영상
1. 지연 없는 제어기
  [퀀서 테스트 non delayed controller](https://youtu.be/6EzNQtzz20k)
2. 지연 있는 제어기
  [퀀서 테스트 delayed controller](https://youtu.be/_Q-o9VO9SZw)
