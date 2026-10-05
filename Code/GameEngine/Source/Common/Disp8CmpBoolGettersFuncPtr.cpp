// Two disp32 compare bool getters split out of Disp8CmpBoolGetters.cpp: each
// tests the dword at this+0x1E0 against a code address (retail compares it
// with the immediates 0x008020CE and 0x00727E5D; the latter is
// GadgetPushButtonInput's entry, so +0x1E0 is most likely a GameWindow input
// callback). Neither callback has a matched body yet, so the immediates stay
// literal here and only these two rows wait on them; the rest of the family
// links. Identity is not recovered: names derive from the addresses.
// cl: /O1

#define BFME_DISP8_CMP_IMM_BOOL_GETTER(NAME, DISP, IMM, OP) \
	class NAME \
	{ \
	public: \
		bool get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	bool NAME::get() const \
	{ \
		return m_value OP IMM; \
	}

BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva00313913CmpBoolField, 0x1E0, 0x8020CE, ==)
BFME_DISP8_CMP_IMM_BOOL_GETTER(Rva0031393ACmpBoolField, 0x1E0, 0x727E5D, ==)
