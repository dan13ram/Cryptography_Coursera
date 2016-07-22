#include<iostream>
#include<gmp.h>
#include<cmath>
#include<cstdlib>

using namespace std;
void merge(mpz_t* input, int p, int r);
void merge_sort(mpz_t* input, int p, int r);

int main(){
    const int B=pow(2,20);
    mpz_t p,g,x,h;
    mpz_inits(p,x,g,h,NULL);
//    mpz_set_ui(B,pow(2,20));
//    mpz_out_str(stdout,10,B);
    mpz_set_str(p,"134078079299425970995740249982058461274793658205923933 \
            77723561443721764030073546976801874298166903427690031 \
            858186486050853753882811946569946433649006084171",10);
    mpz_set_str(g,"11717829880366207009516117596335367088558084999998952205 \
            59997945906392949973658374667057217647146031292859482967 \
            5428279466566527115212748467589894601965568",10);
    mpz_set_str(h,"323947510405045044356526437872806578864909752095244 \
            952783479245297198197614329255807385693795855318053 \
            2878928001494706097394108577585732452307673444020333",10);
    mpz_t* left;
    left = (mpz_t*)malloc(sizeof(mpz_t) * B);
    for(int i=0;i<B;++i){
        mpz_init(left[i]);
    }
    for(int i=0;i<B;i++){
        mpz_powm_ui(left[i],g,i,p);
        if(mpz_invert (left[i], left[i], p)){
            mpz_mul(left[i],h,left[i]);
        }
        else mpz_set_ui(left[i],0);
        mpz_mod(left[i],left[i],p);
    }
    cout<<"Clear 1"<<endl;
    merge_sort(left,0,B);
    cout<<"Clear 2"<<endl;
    mpz_t temp;
    mpz_init(temp);
    mpz_t right;
    mpz_init(right);
    mpz_set_ui(x,B);
    int flag=-1;
    for(int i=0;i<B;i++){
        mpz_powm_ui(right,g,B,p);
        mpz_powm_ui(right,g,i,p);
        for(int j=0;j<B;j++){
            if(!mpz_cmp(right,left[j])){
                mpz_mul_ui(x,x,i);
                mpz_add_ui(x,x,j);
                mpz_powm(temp,g,x,p);
                if(mpz_cmp(temp,h)){
                    mpz_set_ui(x,B);
                }
                else{
                    flag=0;
                    break;
                }
            }
            else if(mpz_cmp(right,left[j])<0){
                flag=2;
                break;
            }
            else if(mpz_cmp(right,left[j])>0){
                flag=3;
                break;
            }
            flag=4;
        }
        if(!flag)break;

        cout<<" in "<<flag<<endl;
        cout<<"DONE "<<(float)(i*100.0)/B <<" % "<<endl;
        system("clear");
    }
    cout<<"Answer is x = ";
    mpz_out_str(stdout,10,x);
    cout<<endl;
    mpz_powm(temp,g,x,p);
    if(mpz_cmp(temp,h)){
        cout<<"x is incorrect"<<endl;
    }
    else cout<<"x is correct! :D Awesome!"<<endl;
//    mpz_t i,C;
//    mpz_init_set_ui(i,0);
//    mpz_init(C);
//    mpz_ui_pow_ui(C,2,40);
//    while(mpz_cmp(i,C)){
//        mpz_powm(temp,g,i,p);
//        if(!mpz_cmp(temp,h))     break;
//        mpz_add_ui(i,i,1);
//        mpz_out_str(stdout,10,i);
//        cout<<endl;
//    }
//    cout<<"Answer should be : ";
//    mpz_out_str(stdout,10,i);
//    cout<<endl;
    free(left);
    return 0;
}

void merge(mpz_t* input, int p, int r)
{
    int mid = floor((p + r) / 2);
    int i1 = 0;
    int i2 = p;
    int i3 = mid + 1;

    // Temp array
    mpz_t *temp;
    temp=(mpz_t*)malloc(sizeof(mpz_t)*(r-p+1));
    for(int i=0;i<(r-p+1);++i){
        mpz_init(temp[i]);
    }

    // Merge in sorted form the 2 arrays
    while ( i2 <= mid && i3 <= r )
        if ( mpz_cmp(input[i2],input[i3]) < 0 )
            mpz_set(temp[i1++],input[i2++]);
        else
            mpz_set(temp[i1++],input[i3++]);

    // Merge the remaining elements in left array
    while ( i2 <= mid )
        mpz_set(temp[i1++],input[i2++]);

    // Merge the remaining elements in right array
    while ( i3 <= r )
        mpz_set(temp[i1++],input[i3++]);

    // Move from temp array to master array
    for ( int i = p; i <= r; i++ )
        mpz_set(input[i],temp[i-p]);
    
    free(temp);
}


void merge_sort(mpz_t* input, int p, int r)
{
    if ( p < r )
    {
        int mid = floor((p + r) / 2);
        merge_sort(input, p, mid);
        merge_sort(input, mid + 1, r);
        merge(input, p, r);
    }
}

