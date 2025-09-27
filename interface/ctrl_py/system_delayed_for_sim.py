# Need to move from the venv or operational reference position to the Python folder at the bottom
import sys
sys.path.append(r"./python")

import tcp_protocol_client as tcc
import controller as ctr

import time
import os

HOST = 'localhost'
PORT = 9999

def main():
    ts = 20
    state = 1
    u = 0.0
    time_stack = 0
    EoL = True
    controller_obj = ctr.Controller_delayed()

    with tcc.tcp_client(HOST, PORT) as tccp:
        while EoL:
            if state == 1:
                _, flag = tccp.recv()

                if flag == "R":
                    tccp.send("g_y")

                    _, y0 = tccp.recv()
                    _, y1 = tccp.recv()
                    u = controller_obj.ctrl(y0, y1)

                    print(f"y0: {y0} | y1: {y1}")

                    state = 2
                elif flag == "E":
                    EoL = False
                else:
                    os.Exit(-1)
            elif state == 2:
                while True:
                    _, flag = tccp.recv()
                    
                    if flag == "R":
                        time_stack = time_stack + 1
                        
                        if time_stack < ts:
                            tccp.send("w")
                        else:
                            tccp.send("s_u")
                            tccp.send(u)
                            print(f"sample_period: {time_stack}ms")
                            time_stack = 0
                            state = 1
                            break
                    elif flag == "E":
                        EoL = False
                        break
                    else:
                        os.Exit(-1)
            else:
                os.Exit(-1)

if __name__ == "__main__":
    main()
