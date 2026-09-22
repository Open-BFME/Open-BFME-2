// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ProductionPrerequisite default ctor / clear / dtor vein.
//
// Retail RE (all byte-measured with capstone + raw E8 scans):
// - ??0ProductionPrerequisite@@QAE@XZ @0x004F527A (81B): EH head
//   (mov eax,scope + call __EH_prolog @0x00629188), three empty
//   _Vector_base inits via the folded 29B base ctor @0x00211E58, then a call
//   to the clear helper below. Ends where addUnitPrereq @0x004F52CB begins.
// - ?clear@ProductionPrerequisite@@QAEXXZ @0x004F5227 (27B, frameless):
//   full-range erases of the +0x00 member via @0x004F50E2 and the +0x0C
//   member via the rowed ParticleSystemID erase @0x00532803. This is the
//   BFME1 donor ctor body (ProductionPrerequisiteCtorThunk.cpp calls
//   m_prereqUnits.clear() + m_prereqSciences.clear()) factored into a helper;
//   the BFME2 default ctor calls it instead of repeating the two clears.
// - erase<PrereqUnitRec> @0x004F50E2 (49B): copy-down via the rowed nested
//   __copy_ptrs @0x002CF594, destroy-range via @0x002D02A8, finish store.
// - destroy range @0x002D02A8 (25B): per-12-byte-element dtor loop.
// - ??1PrereqUnitRec@ProductionPrerequisite@@QAE@XZ @0x00577998 (8B):
//   add ecx,8 + tail-jump to the AsciiString dtor @0x00036410, so the record
//   carries an AsciiString at +0x08 (12 bytes total).
// - ??1?$vector@UPrereqUnitRec@ProductionPrerequisite@@... @0x002D040C (63B):
//   EH teardown of the +0x00 member (destroy range + _free @0x00030830).
// - ??1ProductionPrerequisite@@QAE@XZ @0x004F5115 (80B): EH head, inline
//   null-checked _free of the +0x18 / +0x0C members (trivial elements),
//   then the +0x00 member teardown above. Ends where insert_aux @0x004F5165
//   begins.
//
// Layout (retail-proven, agrees with the copy-ctor + push_back TUs):
// +0x00 vector<PrereqUnitRec> (12-byte non-trivial elements),
// +0x0C vector<ScienceType> (4-byte trivial elements),
// +0x18 vector<unsigned int>, 0x24 bytes total.

#include <vector>

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_first;
		unsigned int m_second;
		AsciiString m_name;
		~PrereqUnitRec();
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();
	void clear();

private:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<unsigned int> m_unused;
};

typedef char ProductionPrerequisiteVeinSizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

ProductionPrerequisite::PrereqUnitRec::~PrereqUnitRec()
{
}

void ProductionPrerequisite::clear()
{
	m_prereqUnits.clear();
	m_prereqSciences.clear();
}

ProductionPrerequisite::ProductionPrerequisite()
{
	clear();
}

ProductionPrerequisite::~ProductionPrerequisite()
{
}
