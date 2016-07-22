#include<iostream>
#include<cmath>
#include<string>
#include<gmp.h>

typedef unsigned char byte;
using namespace std;

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

void printText(const char *text, const int size){
	for(int i=0;i<size;i++)	cout<<text[i];
}

void inv(mpz_t a, mpz_t b,mpz_t old_t){
	mpz_t s,old_s,t,r,old_r;
	mpz_inits(s,old_s,t,r,old_r,NULL);
	mpz_set_ui(s,0);
	mpz_set_ui(old_s,1);
	mpz_set_ui(t,1);
	mpz_set_ui(old_t,0);
	mpz_set(r,b);
	mpz_set(old_r,a);
    while(mpz_cmp_ui(r,0)){
        mpz_t quotient,temp1,temp2,temp3;
	mpz_inits(quotient,temp1,temp2,temp3,NULL);
	mpz_fdiv_q(quotient, old_r, r);
	mpz_set(temp1,old_r);
	mpz_set(temp2,r);
	mpz_set(old_r,temp2);
	mpz_mul(temp3,quotient,temp2);
	mpz_sub(r,temp1,temp3);
//	r=temp1 - quotient*temp2;

	mpz_set(temp1,old_s);
	mpz_set(temp2,s);
	mpz_set(old_s,temp2);
	mpz_mul(temp3,quotient,temp2);
	mpz_sub(s,temp1,temp3);
//	s=temp1 - quotient*temp2;

	mpz_set(temp1,old_t);
	mpz_set(temp2,t);
	mpz_set(old_t,temp2);
	mpz_mul(temp3,quotient,temp2);
	mpz_sub(t,temp1,temp3);
//	t=temp1 - quotient*temp2;
//	(old_r, r) = (r, old_r - quotient*r);
//        (old_s, s) = (s, old_s - quotient*s);
//        (old_t, t) = (t, old_t - quotient*t);       
   } 
//cout<<"Euler coefficients: ";
//mpz_out_str(stdout,10,old_s);
//cout<<", ";
//mpz_out_str(stdout,10,old_t);
//cout<<endl;
//cout<<"greatest common divisor: ";
//mpz_out_str(stdout,10,old_r);
//cout<<endl;
//cout<<"quotients by the gcd: ";
//mpz_out_str(stdout,10,t);
//cout<<", ";
//mpz_out_str(stdout,10,s);
//cout<<endl;
if(mpz_cmp_ui(old_t,0)<0)mpz_add(old_t,old_t,a);
}


