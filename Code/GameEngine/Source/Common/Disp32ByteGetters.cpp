// Disp32 byte getters: seven-byte __thiscall members with one shape:
//
//     mov al,[ecx+<DISP>] / ret
//
// One byte is read at a fixed 32-bit displacement from `this` and returned
// in `al` (only the low byte is defined; the caller uses `al`). The offset
// does not fit the sign-byte form, so MSVC 7.1 emits `8A 81 DISP32`, plus
// `ret`, for seven bytes total. This is the disp32 sibling of the
// byte-getter lane; the opcode itself is why it lives in its own
// translation unit. Identity is not recovered: every name is derived from
// its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP32_BYTE_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return m_value; \
	}
BFME_DISP32_BYTE_GETTER(Rva00203BDAByteField, 0x1A4D7)
BFME_DISP32_BYTE_GETTER(Rva002259E8ByteField, 0x9D)
BFME_DISP32_BYTE_GETTER(Rva0023C411ByteField, 0x11D)
BFME_DISP32_BYTE_GETTER(Rva002622A9ByteField, 0x614)
BFME_DISP32_BYTE_GETTER(Rva00262304ByteField, 0x3BA)
BFME_DISP32_BYTE_GETTER(Rva0026234FByteField, 0x3CC)
BFME_DISP32_BYTE_GETTER(Rva0026FC5CByteField, 0x9A)
BFME_DISP32_BYTE_GETTER(Rva0026FCE5ByteField, 0x43F)
BFME_DISP32_BYTE_GETTER(Rva0029A268ByteField, 0x278)
BFME_DISP32_BYTE_GETTER(Rva002A9DA5ByteField, 0x33C)
BFME_DISP32_BYTE_GETTER(Rva002B223DByteField, 0x88)
BFME_DISP32_BYTE_GETTER(Rva002B22F3ByteField, 0x10B)
BFME_DISP32_BYTE_GETTER(Rva002B2319ByteField, 0xC8)
BFME_DISP32_BYTE_GETTER(Rva002B232DByteField, 0x168)
BFME_DISP32_BYTE_GETTER(Rva002B242AByteField, 0x2C0)
BFME_DISP32_BYTE_GETTER(Rva002C74ABByteField, 0x35C)
BFME_DISP32_BYTE_GETTER(Rva002D9487ByteField, 0x44A)
BFME_DISP32_BYTE_GETTER(Rva0030EC75ByteField, 0x8B9)
BFME_DISP32_BYTE_GETTER(Rva0033F167ByteField, 0x33D)
BFME_DISP32_BYTE_GETTER(Rva0033F939ByteField, 0x3C8)
BFME_DISP32_BYTE_GETTER(Rva0033F99CByteField, 0x5FD)
BFME_DISP32_BYTE_GETTER(Rva00367487ByteField, 0x558)
BFME_DISP32_BYTE_GETTER(Rva00376D10ByteField, 0x174)
BFME_DISP32_BYTE_GETTER(Rva00381D56ByteField, 0xFEC)
BFME_DISP32_BYTE_GETTER(Rva00381D6AByteField, 0xFED)
BFME_DISP32_BYTE_GETTER(Rva00381E1FByteField, 0x5CC)
BFME_DISP32_BYTE_GETTER(Rva00386125ByteField, 0x163C)
BFME_DISP32_BYTE_GETTER(Rva00388995ByteField, 0x49C)
BFME_DISP32_BYTE_GETTER(Rva0039D48EByteField, 0x31E)
BFME_DISP32_BYTE_GETTER(Rva0039D525ByteField, 0x3BE)
BFME_DISP32_BYTE_GETTER(Rva0039D7C1ByteField, 0x324)
BFME_DISP32_BYTE_GETTER(Rva003B23D7ByteField, 0x1A4DA)
BFME_DISP32_BYTE_GETTER(Rva003BA61AByteField, 0x339)
BFME_DISP32_BYTE_GETTER(Rva003BA6A2ByteField, 0xDE)
BFME_DISP32_BYTE_GETTER(Rva003FD16CByteField, 0xAC)
BFME_DISP32_BYTE_GETTER(Rva004318A1ByteField, 0x9B4)
BFME_DISP32_BYTE_GETTER(Rva0044951BByteField, 0xF68)
BFME_DISP32_BYTE_GETTER(Rva0046F859ByteField, 0x190)
BFME_DISP32_BYTE_GETTER(Rva0047C033ByteField, 0x104)
BFME_DISP32_BYTE_GETTER(Rva004A9B9CByteField, 0xD6)
BFME_DISP32_BYTE_GETTER(Rva004A9BB0ByteField, 0xD4)
BFME_DISP32_BYTE_GETTER(Rva004B0CE8ByteField, 0x18D)
BFME_DISP32_BYTE_GETTER(Rva004B872BByteField, 0x735)
BFME_DISP32_BYTE_GETTER(Rva004BF8D8ByteField, 0xB7)
BFME_DISP32_BYTE_GETTER(Rva004EF33BByteField, 0x338)
BFME_DISP32_BYTE_GETTER(Rva004F0307ByteField, 0x110)
BFME_DISP32_BYTE_GETTER(Rva0052BAABByteField, 0xB4)
BFME_DISP32_BYTE_GETTER(Rva0053B8DEByteField, 0x43B)
BFME_DISP32_BYTE_GETTER(Rva0055D968ByteField, 0x194)
BFME_DISP32_BYTE_GETTER(Rva0056285EByteField, 0x1A0)

// Clean BF1 9cbfb551fe Common/Rva003CBA00Indexed.cpp semantic donor, normal O1/SSE/G7.
// Native 0029A25D..0029A268 has its own complete RET boundary and establishes
// receiver10 indexed dword load, RET4. Original owner and full array bound remain
// unresolved; this separate address-owned view models only observed accesses.
class Rva0029A25DArray {
public: int getValue(int index);
private: unsigned char unknown[0x10]; int values[1];
};
int Rva0029A25DArray::getValue(int index) { return values[index]; }

// BF1 9cbfb551fe Common/Rva0028ED50Get.cpp is the clean semantic donor.
// Full native leaf 004B0CEF..004B0CFD ends at its own RET boundary.
// Target evidence: receiver4 pointer; inner0C dword not zero.
// Original owner unresolved; the address-owned type is independent of nearby classes.
struct Rva004B0CEFInner { char unknown[0x0C]; int value; };
class Rva004B0CEFFields {
public: bool get();
private: char unknown[4]; Rva004B0CEFInner *inner;
};
bool Rva004B0CEFFields::get() { return inner->value != 0; }

// BF1 9cbfb551fe Common/Rva0028ED70Nz.cpp is the clean semantic donor.
// Full native leaf 004B0CFD..004B0D0C ends at its own RET boundary.
// Target evidence: receiver4 pointer; inner4C dword not all ones.
// Original owner unresolved; the address-owned type is independent of nearby classes.
struct Rva004B0CFDInner { char unknown[0x4C]; int value; };
class Rva004B0CFDFields {
public: bool get();
private: char unknown[4]; Rva004B0CFDInner *inner;
};
bool Rva004B0CFDFields::get() { return inner->value != -1; }

// BF1 9cb Rva18C170NestedFloatGetter.cpp is a structural guide. Complete
// target 262356..26235C follows the adjacent getter RET; receiver+8 points
// to the float loaded into ST0. Original owner and full bounds unknown.
struct Rva00262356Fields
{
    char unknown00[8];
    const float *pointer;
    float get() const;
};
float Rva00262356Fields::get() const { return *pointer; }
