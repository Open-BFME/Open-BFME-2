// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00421242@@QAE@XZ @0x00421242 33B
// Derived ctor: baseConstruct via inlined base then vtable 0x0083BE00 then
// BfmeE16 Vector_base at +0xC. Retail is push ecx / push esi / mov esi,ecx /
// call baseConstruct / lea eax,[esp+7] / push eax / lea ecx,[esi+0xC] /
// mov [esi],vtable / call Vector_base / mov eax,esi / pop / ret (33B).
// Evidence: leaf lane; callees baseConstruct 0x001B4E63 and Vector_base
// 0x00211E58 rowed; caller at 0x0022F0F0; neighbours share /O1.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) Rva00421242Base
{
public:
	Rva00421242Base() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	// Slot 0 of the class's vftable is the deleting dtor (as in Rva00421242Dtor.cpp's view).
	virtual ~Rva00421242Base();
	char m_flag;
	int m_value;
};

class Rva00421242 : public Rva00421242Base
{
public:
	Rva00421242();
protected:
	virtual ~Rva00421242();
private:
	_STL::vector<BfmeE16> m_vec;
};
Rva00421242::Rva00421242()
: m_vec()
{
}
