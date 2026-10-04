// cl: /arch:SSE /MD /DNDEBUG
//
// Argument field setters found in vtable slots with no ledger owner: each
// stores its one stack argument (a float, a byte or a dword) at a fixed
// displacement from `this` and returns (ret 4). The same shapes as the
// Disp*FieldSetters units (disp8 and disp32 forms; the float ones need
// /arch:SSE for the movss pair); identity is not recoverable from the bytes,
// so every name is derived from its address.
#define BFME_ARG_FIELD_SETTER(NAME, TYPE, DISP) \
	class NAME \
	{ \
	public: \
		void set(TYPE value); \
		char m_lead[DISP]; \
		TYPE m_value; \
	}; \
	void NAME::set(TYPE value) \
	{ \
		m_value = value; \
	}

BFME_ARG_FIELD_SETTER(Rva0008BB4AFloatField, float, 0x54)
BFME_ARG_FIELD_SETTER(Rva0008BB6FFloatField, float, 0x68)
BFME_ARG_FIELD_SETTER(Rva0008BB93FloatField, float, 0x70)
BFME_ARG_FIELD_SETTER(Rva00101CBEFloatField, float, 0x8)
BFME_ARG_FIELD_SETTER(Rva003ACAECFloatField, float, 0x34)
BFME_ARG_FIELD_SETTER(Rva00101CB0FloatField, float, 0x4)
BFME_ARG_FIELD_SETTER(Rva00101CCCFloatField, float, 0xC)
BFME_ARG_FIELD_SETTER(Rva00101CE8FloatField, float, 0x14)
BFME_ARG_FIELD_SETTER(Rva0025EF0AFloatField, float, 0x40)
BFME_ARG_FIELD_SETTER(Rva0008BC6BFloatField, float, 0x9C)
BFME_ARG_FIELD_SETTER(Rva0008BC7CFloatField, float, 0xA4)
BFME_ARG_FIELD_SETTER(Rva0009ACA7FloatField, float, 0x11C)
BFME_ARG_FIELD_SETTER(Rva003B23CDByteSlot, unsigned char, 0x4D)
BFME_ARG_FIELD_SETTER(Rva00049F2BByteSlot, unsigned char, 0x18)
BFME_ARG_FIELD_SETTER(Rva0008BB3CByteSlot, unsigned char, 0x75)
BFME_ARG_FIELD_SETTER(Rva0008BB85ByteSlot, unsigned char, 0x74)
BFME_ARG_FIELD_SETTER(Rva002B2420ByteSlot, unsigned char, 0x44)
BFME_ARG_FIELD_SETTER(Rva0009AA01ByteSlot, unsigned char, 0x19)
BFME_ARG_FIELD_SETTER(Rva00210CD3ByteSlot, unsigned char, 0x20)
BFME_ARG_FIELD_SETTER(Rva002B22A5DwordSlot, int, 0x14)
BFME_ARG_FIELD_SETTER(Rva002E067DDwordSlot, int, 0x54)
BFME_ARG_FIELD_SETTER(Rva002E640BDwordSlot, int, 0x40)
