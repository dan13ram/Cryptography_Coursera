#include<iostream>
#include<cstdlib>
#include<cmath>
#include<gmp.h>

using namespace std;

int main(){

    mpz_t B;
    mpz_init_set_ui(B,pow(2,20));
    char *temp=new char[30];
    gmp_sprintf (temp,"%Zd\n",B);
    cout<<temp;
    delete []temp;
    return 0;
    
}

