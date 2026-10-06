// cl: /DNDEBUG /MD
// ?rva006F7540@Rva006F7540@@QAEXXZ @0x006F7540 45B. AptDisplayList empty
// check: count at +0x80, assert "nElements == 0" at AptDisplayList.cpp:0x537.
// Same class and assert shape as Rva006F7600Remove.cpp (AptDisplayList).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006F7540
{
public:
	void rva006F7540();
private:
	void *m_items[32];
	int m_nElements;
};

void Rva006F7540::rva006F7540()
{
	if (m_nElements != 0) {
		g_bfmeAptAssertAtE17734("nElements == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp", 0x537);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
}
