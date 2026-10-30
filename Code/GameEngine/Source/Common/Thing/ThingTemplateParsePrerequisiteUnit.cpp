// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RE: ?parsePrerequisiteUnit@@YAXPAVINI@@PAX1PBX@Z @0x0033EA47 (118B).
//
// BFME1 donor: Code/GameEngine/Source/Common/Thing/ThingTemplate_parsePrerequisites_Thunk.cpp
// (ParsePrerequisiteUnitThunk.cpp: default prereq + throwing-first-token loop
// with in-place AsciiString temp + addUnitPrereq(unit, orFlag) + push_back).
// BFME2 adaptations: getNextToken(0)/getNextTokenOrNull(0) seps-pointer forms
// (matched row + existing OrNull pin), addUnitPrereq outlined to 0x004F52CB
// (new pin, BFME1 (AsciiString,bool) mangling), AsciiString temp built
// directly in the outgoing-arg slot (mov ecx,esp) via the delegating inline
// ctor over the matched private StringBase<char> ctor row 0x37BA0. /O1 for
// the outlined __EH_prolog head (pool-key law), same as the Science twin.
// Shares the Science TU's replica-vector idiom and its ctor/dtor/push_back pins.

#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

#include "ascii_string.h"

class ProductionPrerequisite;

namespace _STL
{

// Bind the rowed push_backs to their workers: vector<ScienceType> at
// 0x002E01C6 and vector<ProductionPrerequisite> at 0x0033EA10. Declarations
// only: the definitions live in the row owners.
template <class T, class A> class vector;
template <> class vector<int, allocator<int> >
{
private:
	int *m_start;
	int *m_finish;
	int *m_endOfStorage;
};
template <> class vector<ScienceType, allocator<ScienceType> >
{
public:
	void push_back(const ScienceType &x);
private:
	ScienceType *m_start;
	ScienceType *m_finish;
	ScienceType *m_endOfStorage;
};
template <> class vector<ProductionPrerequisite, allocator<ProductionPrerequisite> >
{
public:
	void push_back(const ProductionPrerequisite &x);
private:
	ProductionPrerequisite *m_start;
	ProductionPrerequisite *m_finish;
	ProductionPrerequisite *m_endOfStorage;
};

}

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	static ScienceType scanScience(const char *token);
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	~ProductionPrerequisite();

	void addUnitPrereq(AsciiString unit, bool orUnitWithPrevious);

public:
	_STL::vector<int> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<ScienceType> m_unused;
};

void __cdecl parsePrerequisiteUnit(INI *ini, void *instance, void *, const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	bool orUnitWithPrevious = false;
	for (const char *token = ini->getNextToken(0); token != 0;
		token = ini->getNextTokenOrNull(0))
	{
		prerequisite.addUnitPrereq(AsciiString(token), orUnitWithPrevious);
		orUnitWithPrevious = true;
	}

	prerequisites->push_back(prerequisite);
}
