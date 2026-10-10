// ?Rva004AEB84Parse@@YAXPAVINI@@PAX1PBX@Z
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Oi- /DNDEBUG /D_CRTIMP=
// stlport
// Native004AEB84..004AEC9A cdecl callback parses AnimState/AnimTime/RiderOCL records.
// The native vector append uses84-byte elements: 19 dword conditions, a
// duration at4C and OCL at50. DetachableRider's618-byte update consumes the
// same84-byte records from its ModuleData+8 vector; its owned buildFieldParse
// 4AEF05 registers this callback in the C55638 table at offset8. Name remains
// neutral; WeaponTemplateSet and BitFlags<304> are existing provider ABI
// spellings, not assertions about the target record's semantic type.
// Previous bank followed the BFME RiderInfo parser. Target constructor44B
// Rva0028F59A and existing append55B are independently rowed providers.
// INIException's8-byte object extent restores nativeA8 stack temporaries;
// its internal member interpretation remains unknown.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <string.h>

typedef unsigned int UnsignedInt;

extern "C" int __cdecl strcmp(const char *, const char *);

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseDurationUnsignedInt(INI *, void *, void *, const void *);
	static void parseObjectCreationList(INI *, void *, void *, const void *);
	const char *getSepsColon() const { return *(const char **)((const char *)this + 0x420); }
};

class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);
	~INIException();
private: unsigned opaque[2];
};

template<int N> class BitFlags
{
public:
	static int getSingleBitFromName(const char *);
};

class Rva0028F59A
{
public:
	Rva0028F59A() {}
	inline __declspec(noinline) Rva0028F59A(int, int bit) { memset(this,0,0x4c); m_bits[(unsigned)bit>>5] |= 1u << (bit&31); }
	unsigned int m_bits[19];
};

class WeaponTemplateSet
{
public:
	Rva0028F59A m_flags;
	UnsignedInt m_animTime;
	const void *m_ocl;
};

// ?Rva004AEB84Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004AEB84Parse(INI *ini, void *instance, void *store, const void *)
{
	WeaponTemplateSet info;
	memset(&info.m_flags, 0, sizeof(info.m_flags));
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (token == 0 || strcmp(token, "AnimState") != 0)
		throw INIException(3, "AnimState expected");

	int bit = BitFlags<304>::getSingleBitFromName(ini->getNextToken());
	info.m_flags = Rva0028F59A(0, bit);

	token = ini->getNextToken(ini->getSepsColon());
	if (token == 0 || strcmp(token, "AnimTime") != 0)
		throw INIException(3, "AnimDuration expected");
	INI::parseDurationUnsignedInt(ini, instance, &info.m_animTime, 0);

	token = ini->getNextToken(ini->getSepsColon());
	if (token == 0 || strcmp(token, "RiderOCL") != 0)
		throw INIException(3, "RiderOCL expected");
	INI::parseObjectCreationList(ini, instance, &info.m_ocl, 0);

	((std::vector<WeaponTemplateSet> *)store)->push_back(info);
}
