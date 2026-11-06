// cl: -GR- -EHsc- /Ireference/shims/bfme2_ascii
// ?Run@Rva005B5AC3Box@@QAEXXZ @0x005B5AC3 32B: non-negative one-shot. When
// +0x24 reads non-negative, forward AsciiString::TheEmptyString (VA
// 0x00DE0878) twice plus 0 through the pinned cdecl 3-arg callee, then set
// +0x24 to -1. Target read from retail REL32.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"
struct Rva005B5AC3Box
{
	char pad[0x24];
	int m_24;

	void Run();
	int rva005B5AE3(int msg, unsigned int key, unsigned int state);
};

void Rva005B23D7Wrap(int a, int b, int c);
void __cdecl Rva005B23D7HeroPowersDescription(void *a, const AsciiString &b, const AsciiString &c); // rowed 0x005B23D7
void __cdecl Rva00513866();

void Rva005B5AC3Box::Run()
{
	if (m_24 >= 0) {
		Rva005B23D7HeroPowersDescription((void*)0, AsciiString::TheEmptyString, AsciiString::TheEmptyString);
		m_24 |= -1;
	}
}

int Rva005B5AC3Box::rva005B5AE3(int msg, unsigned int key, unsigned int state)
{
	if (msg == 0x15 && (unsigned char)key == 1 && (state & 1) != 0) {
		Rva00513866();
		return 1;
	}
	return 0;
}

struct Rva005B5C70Box
{
	char pad[8];
	void *m_8;
	char pad2[0x15 - 0x0C];
	unsigned char m_15;

	void Run(int a);
	int rva005B5E03(int msg, void *win, int param);
};

int Rva005B5C70Box::rva005B5E03(int msg, void *win, int param)
{
	if (m_15 != 0)
		return 1;
	if (msg == 0x4014 && win == m_8) {
		Run(1);
		return 1;
	}
	return 0;
}

struct Rva005B6182Screen
{
	char pad[0x3c8];
	int m_3c8;
};

#include "../../Include/Common/AptCreateAHero.h"

class AptCreateAHero::Manager
{
public:
	void PopulateAwards();
	void rva005B5F2E();
	void rva005B6182(bool flag);
private:
	char pad0[4];
	Rva005B6182Screen *m_4;
	char pad8[0x14 - 8];
	bool m_14;
};

void AptCreateAHero::Manager::rva005B6182(bool flag)
{
	if (flag && m_14 && m_4->m_3c8 != 1) {
		m_14 = false;
		PopulateAwards();
		rva005B5F2E();
	}
}

