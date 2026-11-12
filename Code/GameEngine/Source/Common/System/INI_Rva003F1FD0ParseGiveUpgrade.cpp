// cl: /DNDEBUG /MD /GX-
// Rva003F1FD0_ParseGiveUpgrade (retail 0x003F1FD0, 99 bytes). Throws a
// 0xDEAD0001-marked word through the CxxThrowException thunk at
// 0x00629094 when TheUpgradeCenter is still null, then reads an OrNull
// token list through the rowed getNextTokenOrNull at 0x002DEED: each
// token keys through the rowed NameKeyGenerator::nameToKey at 0x00148E1A
// and the rowed UpgradeCenter::findUpgradeByKey at 0x0026EEB8 into a
// stack temp; null results and templates with a nonzero word at +0x04
// are skipped, the rest ride the UpgradeTemplate-spelled vector
// push_back pin at 0x004DFCB0 onto the store (prerequisiteUpgrade
// precedent for the element spelling). Serves the OnEnterGiveUpgrade and
// OnVictoryRemoveUpgrade entries of the table at 0x836560. The callback
// name stays address-derived; the owning struct is BFME2-new.

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
// The throw pushes retail's ErrorCode ThrowInfo at 0x8FEEE4, the compiler's own
// __TI1?AW4ErrorCode@@ that the units throwing an ErrorCode emit as a COMDAT.
// Name it rather than a zero stand-in, so a throw finds the catchable type.
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AW4ErrorCode@@");

// ?Rva003F1FD0_ParseGiveUpgrade@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003F1FD0_ParseGiveUpgrade(INI *ini, void *instance, void *store, const void *userData)
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
		if (upgrade == 0 || upgrade->m_type != 0)
			continue;
		((_STL::vector<const UpgradeTemplate *> *)store)->push_back(upgrade);
	}
}
