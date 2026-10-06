// cl: /MD
// stlport
// ??0Rva00524415@@QAE@XZ @0x00524415 33B
// Default ctor of two BfmeE16 vectors at +0 and +0xc via rowed _Vector_base
// 0x00211E58 with dummy allocator. Unlocks 5 callers including 0x002D2C34.
// Evidence: lea [ebp-1] push mov esi ecx call then lea ecx [esi+0xc] call.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
struct Rva00524415
{
	_STL::vector<BfmeE16> m_00;
	_STL::vector<BfmeE16> m_0c;
	Rva00524415();
};
Rva00524415::Rva00524415()
{
}
