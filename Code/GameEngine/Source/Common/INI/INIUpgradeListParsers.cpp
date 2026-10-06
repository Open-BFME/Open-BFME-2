// cl: /Ireference/shims/bfme2_ascii /Oy- /GX /DNDEBUG /MD
//
// Upgrade-list FieldParse proc (name address-derived): every remaining
// token is resolved through TheUpgradeCenter (VA 0x00DFEB60) and each hit is
// appended to a const UpgradeTemplate * vector (pinned push_back fold
// 0x004DFCB0).
//   0x002890D1 104B Upgrades (0x00BFBB30): looks each token up by AsciiString
//       (rowed findUpgrade 0x0026F26D) into the vector at instance + 0x4C.
//   0x00339A13 93B NeededUpgrade (0x00C154A8, store): resolves tokens through
//       the rowed nameToKey 0x00148E1A and findUpgradeByKey 0x0026EEB8. Its
//       missing-center path writes 0xDEAD0001 into the store parameter slot,
//       then calls the pinned MSVC throw helper 0x00629094 with the named
//       ErrorCode ThrowInfo COMDAT at retail VA 0x00CFEEE4.

#include "ascii_string.h"

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0000)
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
};
extern UpgradeCenter *TheUpgradeCenter;

extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);
struct _s__ThrowInfo;
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AW4ErrorCode@@");

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<const UpgradeTemplate *, allocator<const UpgradeTemplate *> >
{
public:
	void push_back(const UpgradeTemplate *const &x);
private:
	const UpgradeTemplate **m_start;
	const UpgradeTemplate **m_finish;
	const UpgradeTemplate **m_endOfStorage;
};
}

typedef _STL::vector<const UpgradeTemplate *, _STL::allocator<const UpgradeTemplate *> > UpgradeTemplateVector;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	static void Rva002890D1_ParseUpgradeList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00339A13_ParseUpgradeKeyList(INI *ini, void *instance, void *store, const void *userData);
};

struct Rva002890D1Owner
{
	unsigned char m_unreconstructed_00[0x4C];
	UpgradeTemplateVector m_upgrades;	// +0x4C
};

// ?Rva002890D1_ParseUpgradeList@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002890D1_ParseUpgradeList(INI *ini, void *instance, void *, const void *)
{
	const char *token;
	while ((token = ini->getNextTokenOrNull()) != NULL)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(AsciiString(token));
		if (upgrade)
			((Rva002890D1Owner *)instance)->m_upgrades.push_back(upgrade);
	}
}

void INI::Rva00339A13_ParseUpgradeKeyList(INI *ini, void *, void *store, const void *)
{
	if (TheUpgradeCenter == NULL)
	{
		store = (void *)ERROR_BUG;
		_CxxThrowException(&store, (void *)&__identifier("_TI1?AW4ErrorCode@@"));
		__assume(0);
	}

	const char *token;
	while ((token = ini->getNextTokenOrNull()) != NULL)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgradeByKey(TheNameKeyGenerator->nameToKey(token));
		if (upgrade)
			((UpgradeTemplateVector *)store)->push_back(upgrade);
	}
}
