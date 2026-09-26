// cl: /O1 /DNDEBUG /MD /GX-
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

class UpgradeTemplate
{
public:
	unsigned char m_unreconstructed[4];
	int m_requiredZero; // +0x04: entries with a nonzero word here are skipped
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
};

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

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	static void Rva003F1FD0_ParseGiveUpgrade(INI *ini, void *instance, void *store, const void *userData);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;

__declspec(noreturn) void __stdcall _CxxThrowException(void *pExc, void *pInfo);

// ?Rva003F1FD0_ParseGiveUpgrade@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003F1FD0_ParseGiveUpgrade(INI *ini, void *instance, void *store, const void *userData)
{
	if (TheUpgradeCenter == 0) {
		int &marker = (int &)store;
		marker = 0xDEAD0001;
		_CxxThrowException(&marker, (void *)0xCFEEE4);
	}
	for (;;) {
		const char *token = ini->getNextTokenOrNull(0);
		if (token == 0)
			break;
		NameKeyType key = TheNameKeyGenerator->nameToKey(token);
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgradeByKey(key);
		if (upgrade == 0 || upgrade->m_requiredZero != 0)
			continue;
		((_STL::vector<const UpgradeTemplate *> *)store)->push_back(upgrade);
	}
}
