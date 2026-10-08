// Disp8 byte flag setters: five-byte __thiscall members with one shape:
//
//     mov byte ptr [ecx+<DISP>],<IMM8> / ret
//
// One byte at a fixed displacement from `this` is set to a hardcoded
// immediate (0 or 1 in every body found so far) and nothing is read back.
// This is the small-offset sibling of the disp32 family in
// DispByteOneSetters.cpp (MSVC 7.1 uses disp8 whenever the offset fits, so
// every offset here fits in a signed byte). Members before the accessed one
// are spelled as a lead array because their types are not witnessed here,
// only their total size. Identity is not recovered: every name is derived
// from its address.
// No // cl: line (defaults match the frameless five-byte shape).
#define BFME_DISP8_BYTE_ONE_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void enable(); \
		char m_lead[DISP]; \
		unsigned char m_enabled; \
	}; \
	void NAME::enable() \
	{ \
		m_enabled = 1; \
	}

#define BFME_DISP8_BYTE_ZERO_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void disable(); \
		char m_lead[DISP]; \
		unsigned char m_enabled; \
	}; \
	void NAME::disable() \
	{ \
		m_enabled = 0; \
	}

#define BFME_DISP8_BYTE_TWO_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(); \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	void NAME::set() \
	{ \
		m_value = 2; \
	}

BFME_DISP8_BYTE_ONE_SETTER(Rva000D4A7COneSetter, 0x4D)
BFME_DISP8_BYTE_ONE_SETTER(Rva001DBB82OneSetter, 0x69)
BFME_DISP8_BYTE_ZERO_SETTER(Rva001DBB87ZeroSetter, 0x69)
BFME_DISP8_BYTE_ZERO_SETTER(Rva00420B2AZeroSetter, 0x08)
BFME_DISP8_BYTE_ONE_SETTER(Rva00050D06OneSetter, 0x4F)
BFME_DISP8_BYTE_ZERO_SETTER(Rva00050D0BZeroSetter, 0x4F)
BFME_DISP8_BYTE_ONE_SETTER(Rva000664EFOneSetter, 0x21)
BFME_DISP8_BYTE_ONE_SETTER(Rva00090753OneSetter, 0x52)
BFME_DISP8_BYTE_ONE_SETTER(Rva0009D6E8OneSetter, 0x25)
BFME_DISP8_BYTE_ZERO_SETTER(Rva0009D6F5ZeroSetter, 0x25)
BFME_DISP8_BYTE_ONE_SETTER(Rva00131075OneSetter, 0x0D)
BFME_DISP8_BYTE_ONE_SETTER(Rva00238D92OneSetter, 0x6C)
BFME_DISP8_BYTE_ONE_SETTER(Rva0025DD11OneSetter, 0x38)
BFME_DISP8_BYTE_ZERO_SETTER(Rva0025DD16ZeroSetter, 0x38)
BFME_DISP8_BYTE_ZERO_SETTER(Rva002886A2ZeroSetter, 0x24)
BFME_DISP8_BYTE_ONE_SETTER(Rva0028A813OneSetter, 0x28)
BFME_DISP8_BYTE_ONE_SETTER(Rva0028AA1COneSetter, 0x2C)
BFME_DISP8_BYTE_ONE_SETTER(Rva002B2361OneSetter, 0x75)
BFME_DISP8_BYTE_ONE_SETTER(Rva003860FAOneSetter, 0x04)
BFME_DISP8_BYTE_ZERO_SETTER(Rva0039ABE6ZeroSetter, 0x20)
BFME_DISP8_BYTE_ONE_SETTER(Rva00428DBCOneSetter, 0x51)
BFME_DISP8_BYTE_ONE_SETTER(Rva00433D22OneSetter, 0x54)
BFME_DISP8_BYTE_ZERO_SETTER(Rva0045F37DZeroSetter, 0x30)
BFME_DISP8_BYTE_ONE_SETTER(Rva004A18C0OneSetter, 0x24)
BFME_DISP8_BYTE_ONE_SETTER(Rva00050CDCOneSetter, 0x4C)
BFME_DISP8_BYTE_ONE_SETTER(Rva00050CF7OneSetter, 0x50)
BFME_DISP8_BYTE_ONE_SETTER(Rva00050CFCOneSetter, 0x53)
BFME_DISP8_BYTE_ZERO_SETTER(Rva00050D01ZeroSetter, 0x53)
BFME_DISP8_BYTE_TWO_SETTER(Rva0026FC9ETwoSetter, 0x38)
BFME_DISP8_BYTE_ONE_SETTER(Rva004D9362OneSetter, 0x20)
BFME_DISP8_BYTE_ONE_SETTER(Rva004F5FA7OneSetter, 0x18)
BFME_DISP8_BYTE_ONE_SETTER(Rva0050E7BBOneSetter, 0x10)
BFME_DISP8_BYTE_ZERO_SETTER(Rva0050E7C0ZeroSetter, 0x10)
BFME_DISP8_BYTE_ONE_SETTER(Rva00531113OneSetter, 0x35)
BFME_DISP8_BYTE_ZERO_SETTER(Rva00531118ZeroSetter, 0x35)
BFME_DISP8_BYTE_ZERO_SETTER(Rva0056B119ZeroSetter, 0x1C)
BFME_DISP8_BYTE_ONE_SETTER(Rva005C399EOneSetter, 0x45)
BFME_DISP8_BYTE_ZERO_SETTER(Rva006005D0ZeroSetter, 0x0C)
BFME_DISP8_BYTE_ZERO_SETTER(Rva00238D8DZeroSetter, 0x6C)
BFME_DISP8_BYTE_ONE_SETTER(Rva006005CBOneSetter, 0x0C)

// BF1 9cbfb551fe Common/Rva004021B0PositiveGetter.cpp is the clean semantic donor.
// Target 53110B..531113 RET0 followsRET4; signed dword0 greaterthan0 returnedAL
// Original owner/purpose is unproven; retain an independent address-owned type.
class Rva0053110BFields
{
public: bool isPositive() const;
private: int field00;
};
bool Rva0053110BFields::isPositive() const { return field00>0; }
