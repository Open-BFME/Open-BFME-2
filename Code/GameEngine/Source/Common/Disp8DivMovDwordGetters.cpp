// Disp8 div-mov dword getters: fourteen-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / sub eax,[ecx+<DISP2>] / mov ecx,<DIV>
//     cdq / idiv ecx / ret
//
// The difference of two dwords at fixed displacements from `this` is divided
// by a constant. MSVC 7.1 under /O1 materializes small divisors through the
// stack (`push imm8` + `pop ecx`, three bytes; the DivAvg sister TU) but
// large divisors (>=0x80, needing `push imm32` + `pop`, six bytes) via
// `mov ecx,imm32` (five bytes). All divisors here need imm32, so /O1 emits
// mov. Fourteen-to-fifteen bytes total. Identity is not recovered: every
// name is derived from its address.
// cl: /O1
#define BFME_DISP8_DIV_MOV_DWORD_GETTER(NAME, DISP1, DISP2, DIVISOR) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP1]; \
		int m_first; \
	}; \
	int NAME::get() const \
	{ \
		return (m_first - *(int *)((char *)this + DISP2)) / DIVISOR; \
	}

BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva00051A6BDivMovField, 0x04, 0x00, 0x90)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva00087A36DivMovField, 0x04, 0x00, 0xB8)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva000B3F67DivMovField, 0x04, 0x00, 0xFC)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva000B4071DivMovField, 0x04, 0x00, 0xB4)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva000B40BDDivMovField, 0x04, 0x00, 0xF8)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva001EAEAFDivMovField, 0x04, 0x00, 0xAC)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva001EAEEBDivMovField, 0x08, 0x00, 0xAC)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva001FD252DivMovField, 0x04, 0x00, 0x1DC)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva002196CBDivMovField, 0x18, 0x14, 0xD8)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva002CF012DivMovField, 0x04, 0x00, 0x368)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva002CF020DivMovField, 0x08, 0x00, 0x368)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva002CF02EDivMovField, 0x04, 0x00, 0x104)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva002CF03CDivMovField, 0x08, 0x00, 0x104)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva002E0856DivMovField, 0x08, 0x00, 0xD8)
BFME_DISP8_DIV_MOV_DWORD_GETTER(Rva00360C37DivMovField, 0x04, 0x00, 0x94)
