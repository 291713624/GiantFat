#include<bits/stdc++.h>
#include"Elevator.h"
using namespace std;
int N,n,i,j,l,num,sumtime1=0,sumtime2=0,sumtime3=0,sumtime4=0,sumtime=0,nowtime=0,disfloor,distime,in,out;
int time1[10]={0},time2[10]={0},time3[10]={0},floor1[10]={0},floor2[10]={0},floor3[10]={0},time4[10]={0},floor4[10]={0};
int m1=1,m2=1,m3=1,m4=1;//����ȫ�ֱ�����
int main(){
	ifstream infile("./input.txt",ios::in);
	if (!infile)
	{
		cerr << "open infile wrong!\n";
		exit(1);
	}
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//�ж��ļ����Ƿ�ɹ�
	{  
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	Elevator e;
	man people[100006];
	while(!infile.eof( )){
	infile>>N;
	num=N;
    for(i=1;i<=N;i++){
        infile>>people[i].asktime >>people[i].askfloor >>people[i].askspace;
        people[i].usetime=0;
        people[i].now =-1;
        e.destinationqueue.push(people[i].askspace );
    }//��ȡN������
    j=1;
    e.nowfloor=0;
    nowtime=people[1].asktime ;//���ݵȴ������յ���һ������ 
    if(people[1].askfloor >e.nowfloor) e.indicator=1; 
    if(people[1].askfloor <e.nowfloor) e.indicator=0; 
    if(people[1].askfloor ==e.nowfloor){
		e.stop(nowtime,e.nowfloor);
		nowtime++;
		people[1].now =0;
		if(people[j].askspace>e.nowfloor) e.indicator=1;
		else e.indicator=0; 
		j++; 
    }//�Ե�һ������������Ӧ 
    while(1){
		nowtime++;
		if(e.indicator==1&&e.nowfloor==2) e.indicator =0;
		if(e.indicator==0&&e.nowfloor==0) e.indicator =1; //�����������з��� 
		if(e.indicator==1) e.nowfloor++;
		if(e.indicator==0) e.nowfloor--;
		if(nowtime>=e.nowfloor &&e.nowfloor==people[j].askfloor&&people[j].now==-1){
			e.stop(nowtime,e.nowfloor);
			nowtime++;
			people[j].now=0;
			if(people[j].askspace>e.nowfloor) e.indicator=1;
			else e.indicator=0; 
			j++; 
		}//�����������¥�㣬�ӳ˿� 
		if(e.nowfloor==people[j-1].askspace&&people[j-1].now==0){
			e.stop(nowtime,e.nowfloor);
			nowtime++;
			people[j].now=1;
			j++;
			if(people[j-1].now!=1){
				if(people[j-1].now==-1){
					if(people[j-1].askfloor>e.nowfloor) e.indicator=1;
					else e.indicator=0; 
				}else{
					if(people[j-1].askspace>e.nowfloor) e.indicator=1;
					else e.indicator=0; 
				}
			}//����˿ͺ󣬸�����һ������������ݷ��� 
		}//�������Ŀ�ĵأ��ͳ˿� 
		if(nowtime>=people[j].asktime &&people[j].now ==-1 &&j>=2){//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ��������ܵ�����һ���˿͵�����Ĵ��� 
			if(people[j].askfloor >e.nowfloor &&e.indicator==1&&people[j-1].now!=1&&people[j].askfloor ==people[j-1].askspace ){
				nowtime+=people[j].askfloor-e.nowfloor;
				e.nowfloor=people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				num--;
				people[j].now =0;
				people[j-1].now =1;
				j++;
			}//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ�������һ���˿�����¥��͵�ǰĿ�ĵ�һ���Ĵ��� ���������ϣ� 
			if(people[j].askfloor >e.nowfloor &&e.indicator==1&&people[j-1].now!=1&&people[j].askfloor <people[j-1].askspace ){
				nowtime+=people[j].askfloor-e.nowfloor;
				e.nowfloor=people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				people[j].now =0;
				if(people[j].askspace >people[j].askfloor &&people[j].askspace <people[j-1].askspace ){
					nowtime+=people[j].askspace -e.nowfloor ;
					e.nowfloor =people[j].askspace ;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--;
					nowtime+=people[j-1].askspace -e.nowfloor ;
					e.nowfloor =people[j-1].askspace;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--; 
					j++;
				}//�����һ���˿͵�Ŀ�ĵ���ȥ����ǰĿ�ĵ�ǰ���Ե���Ĵ��� 
				else if(people[j].askspace >people[j].askfloor &&people[j].askspace ==people[j-1].askspace){
					nowtime+=people[j].askspace -e.nowfloor ;
					e.nowfloor =people[j].askspace ;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--;
					num--;
					j++;
				}//�����һ���˿͵�Ŀ�ĵ��뵱ǰĿ�ĵ���ͬ�Ĵ��� 
				else{
					nowtime+=people[j-1].askspace-e.nowfloor;
					e.nowfloor=people[j-1].askfloor ;
					e.stop(nowtime,e.nowfloor);
					nowtime++;
					num--;
					people[j-1].now =1;
					j++;
				}
			}//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ�������һ���˿�����¥��С�ڵ�ǰĿ�ĵصĴ����������ϣ� 
			if(people[j].askfloor >e.nowfloor &&e.indicator==1&&people[j-1].now!=1&&people[j].askfloor >people[j-1].askspace ){
				nowtime+=people[j-1].askspace-e.nowfloor;
				e.nowfloor=people[j-1].askspace;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				num--;
				people[j-1].now =1;
				nowtime+=people[j].askfloor-e.nowfloor;
				e.nowfloor=people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++; 
				people[j].now =0;
				j++;
			}//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ�������һ���˿�����¥����ڵ�ǰĿ�ĵصĴ����������ϣ� 
			if(people[j].askfloor <e.nowfloor &&e.indicator ==0&&people[j-1].now !=1&&people[j].askfloor ==people[j-1].askspace ){
				nowtime+=e.nowfloor-people[j].askfloor;
				e.nowfloor=people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				num--;
				people[j].now =0;
				people[j-1].now =1;
				j++;
			}//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ�������һ���˿�����¥��͵�ǰĿ�ĵ�һ���Ĵ��� ���������£�
			if(people[j].askfloor <e.nowfloor &&e.indicator ==0&&people[j-1].now !=1&&people[j].askfloor <people[j-1].askspace ){
				nowtime += e.nowfloor-people[j-1].askspace;
				e.nowfloor = people[j-1].askspace;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				num--;
				people[j-1].now =1;
				nowtime += e.nowfloor-people[j].askfloor;
				e.nowfloor = people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				people[j].now = 0;
				j++;
			}//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ�������һ���˿�����¥��С�ڵ�ǰĿ�ĵصĴ����������£�
			if(people[j].askfloor <e.nowfloor &&e.indicator ==0&&people[j-1].now !=1&&people[j].askfloor >people[j-1].askspace ){
				nowtime+=e.nowfloor-people[j].askfloor;
				e.nowfloor = people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				people[j].now = 0;
				
				if(people[j].askspace >people[j].askfloor &&people[j].askspace >people[j-1].askspace ){
					nowtime+=e.nowfloor-people[j].askspace ;
					e.nowfloor = people[j].askspace ;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--;
					nowtime+=e.nowfloor-people[j-1].askspace ;
					e.nowfloor =people[j-1].askspace;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--; 
					j++;
				}//�����һ���˿͵�Ŀ�ĵ���ȥ����ǰĿ�ĵ�ǰ���Ե���Ĵ��� 
				
				else if(people[j].askspace >people[j].askfloor &&people[j].askspace ==people[j-1].askspace){
					nowtime+=e.nowfloor -people[j].askspace;
					e.nowfloor =people[j].askspace ;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--;
					num--;
					j++;
				}//�����һ���˿͵�Ŀ�ĵ��뵱ǰĿ�ĵ���ͬ�Ĵ��� 
				
				else{
					nowtime+=e.nowfloor-people[j-1].askspace;
					e.nowfloor=people[j-1].askfloor ;
					e.stop(nowtime,e.nowfloor);
					nowtime++;
					num--;
					people[j-1].now =1;
					j++;
				}
			}//��Ŀǰ�˿�ȥ��Ŀ�ĵ�ʱ�������һ���˿�����¥����ڵ�ǰĿ�ĵصĴ����������£� 
		}
		
		if(num==0) break; //���N���˿Ͷ������꣬����ѭ�� 
    }
    } 
    return 0;
}
