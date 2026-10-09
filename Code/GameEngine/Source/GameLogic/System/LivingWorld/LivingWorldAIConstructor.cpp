// cl: /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Native4FB3F2..4FB4D1 is an ordinary224-byte constructor, also called
// on LivingWorldPlayer+4C at2E27D5. WB1319960 independently witnesses each
// embedded member initialization and returns this; the prior pointer-method
// lead is superseded by that target lifetime evidence. LivingWorldAI owner
// identity comes from named SubmitOrders WB131A480 and its receiver fields.
// Unknown state member types remain neutral; their empty constructor and
// iterator folds are independently verified in LivingWorldAIEmptyMembers.cpp.
#include <vector>
#include <deque>
struct BfmeE16 { char bytes[16]; };
struct Rva00063333Element { char bytes[1]; };
// Existing admitted game allocator30830 alias is a potentially throwing C++
// call. The plain CRT allocator would erase native teardown EH states and
// call628F98; specialize only this proven POD storage deallocation route.
void Rva00030830FreeAllocation(void *);
namespace _STL {
template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *p,unsigned int) const { if(p) Rva00030830FreeAllocation(p); }
template<> _Vector_base<BfmeE16,allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16>&) throw();
template<> _Deque_iterator_base<Rva00063333Element>::_Deque_iterator_base();
}
class Rva0050292B { public: ~Rva0050292B(); };
class Rva00502C80 { public: Rva00502C80(); ~Rva00502C80() { reinterpret_cast<Rva0050292B *>(this)->~Rva0050292B(); } char bytes[0x50]; };
class Rva0059BE1A { public: void rva0059BE1A(); };
class Rva004E35A3 { public: Rva004E35A3(); ~Rva004E35A3() { reinterpret_cast<Rva0059BE1A *>(this)->rva0059BE1A(); } char bytes[0x24]; };
class Rva004FB3F2State8C { public: Rva004FB3F2State8C(); ~Rva004FB3F2State8C(); char bytes[0x60]; };
class Rva004FB3F2State120 { public: Rva004FB3F2State120(); ~Rva004FB3F2State120(); int value; };
class Rva004FB3F2Iterator { public: Rva004FB3F2Iterator(); ~Rva004FB3F2Iterator(); int first,last,current,node; };
class LivingWorldAI { public: LivingWorldAI(); ~LivingWorldAI(); private:
 int owner,unknown4,level,unknownC,unknown10,unknown14;
 Rva00502C80 builder;
 _STL::vector<BfmeE16> orders68,orders74,orders80;
 Rva004FB3F2State8C state8C;
 Rva004FB3F2Iterator iteratorEC;
 Rva004E35A3 stateFC;
 Rva004FB3F2State120 state120;
 float scale124,scale128,scale12C,scale130;
};
LivingWorldAI::LivingWorldAI():owner(0),unknown4(0),level(5),unknownC(0),unknown10(0),unknown14(0),builder(),orders68(),orders74(),orders80(),state8C(),iteratorEC(),stateFC(),state120(),scale124(1.0f),scale128(1.0f),scale12C(3.0f),scale130(5.0f) {}

// WB1319B10 and native4FB4D2 zero owner before reverse member teardown.
LivingWorldAI::~LivingWorldAI() { owner=0; }
