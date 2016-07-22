#include<iostream>


using namespace std;

int main(){

char c=' ';
cout<<std::hex;
//cout<<"Space : \""<<c<<"\""<<endl;
//cout<<"in hex: \""<<(int)c<<"\""<<endl;

for(char d='A';d<='Z';d++){
int a = (int) d;
int b = (int) c;
int e=a^b;
cout<<"d : \""<<d<<"\" --- \""<<a<<"\""<<endl;
cout<<"c : \""<<c<<"\" --- \""<<b<<"\""<<endl;
cout<<"xor \""<<(char)e<<"\" --- \""<<e<<"\""<<endl<<endl;
}
for(char d='a';d<='z';d++){
int a = (int) d;
int b = (int) c;
int e=a^b;
cout<<"d : \""<<d<<"\" --- \""<<a<<"\""<<endl;
cout<<"c : \""<<c<<"\" --- \""<<b<<"\""<<endl;
cout<<"xor \""<<(char)e<<"\" --- \""<<e<<"\""<<endl<<endl;
}
for(char d='0';d<='9';d++){
int a = (int) d;
int b = (int) c;
int e=a^b;
cout<<"d : \""<<d<<"\" --- \""<<a<<"\""<<endl;
cout<<"c : \""<<c<<"\" --- \""<<b<<"\""<<endl;
cout<<"xor \""<<(char)e<<"\" --- \""<<e<<"\""<<endl<<endl;
}
cout<<std::dec;
}
