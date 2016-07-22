#include<iostream>
#include<gmp.h>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;
typedef unsigned int byte;

/*
int hexValue(char c){
	if(c>='0' && c<='9') return (int)(c-'0');
	else if(c>='a' && c<='f') return (int)(c-'a') + 10;
	else if(c>='A' && c<='F') return (int)(c-'A') + 10;
	else return (-1);
}

byte* strByte(char *str,byte *output,int *len){
	for(*len=0;str[*len]!='\0';*len++);
	output=new byte[*len/2];
	for( int i=0;i<*len;i+=2)	output[i/2] = hexValue(str[i])*16 + hexValue(str[i+1]);
	return output;
}

void printBytes( const byte  *text, const int size ){
	for(int i=0;i<size;i++)	{
	cout<<hex<<setw(2)<<setfill('0')<<uppercase<<(unsigned int)text[i]<<" "<<dec;
	}
}
*/
void printText( const char  *text, const int size ){
	for(int i=0;i<size;i++)	{
	cout<<text[i];
	}
}

int main(){
mpz_t a,b,c;
mpz_inits(a,b,c,NULL);
mpz_set_ui(a,18);
mpz_set_ui(b,5);

//stringstream ss;
//mpz_out_str(ss,16,a);
//string a;
//ss>>a;
//cout<<a;i

//int size=0;
char *ab=new char[4];
gmp_sprintf(ab,"%Z0x",a);

//cout<<ab[0]<<ab[1];
//cout<<endl;
int len=0;
for(len=0;ab[len]!='\0';len++);

cout<<len<<endl;
//byte *example=NULL;
//strByte(ab, example, &size);
printText(ab, len);
cout<<endl;

return 0;
}
