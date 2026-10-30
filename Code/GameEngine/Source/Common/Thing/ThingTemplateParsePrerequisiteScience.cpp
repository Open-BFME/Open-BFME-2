// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RE: ?parsePrerequisiteScience@@YAXPAVINI@@PAX1PBX@Z @0x0033EABD (93B).
//
// BFME1 donor: Code/GameEngine/Source/Common/INI/ParsePrerequisiteScienceThunk.cpp
// (same shape: default-constructed ProductionPrerequisite + addSciencePrereq of
// INI::scanScience(ini->getNextToken(0)) + push_back into the instance vector).
// BFME2 adaptations (all retail-measured): getNextToken takes a seps pointer
// (NULL here; the matched row is ?getNextToken@INI@@QAEPBDPBD@Z) and
// addSciencePrereq is outlined as a direct vector<ScienceType>::push_back call
// to the matched row at 0x002E01C6. /O1 selects the outlined __EH_prolog head
// (mov eax,scope + call 0x629188), same axis as the pool-key family.
// Pins (same batch, all byte-decoded + evidence in notes): INI::scanScience
// @0x338A8D (BFME1 mangling; 11B forwarder via ScienceStore global),
// ProductionPrerequisite ctor @0x4F527A / dtor @0x4F5115 (BFME1 QAE
// manglings; 3x vector inits at +0/+0xC/+0x18), prereq-vector push_back
// @0x33EA10 (0x24 stride = 3x12B vectors; compiler-attested mangling).

#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ProductionPrerequisite;

namespace _STL
{

// Bind the two rowed push_backs to their workers: vector<ScienceType> at
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
	static ScienceType scanScience(const char *token);
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	~ProductionPrerequisite();

	_STL::vector<int> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<ScienceType> m_unused;
};

void __cdecl parsePrerequisiteScience(INI *ini, void *instance, void *, const void *)
{
	_STL::vector<ProductionPrerequisite> *prerequisites =
		static_cast<_STL::vector<ProductionPrerequisite> *>(instance);

	ProductionPrerequisite prerequisite;
	prerequisite.m_prereqSciences.push_back(INI::scanScience(ini->getNextToken(0)));
	prerequisites->push_back(prerequisite);
}
