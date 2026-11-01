// cl: /DNDEBUG /MD /GX-
// Rva003F2033_ParseOnVictoryGiveUpgrade (retail 0x003F2033, 105 bytes).
// Throws a 0xDEAD0001-marked word through the CxxThrowException thunk at
// 0x00629094 when TheUpgradeCenter is still null, then reads an OrNull
// token list through the rowed getNextTokenOrNull at 0x002DEED: each
// token keys through the rowed NameKeyGenerator::nameToKey at 0x00148E1A
// and the rowed UpgradeCenter::findUpgradeByKey at 0x0026EEB8 into a
// stack temp; null results, templates with a nonzero word at +0x04, and
// templates with a zero byte at +0x78 are skipped, the rest ride the
// UpgradeTemplate-spelled vector push_back pin at 0x004DFCB0 onto the
// store (GiveUpgrade precedent for the shape, plus the +0x78 gate).
// Serves the OnVictoryGiveUpgrade entry of the table at 0x836560. The
// callback name stays address-derived; the owning struct is BFME2-new.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../../Include/Common/Upgrade.h"

#include "../../../Include/Common/NameKeyGenerator.h"


namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

#include "../../../Include/Common/INI/INI.h"

extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
// DataChunkReadDict's ErrorCode throw provides this COMDAT at retail 0xCFEEE4.
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AW4ErrorCode@@");

// ?Rva003F2033_ParseOnVictoryGiveUpgrade@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003F2033_ParseOnVictoryGiveUpgrade(INI *ini, void *instance, void *store, const void *userData)
{
	if (TheUpgradeCenter == 0) {
		int &marker = (int &)store;
		marker = 0xDEAD0001;
		_CxxThrowException(&marker, &__identifier("_TI1?AW4ErrorCode@@")); __assume(0);
	}
	for (;;) {
		const char *token = ini->getNextTokenOrNull(0);
		if (token == 0)
			break;
		NameKeyType key = TheNameKeyGenerator->nameToKey(token);
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgradeByKey(key);
		if (upgrade == 0 || upgrade->m_type != 0 || upgrade->field78 == 0)
			continue;
		((_STL::vector<const UpgradeTemplate *> *)store)->push_back(upgrade);
	}
}
