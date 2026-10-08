// cl: /O1 /arch:SSE /G7 /EHsc /MD
//
// ?Rva00464081ParseMask@@YAXPAVINI@@PAX1PBX@Z, retail 0x00464081..0x004640BE
// (61 bytes, cdecl): an INI field parser for a 16-byte bit mask. A cleared
// mask (memset) is filled by the rowed parser 0x003B1017 -- Disp8SarAvg
// DwordGetters.cpp's Rva003B1017, which reads the KindOf-style name list --
// then copied into the field, and the owning instance's +0x86 flag records
// that the field was given. The field and owner names are not known; no
// WorldBuilder twin was matched.

extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);

class INI;

class Rva003B1017
{
public:
	Rva003B1017() { memset(m_words, 0, sizeof(m_words)); }
	void rva003B1017(INI *ini, void *extra);
private:
	unsigned int m_words[4];
};

struct Rva00464081Owner
{
	unsigned char m_pad00[0x86];
	bool m_maskGiven86;
};

void Rva00464081ParseMask(INI *ini, void *instance, void *store, const void * /*userData*/)
{
	Rva003B1017 mask;
	mask.rva003B1017(ini, 0);
	*(Rva003B1017 *)store = mask;
	((Rva00464081Owner *)instance)->m_maskGiven86 = true;
}
