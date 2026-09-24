// cl: /O1 /G7
// Disp8 imul-add dword getters: twelve-byte __thiscall members with one shape:
//
//     mov eax,[esp+4] / imul eax,eax,<IMM> / add eax,[ecx] / ret 4
//
// A stack-passed integer is scaled by a small immediate and biased by the
// dword at `this`. MSVC 7.1 emits `8B 44 24 04` + `6B C0 XX` + `03 01`,
// plus `ret 4` for the single callee-cleaned stack argument, for twelve
// bytes total. /O1 keeps the memory-add after the multiply; /O2 hoists the
// member load into edx first. /G7 keeps small multipliers as true `imul`
// (/O1 alone strength-reduces them to lea sequences). Identity is not
// recovered: every name is derived from its address.
#define BFME_IMUL_ADD_DWORD_GETTER(NAME, IMM) \
	class NAME \
	{ \
	public: \
		int get(int scale) const; \
		int m_value; \
	}; \
	int NAME::get(int scale) const \
	{ \
		return scale * IMM + m_value; \
	}

BFME_IMUL_ADD_DWORD_GETTER(Rva0004686FImulAddField, 0x5C)
BFME_IMUL_ADD_DWORD_GETTER(Rva0007E95EImulAddField, 0x0C)
BFME_IMUL_ADD_DWORD_GETTER(Rva0014F3B8ImulAddField, 0x4C)
BFME_IMUL_ADD_DWORD_GETTER(Rva001DD2A7ImulAddField, 0x30)
BFME_IMUL_ADD_DWORD_GETTER(Rva001DD2B3ImulAddField, 0x34)
