%% ���Լ��ʱ��
clc;clear;
q0 = [10,20];
qv0 = [0,0];
qa0 = [0,0];
qf = [60,100];
qvf = [0,0];
qaf = [0,0];
tmax = 0;
for tf=1:100 % ö����ʱ��
    for j=1:2
	      a0(j) = q0(j);                                       
          a1(j) = qv0(j);
          a2(j) = qa0(j)/2.0;
          a3(j) = (20*(qf(j) - q0(j)) - (8*qvf(j) + 12*qv0(j))*tf + (qaf(j) - 3*qa0(j))*tf^2)/(2*tf^3);
          a4(j) = (-30*(qf(j) - q0(j)) + (14*qvf(j) + 16*qv0(j))*tf - (2*qaf(j) - 3*qa0(j))*tf^2)/(2*tf^4);
          a5(j) = (12*(qf(j) - q0(j)) - (60*qvf(j) + 6*qv0(j))*tf + (qaf(j) - qa0(j))*tf^2)/(2*tf^5);
          for t=0:0.1:tf % �������ʱ���µĸ����׶��ٶȺͼ��ٶ�
              v = a1(j) + 2*a2(j)*t + 3*a3(j)*t^2 + 4*a4(j)*t^3 + 5*a5(j)*t^4;
              a = 2*a2(j) + 6*a3(j)*t + 12*a4(j)*t^2 + 20*a5(j)*t^3;
              if (v >= 5)||( a <= -0.5)||(a >= 0.5)
                tmax=tf; % ��¼������������ʱ�����ֵ
              end
          end
    end
end
% Լ��ʱ���ȡtmax+1
tmin = tmax+1;


%% ����ģ��
L=1;    %���˳���


% ʹ�þ���DH��������������ģ��
L1 = Revolute('d',0,'a',L,'alpha',0,'r', [-L/2,0,0],'qlim',[-2*pi, 2*pi]);
L2 = Revolute('d',0,'a',L,'alpha',0,'r', [-L/2,0,0],'qlim',[-2*pi, 2*pi]);
r=SerialLink([L1,L2],'name','two-link');

% �������ѡ��
ws = [-4 4 -4 4 -4 4];
plotopt = {'workspace',ws,'nobase', 'notiles', 'noshading', 'noshadow', 'nowrist','top','fps',60};

init_ang=[pi/18 pi/9];                  % ��ʼ�Ƕ�
targ_ang=[pi/3,5*pi/9];                 % ��ĩ�Ƕ�
v=[0 0];                                % ʼĩ�ٶȾ�Ϊ0
t=[0:1:tmin]';                         % �����˶�������tmin�ڣ��������Ϊ1s
[q,qd,qdd] = jtraj(init_ang, targ_ang, t,v,v); % ʹ����ζ���ʽ�滮
% �����ͼ
figure(1);
r.plot(q,plotopt{:},'movie','jtraj.gif');


% �����ת��
q = q*180/pi;
qd = qd*180/pi;
qdd = qdd*180/pi;
figure(2);
subplot(311);
j=1:2;
plot(q(:,j));
title('�ؽڽǶ�');
grid on;
subplot(312);
j=1:2;
plot(qd(:,j));
title('���ٶ�');
grid on;
subplot(313);
j=1:2;
plot(qdd(:,j));
title('�Ǽ��ٶ�');
xlabel('ʱ��(s)')
grid on;
