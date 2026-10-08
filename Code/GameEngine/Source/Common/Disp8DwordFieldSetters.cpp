// Disp8 dword setters: ten-byte __thiscall members with one shape:
//
//     mov eax,[esp+4] / mov [ecx+<DISP>],eax / ret 4
//
// One dword is taken from the stack argument slot and stored at a fixed
// displacement from `this`. Same macro as DispDwordFieldSetters.cpp; every
// displacement here fits disp8 (MSVC 7.1 uses disp8 whenever the offset
// fits, so every offset is below 0x80).
// Identity is not recovered: every name is derived from its address,
// following DispDwordFieldSetters.cpp.
// No // cl: line (defaults match the frameless ten-byte shape).
#define BFME_DISP8_DWORD_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(int value); \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	void NAME::set(int value) \
	{ \
		m_value = value; \
	}

BFME_DISP8_DWORD_SETTER(Rva002D94FEDwordSlot, 0x74)
BFME_DISP8_DWORD_SETTER(Rva0033F15DDwordSlot, 0x6C)
BFME_DISP8_DWORD_SETTER(Rva003FF0E7DwordSlot, 0x5C)
BFME_DISP8_DWORD_SETTER(Rva00050CADDwordSlot, 0x78)
BFME_DISP8_DWORD_SETTER(Rva00050CB7DwordSlot, 0x7C)
BFME_DISP8_DWORD_SETTER(Rva0050E7E1DwordSlot, 0x58)
BFME_DISP8_DWORD_SETTER(Rva0065ECC0DwordSlot, 0x50)

// BF1 9cb WWDownload/CDownloadDownloadFile.cpp RestartFrom supplies the
// store-and-zero-return expression only. Complete native6C9630..6C963C
// lies between INT3 padding: raw32 argument to receiver2C then EAX0 RET4.
// Original receiver, field purpose and return type remain unknown.
class Rva006C9630DwordSlot
{
public:
    unsigned int store(unsigned int value);
private:
    char unknown00[0x2C];
    unsigned int value2C;
};
unsigned int Rva006C9630DwordSlot::store(unsigned int value)
{
    value2C = value;
    return 0;
}
