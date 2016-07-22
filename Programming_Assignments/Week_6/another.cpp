#include<iostream>
#include<string>
using namespace std;

typedef unsigned char byte;

int hexValue(char c){
	if(c>='0' && c<='9') return (int)(c-'0');
	else if(c>='a' && c<='f') return (int)(c-'a') + 10;
	else if(c>='A' && c<='F') return (int)(c-'A') + 10;
	else return (-1);
}

byte* strByte(string str){
	byte *output=new byte[str.size()/2];
	for(unsigned int i=0;i<str.size();i+=2)	output[i/2] = hexValue(str[i])*16 + hexValue(str[i+1]);
	return output;
}

void printText(const byte *text, const int size){
	for(int i=0;i<size;i++)	cout<<text[i];
}

int main(){



string str="466163746f72696e67206c65747320757320627265616b205253412e";
byte *test=strByte(str);
printText(test,str.size()/2);
cout<<endl;


return 0;

}

