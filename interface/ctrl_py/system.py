import sys
sys.path.append(r"../../python")

import tcp_protocol_client as tcc
import controller as ctr

import time
import os

HOST = 'localhost'
PORT = 9999

def main():
    controller_obj = ctr.Controller()

    with tcc.tcp_client(HOST, PORT) as tccp:
        while True:
            _, flag = tccp.recv()

            if flag == "R":
                stc = time.perf_counter_ns() / 1000000

                _, y0 = tccp.recv()
                _, y1 = tccp.recv()
                u = controller_obj.ctrl(y0, y1)
                print(f"y0: {y0} | y1: {y1}")

                edc = time.perf_counter_ns() / 1000000
                print(f"sample_period: {edc-stc}ms")
                
                tccp.send(u)
            elif flag == "E":
                break
            else:
                os.Exit(-1)

if __name__ == "__main__":
    main()
