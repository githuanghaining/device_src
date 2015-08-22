#include <stdio.h>
#include "ly_trace.h"
int main(int argc,char** argv)
{

int ttl_num;
route_info_t* route_list;
trace_route("120.24.88.82",&ttl_num,&route_list);
//trace_route("120.24.88.82",&ttl_num,&route_list);
////trace_route("120.24.88.82",&ttl_num,&route_list);
////trace_route("120.24.88.82",&ttl_num,&route_list);
////trace_route("120.24.88.82",&ttl_num,&route_list);
printf("ttl_num = %d\n",ttl_num);
int i,j;
for(i=0;i<ttl_num;i++){
	for(j=0;j<3;j++){
		printf("ttl:%d  %s(%s) %d ms\n",i+1,route_list[i].domain[j],route_list[i].ip[j],route_list[i].time[j]);
	}
}	

}
