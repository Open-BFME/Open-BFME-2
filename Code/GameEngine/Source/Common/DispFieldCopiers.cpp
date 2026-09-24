// Field copiers: ten-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<SRC>] / mov [ecx+<DST>],eax / ret
//
// One int is read at a fixed displacement from `this` and stored at a
// second displacement. Members before, between and after the accessed ones
// are spelled as lead arrays because their types are not witnessed here,
// only their total size. Identity is not recovered: every name is derived
// from its address.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_FIELD_COPIER(NAME, SRC, DST) \
	class NAME \
	{ \
	public: \
		void copy(); \
		char m_lead[SRC]; \
		int m_src; \
		char m_mid[(DST) - (SRC) - 4]; \
		int m_dst; \
	}; \
	void NAME::copy() \
	{ \
		m_dst = m_src; \
	}

BFME_FIELD_COPIER(Rva0028A5F9FieldCopy, 0x40, 0x180)
