#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int i,j,sumtime=0,nowtime=0,time,nowfloor=1,disfloor,distime;//����ȫ�ֱ�����
struct passenger{
    int ask_time;
    int ask_floor;
    int ask_space;
}passenger[6];//����һ���洢�˿�����Ľṹ�壻
int istime(int ask_time,int ask_floor,int ask_space){
    time=fabs(ask_time-nowtime)>fabs(ask_floor-nowfloor)?fabs(ask_time-nowtime):fabs(ask_floor-nowfloor);
    disfloor=fabs(ask_floor-nowfloor);
    distime=ask_time>nowtime?fabs(ask_time-nowtime):(disfloor-fabs(ask_time-nowtime));
    nowtime+=time;
    sumtime+=time+1-distime;
    nowfloor=ask_floor;
    cout<<nowtime<<"ʱ��ͣ����"<<ask_floor<<"¥"<<endl;
    nowtime++;
    if(ask_space==1){
        time=fabs(nowfloor-1);
        nowtime+=time;
        sumtime+=time;
        cout <<nowtime<<"ʱ��ͣ����"<<"1¥"<<endl;
        nowfloor=1;
    }else{
        time=fabs(nowfloor-10);
        nowtime+=time;
        sumtime+=time;
        cout <<nowtime<<"ʱ��ͣ����"<<"10¥"<<endl;
        nowfloor=10;
    }
}//����һ�����ڵ�������һ������ĺ�����
int compare(int i,int j,int k){
    time=2*fabs(passenger[j].ask_floor-nowfloor+1)+2*(passenger[j].ask_floor+1);
    nowtime+=fabs(passenger[j].ask_floor-nowfloor);
    cout <<nowtime<<"ʱ��ͣ����"<<passenger[j].ask_floor<<"¥"<<endl;
    nowtime+=1+fabs(passenger[j].ask_floor-passenger[i].ask_floor);
    cout <<nowtime<<"ʱ��ͣ����"<<passenger[i].ask_floor<<"¥"<<endl;
    nowtime+=1+fabs(passenger[i].ask_floor-k);
    cout <<nowtime<<"ʱ��ͣ����"<<k<<"¥"<<endl;
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
int main(){
	passenger[0].ask_time=passenger[0].ask_floor=passenger[0].ask_space=0;
    for(i=1;i<=5;i++){
        cin >>passenger[i].ask_time >>passenger[i].ask_floor >>passenger[i].ask_space;
    }//��ȡ5������
	for(i=1;i<=5;i++){
        for(j=1;j<=5;j++){
            if(passenger[i].ask_time>passenger[j].ask_time){
                passenger[0]=passenger[i];
                passenger[i]=passenger[j];
                passenger[j]=passenger[0];
            }
        }
    }//�����г˿͵�����ʱ���С����5��������������
    if(same()==1){
        if(passenger[1].ask_time>passenger[1].ask_floor){
            cout <<passenger[1].ask_time<<"ʱ��ͣ����"<<passenger[1].ask_floor<<"¥"<<endl;
            nowtime+=passenger[1].ask_time;
            if(passenger[1].ask_space==1){
                disfloor=fabs(passenger[1].ask_floor-1);
                sumtime+=5*(disfloor+1);
                nowtime+=disfloor+1;
                cout <<nowtime<<"ʱ��ͣ����"<<"1¥"<<endl;
            }else{
                disfloor=fabs(passenger[1].ask_floor-10);
                sumtime+=5*(disfloor+1);
                nowtime+=disfloor+1;
                cout <<nowtime<<"ʱ��ͣ����"<<"10¥"<<endl;
            }
        }else{
            cout <<passenger[1].ask_floor<<"ʱ��ͣ����"<<passenger[1].ask_floor<<"¥"<<endl;
            nowtime+=passenger[1].ask_floor;
            if(passenger[1].ask_space==1){
                disfloor=fabs(passenger[1].ask_floor-1);
                sumtime=5*(disfloor+1);
                nowtime+=disfloor+1;
                cout <<nowtime<<"ʱ��ͣ����"<<"1¥"<<endl;
            }else{
                disfloor=fabs(passenger[1].ask_floor-10);
                sumtime=5*(disfloor+1);
                nowtime+=disfloor+1;
                cout <<nowtime<<"ʱ��ͣ����"<<"10¥"<<endl;
            }
        }
    }
    else{for(i=1;i<=5;){
    	if((passenger[i].ask_floor==passenger[i].ask_space==1) || (passenger[i].ask_floor==10 && passenger[i].ask_space==0)){
            i++;
            continue;
        }//�ж��Ƿ�������ȥ��¥�������¥��һ����ƤƤϺ��
        if(passenger[i].ask_time==passenger[i+1].ask_time){
        if(passenger[i].ask_floor==passenger[i+1].ask_floor){
            time=passenger[i].ask_time>passenger[i].ask_floor?passenger[i].ask_time:fabs(passenger[1].ask_floor-nowfloor);
            disfloor=fabs(passenger[i].ask_floor-nowfloor);
            distime=passenger[i].ask_time>nowtime?fabs(passenger[i].ask_time-nowtime):(fabs(passenger[i].ask_time-nowtime)+disfloor);
            nowtime+=time;
            sumtime+=time+1-distime;
            nowfloor=passenger[i].ask_floor;
            cout <<nowtime<<"ʱ��ͣ����"<<passenger[i].ask_floor<<"¥"<<endl;
            nowtime++;
            if(passenger[i].ask_space==passenger[i+1].ask_space){
                if(passenger[i].ask_space==1){
                    time=fabs(nowfloor-1);
                    nowtime+=time;
                    sumtime+=time;
                    cout <<nowtime<<"ʱ��ͣ����"<<"1¥"<<endl;
                    nowfloor=1;
                }else{
                    time=fabs(nowfloor-10);
                    nowtime+=time;
                    sumtime+=time;
                    cout <<nowtime<<"ʱ��ͣ����"<<"10¥"<<endl;
                    nowfloor=10;
                }
                i+=2;
            }else{
                time=fabs(nowfloor-1)<fabs(nowfloor-10)?fabs(nowfloor-1):fabs(nowfloor-10);
                nowtime+=time;
                sumtime+=2*time+10;
                cout <<nowtime<<"ʱ��ͣ����1¥"<<endl;
                nowfloor=1;
                nowtime+=10;
                cout <<nowtime<<"ʱ��ͣ����10¥"<<endl;
                nowfloor=10;
                nowtime++;
                i+=2;
            }//��������������������ȥ��¥����ͬ�Ĵ��� 
        }else{
           if(passenger[i].ask_space==passenger[i+1].ask_space){
               if(passenger[i].ask_space==1){
                   if(fabs(passenger[i].ask_floor-1)<fabs(passenger[i+1].ask_floor-1)){
                       compare(i,i+1,1);
                   }else{
                       compare(i+1,i,1);
                   }
               }else{
                   if(fabs(passenger[i].ask_floor-10)<fabs(passenger[i+1].ask_floor-10)){
                       compare(i,i+1,10);
                   }else{
                       compare(i+1,i,10);
                   }
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
    }
    }
    cout <<"�˿͵ȴ��ܺ�:"<<sumtime<<"s"<<endl;
    return 0;
}
