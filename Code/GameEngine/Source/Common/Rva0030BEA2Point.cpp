// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native30BEA2..30BEE6 RET8. Receiver lies28 bytes after the vector prefix.
// Indices traverse first halves forward then second halves backward;16-byte
// elements and the12-byte operator[] provider are independently rowed.
#include <vector>
struct BfmeE16 { float x,y,z,w; };
typedef _STL::vector<BfmeE16,_STL::allocator<BfmeE16> > Rva0030BEA2Vector;
namespace _STL { template<> BfmeE16 &Rva0030BEA2Vector::operator[](size_type); }
struct Rva0030BEA2Point {
 float x,y;
 __forceinline Rva0030BEA2Point(float a,float b):x(a),y(b){}
 __forceinline Rva0030BEA2Point(const Rva0030BEA2Point &p):x(p.x),y(p.y){}
};
class Rva0030BEA2Owner;
class Rva0030BEA2Base {
public: Rva0030BEA2Point rva0030BEA2(int index);
private: int unknown28;
};
struct Rva0030BEA2Prefix { Rva0030BEA2Vector entries; char unknown0C[0x28-0x0C]; };
class Rva0030BEA2Owner:public Rva0030BEA2Prefix, public Rva0030BEA2Base {};
Rva0030BEA2Point Rva0030BEA2Base::rva0030BEA2(int index)
{
 Rva0030BEA2Vector &entries=reinterpret_cast<Rva0030BEA2Owner *>(reinterpret_cast<char *>(this)-0x28)->entries;
 int count=entries.size();
 const float *point;
 if(index==0) point=&entries[0].x;
 else if(--index<count) point=&entries[index].z;
 else point=&entries[count*2-index-1].x;
 return *reinterpret_cast<const Rva0030BEA2Point *>(point);
}
