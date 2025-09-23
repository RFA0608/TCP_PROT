import tcp_protocol_server as tcs

HOST = 'localhost'
PORT = 9999

with tcs.tcp_server(HOST, PORT) as tcsp:
    tcsp.set_metric(True, 1000)
    tcsp.set_sampleconst(False, 10)
    for i in range(10):
        # tcsp.send("python 인덱스:"+str(i))
        tcsp.send(i)
        k, l = tcsp.recv()
        print(l)

    tcsp.diagnostic_metric()