// Disp0 dword getters: three-byte __thiscall members with one shape:
//
//     mov eax,[ecx] / ret
//
// One dword is read at offset zero from `this` and returned. Members after
// the accessed one are not witnessed here. Identity is not recovered: every
// name is derived from its address.
// No // cl: line (defaults match the frameless three-byte shape).
#define BFME_DISP0_DWORD_GETTER(NAME) \
	class NAME \
	{ \
	public: \
		int get() const; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value; \
	}

BFME_DISP0_DWORD_GETTER(Rva001816E0DwordField)