int main(){

mpz_t N;  
mpz_init_set_str(N,"17976931348623159077293051907890247336179769789423065727343008115\
77326758055056206869853794492129829595855013875371640157101398586\
47833778606925583497541085196591615128057575940752635007475935288\
71082364994994077189561705436114947486504671101510156394068052754\
0071584560878577663743040086340742855278549092581", 10);

/*
mpz_init_set_str(N,"72006226374735042527956443552558373833808445147399984182665305798191 \
    63556901883377904234086641876639384851752649940178970835240791356868 \
    77441155132015188279331812309091996246361896836573643119174094961348 \
    52463970788523879939683923036467667022162701835329944324119217381272 \
    9276147530748597302192751375739387929",10);

mpz_init_set_str(N,"6484558428080716696628242653467722787263437207069762630604390703787 \
    9730861808111646271401527606141756919558732184025452065542490671989 \
    2428844841839353281972988531310511738648965962582821502504990264452 \
    1008852816733037111422964210278402893076574586452336833570778346897 \
    15838646088239640236866252211790085787877",10);
*/

//mpz_root(root, newV,2);
//mpz_t val,root1,val1;
//mpz_inits(val,root1,val1,NULL);
//mpz_set_str(root1,"1",10);
//mpz_mul(val,root,root);
//mpz_add(root1,root,root1);
//mpz_mul(val1,root1,root1);
//mpz_sub(val,newV,val);
//mpz_sub(val1,val1,newV);
//cout<<" newV is : "<<endl;
//mpz_out_str(stdout, 10, newV);
//cout<<endl;
//
//cout<<" root is : "<<endl;
//mpz_out_str(stdout, 10, root);
//cout<<endl;
//
//cout<<" root1 is : "<<endl;
//mpz_out_str(stdout, 10, root1);
//cout<<endl;
//
//cout<<" root squared is : "<<endl;
//mpz_out_str(stdout, 10, val);
//cout<<endl;
//
//cout<<" root1 squared is : "<<endl;
//mpz_out_str(stdout, 10, val1);
//cout<<endl;

//mpz_t test;
//mpz_inits(test,NULL);
//
//mpz_t val,sub;
//mpz_inits(val,sub,NULL);
//mpz_t a,a2,x,p,q,_N;
//mpz_inits(a,a2,x,p,q,_N,NULL);
//
//mpz_mul_ui(_N,N,24);
//
//mpz_root(a,_N,2);
//mpz_add_ui(a,a,1);
//
//mpz_mul(a2,a,a);
//mpz_sub(x,a2,_N);
//mpz_root(x,x,2);
//mpz_add(p,a,x);
//mpz_sub(q,a,x);
//
//mpz_mul(val,p,q);
//mpz_sub(sub,_N,val);
//mpz_fdiv_r(test,_N,q);
//
//cout<<endl;
//mpz_out_str(stdout,10,_N);
//cout<<endl;
//mpz_out_str(stdout,10,val);
//cout<<endl;
//mpz_out_str(stdout,10,sub);
//cout<<endl;

//int i=1;
//while(mpz_cmp_ui(test,0)){
//
//mpz_add_ui(a,a,1);
//
//mpz_mul(a2,a,a);
//mpz_sub(x,a2,N);
//mpz_root(x,x,2);
//mpz_add(p,a,x);
//mpz_sub(q,a,x);
//
//
//mpz_fdiv_r(test,N,q);
//
//cout<<i++<<endl;
//if(i==pow(2,20))break;
//}

//cout<<"ans : "<<endl;
//mpz_fdiv_q_ui(p,p,4);
//mpz_out_str(stdout,10,p);
//cout<<endl;
//mpz_fdiv_q_ui(q,q,6);
//mpz_out_str(stdout,10,q);
//cout<<endl;
//
//mpz_out_str(stdout,10,test);
//cout<<endl;
//mpz_fdiv_r(test,N,p);
//mpz_out_str(stdout,10,test);
//cout<<endl;

mpz_t p,q,phi,e,d,cypher;
mpz_inits(p,q,phi,e,d,cypher,NULL);
mpz_set_str(p,"134078079299425970995740249982058461274793658205923\
933777235614437217640300736627688911116143623269986750405460943393\
20838419523375986027530441562135724301",10);

mpz_fdiv_q(q,N,p);
mpz_set_str(e,"65537",10);

mpz_set_str(cypher,"2209645186741038177630656113488341801741006978\
789283107173183914367613560012053800428232965047350942434394621975\
151225646583996794288946076454204058156474898801373486412045232522\
932017648791666640299750918872997169052608322206777160001932926087\
0009579993724077458967773697817571267229951148662959627934791540",10);


mpz_t temp1,temp2;
mpz_inits(temp1,temp2,NULL);
mpz_sub_ui(temp1,p,1);
mpz_sub_ui(temp2,q,1);

mpz_mul(phi,temp1,temp2);

inv(phi,e,d);

//cout<<"inv ";
//mpz_out_str(stdout,10,d);
//cout<<endl;
//mpz_mul(d,d,e);
//mpz_fdiv_r(d,d,phi);
//mpz_out_str(stdout,10,d);
//cout<<endl;
mpz_t rsa;
mpz_init(rsa);
mpz_powm (rsa,cypher,d,N);

mpz_out_str(stdout,10,rsa);
cout<<endl;
int size=mpz_sizeinbase (rsa, 10);
char *str=new char[size];
gmp_sprintf (str,"%Z0x",rsa);
int len=0;
for(len=0;str[len]!='\0';len++);
cout<<size<<" "<<len<<endl;
printText(str,len);
cout<<endl;






return 0;
}
