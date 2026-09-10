// ?baseConstruct@BFME2NativeNetwork@@QAEXXZ
// partial score=0.6 date=2026-09-09
// cl: /O1 /DNDEBUG /MD
//
// BFME2NativeNetwork::baseConstruct, retail 0x001B4E63, 17 bytes.
// Kept out of NetworkInterfaceConstructor.cpp so construct() cannot
// see this body (matching.md callee-visibility trap).
// Retail: mov eax,ecx / mov [eax],vtable / and [eax+8],0 / mov byte [eax+4],0 / ret

class BFME2NativeNetwork
{
	void *m_vtable;
	bool m_flag4;
	int m_field8;

public:
	void baseConstruct();
};

void BFME2NativeNetwork::baseConstruct()
{
	BFME2NativeNetwork *p = this;
	p->m_vtable = (void *)0x00BD77A0;
	p->m_field8 = 0;
	p->m_flag4 = false;
}
