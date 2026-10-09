// cl: /MD /EHsc /DNDEBUG
//
// ?rva000A9211@@YAPAXPAX@Z @0x000A9211 45B: format-and-create. Fills a
// 0x100-byte stack buffer through AptPlayer::GetExtern at 0x00223E4B
// (this is the 0x00DFE4CC window-manager global) from the argument, then
// returns the rowed 0x006CB9D0 string factory's value for the buffer.
// Honest address-derived names; boundary verified (frame at 0xA9211,
// leave + ret at end).

class AptPlayer
{
public:
	void GetExtern(const char *name, char *buf);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

void *Rva006CB9D0(const char *s);

// ?rva000A9211@@YAPAXPAX@Z
void *rva000A9211(void *a)
{
	char buf[256];
	reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->GetExtern(static_cast<const char *>(a), buf);
	return Rva006CB9D0(buf);
}

#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
