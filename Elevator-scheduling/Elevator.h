#include<bits/stdc++.h>
using namespace std;
class man{
	public: 
    		int asktime;//����ʱ�� 
    		int askfloor;//���������¥�� 
    		int askspace;//����ǰ����Ŀ�ĵ� 
    		int usetime;//������˿�����ʱ�䣨���ε���û�õ��� 
    		int now;//�����жϸó˿��Ƿ��Ѵ����״̬��
};//����һ���洢�˿�����Ľṹ�壻 
class Elevator{
    public:
    		queue < int > destinationqueue; //Ŀ�ĵض���
    		int nowfloor;//��ǰλ��
    		int indicator; //���з���
    		void gotofloor(); //ǰ�������׵�¥��
    		void stop(int time,int floor); //ͣ���ڵ�ǰ¥��
    		void updatedestinationqueue(); //����Ŀ�ĵض���
};
