// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../Include/Common/Rva00894D80Accessor.h"

unsigned int bfmeDecVGO(unsigned int *value);
void bfmeDropVGO(void *value);

class BfmeRefVGO {
public:
    void *m_value;
    BfmeRefVGO(const BfmeRefVGO &other);
    ~BfmeRefVGO() {
        if(m_value && bfmeDecVGO((unsigned int *)m_value)==0) bfmeDropVGO(m_value);
    }
};

class Rva006D07E0Key
{
public:
	Rva006D07E0Key(void *value) : m_value(value) {}
    // The incoming animation handle and the manager's neutral key view both
    // own the pointer at +0. Acquire explicitly when handing that ownership on.
    __declspec(dllimport) __forceinline Rva006D07E0Key(const BfmeRefVGO &other):m_value(other.m_value) {
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

class Rva008951B0Owner
{
public:
	void rva006D25C0(Rva006D07E0Key value, void *first, void *second, void *third);
};

class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
// g_rva00893030Manager: matched references place it at VA 0xe176cc (zero-filled .bss).
Rva00893030Manager * g_rva00893030Manager;

void Rva00893030(BfmeRefVGO value, void *first, void *second, void *third)
{
	((Rva008951B0Owner *)g_rva00893030Manager)->rva006D25C0(Rva006D07E0Key(value), first, second, third);
}
