// ?Rva00339A13_ParseUpgradeKeyList@INI@@SAXPAV1@PAX1PBX@Z
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /GX /DNDEBUG /MD
//
// Upgrade-list FieldParse procs (names address-derived): every remaining
// token is resolved through TheUpgradeCenter (VA 0x00DFEB60) and each hit is
// appended to a const UpgradeTemplate * vector (pinned push_back fold
// 0x004DFCB0).
//   0x00339A13 93B NeededUpgrade (0x00C154A8, store): throws ERROR_BUG when
//       TheUpgradeCenter is missing, then looks each token up by name key
//       (rowed nameToKey 0x00148E1A, findUpgradeByKey 0x0026EEB8).
//   0x002890D1 104B Upgrades (0x00BFBB30): looks each token up by AsciiString
//       (rowed findUpgrade 0x0026F26D) into the vector at instance + 0x4C.

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
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

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
	static void Rva00339A13_ParseUpgradeKeyList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002890D1_ParseUpgradeList(INI *ini, void *instance, void *store, const void *userData);
};

struct Rva002890D1Owner
{
	unsigned char m_unreconstructed_00[0x4C];
	UpgradeTemplateVector m_upgrades;	// +0x4C
};

// ?Rva00339A13_ParseUpgradeKeyList@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00339A13_ParseUpgradeKeyList(INI *ini, void *, void *store, const void *)
{
	if (TheUpgradeCenter == NULL)
	{
		ErrorCode error = ERROR_BUG;
		throw error;
	}

	const char *token;
	while ((token = ini->getNextTokenOrNull()) != NULL)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgradeByKey(TheNameKeyGenerator->nameToKey(token));
		if (upgrade)
			((UpgradeTemplateVector *)store)->push_back(upgrade);
	}
}

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
