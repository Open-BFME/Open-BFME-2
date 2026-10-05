// cl: /O1 /G7 /arch:SSE2 /GX- /MD
// ???0Rva000F0F2B@@QAE@XZ @0x000F0F2B 48B: native boundary from Ghidra.
// Address-derived constructor; the original class name remains unknown.
// Body is byte-exact against retail and reuses the rowed void initializer
// 0x000EFA4E, whose own prefix view lives in BfmeShadowPrefix.h. The three
// consecutive words observed at 0x00BCEFA0 (EFAD2, B3FD0, __purecall) are
// read as this class's three-slot dispatch table; the extent is not
// independently proven, adjacent tables remain possible.
#include "BfmeShadowPrefix.h"

// The three consecutive words read at 0x00BCEFA0 are the table this
// constructor installs.
extern "C" const void *const Rva000F0F2BDispatchTable[];

class Rva000F0F2B : public Rva000EFA4E
{
public:
	Rva000F0F2B();
	float m_value58;
	float m_value5c;
	float m_value60;
	bool m_flag64;
};

Rva000F0F2B::Rva000F0F2B()
{
	initialize();
	m_value58 = 0.0f;
	m_value5c = 0.0f;
	*(const void *const **)this = Rva000F0F2BDispatchTable;
	m_value60 = 20.0f;
	m_flag64 = false;
}
