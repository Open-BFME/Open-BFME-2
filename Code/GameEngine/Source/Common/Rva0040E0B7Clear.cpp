// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// ?rva0040E0B7@Rva0040E0B7@@QAEXXZ @0x0040E0B7 14B.
// Unlock for 0x0023D033: clears the ScienceType vector at +0x14 via its
// rowed erase. Evidence: pin class from tail jmp caller, rowed erase
// 0x00532803 in ProductionPrerequisiteCtor.cpp, caller 0x0023D039.
#include <vector>
enum ScienceType
{
	SCIENCE_INVALID = 0
};
class Rva0040E0B7
{
public:
	void rva0040E0B7();
private:
	char m_pad00[0x14];
	_STL::vector<ScienceType> m_vec;
};
void Rva0040E0B7::rva0040E0B7()
{
	m_vec.clear();
}
