#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <math.h>
//#include "ece150-proj2-stats.cpp"
//#include "ece150-proj2-helper.cpp"
using namespace std;
//is it at any time uri match, do we return 0;
extern int randomnum(int a);
extern float avg(float item[], int size);
extern float median(float item[], int size);
extern float stdDev (float item[], float a, int size);
extern float aad(float item[], float m, int size);


int main(int argc, char *argv[]) {
	if (argc<2)
		return -1; 
		
	ifstream infile;
	infile.open("webserveruri.txt");
	char uri2[200][150];
	int size[200]={0};
	float priority[200]={0};
	char uri1[200][150];
	int i=0;
	char exit[5]={'e','x','i', 't', 0};
	while(!infile.eof()) {
		infile>> uri2[i] >>size[i] >> priority[i];
		i++;
	}
	
	int j = 0;
	while(true){
		cin>>uri1[j];
		if ((strcmp(uri1[j], exit))==0) {
			break;
		}
		j++;
	}
	int n=0;
	float newpriority[200]={0};
	float newsize[200]={0};
	for(int t=0; t<j; t++) {
		int a=1;
		int l=0;
		for(int p=0; p<i && a!=0; p++) {
			a=strcmp(uri1[t],uri2[p]);
			//cout<< uri1[t] << " " << uri2[p] << " " << endl; 
			if(a==0){
				newsize[n]=size[p];
				newpriority[n]=priority[p];
				n++;
				l=1;
			}
			
			}
			if(l==0){
				cerr<<"dfdfg"<< endl;
				return -1;
			}
		}
	
	float transdelay[200]={0}; //calculating the delay that occurs in processing the uri
	int a=atoi(argv[1]);
	srand(time(NULL));
	for (int z=0; z<n; z++) {
		int y=randomnum(a);
		
		while(abs(y)>=newsize[z]) {
			y=randomnum(a);
		}
		transdelay[z]=0.8*(newsize[z]+y);
	}
	
	//transdelay[0]=0.8*(newsize[0]-5);
	//transdelay[1]=0.8*(newsize[1]+3);
	//transdelay[2]=0.8*(newsize[2]+7);
	//transdelay[3]=0.8*(newsize[3]+7);
	//transdelay[4]=0.8*(newsize[4]-2);
	//transdelay[5]=0.8*(newsize[5]);
	
	cout<< avg(newsize, n) << " " << median(newsize, n) << " " << stdDev(newsize, avg(newsize,n), n) << " " << aad(newsize, median(newsize, n), n)<< endl;
	cout<< avg(newpriority, n) << " " << median(newpriority, n) << " " << stdDev(newpriority, avg(newpriority,n), n) << " " << aad(newpriority, median(newpriority, n), n) << endl;
	cout<< avg(transdelay, n) << " " << median(transdelay, n) << " " << stdDev(transdelay, avg(transdelay,n), n) << " " << aad(transdelay, median(transdelay, n), n) << endl;
	
	return 0;
	}

// following functions defined to calculate basic statistics 
float avg(float item[], int size) {
float sum=0;
for(int i=0; i<size; i++) {
	sum+=item[i];
}
float average=sum/(float)size;
return average;
}

float median(float item[], int size) {
    if(size == 1) {
	return item[0];
    }
    for(int n = size-1; n >= 1; n--) {
		for(int i = 1; i < n; i++) {
			if(item[i-1] > item[i]) {
				int tmp = item[i-1];
				item[i-1] = item[i];
				item[i] = tmp;
			}	
		}
	}
	float median=0;
	if(size%2==1) {
	median=item[(size-1)/2];
	}
	if (size%2==0) {
	 median=(item[((size-2)/2)]+item[(size/2)])/2;
	} 
	return median;
}	
	
float stdDev (float item[], float a, int size){
float sum=0;

for(int i=0; i<size; i++) {
	sum+=pow((item[i]-a),2);	
}
float sd=sqrt(sum/size);
return sd;
}


float aad(float item[], float m, int size){
	float sum=0;
	for(int i=0; i<size; i++) {
		if(item[i]-m<0)
			sum+=(item[i]-m)*-1;
		else
		sum+=(item[i]-m);
	}	
	float aad=sum/size;
	return aad;
}
