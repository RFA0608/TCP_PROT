package main

import (
	"gonum.org/v1/gonum/mat"
)

const host = "localhost"
const port = "9999"

func main() {
	F := mat.NewDense(4, 4, []float64{
		-0.536627792820633, -0.0616616464699388, 0.00866858350768544, -0.00463375401067145,
		0.00500554483113348, -0.601557630748387, 0.00362678875646218, 0.000421412722115318,
		-114.091783546364, -22.4291804036030, 2.46787179162606, -1.85343312684920,
		4.67284205745743, -140.995944698502, 1.45149348677951, -0.831327144074360,
	})

	G := mat.NewDense(4, 2, []float64{
		1.55270125254271, 0.0119013552498322,
		0.0108847973351295, 1.55379044548734,
		120.523088182329, 2.51929505177743,
		1.68670345396683, 121.878828984762,
	})

	H := mat.NewDense(1, 4, []float64{
		25.8509647864634, -83.0321122531947, 5.90039644952970, -7.45747542479626,
	})

	x := mat.NewDense(4, 1, []float64{
		0,
		0,
		0,
		0,
	})

	temp_x := mat.NewDense(4, 1, []float64{
		0,
		0,
		0,
		0,
	})

	u := mat.NewDense(1, 1, []float64{
		0,
	})

	y := mat.NewDense(2, 1, []float64{
		0,
		0,
	})

	conn := InitTCP(host, port)

	max_iter := 300

	for i := 0; i < max_iter; i++ {
		u.Mul(H, x)

		Send(conn, u.At(0, 0))

		_, y0 := Recv(conn)
		_, y1 := Recv(conn)

		y0_float, _ := y0.(float64)
		y1_float, _ := y1.(float64)

		y.Set(0, 0, y0_float)
		y.Set(1, 0, y1_float)

		x.Mul(F, x)
		temp_x.Mul(G, y)
		x.Add(x, temp_x)
	}

	ExitTCP(conn)
}
