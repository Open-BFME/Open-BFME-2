// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
// Retail RE: ?parsePrerequisiteUpgrade@@YAXPAVINI@@PAX1PBX@Z @0x0033EB1A (93B).
//
// BFME1 donor: Code/GameEngine/Source/Common/INI/ParsePrerequisiteUpgradeThunk.cpp
// (default-constructed ProductionPrerequisite + addUpgradePrereq of
// bfmeFindUpgradeByName(ini->getNextToken(0)) + push_back into the instance
// vector). BFME2 adaptations (all retail-measured): getNextToken takes a seps
// pointer (NULL here; the matched row is ?getNextToken@INI@@QAEPBDPBD@Z) and
// addUpgradePrereq is outlined as a direct vector<const UpgradeTemplate *>
// push_back call to 0x004DFCB0 (new pin; ICF-folded with the ModuleData-const,
// ObjectCreationNugget and RankInfo pointer-vector rows at the same address).
// /O1 selects the outlined __EH_prolog head (mov eax,scope + call 0x629188),
// same axis as the Science/Unit twins. Shares their replica-vector idiom and
// its ctor/dtor/push_back pins. The finder pin
// (?bfmeFindUpgradeByName@@YAPBVUpgradeTemplate@@PBD@Z @0x33970D) is
// BFME1-donor-backed and shape-proven: global-guard + AsciiString temp +
// lookup call + teardown + null path, sole caller passing a prereq token.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class UpgradeTemplate;

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);

public:
	~StringBase();

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

namespace _STL
{

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	void push_back(const T &x);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};

}

class INI
{
public:
	const char *getNextToken(const char *seps);
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	~ProductionPrerequisite();

	_STL::vector<int> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<const UpgradeTemplate *> m_prereqUpgrades;
};

const UpgradeTemplate *bfmeFindUpgradeByName(const char *name);

// ?bfmeFindUpgradeByName@@YAPBVUpgradeTemplate@@PBD@Z
const UpgradeTemplate *bfmeFindUpgradeByName(const char *name)
{
	if (TheUpgradeCenter != 0)
	{
		AsciiString key(name);
		return TheUpgradeCenter->findUpgrade(key);
	}
	return 0;
}

// ?parsePrerequisiteUpgrade@@YAXPAVINI@@PAX1PBX@Z
void __cdecl parsePrerequisiteUpgrade(INI *ini, void *instance, void *, const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	prerequisite.m_prereqUpgrades.push_back(bfmeFindUpgradeByName(ini->getNextToken(0)));
	prerequisites->push_back(prerequisite);
}
