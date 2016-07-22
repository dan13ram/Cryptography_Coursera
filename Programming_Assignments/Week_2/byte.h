#include<iostream>
#include<iomanip>
template <class T>
class byte_templ {
T v;

public:
byte_templ<T>() : v() { }

byte_templ<T>(const T &w) : v(w) { }

byte_templ<T>(const byte_templ<T> &w) : v(w.v) { }

byte_templ<T> &operator=(const byte_templ<T> &w) { v = w.v; return *this; }
byte_templ<T> &operator=(const T &w) { v = w; return *this; }


//byte_temp<T> &operator^(const byte_templ<T> &b) {
//T temp=v^b.v;
//return temp;
//}

operator T() const { return v; }
operator T &() { return v; }

};

std::ostream &operator<<(std::ostream &os, const byte_templ<unsigned char> &b) {

os <<std::setfill('0')<<std::hex<<std::uppercase<<std::setw(2)<< (unsigned short)b<<std::nouppercase<<std::dec;
return os;
}

std::istream &operator>>(std::istream &is, byte_templ<unsigned char> &b) {
unsigned short i;

is >> i;
b = (unsigned char)i;
return is;
}


typedef byte_templ<unsigned char> byte;
