// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?parseCreateAHeroSubClass@CreateAHeroManager@@SAXPAVINI@@PAX1PBX@Z retail
// 0x0021FB0C..0x0021FDD2 (710 bytes).
// Evidence: WB twin 0x00B80730 is CreateAHeroManager::parseCreateAHeroSubClass
// (CreateAHero.cpp asserts 3151..3180); retail stores it in the SubClass
// entry (+0x54) of the CreateAHeroClass field table 0x00DBA0D8 so the store
// argument is the class's subclass vector (+0x14). It builds a subclass from
// four "None" strings (rowed ctor 0x0021E793) fills it from the subclass
// field table 0x00DB9FC8 (initFromINI 0x0002DE78) and throws INIException for
// a missing or duplicate upgrade name (compareNoCase against each existing
// subclass +0x20) or an upgrade TheUpgradeCenter cannot find; touches the
// name and description tags through TheGameText (slot 14); walks the upgrade
// templates (list head getter 0x001DB0A8; name key +0x84; name +0x08; next
// +0x64) skipping the function-static empty-name key (guard 0x00DFE478
// value 0x00DFE474) and files every upgrade whose group the subclass knows
// (0x0021BD22) and that TheCreateAHeroManager maps to a bling (rowed
// FindBlingByUpgradeName / AddBling); sorts the +0x3C key vector (rowed sort
// 0x0021F0F9) and appends the subclass (rowed push_back 0x0021FAAE) before
// its destructor ??1CreateAHeroSubClass@CreateAHeroManager@@QAE@XZ
// (0x0021E50F). WB's debug build runs three cross-check blocks
// (`if (1)` at 0x00B80B56 0x00B80C36 0x00B80D2C); retail compiles them out
// but keeps the two EH states their AsciiString locals own (unwind entries 10
// and 11 with no action) so they stay here as dead blocks.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct FieldParse;
class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
	char *mFailureMessage;
	int mErrorCode;
};

class UpgradeTemplate
{
public:
	NameKeyType getNameKey() const { return m_nameKey; }
	const AsciiString &getUpgradeName() const { return m_name; }
	const UpgradeTemplate *friend_getNext() const { return m_next; }

private:
	unsigned char m_pad00[8];
	AsciiString m_name;					// +0x08
	unsigned char m_pad0C[0x64 - 0xc];
	const UpgradeTemplate *m_next;				// +0x64
	unsigned char m_pad68[0x84 - 0x68];
	NameKeyType m_nameKey;					// +0x84
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

// The upgrade list head getter is ICF-folded at 0x001DB0A8 (mov eax,[ecx+0Ch]).
class FrameDataManager
{
public:
	UnsignedInt getQuitFrame();
};

class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0);
};
extern GameTextInterface *TheGameText;

enum Rva0021B68DKey
{
	RVA0021B68D_KEY_INVALID = -1
};

struct Rva0021B68DCmp
{
	bool operator()(const Rva0021B68DKey &a, const Rva0021B68DKey &b) const;
};

namespace _STL
{
template <class _RandomAccessIter, class _Compare>
void sort(_RandomAccessIter first, _RandomAccessIter last, _Compare comp);
}

extern "C" const FieldParse CreateAHeroSubClassFieldParse[];

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass
	{
	public:
		CreateAHeroSubClass(const AsciiString &, const AsciiString &, const AsciiString &, const AsciiString &);
		~CreateAHeroSubClass();
		Int *rva0021BD22(Int groupKey) const;
		NameKeyType GetBlingGroupNameKey(UnsignedInt index);
		Int rva0021BC2C(Int blingKey) const;
		void AddBling(Int blingKey, UnsignedInt index, Bool makeDefault);

		AsciiString m_nameTag, m_descriptionTag, m_iconName, m_emptyString;
		unsigned m_word10, m_word14, m_word18;
		int m_spendablePoints;
		AsciiString m_upgradeName;				// +0x20
		std::map<int, std::vector<unsigned int> > m_blingIds;	// +0x24
		std::vector<NameKeyType> m_keys30, m_keys3C;		// +0x30 +0x3C
		unsigned char m_pad48[0xd8 - 0x48];
	};

	static void parseCreateAHeroSubClass(INI *ini, void *instance, void *store, const void *userData);
	Bool FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId);
};
extern CreateAHeroManager *TheCreateAHeroManager;

