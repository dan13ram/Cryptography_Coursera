#include<iostream>
#include<gmp.h>
#include<cstdlib>
#include<cstring>
#include<gmpxx.h>
using namespace std;
int main(void){
    mpz_t temp;
    mpz_init_set_ui(temp,10);
    int ArraySize=5;
    unsigned char result[ArraySize];
    memset ( result, 0, ArraySize );
    for (int j = 0; j < 5; j++ )
        {
        mpz_export (result,
                    NULL,   // number of words produced
                    1,      // order
                    1,      // word size
                    0,      // use native endianness
                    0,      // "nails" - produce full "words"
                    temp
            );
        cout << "---------------------------" << endl;
        for (int i = 0; i < ArraySize; i++)
            {
            cout << "result[" << i << "] = " << hex << (int)result[i] << endl;
            }
//        x -= 1;
        mpz_add_ui(temp,temp,1);
        }
    return 0;
}
