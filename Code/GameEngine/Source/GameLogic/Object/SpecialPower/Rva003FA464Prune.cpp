// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// NEW native3FA464..3FA4DB RET8. Address-derived owner and method; no
// original class or method identity claimed from the neighboring upgrade unit.
// Reverse visits vector8 at+4, preserves records whose indexed mask word has
// the requested bit, and globally deletes other pointed objects before erase.
// First argument unused. Bit-index bounds and original mask type remain unknown.
struct BfmePod8 {void*object;unsigned mask;};
namespace _STL {template<class T>class allocator{};template<class T,class A>class vector{public:T*begin;T*end;T*cap;unsigned size()const{return (unsigned)(end-begin);}T&operator[](unsigned n){return begin[n];}T*erase(T*);};}
class Rva003FA464Object {public:virtual ~Rva003FA464Object();};
class Rva003FA464 {public:void rva003FA464(void*,unsigned);private:unsigned opaque;_STL::vector<BfmePod8,_STL::allocator<BfmePod8> >records;};
void Rva003FA464::rva003FA464(void*,unsigned bit)
{
 for(int i=(int)records.size()-1;i>=0;--i) {
  BfmePod8&item=records[i];
  if(!(*(const unsigned*)((const char*)&item.mask+(bit>>5)*4)&(1U<<(bit&31)))) {
   ::delete (Rva003FA464Object*)item.object;
   records.erase(&records[i]);
  }
 }
}