// The subclass vector's push_back is rowed at 0x0021FAAE (stlport_pod_vector_bodies.cpp);
// declare its specialization so this unit calls it instead of emitting a copy.
namespace _STL
{
template <> void vector<CreateAHeroManager::CreateAHeroSubClass, allocator<CreateAHeroManager::CreateAHeroSubClass> >::push_back(
	const CreateAHeroManager::CreateAHeroSubClass &x);
}

void CreateAHeroManager::parseCreateAHeroSubClass(INI *ini, void *, void *store, const void *)
{
	std::vector<CreateAHeroSubClass> *subClasses = (std::vector<CreateAHeroSubClass> *)store;
	CreateAHeroSubClass subClass(AsciiString("None"), AsciiString("None"), AsciiString("None"), AsciiString("None"));
	ini->initFromINI(&subClass, CreateAHeroSubClassFieldParse);

	if (subClass.m_upgradeName.isNone() || ((const StringBase<char> *)&subClass.m_upgradeName)->isEmpty())
		throw INIException(3, "No upgrade name specified while parsing CreateAHeroClass.");

	Bool found = false;
	for (UnsignedInt i = 0; !found && i < subClasses->size(); ++i)
	{
		if (subClass.m_upgradeName.compareNoCase((*subClasses)[i].m_upgradeName) == 0)
			found = true;
	}
	if (found)
		throw INIException(3, "A Create-a-Hero SubClass with the upgrade %s already exists.", subClass.m_upgradeName.str());

	if (TheUpgradeCenter->findUpgrade(subClass.m_upgradeName) == 0)
		throw INIException(3, "Upgrade %s not found while parsing CreateAHeroClass.", subClass.m_upgradeName.str());

	Bool exists = false;
	TheGameText->fetch(subClass.m_nameTag, &exists);
	TheGameText->fetch(subClass.m_descriptionTag, &exists);

	const UpgradeTemplate *upgrade = (const UpgradeTemplate *)((FrameDataManager *)TheUpgradeCenter)->getQuitFrame();
	static NameKeyType emptyKey = TheNameKeyGenerator->nameToKey("");
	for (; upgrade; upgrade = upgrade->friend_getNext())
	{
		if (upgrade->getNameKey() == emptyKey)
			continue;
		const Int *attrib = subClass.rva0021BD22(upgrade->getNameKey());
		if (attrib == 0)
			continue;
		if (0)
		{
			AsciiString groupName = TheNameKeyGenerator->keyToName((NameKeyType)*attrib);
			AsciiString upgradeGroupName = TheNameKeyGenerator->keyToName(upgrade->getNameKey());
		}
		Int index = 0;
		Int blingId = 0;
		if (TheCreateAHeroManager->FindBlingByUpgradeName(upgrade->getUpgradeName(), &index, &blingId))
			subClass.AddBling(blingId, index, false);
	}

	if (0)
	{
		for (UnsignedInt i = 0; i < subClass.m_blingIds.size(); ++i)
		{
			NameKeyType groupKey = subClass.GetBlingGroupNameKey(i);
			AsciiString groupName = TheNameKeyGenerator->keyToName(groupKey);
			Int blingCount = subClass.rva0021BC2C(groupKey);
		}
	}

	_STL::sort((Rva0021B68DKey *)subClass.m_keys3C.begin(), (Rva0021B68DKey *)subClass.m_keys3C.end(), Rva0021B68DCmp());
	subClasses->push_back(subClass);
}
