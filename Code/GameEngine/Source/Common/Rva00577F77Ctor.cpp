// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00577F77@@QAE@PAXH@Z @0x00577F77 48B: ctor calls base 0x005C6D4D then stores args to +0x3c/+0x40 then sets vtable g_00C6EA28 then constructs vector<BfmeE16> at +0x44. Evidence: unlock packet calls pin-only base plus rowed Vector_base plus caller 0x005782F4 pushes parent plus int.
#include <vector>
#include "../../Include/Common/Rva005C6C7B.h"

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

extern const void *const g_00C6EA28[];

class Rva00577F77 : public Rva005C6C7B
{
public:
	Rva00577F77(void *p, int v);
	virtual ~Rva00577F77();
private:
	char _pad[0x38];
	void *m_3c;
	int m_40;
	_STL::vector<BfmeE16> m_44;
};

Rva00577F77::Rva00577F77(void *p, int v) : m_3c(p), m_40(v), m_44()
{
}
