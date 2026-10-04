// cl: /DNDEBUG /MD /EHsc
//
// Address-derived recovery of the 114-byte string-format helper at RVA
// 0x006D7010. The body calls the msvcr71 vsprintf import thunk (0x00629A7E,
// rowed as ?ji_00629a7e@@YAXXZ, slot 0x00BBA4E0) with the global format buffer
// at 0x00E17820, builds a temporary EAStringC from that buffer through the
// rowed ??0EAStringC@@QAE@PBD@Z (0x006D4C80), assigns it into the EAStringC
// member at owner+8 through the rowed ??4EAStringC@@QAEAAV0@ABV0@@Z
// (0x006D3030) and destroys the temporary through ??1EAStringC@@QAE@XZ
// (0x006D3010). No call site names the helper, so the function and its owner
// are address-derived.

extern "C" int __cdecl vsprintf(char *buf, const char *fmt, char *args);

class EAStringC
{
public:
	EAStringC(const char *text);
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();

private:
	void *m_pData;
};

class Rva006D7010Owner
{
public:
	char m_bfmePad[8];
	EAStringC m_bfmeString;
};

// Native DIR32 operands at +0x21 and +0x2E both identify VA 0x00E17820.
// INIException owns a separate buffer at VA 0x00DDF9D0; capacity here is unproven.
char Va00E17820FormatBuffer[2048];

// ?rva006D7010@@YAXPAVRva006D7010Owner@@PBDZZ
void rva006D7010(Rva006D7010Owner *owner, const char *fmt, ...)
{
	vsprintf(Va00E17820FormatBuffer, fmt, (char *)(&fmt + 1));
	EAStringC temp(Va00E17820FormatBuffer);
	owner->m_bfmeString = temp;
}
