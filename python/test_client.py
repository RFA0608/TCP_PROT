import tcp_protocol_client as tcc

HOST = 'localhost'
PORT = 9999

with tcc.tcp_client(HOST, PORT) as tccp:
    for i in range(1000):
        k, l = tccp.recv()
        print(l)
        # k, l = tccp.recv()
        # print(l)
        tccp.send("ddddddddddddddddddddddddddddddddddddddddddddddd")
    