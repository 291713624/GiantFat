#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
int i,j,l,sumtime1=0,sumtime2=0,sumtime3=0,sumtime4=0,sumtime=0,nowtime=0,time,nowfloor=1,disfloor,distime,in,out;
int time1[10]={0},time2[10]={0},time3[10]={0},floor1[10]={0},floor2[10]={0},floor3[10]={0},time4[10]={0},floor4[10]={0};
int m1=1,m2=1,m3=1,m4=1;//设置全局变量；
struct passenger{
    int ask_time;
    int ask_floor;
    int ask_space;
    int now;//用于判断该乘客是否已处理的状态；
}passenger[6];//构建一个存储乘客请求的结构体； 
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
}//构造一个用于单独处理一个请求的函数；
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
}//构造一个“出租车” taxi mode；
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
}//构造一个 “公共汽车” bus mode中电梯从1楼到10楼的过程；
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
}//构造一个 “公共汽车” bus mode中电梯从10楼到1楼的过程；
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
}//构造一个用于处理两个不同请求楼层去往相同楼层请求的函数;
int same(){
    if((passenger[1].ask_time==passenger[2].ask_time && passenger[1].ask_time==passenger[3].ask_time &&
        passenger[1].ask_time==passenger[4].ask_time && passenger[1].ask_time==passenger[5].ask_time) &&
        (passenger[1].ask_floor==passenger[5].ask_floor && passenger[1].ask_floor==passenger[4].ask_floor &&
        passenger[1].ask_floor==passenger[3].ask_floor && passenger[1].ask_floor==passenger[2].ask_floor) &&
        (passenger[1].ask_space==passenger[4].ask_space && passenger[1].ask_space==passenger[3].ask_space &&
        passenger[1].ask_space==passenger[2].ask_space && passenger[1].ask_space==passenger[5].ask_space)) return 1;
        else return 0;
}//判断五个请求是否相同；
int puts1(){
    ofstream outfile("./output.txt",ios::app);
	if (!outfile)//判断文件打开是否成功
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	for(i=1;i<=5;i++){
    for(i=1;i<=5;i++){
        if(time1[i]==0) continue;
        outfile <<time1[i]<<"时，停靠在"<<floor1[i]<<"楼"<<endl;
    } 
    outfile <<"乘客等待总和:"<<sumtime1<<"s"<<endl<<endl;
	}
}//构造sumtime1最优时的输出函数；
int puts2(){
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//判断文件打开是否成功
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
    for(i=1;i<=5;i++){
        if(time2[i]==0) continue;
        outfile <<time2[i]<<"时，停靠在"<<floor2[i]<<"楼"<<endl;
    }
    outfile <<"乘客等待总和:"<<sumtime2<<"s"<<endl<<endl;
}//构造sumtime2最优时的输出函数；
int puts3(){
	ofstream outfile("./output.txt",ios::app);
	if (!outfile)//判断文件打开是否成功
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
    for(i=1;i<=5;i++){
        if(time3[i]==0) continue;
        outfile <<time3[i]<<"时，停靠在"<<floor3[i]<<"楼"<<endl;
    }
    outfile <<"乘客等待总和:"<<sumtime3<<"s"<<endl<<endl;
}//构造sumtime3最优时的输出函数；
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
	while (!infile.eof()) {
	passenger[0].ask_time=passenger[0].ask_floor=0;
	passenger[0].ask_space=1;
    for(i=1;i<=5;i++){
        infile>>passenger[i].ask_time >>passenger[i].ask_floor >>passenger[i].ask_space;
    }//读取5个请求；
	for(i=1;i<=4;i++){
        for(j=i+1;j<=5;j++){
            if(passenger[i].ask_time>passenger[j].ask_time){
                passenger[0]=passenger[i];
                passenger[i]=passenger[j];
                passenger[j]=passenger[0];
            }
        }
    }//按所有乘客的请求时间从小到大将5个请求重新排序；
    if(same()==1){
        if(passenger[1].ask_time>passenger[1].ask_floor){
            outfile <<passenger[1].ask_time<<"时，停靠在"<<passenger[1].ask_floor<<"楼"<<endl;
            nowtime+=passenger[1].ask_time;
            disfloor=fabs(passenger[1].ask_floor-passenger[1].ask_space);
            sumtime+=5*(disfloor+1);
            nowtime+=disfloor+1;
            outfile <<nowtime<<"时，停靠在"<<passenger[1].ask_space<<"楼"<<endl;
        }else{
            outfile <<passenger[1].ask_floor<<"时，停靠在"<<passenger[1].ask_floor<<"楼"<<endl;
            nowtime+=passenger[1].ask_floor;
            disfloor=fabs(passenger[1].ask_floor-passenger[1].ask_space);
            sumtime=5*(disfloor+1);
            nowtime+=disfloor+1;
            outfile <<nowtime<<"时，停靠在"<<passenger[1].ask_space<<"楼"<<endl;
        }
        outfile <<"乘客等待总和:"<<sumtime<<"s"<<endl<<endl;
    }//如果五个请求相同，进行特殊处理；
    else{passenger[1].now=passenger[2].now=passenger[3].now=passenger[4].now=passenger[5].now=0;
        for(i=1;i<=5;){
    	if(passenger[i].ask_floor==passenger[i].ask_space){
            passenger[i].now=1;
            i++;
			continue;
        }//判断是否有请求去往楼层和所在楼层一样的皮皮虾,有就跳过他，不进行处理；
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
            }//如果连续两个请求的请求去往楼层相同的处理； 
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
    }//如果连续两个请求的请求时间相同的处理； 
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
    }//用 “出租车” taxi mode处理这五个请求；
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
    }//用 “公共汽车” bus mode处理这五个请求；
    if(sumtime1<=sumtime2&&sumtime1<=sumtime3)  puts1();
	else if(sumtime2<=sumtime1&&sumtime2<=sumtime3)  puts2();
	else if(sumtime3<=sumtime1&&sumtime3<=sumtime2)  puts3();
    }
    }
    return 0;
}
