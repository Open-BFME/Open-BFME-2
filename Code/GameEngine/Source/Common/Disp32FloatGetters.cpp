// Disp32 float getters: seven-byte __thiscall members with one shape:
//
//     fld dword [ecx+<DISP>] / ret
//
// One float is read at a fixed 32-bit displacement from `this` and returned
// in ST0. The offset does not fit the sign-byte form, so MSVC 7.1 emits
// `D9 81 DISP32`, plus `ret`, for seven bytes total. This is the disp32
// sibling of the float-getter lane; the opcode itself is why it lives in
// its own translation unit. Identity is not recovered: every name is
// derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP32_FLOAT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		float get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	float NAME::get() const \
	{ \
		return m_value; \
	}
BFME_DISP32_FLOAT_GETTER(Rva0006659DFloatField, 0x37DC)
BFME_DISP32_FLOAT_GETTER(Rva000879E6FloatField, 0x24F4)
BFME_DISP32_FLOAT_GETTER(Rva0008BC5DFloatField, 0x9C)
BFME_DISP32_FLOAT_GETTER(Rva0009ACA0FloatField, 0x11C)
BFME_DISP32_FLOAT_GETTER(Rva000ABD4FFloatField, 0x37E4)
BFME_DISP32_FLOAT_GETTER(Rva000B2286FloatField, 0x280)
BFME_DISP32_FLOAT_GETTER(Rva000E9DFCFloatField, 0x1918)
BFME_DISP32_FLOAT_GETTER(Rva00167EA3FloatField, 0xFC)
BFME_DISP32_FLOAT_GETTER(Rva00167ED1FloatField, 0xEC)
BFME_DISP32_FLOAT_GETTER(Rva001E37E1FloatField, 0x1F8)
BFME_DISP32_FLOAT_GETTER(Rva001E3809FloatField, 0x538)
BFME_DISP32_FLOAT_GETTER(Rva0028A8E2FloatField, 0x4C8)
BFME_DISP32_FLOAT_GETTER(Rva0028BB86FloatField, 0x1B8)
BFME_DISP32_FLOAT_GETTER(Rva002C5820FloatField, 0x560)
BFME_DISP32_FLOAT_GETTER(Rva002DABF0FloatField, 0x144)
BFME_DISP32_FLOAT_GETTER(Rva00376CC9FloatField, 0x324)
BFME_DISP32_FLOAT_GETTER(Rva0052E4C2FloatField, 0x4A4)
BFME_DISP32_FLOAT_GETTER(Rva0053916BFloatField, 0xB4)
BFME_DISP32_FLOAT_GETTER(Rva0055F4AEFloatField, 0x17C)
BFME_DISP32_FLOAT_GETTER(Rva00561F07FloatField, 0x184)
