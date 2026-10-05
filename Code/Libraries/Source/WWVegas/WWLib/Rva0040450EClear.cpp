// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0040450E@Rva0040450E@@QAEXH@Z retail 0x0040450E 111 bytes.
// Reset method: erases vector at +0 via rowed erase 0x004043AE, sets +0x14 to
// arg, zeroes +0x18, memsets two 0x4C members at +0x1C/+0x68 through rowed
// memset, then zeroes +0x0C/+0xCC/bytes +0xD0-D3 and two int[3] at +0xB4/+0xC0.
// Evidence: caller 0x00214B61 constructs vector via Vector_base 0x00211E58 and
// two Rva0042526Member via 0x00042526 then calls this with 0; prev/next rows
// give TU and flags; memset target 0x006291AE rowed.
#include <string.h>

namespace _STL
{
template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	typedef _Tp *pointer;
	pointer erase(pointer, pointer);
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};
}

struct Rva004043AEElement;

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class Rva0040450E
{
public:
	void rva0040450E(int arg);
private:
	_STL::vector<Rva004043AEElement> m_vec;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	Rva0042526Member m_1C;
	Rva0042526Member m_68;
	int m_B4[3];
	int m_C0[3];
	int m_CC;
	unsigned char m_D0;
	unsigned char m_D1;
	unsigned char m_D2;
	unsigned char m_D3;
};

void Rva0040450E::rva0040450E(int arg)
{
	m_14 = arg;
	m_18 = 0;
	m_vec.erase(m_vec._M_start, m_vec._M_finish);
	memset(&m_1C, 0, 0x4C);
	memset(&m_68, 0, 0x4C);
	m_D0 = 0;
	m_D1 = 0;
	m_CC = 0;
	m_D2 = 0;
	m_D3 = 0;
	m_0C = 0;
	for (int i = 0; i < 3; ++i)
	{
		m_B4[i] = 0;
		m_C0[i] = 0;
	}
}
