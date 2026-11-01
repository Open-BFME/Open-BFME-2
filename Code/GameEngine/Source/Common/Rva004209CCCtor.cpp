// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004209CC@@QAE@XZ @0x004209AB 33B
// Derived ctor: baseConstruct via inlined base then vtable 0x00C3BD40 then
// BfmeE16 Vector_base at +0xC. Same 33B shape as rowed ??0Rva0022CA74 at
// 0x0022CA74 (push ecx push esi mov esi ecx call baseConstruct lea eax
// [esp+7] push eax lea ecx [esi+0xC] mov [esi] vtable call Vector_base).
// Evidence: leaf packet calls rowed baseConstruct 0x001B4E63 and rowed
// Vector_base 0x00211E58; vtable store 0x00C3BD40 at [esi]; caller at 0x0022F233.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

// Rowed SubsystemInterface ctor/dtor; the destructor view has this same
// twelve-byte base and a single virtual destructor slot.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva004209CC : public SubsystemInterface
{
public:
	Rva004209CC();
protected:
public:
	virtual ~Rva004209CC();
protected:
private:
	_STL::vector<BfmeE16> m_vec;
};

Rva004209CC::Rva004209CC()
: m_vec()
{
}

