#include<bits/stdc++.h>
using namespace std;
class man{
	public: 
    		int asktime;//请求时间 
    		int askfloor;//发出请求的楼层 
    		int askspace;//请求前往的目的地 
    		int usetime;//载这个乘客所用时间（本次电梯没用到） 
    		int now;//用于判断该乘客是否已处理的状态；
};//构建一个存储乘客请求的结构体； 
class Elevator{
    public:
    		queue < int > destinationqueue; //目的地队列
    		int nowfloor;//当前位置
    		int indicator; //运行方向
    		void gotofloor(); //前往队列首的楼层
    		void stop(int time,int floor); //停靠在当前楼层
    		void updatedestinationqueue(); //更新目的地队列
};
