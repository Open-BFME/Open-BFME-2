// cl: /MD
// ?rva00232F4F@Rva00232F4F@@QAEXXZ, retail 0x00232F4F, 46 bytes. IME property
// gate beside Rva00232F0C: GetKeyboardLayout(0) then rowed ImmGetProperty
// thunk 0x00655622 with index 4; bit 0x12 selects dword field +0x3030 and
// bit 0x13 selects byte field +0x3048. Next row getters read +0x3030.

extern "C" __declspec(dllimport) void *__stdcall GetKeyboardLayout(unsigned long threadId);

unsigned long __stdcall ji_00655622(void *hkl, unsigned long index);
#pragma comment(linker, "/alternatename:?ji_00655622@@YGKPAXK@Z=?ji_00655622@@YAXXZ")

class Rva00232F4F
{
	char m_pad[0x3030];
public:
	int m_3030;
	char m_pad2[0x3048 - 0x3030 - 4];
	unsigned char m_3048;
	void rva00232F4F();
};

void Rva00232F4F::rva00232F4F()
{
	void *hkl = GetKeyboardLayout(0);
	unsigned long props = ji_00655622(hkl, 4);
	m_3030 = (props >> 0x12) & 1;
	m_3048 = (unsigned char)((props >> 0x13) & 1);
}
