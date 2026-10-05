// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F7BB4@Rva003F7BB4@@QAEXABURva003F7B22Element@@@Z @0x003F7BB4 8B
// Tail-jmp forwarder adding 0x2c then calling rowed vector push_back 0x003F7B22.
// Evidence: add ecx 0x2c plus jmp to rowed push_back; neighbours share Eva bucket TU; unblocks 0x004E0860 0x003F2150.
#include <vector>

struct Rva003F7B22Element { int a[1]; };

class Rva003F7BB4
{
public:
	void rva003F7BB4(const Rva003F7B22Element &e);
private:
	char m_pad[0x2c];
	_STL::vector<Rva003F7B22Element> m_vec;
};

void Rva003F7BB4::rva003F7BB4(const Rva003F7B22Element &e)
{
	m_vec.push_back(e);
}
