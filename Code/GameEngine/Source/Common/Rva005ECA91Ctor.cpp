// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005ECA91@@QAE@XZ @ 0x005ECA91 (63B): ctor stores vtable plus vector BfmeE16 at +4 plus ObjectCreationList at +0x10.
// Evidence: push ecx push ecx push esi mov esi ecx lea ebp-0xd push allocator call 0x00211E58 Vector_base BfmeE16;
// and ebp-4 0 then lea esi+0x10 call 0x001F81BF ObjectCreationList ctor; vtable 0x008785B0 at +0; same class as dtor 0x005ECAD0.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class ObjectCreationList
{
public:
	ObjectCreationList();
};
class Rva005ECA91
{
public:
	Rva005ECA91();
protected:
	virtual ~Rva005ECA91();
private:
	_STL::vector<BfmeE16> m_vec04;
	ObjectCreationList m_ocl10;
};

Rva005ECA91::Rva005ECA91()
	: m_vec04(_STL::allocator<BfmeE16>()), m_ocl10()
{
}
