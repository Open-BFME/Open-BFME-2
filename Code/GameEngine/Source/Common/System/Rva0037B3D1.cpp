// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037B3D1@Rva0037B3D1@@QAEXXZ retail 0x0037B3D1 38B.
// Close helper: if FILE at +0x10 is set fclose it and null it then clear UnicodeString at +0x14 via rowed releaseBuffer 0x36E70 then tail-call virtual slot1.
// Evidence: callees rowed 0x36E70 plus IAT fclose; caller 0x0043684C; neighbours Rva0037B287Write and Rva0037B5DFDtor same flags.
#include "unicode_string.h"

struct FILE;
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *stream);

class Rva0037B3D1
{
public:
	virtual void slot0();
	virtual void slot1();
	void rva0037B3D1();
private:
	char m_pad04[0x0C]; // +0x04..+0x0F
	FILE *m_file10; // +0x10
	UnicodeString m_str14; // +0x14
};

void Rva0037B3D1::rva0037B3D1()
{
	if (m_file10 != 0) {
		fclose(m_file10);
		m_file10 = 0;
	}
	m_str14.clear();
	return slot1();
}
