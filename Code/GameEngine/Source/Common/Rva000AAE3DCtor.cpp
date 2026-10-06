// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000AAE3D@@QAE@XZ @0x000AAE3D 28B frameless ctor over vector at +0xC
// Evidence: push ecx push esi mov esi ecx lea eax esp+7 push allocator call rowed Vector_base BfmeE16 0x00211E58; vtable 0x00BC947C at +0 gate DIR32; vector last non-trivial plus empty body needs no EH unlike 0x000AA83B which needs unwind for later memset; 8 bytes pad +4 +8 left uninitialized; BfmeE16 16B stand-in from stlport_vector_e16_o1; owner unproven honest Rva name
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva000AAE3D
{
public:
	Rva000AAE3D();
protected:
	virtual void _0();
private:
	int m_04;
	int m_08;
	_STL::vector<BfmeE16> m_vec0C;
};

Rva000AAE3D::Rva000AAE3D()
	: m_vec0C(_STL::allocator<BfmeE16>())
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?_0@Rva000AAE3D@@MAEXXZ=??_GRva00AB15D@@UAEPAXI@Z")
