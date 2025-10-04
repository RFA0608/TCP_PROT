#ifndef CTRL_H
#define CTRL_H

class controller
{
    private:
        const double F[4][4] = {{0.399706, -0.724452, 0.067015, -0.060899},
                                {0.170077, -0.492234, 0.046645, -0.040267},
                                {14.424142, -69.553779, 5.724549, -6.109670},
                                {19.345462, -73.699035, 4.704962, -5.061552}};

        const double G[4][2] = {{0.802998, 0.074437},
                                {0.031031, 0.870239},
                                {5.945486, 4.245664},
                                {0.939717, 10.960342}};

        const double H[1][4] = {{20.282828, -68.054405, 4.704626, -6.113621}};

        double x[4][1] = {{0},
                        {0},
                        {0},
                        {0}};
        
        double u[1][1] = {{0}};
        
        double y[2][1] = {{0},
                        {0}};

    public:
        controller(){};
        ~controller(){};

        void state_update(double y0, double y1)
        {
            double temp_x[4][1] = {{0}};

            // y save in class variable
            this->y[0][0] = y0;
            this->y[1][0] = y1;

            // state update
            for(int i = 0; i < 4; i++)
            {
                temp_x[i][0] = this->F[i][0] * this->x[0][0] + 
                                this->F[i][1] * this->x[1][0] +
                                this->F[i][2] * this->x[2][0] +
                                this->F[i][3] * this->x[3][0] +
                                this->G[i][0] * this->y[0][0] +
                                this->G[i][1] * this->y[1][0];
            }
            for(int i = 0; i < 4; i++)
            {
                this->x[i][0] = temp_x[i][0];
            }
        }

        double ctrl_input()
        {
            // control input generate
            for(int i = 0; i < 4; i++)
            {
                if(i == 0)
                {
                    this->u[0][0] = this->H[0][0] * this->x[0][0];
                }
                else
                {
                    this->u[0][0] += this->H[0][i] * this->x[i][0];
                }
            }

            return this->u[0][0];
        };
};


class controller_delayed
{
    private:
        const double F[4][4] = {{0.399706, -0.724452, 0.067015, -0.060899},
                                {0.170077, -0.492234, 0.046645, -0.040267},
                                {14.424142, -69.553779, 5.724549, -6.109670},
                                {19.345462, -73.699035, 4.704962, -5.061552}};

        const double G[4][2] = {{0.802998, 0.074437},
                                {0.031031, 0.870239},
                                {5.945486, 4.245664},
                                {0.939717, 10.960342}};

        const double H[1][4] = {{20.282828, -68.054405, 4.704626, -6.113621}};

        double x[4][1] = {{0},
                        {0},
                        {0},
                        {0}};
        
        double u[1][1] = {{0}};
        
        double y[2][1] = {{0},
                        {0}};

    public:
        controller_delayed(){};
        ~controller_delayed(){};

        double ctrl(double y0, double y1)
        {
            double temp_x[4][1] = {{0}};

            // y save in class variable
            this->y[0][0] = y0;
            this->y[1][0] = y1;

            // state update
            for(int i = 0; i < 4; i++)
            {
                temp_x[i][0] = this->F[i][0] * this->x[0][0] + 
                                this->F[i][1] * this->x[1][0] +
                                this->F[i][2] * this->x[2][0] +
                                this->F[i][3] * this->x[3][0] +
                                this->G[i][0] * this->y[0][0] +
                                this->G[i][1] * this->y[1][0];
            }
            for(int i = 0; i < 4; i++)
            {
                this->x[i][0] = temp_x[i][0];
            }

            // control input generate
            for(int i = 0; i < 4; i++)
            {
                if(i == 0)
                {
                    this->u[0][0] = this->H[0][0] * this->x[0][0];
                }
                else
                {
                    this->u[0][0] += this->H[0][i] * this->x[i][0];
                }
            }

            return this->u[0][0];
        };
};

#endif