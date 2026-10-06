// cl: /DNDEBUG /MD /GX-
// ?rva00438389@Rva00438389@@QAEAAV1@XZ @0x00438389 49B: clear ints bitset and memset.
// Zeroes dword +0 byte +4 dwords +8 +0xC, resets 128-bit bitset at +0x10 via
// rowed 0x0024CA24, memsets 0x10 at +0x10 via import thunk 0x006291AE,
// clears byte +0x20, returns *this. Callers 0x004397AB 0x00439EE1.
namespace _STL
{
template <int N> class bitset
{
public:
	bitset &reset();
private:
	char m_pad[0x10];
};
}

extern "C" void *memset(void *s, int c, unsigned int n);

class Rva00438389
{
public:
	Rva00438389 &rva00438389();
private:
	int m00;
	unsigned char m04;
	int m08;
	int m0C;
	_STL::bitset<128> m10;
	unsigned char m20;
};

Rva00438389 &Rva00438389::rva00438389()
{
	m00 = 0;
	m04 = 0;
	m08 = 0;
	m0C = 0;
	m10.reset();
	m20 = 0;
	memset(&m10, 0, 0x10);
	return *this;
}
