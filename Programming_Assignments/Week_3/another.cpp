#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<sstream>
#include<string>
#include<cstdio>
#include<cstring>

using namespace std;
#define BLOCK 32
#define KILO 1024

typedef unsigned char byte;

int hexValue(char c){
	if(c>='0' && c<='9') return (int)(c-'0');
	else if(c>='a' && c<='f') return (int)(c-'a') + 10;
	else if(c>='A' && c<='F') return (int)(c-'A') + 10;
	else return (-1);
}

void strByte(string str,byte *output){
	for(unsigned int i=0;i<str.size();i+=2)	output[i/2] = hexValue(str[i])*16 + hexValue(str[i+1]);
}

void strChar(string str,char *output){
	for(unsigned int i=0;i<str.size();i+=2)	output[i/2] = hexValue((byte)str[i])*16 + hexValue((byte)str[i+1]);
}

string exec(const char* cmd) {
//	cout<<cmd<<endl;
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	string result = "";
//	cout<<endl<<"im here 1"<<endl;
	while(!feof(pipe)) {
//	cout<<endl<<"im here 2"<<endl;
		if(fgets(buffer, 128, pipe) != NULL)	result += buffer;
//	cout<<endl<<"im here 3"<<endl;
	}
//	cout<<endl<<"im here 4"<<endl;
	pclose(pipe);
//	cout<<"result is "<<result<<endl;
	return result;
}

template<class T>
void printBytes(const T *t,const int sz){
	for(int i=0;i<sz;++i){
		cout<<hex<<setw(2)<<setfill('0')<<(unsigned int)(byte)t[i]<<dec;
	}
}

void printChars(const char *t,const int sz){
	for(int i=0;i<sz;++i){
		cout<<t[i];
	}
}

void sha256(/*const char* in, const int size ,*/ char *out){
//	char *cmd=new char[2*KILO];
//	strcat(cmd,"echo -n \"");
//	strcat(cmd,in);
//	strcat(cmd,"\" | sha256sum");
	char cmd[]="sha256sum -b example.bin";
	string a="";

	a+=exec(cmd);
//	stringstream ss(a);
//	ss>>a;
//	ss.str("");
//	system(cmd);
//	ifstream temp("anotherfile.tmp");
//	temp>>a;
//	cout<<"answer is "<<a<<endl;

	strChar(a,out);
//	delete []cmd;
}

int main()
{
	ifstream file( "test.mp4", ios::binary | ios::ate);
	
	const size_t size=file.tellg();
	size_t numkb=size/KILO, last=size%KILO;
	char *state=new char[KILO+BLOCK];
	char *oData = new char[last];
	char *b=new char[BLOCK];
	ofstream fileout( "example.bin", ios::binary );
	if(last==0){
	last=KILO;
	numkb--;;
	}
	cout<<size<<endl;
	
	file.seekg(-last,ios::end);
//	int t=file.tellg();
	file.getline( oData, last );

//	char testdata[] = "What";
	fileout.write( oData, last );
//	sha256( testdata, b);
	fileout.flush();
	sha256(b);

//	printChars(oData,last);
//	cout<<endl;

//	char *d=new char[5];
//	d[0]='t';d[1]='e';d[2]='s';d[3]='t';d[4]='\0';
//	sha256(d,4,b);
//	cout<<d<<endl;
//	printBytes(d,4);
//	cout<<endl;

    	cout<<"[ DONE ] "<<setw(2)<<setfill('0')<<int((float)0/numkb * 100.0) << "%";

	for(unsigned int i=0;i<numkb;++i){
		file.seekg(-KILO);
		file.getline( state, KILO );
		for(int j=0;j<BLOCK;++j){
			state[KILO+j]=b[j];
		}
		fileout.write( state, KILO + BLOCK );
		fileout.flush();
		sha256(b);
		for(int j=0;j<12;++j)cout<<'\b';
    		cout<<"[ DONE ] "<<setw(2)<<setfill('0')<<int((float)i/numkb * 100.0) << "%";
	}
	cout<<endl;
	
	printBytes(b,BLOCK);
	cout<<endl;
	
//	string a=exec("echo -n \"74657374\" | sha256sum -b ");
//	cout<<a;
//	cout<<endl;
	file.close();
	fileout.close();
	delete []oData;
	delete []state;
	delete []b;
	return 0;
}

