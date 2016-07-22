#include<iostream>
#include<sparsehash/dense_hash_map>
#include<gmp.h>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include <gmpxx.h>

using namespace std;
using google::dense_hash_map;      // namespace where class lives by default
//using ext::hash;  // or __gnu_cxx::hash, or maybe tr1::hash, depending on your OS
using tr1::hash;
struct eqstr
{
  bool operator()(string s1, string s2) const
  {
   return (s1 == s2)|| (s1.compare(s2) == 0);
  }
};

//bool lookup(const dense_hash_set<const char*, hash<const char*>, eqstr>& Set, const char* word="15")
//{
//  dense_hash_set<const char *, hash<const char *>, eqstr>::const_iterator it = Set.find(word);
//  if(it != Set.end())return true;
//  else return false;
//}

void printBytes( string  text ){
        for(unsigned i=0;i<text.size();i++)	{
	cout<<hex<<setw(2)<<setfill('0')<<(unsigned int)text[i]<<dec;
	}
}

int main(){
    dense_hash_map<string,int, hash<string>, eqstr> Set;
//    Set.set_empty_key(NULL);
    Set.set_empty_key("");
    const int B=pow(2,20);
//    const int B=6;
    mpz_t p,g,x,h;
    mpz_inits(p,x,g,h,NULL);
    mpz_set_str(p,"134078079299425970995740249982058461274793658205923933 \
            77723561443721764030073546976801874298166903427690031 \
            858186486050853753882811946569946433649006084171",10);
    mpz_set_str(g,"11717829880366207009516117596335367088558084999998952205 \
            59997945906392949973658374667057217647146031292859482967 \
            5428279466566527115212748467589894601965568",10);
    mpz_set_str(h,"323947510405045044356526437872806578864909752095244 \
            952783479245297198197614329255807385693795855318053 \
            2878928001494706097394108577585732452307673444020333",10);
/*
    mpz_set_ui(p,19);
    mpz_set_ui(g,2);
    mpz_set_ui(h,15);
*/

    mpz_t* left;
    left = (mpz_t*)malloc(sizeof(mpz_t) * B);
    for(int i=0;i<B;++i){
        mpz_init(left[i]);
    }
    mpz_t mpz_ginv,mpz_temp;
    mpz_inits(mpz_ginv,mpz_temp,NULL);
    mpz_invert(mpz_ginv, g, p);
    mpz_set(mpz_temp, h);

    for(int i=0;i<B;i++){
        mpz_set(left[i],mpz_temp);
        mpz_mul(mpz_temp, mpz_temp, mpz_ginv);
        mpz_mod(mpz_temp, mpz_temp, p);
        Set[mpz_class(left[i]).get_str()]=i;

}
    cout<<"Clear 1"<<endl;

    mpz_t gB;
    mpz_init(gB);
    mpz_powm_ui(gB,g,B,p);

//    cout<<"g power B is : ";
//    mpz_out_str(stdout,10,gB);
//    cout<<endl;

//    merge_sort(left,0,B);
//    cout<<"Clear 2"<<endl;

    mpz_t right;
    mpz_init(right);
    mpz_set_ui(x,B);
    int flag=0;
    mpz_set_ui(right,1);
    cout<<"2nd Loop : "<<endl;
    for(int i=0;i<B;i++){
        if(Set[mpz_class(right).get_str()]>0){
            flag=1;
            mpz_mul_ui(x,x,i);
            mpz_add_ui(x,x,Set[mpz_class(right).get_str()]);
            break;
        }
        mpz_mul(right,right,gB);
        mpz_mod(right,right,p);
    }
    cout<<"x is '"<<mpz_class(x).get_str()<<"'"<<endl;
    if(!flag){
        cout<<"x is incorrect"<<endl;
    }
    else cout<<"x is correct! :D Awesome!"<<endl;
    
    
    
    
    
    cout<<"Program ended."<<endl;
    free(left);
    return 0;
}

