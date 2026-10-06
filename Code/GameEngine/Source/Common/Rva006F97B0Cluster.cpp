// cl: /DNDEBUG /MD
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006F97B0
{
public:
	void rva006F97B0();
private:
	char m_pad[0x5c];
	unsigned int m_nZombieCounter : 16;
};

void Rva006F97B0::rva006F97B0()
{
	if (m_nZombieCounter >= 65536) {
		g_bfmeAptAssertAtE17734("nZombieCounter < 65536", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x53);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	++m_nZombieCounter;
}
