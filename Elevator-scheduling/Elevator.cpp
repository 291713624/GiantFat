#include<bits/stdc++.h>
#include"Elevator.h"
using namespace std;
void Elevator::stop(int time,int floor){
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//�ж��ļ����Ƿ�ɹ�
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	outfile<<time<<" "<<floor<<endl;
}
