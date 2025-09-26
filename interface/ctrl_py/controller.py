import numpy as np

class Controller:
    def __init__(self):
        self.F = np.array([[0.399706, -0.724452, 0.067015, -0.060899],
                           [0.170077, -0.492234, 0.046645, -0.040267],
                           [14.424142, -69.553779, 5.724549, -6.109670],
                           [19.345462, -73.699035, 4.704962, -5.061552]], dtype=float)
        
        self.G = np.array([[0.802998, 0.074437],
                           [0.031031, 0.870239],
                           [5.945486, 4.245664],
                           [0.939717, 10.960342]], dtype=float)
        
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
