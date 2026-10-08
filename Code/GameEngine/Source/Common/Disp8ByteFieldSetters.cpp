// Disp8 byte setters: ten-byte __thiscall members with one shape:
//
//     mov al,[esp+4] / mov [ecx+<DISP>],al / ret 4
//
// One byte is taken from the stack argument slot and stored at a fixed
// displacement from `this`. Same macro as DispByteFieldSetters.cpp; every
// displacement here fits disp8 (MSVC 7.1 uses disp8 whenever the offset
// fits, so every offset is below 0x80).
// Identity is not recovered: every name is derived from its address,
// following DispByteFieldSetters.cpp.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_BYTE_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(unsigned char value); \
		char m_lead[DISP]; \
		unsigned char m_value; \
	}; \
	void NAME::set(unsigned char value) \
	{ \
		m_value = value; \
	}

BFME_DISP8_BYTE_SETTER(Rva00318D14ByteSlot, 0x58)
BFME_DISP8_BYTE_SETTER(Rva004D576CByteSlot, 0x1E)
BFME_DISP8_BYTE_SETTER(Rva004D5984ByteSlot, 0x22)
BFME_DISP8_BYTE_SETTER(Rva00050CCEByteSlot, 0x4B)

// BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 clean GameSlot::mute
// (SkirmishGameInfo_xfer.cpp) guides the expression only. Native
// 0x004E3FF0..0x004E3FFA follows INT3 and ends RET4: copy the stack
// argument's low byte to receiver+0x0A. Owner and field purpose unknown.
BFME_DISP8_BYTE_SETTER(Rva004E3FF0ByteSlot, 0x0A)

// BF1 9cb's LANAPIhandlers.cpp GameInfo::setGameInProgress supplies the
// same expression, without proving its name or bool type here. Native
// 0x002E6A9D..0x002E6AA7 follows an independently rowed RET4 and ends
// RET4 before the next getter: store the raw argument byte at receiver+0x0D.
// Original owner and field purpose remain unresolved.
BFME_DISP8_BYTE_SETTER(Rva002E6A9DByteSlot, 0x0D)
