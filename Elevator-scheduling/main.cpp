#include<bits/stdc++.h>
#include"Elevator.h"
using namespace std;
int N,n,i,j,l,num,sumtime1=0,sumtime2=0,sumtime3=0,sumtime4=0,sumtime=0,nowtime=0,disfloor,distime,in,out;
int time1[10]={0},time2[10]={0},time3[10]={0},floor1[10]={0},floor2[10]={0},floor3[10]={0},time4[10]={0},floor4[10]={0};
int m1=1,m2=1,m3=1,m4=1;//设置全局变量；
int main(){
	ifstream infile("./input.txt",ios::in);
	if (!infile)
	{
		cerr << "open infile wrong!\n";
		exit(1);
	}
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//判断文件打开是否成功
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
    }//读取N个请求；
    j=1;
    e.nowfloor=0;
    nowtime=people[1].asktime ;//电梯等待至接收到第一条请求 
    if(people[1].askfloor >e.nowfloor) e.indicator=1; 
    if(people[1].askfloor <e.nowfloor) e.indicator=0; 
    if(people[1].askfloor ==e.nowfloor){
		e.stop(nowtime,e.nowfloor);
		nowtime++;
		people[1].now =0;
		if(people[j].askspace>e.nowfloor) e.indicator=1;
		else e.indicator=0; 
		j++; 
    }//对第一条请求做出响应 
    while(1){
		nowtime++;
		if(e.indicator==1&&e.nowfloor==2) e.indicator =0;
		if(e.indicator==0&&e.nowfloor==0) e.indicator =1; //调整电梯运行方向 
		if(e.indicator==1) e.nowfloor++;
		if(e.indicator==0) e.nowfloor--;
		if(nowtime>=e.nowfloor &&e.nowfloor==people[j].askfloor&&people[j].now==-1){
			e.stop(nowtime,e.nowfloor);
			nowtime++;
			people[j].now=0;
			if(people[j].askspace>e.nowfloor) e.indicator=1;
			else e.indicator=0; 
			j++; 
		}//如果到达请求楼层，接乘客 
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
			}//送完乘客后，根据下一个请求调整电梯方向 
		}//如果到达目的地，送乘客 
		if(nowtime>=people[j].asktime &&people[j].now ==-1 &&j>=2){//送目前乘客去往目的地时，如果接受到了下一个乘客的请求的处理 
			if(people[j].askfloor >e.nowfloor &&e.indicator==1&&people[j-1].now!=1&&people[j].askfloor ==people[j-1].askspace ){
				nowtime+=people[j].askfloor-e.nowfloor;
				e.nowfloor=people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				num--;
				people[j].now =0;
				people[j-1].now =1;
				j++;
			}//送目前乘客去往目的地时，如果下一个乘客请求楼层和当前目的地一样的处理 （方向向上） 
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
				}//如果下一个乘客的目的地在去往当前目的地前可以到达的处理 
				else if(people[j].askspace >people[j].askfloor &&people[j].askspace ==people[j-1].askspace){
					nowtime+=people[j].askspace -e.nowfloor ;
					e.nowfloor =people[j].askspace ;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--;
					num--;
					j++;
				}//如果下一个乘客的目的地与当前目的地相同的处理 
				else{
					nowtime+=people[j-1].askspace-e.nowfloor;
					e.nowfloor=people[j-1].askfloor ;
					e.stop(nowtime,e.nowfloor);
					nowtime++;
					num--;
					people[j-1].now =1;
					j++;
				}
			}//送目前乘客去往目的地时，如果下一个乘客请求楼层小于当前目的地的处理（方向向上） 
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
			}//送目前乘客去往目的地时，如果下一个乘客请求楼层大于当前目的地的处理（方向向上） 
			if(people[j].askfloor <e.nowfloor &&e.indicator ==0&&people[j-1].now !=1&&people[j].askfloor ==people[j-1].askspace ){
				nowtime+=e.nowfloor-people[j].askfloor;
				e.nowfloor=people[j].askfloor ;
				e.stop(nowtime,e.nowfloor);
				nowtime++;
				num--;
				people[j].now =0;
				people[j-1].now =1;
				j++;
			}//送目前乘客去往目的地时，如果下一个乘客请求楼层和当前目的地一样的处理 （方向向下）
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
			}//送目前乘客去往目的地时，如果下一个乘客请求楼层小于当前目的地的处理（方向向下）
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
				}//如果下一个乘客的目的地在去往当前目的地前可以到达的处理 
				
				else if(people[j].askspace >people[j].askfloor &&people[j].askspace ==people[j-1].askspace){
					nowtime+=e.nowfloor -people[j].askspace;
					e.nowfloor =people[j].askspace ;
					e.stop(nowtime,e.nowfloor );
					nowtime++;
					num--;
					num--;
					j++;
				}//如果下一个乘客的目的地与当前目的地相同的处理 
				
				else{
					nowtime+=e.nowfloor-people[j-1].askspace;
					e.nowfloor=people[j-1].askfloor ;
					e.stop(nowtime,e.nowfloor);
					nowtime++;
					num--;
					people[j-1].now =1;
					j++;
				}
			}//送目前乘客去往目的地时，如果下一个乘客请求楼层大于当前目的地的处理（方向向下） 
		}
		
		if(num==0) break; //如果N个乘客都处理完，结束循环 
    }
    } 
    return 0;
}
