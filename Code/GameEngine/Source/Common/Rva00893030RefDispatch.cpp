// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../Include/Common/Rva00894D80Accessor.h"

unsigned int bfmeDecVGO(unsigned int *value);
void bfmeDropVGO(void *value);

#include "../../Include/Common/BfmeRefVGO.h"

// Inline release: the dispatcher's main path inlines it for its by-value
// argument, and its unwind funclet calls the out-of-line copy.
inline BfmeRefVGO::~BfmeRefVGO() {
    if(value && bfmeDecVGO(value)==0) bfmeDropVGO(value);
}

class Rva006D07E0Key
{
public:
	Rva006D07E0Key(void *value) : m_value(value) {}
    // The incoming animation handle and the manager's neutral key view both
    // own the pointer at +0. Acquire explicitly when handing that ownership on.
    __declspec(dllimport) __forceinline Rva006D07E0Key(const BfmeRefVGO &other):m_value(other.value) {
        if(m_value) Rva00894D80Accessor::increment((unsigned int *)m_value);
    }
	// Inlined by the rowed caller; dllimport keeps cl from emitting a stray
	// out-of-line copy that differs from retail's 0x006CFE80 (no reference uses it).
	__declspec(dllimport) __forceinline Rva006D07E0Key(const Rva006D07E0Key &other) : m_value(other.m_value)
	{
		if (m_value)
			Rva00894D80Accessor::increment((unsigned int *)m_value);
	}
	// Keep the inlined teardown without emitting an unused private destructor
	// copy that differs from the already owned out-of-line implementation.
	__declspec(dllimport) __forceinline ~Rva006D07E0Key()
	{
		if (m_value && bfmeDecVGO((unsigned int *)m_value) == 0)
			bfmeDropVGO(m_value);
	}

	void *m_value;
};

class Rva008951B0Node;
#include "../../Include/Common/Rva008951B0Owner.h"

class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
// g_rva00893030Manager: matched references place it at VA 0xe176cc (zero-filled .bss).
Rva00893030Manager * g_rva00893030Manager;

void Rva00893030(BfmeRefVGO value, void *first, void *second, void *third)
{
	((Rva008951B0Owner *)g_rva00893030Manager)->rva006D25C0(Rva006D07E0Key(value), first, second, third);
}
