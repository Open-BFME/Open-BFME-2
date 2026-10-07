// ?Rva004AEB84Parse@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Oi-
// Parser identity inferred from the AnimState, AnimTime, and RiderOCL fields;
// owner class is unproven. Structure follows the BFME RiderInfo parser.

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
	Rva0028F59A(int, int);
	unsigned int m_bits[19];
};

struct WeaponTemplateSet
{
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

	int bit = BitFlags<0xBDA>::getSingleBitFromName(ini->getNextToken());
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
