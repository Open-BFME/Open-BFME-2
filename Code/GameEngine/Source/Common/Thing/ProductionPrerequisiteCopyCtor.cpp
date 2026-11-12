// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ProductionPrerequisite copy ctor, retail 0x002D08DA.
//
// Layout evidence, all retail-measured: the ctor copies member vectors at
// +0x00 (string-bearing record, 12-byte elements: the callee divides the byte count
// by 0x0C), +0x0C (4-byte elements: the callee shifts the byte count right
// by 2) and +0x18 (calls the matched vector<uint> copy at 0x002CFAB9).
// This mirrors the Zero Hour header carried in
// reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/
// ProductionPrerequisiteCopyCtor.cpp (PrereqUnitRec vector, ScienceType
// vector, third vector), 0x24 bytes total like the push_back TU's replica.

#include <vector>

// This member's retail copy calls the string-bearing record chain
// 0x004F5097 -> 0x002CF99D -> 0x002CF5B1. Keep its type consistent with
// ProductionPrerequisiteAssign.cpp and the corrected copy provider.
#include "ascii_string.h"
#include "../../../Include/Common/BfmeStringRecord002CF5B1.h"
// Bind to the exception-enabled retail copy provider.
namespace _STL { template <> vector<BfmeStringRecord002CF5B1>::vector(const vector<BfmeStringRecord002CF5B1> &); }

enum ScienceType
{
	SCIENCE_NONE = 0
};

class ProductionPrerequisite
{
public:
	ProductionPrerequisite(const ProductionPrerequisite &other);

private:
	_STL::vector<BfmeStringRecord002CF5B1> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<unsigned int> m_unused;
};

typedef char ProductionPrerequisiteCopySizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

ProductionPrerequisite::ProductionPrerequisite(const ProductionPrerequisite &other)
	: m_prereqUnits(other.m_prereqUnits)
	, m_prereqSciences(other.m_prereqSciences)
	, m_unused(other.m_unused)
{
}

