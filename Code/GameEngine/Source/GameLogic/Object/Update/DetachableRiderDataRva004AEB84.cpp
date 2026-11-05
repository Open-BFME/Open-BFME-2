// ?Rva004AEB84Parse@@YAXPAVINI@@PAX1PBX@Z
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Oi- /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
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

#include "../../../../Include/Common/INI/INI.h"

#include "../../../../Include/Common/INI/FieldParse.h"

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
	// This view's empty default constructor stays inline-only: retail's out-of-line
	// WeaponTemplateSet() is ThingTemplate.cpp's (BitFlags ctor plus clear), which this
	// parser never calls; its own select-any copy differed from that one.
	__declspec(dllimport) __forceinline WeaponTemplateSet() {}
	Rva0028F59A m_flags;
	UnsignedInt m_animTime;
	const void *m_ocl;
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(nothrow) void _Construct<WeaponTemplateSet,WeaponTemplateSet>(WeaponTemplateSet *,WeaponTemplateSet const &); }

// ?Rva004AEB84Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004AEB84Parse(INI *ini, void *instance, void *store, const void *)
{
	WeaponTemplateSet info;
	memset(&info.m_flags, 0, sizeof(info.m_flags));
	const char *token = ini->getNextToken(ini->m_sepsColon);
	if (token == 0 || strcmp(token, "AnimState") != 0)
		throw INIException(3, "AnimState expected");

	int bit = BitFlags<304>::getSingleBitFromName(ini->getNextToken());
	info.m_flags = Rva0028F59A(0, bit);

	token = ini->getNextToken(ini->m_sepsColon);
	if (token == 0 || strcmp(token, "AnimTime") != 0)
		throw INIException(3, "AnimDuration expected");
	INI::parseDurationUnsignedInt(ini, instance, &info.m_animTime, 0);

	token = ini->getNextToken(ini->m_sepsColon);
	if (token == 0 || strcmp(token, "RiderOCL") != 0)
		throw INIException(3, "RiderOCL expected");
	INI::parseObjectCreationList(ini, instance, &info.m_ocl, 0);

	((std::vector<WeaponTemplateSet> *)store)->push_back(info);
}
