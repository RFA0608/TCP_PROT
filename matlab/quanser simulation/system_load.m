clear all;
clc;

load("plant_continous_model.mat");

ct_A = rp_sys.A;
ct_B = rp_sys.B;
ct_C = [1 0 0 0;
        0 1 0 0];
ct_D = [0; 0];

ct_sys = ss(ct_A, ct_B, ct_C, ct_D);

ts = 0.02;
dt_sys = c2d(ct_sys, ts);

dt_A = dt_sys.A;
dt_B = dt_sys.B;
dt_C = dt_sys.C;
dt_D = dt_sys.D;

Q_L = eye(4);
Q_L(1,1) = 1;
Q_L(2,2) = 1;
Q_L(3,3) = 1000;
Q_L(4,4) = 100;
R_L = 1;
L = dlqr(dt_A', dt_C', Q_L, R_L, 0)';

Q_K = eye(4);
Q_K(1, 1) = 1000;
Q_K(2, 2) = 500;
R_K = 1;
K = dlqr(dt_A, dt_B, Q_K, R_K, 0);

F = dt_A - L * dt_C - dt_B * K;
G = L;
H = -K;
J = [0 0];

eig(F)

xp_init = [0.1; 0.04; 0; 0];
xp = xp_init;
xc = [0; 0; 0; 0];

max_iter = 100;

e_his = [];

for i=1:max_iter
    y = dt_C * xp;

    u = H * xc;

    xc = F * xc + G * y;
    xp = dt_A * xp + dt_B * u;

    e_his = [e_his; (xp - xc)'];
end

p = zeros(1, 4);
L = acker(F', H', p)';
F_new = F - L * H;

PQ = [];
for i=1:4
    temp = H*F_new^(4-i)*G;
    PQ = [PQ; [temp, H*F_new^(4-i)*L]];
end

figure(1)
subplot(4,1,1)
plot(e_his(:, 1));

subplot(4,1,2)
plot(e_his(:, 2));

subplot(4,1,3)
plot(e_his(:, 3));

subplot(4,1,4)
plot(e_his(:, 4));
