// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva0040E02B@Rva0040E02B@@QAEXXZ @0x0040E02B (14B):
// Full-range erase of a vector<ScienceType> member at +0x4C via the rowed
// erase at 0x00532803 (rowed from ProductionPrerequisiteCtor.cpp).
// STLport vector::clear() inlines to erase(begin(), end()); erase itself is
// declared only and resolved by the gate. Owner unknown: honest address
// name; class is padding plus the touched member. Caller 0x0040E0E0.
// Evidence: leaf lane, callee rowed.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class Rva0040E02B
{
public:
	void rva0040E02B();
private:
	char m_pad[0x4C];
	_STL::vector<ScienceType> m_vec;
};

void Rva0040E02B::rva0040E02B()
{
	m_vec.clear();
}
