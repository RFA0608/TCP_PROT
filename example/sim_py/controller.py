# Need to move from the venv or operational reference position to the Python folder at the bottom
import sys
sys.path.append(r"./py")
sys.path.append(r"../../py")

import tcp_protocol_client as tcc
HOST = 'localhost'
PORT = 9999

import numpy as np

F = np.array([[-0.536627792820633,	-0.0616616464699388,	0.00866858350768544,	-0.00463375401067145],
              [0.00500554483113348,	-0.601557630748387,	0.00362678875646218,	0.000421412722115318],
              [-114.091783546364,	-22.4291804036030,	2.46787179162606,	-1.85343312684920],
              [4.67284205745743,	-140.995944698502,	1.45149348677951,	-0.831327144074360]], dtype=float)

G = np.array([[1.55270125254271,	0.0119013552498322],
              [0.0108847973351295,	1.55379044548734],
              [120.523088182329,	2.51929505177743],
              [1.68670345396683,	121.878828984762]], dtype=float)

H = np.array([[25.8509647864634,	-83.0321122531947,	5.90039644952970,	-7.45747542479626]], dtype=float)

x = np.array([[0],
              [0],
              [0],
              [0]], dtype=float)

u = np.array([[0]], dtype=float)

y = np.array([[0],
              [0]], dtype=float)


max_iter = 300

with tcc.tcp_client(HOST, PORT) as tccp:
    for i in range(max_iter):
        u = H @ x

        tccp.send(u[0, 0])

        _, y0 = tccp.recv()
        _, y1 = tccp.recv()

        y[0, 0] = y0
        y[1, 0] = y1
        
        x = F @ x + G @ y
