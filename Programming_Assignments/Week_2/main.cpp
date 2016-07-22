#include<iostream>
#include"aes.h"
#include<string>
using namespace std;

int hexValue(char c){
	if(c>='0' && c<='9') return (int)(c-'0');
	else if(c>='a' && c<='f') return (int)(c-'a') + 10;
	else if(c>='A' && c<='F') return (int)(c-'A') + 10;
	else return (-1);
}

byte* strByte(string str){
	byte *output=new byte[str.size()/2];
	for(int i=0;i<str.size();i+=2)	output[i/2] = hexValue(str[i])*16 + hexValue(str[i+1]);
	return output;
}

void printText(const byte *text, const int size){
	for(int i=0;i<size;i++)	cout<<text[i];
}

string cbcAESDec(const byte *key,const byte *cypher,const int size){
	byte *output=new byte[size-BLOCK];
	byte *IV=new byte[BLOCK];
	int i=0;
	for(i=0;i<BLOCK;++i)	IV[i]=cypher[i];
	aesDec(key,cypher+BLOCK,output);
	for(int j=0;j<BLOCK;++j)output[j]^=IV[j];
	while(i<size-BLOCK){
		byte *temp=new byte[BLOCK];
		aesDec(key,cypher+BLOCK+i,temp);
		for(int j=0;j<BLOCK;++j)temp[j]^=cypher[i+j];
		for(int j=0;j<BLOCK;++j)output[i++]=temp[j];
		delete []temp;
	}
//	cout<<size-BLOCK<<" : ";	printBytes(output,size-BLOCK);	cout<<endl;
	delete []IV;
	int temp=(int)output[size-BLOCK-1];
	temp=temp>16?0:temp;
	int sz=size-BLOCK-temp;
	string out;
	for(int k=0;k<sz;++k)out.push_back(output[k]);
	delete []output;
	return out;
}

void cbcAESEnc(const byte *iv,const byte *key,const string plain, byte *out){
	int sz=(plain.size()/BLOCK+2)*BLOCK;
	byte *state=new byte[sz-BLOCK];
	for(int i=0;i<BLOCK;++i)out[i]=iv[i];
	for(int i=0;i<plain.size();++i)state[i]=(byte)plain[i];
	for(int i=plain.size();i<sz-BLOCK;++i)state[i]=(byte)(sz-plain.size()-BLOCK);
	int i=0;
	for(int j=0;j<BLOCK;++j)state[i+j]^=iv[j];
	aesEnc(key,state,out+BLOCK);i+=BLOCK;
	while(i<sz-BLOCK){
		for(int j=0;j<BLOCK;++j)state[i+j]^=out[i+j];
		aesEnc(key,state+i,out+BLOCK+i);
		i+=BLOCK;
	}
}

string ctrAESDec(const byte *key,const byte *cypher,const int size){
	byte *output=new byte[size-BLOCK];
	byte *iv=new byte[BLOCK];
	int sz=(size/BLOCK)*BLOCK;
	int i=0;
	for(i=0;i<BLOCK;++i)	iv[i]=cypher[i];
	byte *state=new byte[sz];
	for(int i=0;i<sz/BLOCK;++i){
		byte *temp=new byte[BLOCK];
		aesEnc(key,iv,temp);
		iv[BLOCK-1]++;
		for(int j=0;j<BLOCK;++j)	state[i*BLOCK+j]=temp[j];
		delete []temp;
	}
	delete []iv;
	for(int i=0;i<size-BLOCK;++i)	output[i]=state[i]^cypher[BLOCK+i];
	delete []state;
	string out;
	for(int k=0;k<size-BLOCK;++k)out.push_back(output[k]);
	delete []output;
	return out;
	return " ";
}

void ctrAESEnc(const byte *IV,const byte *key,const string plain, byte *out){
	byte *iv=new byte[BLOCK];
	for(int i=0;i<BLOCK;++i)out[i]=iv[i]=IV[i];
	int sz=(plain.size()/BLOCK+1)*BLOCK;
	byte *state=new byte[sz];
	for(int i=0;i<sz/BLOCK;++i){
		byte *temp=new byte[BLOCK];
		aesEnc(key,iv,temp);
		iv[BLOCK-1]++;
		for(int j=0;j<BLOCK;++j)	state[i*BLOCK+j]=temp[j];
		delete []temp;
	}
	for(int i=0;i<plain.size();++i)	out[BLOCK+i]=state[i]^((byte)plain[i]);
	delete []state;
	delete []iv;
}


int main(){

	string k="140b41b22a29beb4061bda66b6747e14";
	string k2="36f18357be4dbd77f050515c73fcf9f2";
	byte *key=strByte(k2);
	string c="4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81";
	string c2="5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253";
	string c3="69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329";
	string c4="770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451";
	string text="Always avoid the two time pad!";
	byte *cypher=strByte(c4);
	int cypherSize=c4.size()/2;
	cout<<cypherSize<<endl;
	byte *iv=new byte[BLOCK];
	for(int i=0;i<BLOCK;++i)iv[i]=cypher[i];
	string output=ctrAESDec(key,cypher,cypherSize);
	cout<<"Decrypted text : '"<<output<<"'"<<endl;	
	cout<<"Given Cypher : ";printBytes(cypher,cypherSize);cout<<endl;
	int sz=text.size()+BLOCK;
	byte *enc=new byte[sz];
	ctrAESEnc(iv,key,text,enc);
	cout<<"Encrypted tx : ";printBytes(enc,sz);cout<<endl;
	output=ctrAESDec(key,enc,sz);
	cout<<"Decrypted text : '"<<output<<"'"<<endl;	
	delete []enc;
	delete []iv;
        return 0;
}


