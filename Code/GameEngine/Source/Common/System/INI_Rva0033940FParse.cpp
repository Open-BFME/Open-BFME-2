// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi-
// ?Rva0033940F_Parse@INI@@SAXPAV1@PAX1PBX@Z, retail 0x0033940F, 236 bytes.
// INI parse callback in the same family as INI_parseMappedImage (0x003390B2)
// and INI_parseWeaponTemplate (0x00339569): getNextToken, throw ERROR_BUG
// when the ThingFactory collection (g_009FF000) is null, store null for
// "None", otherwise resolve through rowed rva002D06CA and report a missing
// entry through theDebug. Caller 0x002FEE2C passes (ini, 0, &store, 0) like
// parseInt. The callback name stays address-derived.

#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void Rva0033940F_Parse(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
	class Format
	{
	public:
		Format(const char *format, ...);
		char m_buffer[512];
	};
	Debug &operator<<(const Format &f) { return operator<<(f.m_buffer); }
};

extern Debug *theDebug;
void __cdecl _bfme_debugRecordCallsite(int kind);
bool __cdecl bfmeRva000387C0(void);
extern const char g_00C0EA88[];

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0000)
};

void INI::Rva0033940F_Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken(0);
	if (TheThingFactory == 0) {
		throw ERROR_BUG;
	}
	if (_strcmpi(token, "None") == 0) {
		*(void **)store = 0;
		return;
	}
	void *result = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&AsciiString(token));
	if (result == 0 && bfmeRva000387C0()) {
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		Debug &dbg = theDebug->CrashBegin(0, 0, 0);
		dbg << Debug::Format(g_00C0EA88, token);
		dbg.CrashDone(2);
	}
	*(void **)store = result;
}
