#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
int i,j,l,sumtime1=0,sumtime2=0,sumtime3=0,sumtime4=0,sumtime=0,nowtime=0,time,nowfloor=1,disfloor,distime,in,out;
int time1[10]={0},time2[10]={0},time3[10]={0},floor1[10]={0},floor2[10]={0},floor3[10]={0},time4[10]={0},floor4[10]={0};
int m1=1,m2=1,m3=1,m4=1;//����ȫ�ֱ�����
struct passenger{
    int ask_time;
    int ask_floor;
    int ask_space;
    int now;//�����жϸó˿��Ƿ��Ѵ����״̬��
}passenger[6];//����һ���洢�˿�����Ľṹ�壻 
void istime(int ask_time,int ask_floor,int ask_space){
    time=fabs(ask_time-nowtime)>fabs(ask_floor-nowfloor)?fabs(ask_time-nowtime):fabs(ask_floor-nowfloor);
    disfloor=fabs(ask_floor-nowfloor);
    distime=ask_time>nowtime?fabs(ask_time-nowtime):(disfloor-fabs(ask_time-nowtime));
    nowtime+=time;
    sumtime+=time+1-distime;
    nowfloor=ask_floor;
    nowtime++;
    time=fabs(nowfloor-ask_space);
    nowtime+=time;
    sumtime+=time;
    time3[m3]=nowtime;
    floor3[m3]=ask_space;
    m3++;
    nowfloor=ask_space;
}//����һ�����ڵ�������һ������ĺ�����
void taxi(int ask_time,int ask_floor,int ask_space,int k){
    time=fabs(ask_time-nowtime)>fabs(ask_floor-nowfloor)?fabs(ask_time-nowtime):fabs(ask_floor-nowfloor);
    disfloor=fabs(ask_floor-nowfloor);
    distime=ask_time>nowtime?fabs(ask_time-nowtime):(disfloor-fabs(ask_time-nowtime));
    nowtime+=time;
    sumtime1+=time+1-distime;
    nowfloor=ask_floor;
    nowtime++;
    time=fabs(nowfloor-ask_space);
    nowtime+=time;
    sumtime1+=time;
    time1[m1]=nowtime;
    floor1[m1]=ask_space;
    m1++;
    nowfloor=ask_space;
    passenger[k].now=1;
    for(i=k;i<=5;i++){
        if(passenger[i].ask_time<nowtime && passenger[i].now==0){
            sumtime1+=fabs(passenger[i].ask_time-nowtime);
        }
    }
}//����һ�������⳵�� taxi mode��
void busup(){
    for(nowfloor=1;nowfloor<=10;nowfloor++){
    nowtime+=2;
    for(i=1;i<=5;i++){
        if(passenger[i].ask_floor==nowfloor && passenger[i].now==0){
            if(passenger[i].ask_time<nowtime){
                if(passenger[i].ask_space>nowfloor){
                    sumtime2+=2*(passenger[i].ask_space-nowfloor);
                    time2[m2]=nowtime+2*(passenger[i].ask_space-nowfloor);
                    floor2[m2]=passenger[i].ask_space;
                    m2++;
                }else{
                    sumtime2+=4*(10-nowfloor)+2*fabs(passenger[i].ask_space-nowfloor);
                    time2[m2]=nowtime+4*(10-nowfloor)+2*fabs(passenger[i].ask_space-nowfloor);
                    floor2[m2]=passenger[i].ask_space;
                    m2++;
                }
                passenger[i].now=1;
            }
        }
    }
    for(i=1;i<=5;i++){
        if(passenger[i].ask_time<nowtime && passenger[i].now==0){
            sumtime2+=fabs(passenger[i].ask_time-nowtime);
        }
    }
    }
}//����һ�� ������������ bus mode�е��ݴ�1¥��10¥�Ĺ��̣�
void busdown(){
    for(nowfloor=10;nowfloor>=1;nowfloor--){
    nowtime+=2;
    for(i=1;i<=5;i++){
        if(passenger[i].ask_floor==nowfloor && passenger[i].now==0){
            if(passenger[i].ask_time<nowtime){
                if(passenger[i].ask_space>nowfloor){
                    sumtime2+=2*(passenger[i].ask_space-nowfloor);
                    time2[m2]=nowtime+2*(passenger[i].ask_space-nowfloor);
                    floor2[m2]=passenger[i].ask_space;
                    m2++;
                }else{
                    sumtime2+=4*(nowfloor-1)+2*fabs(passenger[i].ask_space-nowfloor);
                    time2[m2]=nowtime+4*(nowfloor-1)+2*fabs(passenger[i].ask_space-nowfloor);
                    floor2[m2]=passenger[i].ask_space;
                    m2++;
                }
                passenger[i].now=1;
            }
        }
    }
    for(i=1;i<=5;i++){
        if(passenger[i].ask_time<nowtime && passenger[i].now==0){
            sumtime2+=fabs(passenger[i].ask_time-nowtime);
        }
    }
    }
}//����һ�� ������������ bus mode�е��ݴ�10¥��1¥�Ĺ��̣�
void compare(int i,int j,int k){
    time=2*fabs(passenger[j].ask_floor-nowfloor+1)+2*(passenger[j].ask_floor+1);
    nowtime+=fabs(passenger[j].ask_floor-nowfloor);
    nowtime+=1+fabs(passenger[j].ask_floor-passenger[i].ask_floor);
    nowtime+=1+fabs(passenger[i].ask_floor-k);
    time3[m3]=nowtime;
    floor3[m3]=k;
    m3++;
    time3[m3]=nowtime;
    floor3[m3]=k;
    m3++;
    nowtime++;
    sumtime+=time;
}//����һ�����ڴ���������ͬ����¥��ȥ����ͬ¥������ĺ���;
int same(){
    if((passenger[1].ask_time==passenger[2].ask_time && passenger[1].ask_time==passenger[3].ask_time &&
        passenger[1].ask_time==passenger[4].ask_time && passenger[1].ask_time==passenger[5].ask_time) &&
        (passenger[1].ask_floor==passenger[5].ask_floor && passenger[1].ask_floor==passenger[4].ask_floor &&
        passenger[1].ask_floor==passenger[3].ask_floor && passenger[1].ask_floor==passenger[2].ask_floor) &&
        (passenger[1].ask_space==passenger[4].ask_space && passenger[1].ask_space==passenger[3].ask_space &&
        passenger[1].ask_space==passenger[2].ask_space && passenger[1].ask_space==passenger[5].ask_space)) return 1;
        else return 0;
}//�ж���������Ƿ���ͬ��
int puts1(){
    ofstream outfile("./output.txt",ios::app);
	if (!outfile)//�ж��ļ����Ƿ�ɹ�
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	for(i=1;i<=5;i++){
    for(i=1;i<=5;i++){
        if(time1[i]==0) continue;
        outfile <<time1[i]<<"ʱ��ͣ����"<<floor1[i]<<"¥"<<endl;
    } 
    outfile <<"�˿͵ȴ��ܺ�:"<<sumtime1<<"s"<<endl<<endl;
	}
}//����sumtime1����ʱ�����������
int puts2(){
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//�ж��ļ����Ƿ�ɹ�
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
    for(i=1;i<=5;i++){
        if(time2[i]==0) continue;
        outfile <<time2[i]<<"ʱ��ͣ����"<<floor2[i]<<"¥"<<endl;
    }
    outfile <<"�˿͵ȴ��ܺ�:"<<sumtime2<<"s"<<endl<<endl;
}//����sumtime2����ʱ�����������
int puts3(){
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//�ж��ļ����Ƿ�ɹ�
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
    for(i=1;i<=5;i++){
        if(time3[i]==0) continue;
        outfile <<time3[i]<<"ʱ��ͣ����"<<floor3[i]<<"¥"<<endl;
    }
    outfile <<"�˿͵ȴ��ܺ�:"<<sumtime3<<"s"<<endl<<endl;
}//����sumtime3����ʱ�����������
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
	while (!infile.eof()) {
	passenger[0].ask_time=passenger[0].ask_floor=0;
	passenger[0].ask_space=1;
    for(i=1;i<=5;i++){
        infile>>passenger[i].ask_time >>passenger[i].ask_floor >>passenger[i].ask_space;
    }//��ȡ5������
	for(i=1;i<=4;i++){
        for(j=i+1;j<=5;j++){
            if(passenger[i].ask_time>passenger[j].ask_time){
                passenger[0]=passenger[i];
                passenger[i]=passenger[j];
                passenger[j]=passenger[0];
            }
        }
    }//�����г˿͵�����ʱ���С����5��������������
    if(same()==1){
        if(passenger[1].ask_time>passenger[1].ask_floor){
            outfile <<passenger[1].ask_time<<"ʱ��ͣ����"<<passenger[1].ask_floor<<"¥"<<endl;
            nowtime+=passenger[1].ask_time;
            disfloor=fabs(passenger[1].ask_floor-passenger[1].ask_space);
            sumtime+=5*(disfloor+1);
            nowtime+=disfloor+1;
            outfile <<nowtime<<"ʱ��ͣ����"<<passenger[1].ask_space<<"¥"<<endl;
        }else{
            outfile <<passenger[1].ask_floor<<"ʱ��ͣ����"<<passenger[1].ask_floor<<"¥"<<endl;
            nowtime+=passenger[1].ask_floor;
            disfloor=fabs(passenger[1].ask_floor-passenger[1].ask_space);
            sumtime=5*(disfloor+1);
            nowtime+=disfloor+1;
            outfile <<nowtime<<"ʱ��ͣ����"<<passenger[1].ask_space<<"¥"<<endl;
        }
        outfile <<"�˿͵ȴ��ܺ�:"<<sumtime<<"s"<<endl<<endl;
    }//������������ͬ���������⴦��
    else{passenger[1].now=passenger[2].now=passenger[3].now=passenger[4].now=passenger[5].now=0;
        for(i=1;i<=5;){
    	if(passenger[i].ask_floor==passenger[i].ask_space){
            passenger[i].now=1;
            i++;
			continue;
        }//�ж��Ƿ�������ȥ��¥�������¥��һ����ƤƤϺ,�о��������������д���
        if(passenger[i].ask_time==passenger[i+1].ask_time){
        if(passenger[i].ask_floor==passenger[i+1].ask_floor){
            time=passenger[i].ask_time>passenger[i].ask_floor?passenger[i].ask_time:fabs(passenger[1].ask_floor-nowfloor);
            disfloor=fabs(passenger[i].ask_floor-nowfloor);
            distime=passenger[i].ask_time>nowtime?fabs(passenger[i].ask_time-nowtime):(fabs(passenger[i].ask_time-nowtime)+disfloor);
            nowtime+=time;
            sumtime+=time+1-distime;
            nowfloor=passenger[i].ask_floor;
            nowtime++;
            if(passenger[i].ask_space==passenger[i+1].ask_space){
                time=fabs(nowfloor-passenger[i].ask_space);
                nowtime+=time;
                sumtime+=time;
                time3[m3]=nowtime;
                floor3[m3]=passenger[i].ask_space;
                m3++;
                nowfloor=passenger[i].ask_space;
                i+=2;
            }else{
                if(fabs(nowfloor-passenger[i].ask_space)<fabs(nowfloor-passenger[i+1].ask_space)){
                time=fabs(nowfloor-passenger[i].ask_space);
                nowtime+=time;
                sumtime+=2*time+fabs(passenger[i].ask_space-passenger[i+1].ask_space);
                time3[m3]=nowtime;
                floor3[m3]=passenger[i].ask_space;
                m3++;
                nowfloor=passenger[i+1].ask_space;
                nowtime+=fabs(passenger[i].ask_space-passenger[i+1].ask_space);
                time3[m3]=nowtime;
                floor3[m3]=passenger[i+1].ask_space;
                m3++;
                nowtime++;
                i+=2;
                }else{
                time=fabs(nowfloor-passenger[i+1].ask_space);
                nowtime+=time;
                sumtime+=2*time+fabs(passenger[i].ask_space-passenger[i+1].ask_space);
                time3[m3]=nowtime;
                floor3[m3]=passenger[i+1].ask_space;
                m3++;
                nowfloor=passenger[i].ask_space;
                nowtime+=fabs(passenger[i].ask_space-passenger[i+1].ask_space);
                time3[m3]=nowtime;
                floor3[m3]=passenger[i].ask_space;
                m3++;
                nowtime++;
                i+=2;
                }
            }//��������������������ȥ��¥����ͬ�Ĵ��� 
        }else{
           if(passenger[i].ask_space==passenger[i+1].ask_space){
            if(fabs(passenger[i].ask_floor-passenger[i].ask_space)<fabs(passenger[i+1].ask_floor-passenger[i].ask_space)){
                compare(i,i+1,passenger[i].ask_space);
                }else{
                compare(i+1,i,passenger[i].ask_space);
                }
               i+=2;
           }else{
               istime(passenger[i].ask_time,passenger[i].ask_floor,passenger[i].ask_space);
               i++;
           }
        }
    }//��������������������ʱ����ͬ�Ĵ��� 
    else{
        istime(passenger[i].ask_time,passenger[i].ask_floor,passenger[i].ask_space);
        i++;
    }
    sumtime3=sumtime;
    sumtime=0;
    }
    nowfloor=1;
    nowtime=0;
    passenger[1].now=passenger[2].now=passenger[3].now=passenger[4].now=passenger[5].now=0;
    for(i=1;i<=5;i++){
    	if(passenger[i].ask_floor==passenger[i].ask_space){
            i++;
            continue;
        }
        taxi(passenger[i].ask_time,passenger[i].ask_floor,passenger[i].ask_space,i);
    }//�� �����⳵�� taxi mode�������������
    nowfloor=1;
    nowtime=0;
    passenger[1].now=passenger[2].now=passenger[3].now=passenger[4].now=passenger[5].now=0;
    for(i=1;i<=5;i++){
        if(passenger[i].ask_floor==passenger[i].ask_space){
            passenger[i].now=1;
            i++;
        }
        while(passenger[1].now==0 || passenger[2].now==0 ||  passenger[3].now==0 || passenger[4].now==0 || passenger[5].now==0){
            busup();
            busdown();
        }
    }//�� ������������ bus mode�������������
    if(sumtime1<=sumtime2&&sumtime1<=sumtime3)  puts1();
	else if(sumtime2<=sumtime1&&sumtime2<=sumtime3)  puts2();
	else if(sumtime3<=sumtime1&&sumtime3<=sumtime2)  puts3();
    }
    }
    return 0;
}
