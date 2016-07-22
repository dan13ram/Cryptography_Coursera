#include <iostream>
#include <sparsehash/dense_hash_map>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;
using google::dense_hash_map;      // namespace where class lives by default
using tr1::hash;

struct eqstr
{
  bool operator()(string s1, string s2) const
  {
    return s1==s2 ||
//    (s1 != NULL) && (s2 != NULL) && 
    (s1.compare(s2) == 0);
  }
};

//struct eqstr
//{
//  bool operator()(int s1, int s2) const
//  {
//    return s1==s2;// || (s1 && s2 && strcmp(s1, s2) == 0);
//  }
//};

//bool lookup(const dense_hash_map<const char*, hash<const char*>, eqstr>& Set,
//            const char* word)
//{
//  dense_hash_set<const char*, hash<const char*>, eqstr>::const_iterator it
//    = Set.find(word);
//  if(it != Set.end())return true;
//  else return false;
//}
//char * process (const char *input){
//    unsigned int length=0;
//    for(length=0;input[length]!='\0';++length);
//    char *output=new char[length+1];
//    for(unsigned int i=0;i<length;++i){
//        output[i]=input[i];
//    }
//    output[length]='\0';
//    return output;
//}
        

int main()
{
  dense_hash_map<string,int , hash<string>, eqstr> Set;
//  dense_hash_map<int,int , hash<int>, eqstr> Set;

  mpz_t temp;
//  char *word=new char [100];
//  mpz_inits(temp,NULL);
  Set.set_empty_key("");
  mpz_init_set_ui(temp,10);
//  gmp_sprintf(word,"%Zd",temp);
//  char *another = process(word);
//    int mydim = (mpz_sizeinbase(temp, 2) +7)/ 8;
//    char *myb =  ( char*) malloc(sizeof(char) * mydim);
//    size_t *count = (size_t*) malloc(sizeof(size_t));
//
//                    mpz_export((void *) myb, count, 1, sizeof( char), 1, 0, c);
//    mpz_export (myb,
//                    NULL,   // number of words produced
//                    1,      // order
//                    1,      // word size
//                    1,      // use native endianness
//                    0,      // "nails" - produce full "words"
//                    
//            );
mpz_class z(temp);
    Set[z.get_str()]=777;


//  Set.insert("plum");
//  Set.insert("apple");
//  Set.insert("mango");
//  Set.insert("apricot");
//  Set.insert("banana");
//  if(lookup(Set, "mango"))cout<<"present"<<endl;
//  else cout<<"not present"<<endl;
//  if(lookup(Set, "apple"))cout<<"present"<<endl;
//  else cout<<"not present"<<endl;
//  if(lookup(Set, "durian"))cout<<"present"<<endl;
//  else cout<<"not present"<<endl;



//  char tmp[]="10";
//  cout<<"word is '"<<word<<"'"<<endl;
//  cout<<"another is '"<<another<<"'"<<endl;
//  cout<<"tmp is '"<<tmp<<"'"<<endl;
//  cout<<"another and word are ";
//  cout<<(strcmp(another,word)==0?"equal":"not equal")<<endl;
//  cout<<"word and '10' are ";
//  cout<<(strcmp(word,tmp)==0?"equal":"not equal")<<endl;
//  cout<<"another and '10' are ";
//  cout<<(strcmp(another,tmp)==0?"equal":"not equal")<<endl;
//  cout<<"word is '"<<word<<"' and  Set[word] is '"<<Set[word]<<"'"<<endl;
//  cout<<"another is '"<<another<<"' and  Set[another] is '"<<Set[another]<<"'"<<endl;
//  cout<<"tmp is '"<<tmp<<"' and  Set[tmp] is '"<<Set[tmp]<<"'"<<endl;
//  char *b=process(word);
//  cout<<"b is '"<<tmp<<"' and  Set[b] is '"<<Set[b]<<"'"<<endl;
  
  mpz_t t;
  mpz_init_set_ui(t,10);
  z=mpz_class(t);
  cout<<" and  Set[a] is '"<<Set[z.get_str()]<<"'"<<endl;
        
  return 0;
}

