// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0BfmeItemERF@@QAE@XZ @0x003F609E 42B evidence: leaf pin plus caller resize 0x003F700F plus rowed Vector-base 0x00211E58 twice plus members +0 +4 +0x10
#include <vector>

struct BfmeE16
{
	char m_pad[16];
};

class BfmeItemERF
{
public:
	BfmeItemERF();

private:
	int m_0;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_04;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_10;
};

BfmeItemERF::BfmeItemERF() : m_0(-2)
{
}
