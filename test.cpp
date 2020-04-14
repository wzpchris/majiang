#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
#include "majiang.h"

unsigned  char all_card[] =
{
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,//万	
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,//条	
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,//筒	
	0x31, 0x32, 0x33, 0x34, 0x41, 0x42, 0x43,  //东、南、西、北、中、发、白
};


int main()
{
	struct timeval _tv; 
	gettimeofday(&_tv, NULL); 
	struct tm _tm; 
	localtime_r(&_tv.tv_sec, &_tm); 
	printf("dbug|%d-%02d-%02d %02d:%02d:%02d.%06ld \n", 1900 + _tm.tm_year, 1 + _tm.tm_mon, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec, _tv.tv_usec);

	//int arr[] = { 0x1, 0x1 };
	//int arr[] = { 0x1, 0x1 , 0x1,0x2, 0x3,   0x41, 0x41, 0x41  };
	//int arr[] = { 0x1 };
	////int arr[] = { 0x1, 0x2, 0x4, 0x4 };
	//int arr[ 6] = {  0x16,  0x17, 0x18,  0x22,  0x24,  0x28 };
	// int arr[ 11 ] = {  0x9 , 0x24,0x24,0x25,0x25 ,0x26,0x26 , 0x27,0x28,0x28,0x29 };
	//int  arr[] = { 0x3,0x4,0x5 ,0x8,0x8,0x8 };

	//int  arr[] = { 0x3, 0x3,0x3,0x4,05, 0x17,0x21 };
	int   arr[] = {   0x1,0x1,0x2,0x2,0x3, 0x3, 0x4,0x4,0x11,0x11    };
	
	
	int  len = sizeof(arr) / sizeof(arr[0]); 	
	for(int i = 0 ; i< 10000 ; i++)
		laizi_can_hu(arr, len, 1);
	
	gettimeofday(&_tv, NULL);
	localtime_r(&_tv.tv_sec, &_tm);
	printf("dbug|%d-%02d-%02d %02d:%02d:%02d.%06ld  \n", 1900 + _tm.tm_year, 1 + _tm.tm_mon, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec, _tv.tv_usec);

	return 0;  

	//for (int tt = 0; tt < 10000; tt++)
	//{
	//	len = 0;		
	//	memset(arr, 0, sizeof(arr)); 
	//	for (int i = 0; i < 9; i++)
	//	{
	//		int ct = rand() % 34;
	//		arr[len++] = all_card[ct]; 
	//	}			
	//	ret = laizi_can_hu(arr, len,    kezi );
	//	if (ret)
	//	{
	//		sort(arr  , arr+len); 
	//		for (int i = 0; i < 9; i++)
	//			printf(" [%x] ", arr[i]);
	//		printf("\n ret --len[%d]----------%d \n", 4, ret); 
	//	}	
	//}
	//for (int tt = 0; tt < 10000; tt++)
	//{
	//	len = 0;
	//	memset(arr, 0, sizeof(arr));
	//	for (int i = 0; i < 13 ; i++)
	//	{
	//		int ct = rand() % 34;
	//		arr[len++] = all_card[ct];
	//	}
	//	ret = laizi_can_hu(arr, len,  1);
	//	if (ret)
	//	{
	//		sort(arr, arr + len);
	//		for (int i = 0; i < 13 ; i++)
	//			printf(" [%x] ", arr[i]);
	//		printf("\n ret --len[%d]----------%d \n", 4, ret);
	//	}
	//} 	
	
	//

	//return 0 ;

	//int arr[14] = {0} ;
	
	//for(int i = 0 ; i< 100; i++)
	//{
 //        int c =  rand()  % 34 ;
 //        arr[0] =  all_card[c] ;
 //        for(int j = 1 ; j<= 3 ;j++)
 //        {
 //        	 c =  rand()  % 34 ;         
 //        	arr[j]  = all_card[c] ;
 //        }
 //        len=1 ;
 //        int ret = laizi_can_hu(arr, 4 ,  kezi  ); 
 //        for(int j = 0 ; j<= 3 ; j++)
 //        	printf("%x  ",  arr[j]);

	//	 printf("ret   card[%x]--len[%d]----------%d\n", arr[0] ,  len ,  ret);
	//}
	// return 0;
}