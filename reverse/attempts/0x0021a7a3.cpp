// ?Rva0021A7A3Parse@@YAXPAVINI@@PAXPAVRva0014921EVector@@PBX@Z
// partial score=0.97 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?Rva0021A7A3Parse@@YAXPAVINI@@PAXPAVRva0014921EVector@@PBX@Z @0x0021A7A3 181B
// Free INI field parser for the "Awards" slot at 0x009B9FDC (neighbour "Awards").
// Parses a NameKey list via rowed worker 0x00149002 then validates each key
// against the award manager vector at g_00E02F74 via rowed find 0x0040AAD5.
// Unknown keys throw INIException "The Award %s does not exist..." with the
// keyToName spelling. Signature follows the 4-arg INI parser shape
// (INI* ini, void* instance, vector* store, const void* userData).
#include "ascii_string.h"

class INI;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva0014921EVector
{
public:
	NameKeyType *m_begin;
	NameKeyType *m_end;
};

void rva00149002(int a, int b, Rva0014921EVector *buffer, int d);

struct BfmePod40
{
	int a[10];
};

class Rva0040AAD5
{
public:
	BfmePod40 *rva0040AAD5(int key);
};

extern Rva0040AAD5 *g_00E02F74;

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

// ?Rva0021A7A3Parse@@YAXPAVINI@@PAXPAVRva0014921EVector@@PBX@Z
void Rva0021A7A3Parse(INI *ini, void *instance, Rva0014921EVector *store, const void *userData)
{
	bool flag = true;
	rva00149002((int)ini, 0, store, (int)&flag);
	for (unsigned int i = 0; i < (unsigned int)(store->m_end - store->m_begin); ++i) {
		if (!g_00E02F74->rva0040AAD5(store->m_begin[i])) {
			_ReadWriteBarrier();
			AsciiString name = TheNameKeyGenerator->keyToName(store->m_begin[i]);
			throw INIException(3, "The Award %s does not exist in the AwardSystemManager.", name.str());
		}
	}
}
