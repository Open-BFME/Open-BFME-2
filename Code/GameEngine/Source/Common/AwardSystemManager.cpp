// cl: /Ob1 /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native40ADDD..40ADFA and40BAAA..40BAD0. Award trigger records
// occupy16B, and their key-list prefixes are compared by rowed40AD5A.
// The389B INI award parser40BAF7 uses these contains/add operations.
#include <vector>
class Rva0040A7D5;
struct Rva0040ABA5Item;
const Rva0040ABA5Item *Rva0040AD5AFind(const Rva0040ABA5Item *,const Rva0040ABA5Item *,const Rva0040A7D5 *);

enum NameKeyType { NAMEKEY_INVALID=0 };
class Rva0040AECC {
public:Rva0040AECC();
private:_STL::vector<NameKeyType> keys;int flag;
};
Rva0040AECC::Rva0040AECC() : flag(0) {}

class Rva0040AEE3;
namespace _STL {
template<> void vector<Rva0040AEE3>::push_back(const Rva0040AEE3 &);
}

class Rva0040ADDD {
public:
 unsigned char rva0040ADDD(const Rva0040A7D5 *) const;
 bool rva0040BAAA(const Rva0040AEE3 *);
private:
 char prefix[0x1C];
 const Rva0040ABA5Item *first,*last,*limit;
};
unsigned char Rva0040ADDD::rva0040ADDD(const Rva0040A7D5 *trigger) const
{
 const Rva0040ABA5Item *end=last;
 return Rva0040AD5AFind(first,end,trigger)!=end;
}
bool Rva0040ADDD::rva0040BAAA(const Rva0040AEE3 *trigger)
{
 if(!rva0040ADDD(reinterpret_cast<const Rva0040A7D5 *>(trigger))) {
  reinterpret_cast<_STL::vector<Rva0040AEE3,_STL::allocator<Rva0040AEE3> > *>(&first)->push_back(*trigger);
  return true;
 }
 return false;
}
