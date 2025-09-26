import numpy as np

class Controller:
    def __init__(self):
        self.F = np.array([[0.231949, -0.711891, 0.067015, -0.060899],
                           [0.184216, -0.569701, 0.046645, -0.040267],
                           [8.841868, -69.289390, 5.724549, -6.109670],
                           [19.807300, -76.488943, 4.704962, -5.061552]], dtype=float)
        
        self.G = np.array([[0.970755, 0.061877],
                           [0.016892, 0.947707],
                           [11.527760, 3.981276],
                           [0.477878, 13.750250]], dtype=float)
        
        self.H = np.array([[20.282828, -68.054405, 4.704626, -6.113621]], dtype=float)

        self.x = np.array([[0],
                           [0],
                           [0],
                           [0]], dtype=float)
        
        self.y = np.array([[0],
                           [0]], dtype=float)

    def ctrl(self, y0, y1):
        u = self.H @ self.x

        self.y[0, 0] = y0
        self.y[1, 0] = y1
        self.x = self.F @ self.x + self.G @ self.y

        return u[0, 0]
