#include<cryptopp/sha.h>
#include<iostream>
#include<iomanip>
#include<fstream>

#define KILO 1024
#define BLOCK 32

using namespace std;
using namespace CryptoPP;
typedef unsigned char byte;

void printBytes(const byte *t,const int sz){
	for(int i=0;i<sz;++i){
		cout<<hex<<setw(2)<<setfill('0')<<(unsigned int)t[i]<<dec;
	}
}

int main(){
        byte *out=new byte[SHA256::DIGESTSIZE];
	ifstream file( "Introduction.mp4", ios::binary | ios::ate);
	
	int size=file.tellg();
	int last=size%KILO;
	unsigned char *state=new unsigned char[KILO+BLOCK];
	unsigned char *oData = new unsigned char[last ];
	
        if(last==0)     last=KILO;
	cout<<size<<endl;
	
	file.seekg(-last,ios::end);
        cout<<(unsigned int)file.tellg()<<" "<< (unsigned int)(file.tellg())+last <<endl;
	file.read( (char *)oData, last );
        SHA256().CalculateDigest(out, oData, last);
        cout<<(unsigned int)file.tellg()+1<<endl;
        
        file.seekg(0,file.end);
        cout<<(unsigned int)file.tellg()<<endl;

        file.seekg(-(last+KILO),ios::end);
        cout<<(unsigned int)file.tellg()<<endl;
        do{
	        file.read( (char *)state, KILO );
		for(int j=0;j<BLOCK;++j){
			state[KILO+j]=out[j];
		}
                SHA256().CalculateDigest(out, state, KILO + BLOCK);
	}while(file.seekg(-2*KILO,ios::cur));

        cout<<endl<<"Output is '"<<(unsigned int)file.tellg()<<"' : ";
        printBytes(out,SHA256::DIGESTSIZE);
        cout<<endl;
	
        delete []state;
        delete []out;
        delete []oData;
        return 0;
}
