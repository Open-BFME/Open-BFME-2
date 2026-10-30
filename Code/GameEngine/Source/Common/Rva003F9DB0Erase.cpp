// cl: /DNDEBUG /MD
// stlport46
// ?rva003F9DB0@Rva003F9DB0@@QAEXXZ @0x003F9DB0 14B vector<BfmePod8> range-erase.
// Evidence: calls rowed ?erase@?$vector@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEPAUBfmePod8@@PAU3@0@Z 0x003FA4DB with this+0x3C plus pushes of [this+0x40] then [this+0x3C]; caller 0x00210EBF tail-jmps after null-checking [ecx+0x2C4]; same erase-begin-end shape as MilesAudioManagerRva0005710F.
struct BfmePod8
{
	int a[2];
};
#define _STLP_USE_STATIC_LIB 1
#include <vector>
// The range erase is the rowed body at 0x003FA4DB; clear() calls it out of line.
namespace _STL { template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *, BfmePod8 *); }

class Rva003F9DB0
{
public:
	void rva003F9DB0();
private:
	char m_pad[0x3C];
	_STL::vector<BfmePod8> m_vec;
};

void Rva003F9DB0::rva003F9DB0()
{
	m_vec.clear();
}
