// cl: /DNDEBUG /MD
//
// ?rva002A7761@Rva002A7761@@QAEXXZ, retail 0x002A7761 44 bytes.
// Reset method: zeroes +8/+0xc, sets +4 to 100, zeroes +0x18/+0x1c,
// clears the BfmePod12 vector at +0x20 via the rowed range erase at
// 0x002A7644, then clears the byte flag at +0x2c. Evidence: leaf lane,
// single caller at 0x002AFBF2, callee row in StlportVectorEraseRangeFamily.cpp.

struct BfmePod12
{
	int m_a;
	int m_b;
	int m_c;
};

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
	_Tp *erase(_Tp *first, _Tp *last);

public:
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_endOfStorage;
};

}

class Rva002A7761
{
public:
	void rva002A7761();

private:
	int m_pad0; // +0x00
	int m_field4; // +0x04
	int m_field8; // +0x08
	int m_fieldC; // +0x0c
	int m_pad10; // +0x10
	int m_pad14; // +0x14
	int m_field18; // +0x18
	int m_field1C; // +0x1c
	_STL::vector<BfmePod12> m_vec20; // +0x20
	bool m_flag2C; // +0x2c
};

void Rva002A7761::rva002A7761()
{
	_STL::vector<BfmePod12> *pv = &m_vec20;
	m_field8 = 0;
	m_fieldC = 0;
	m_field4 = 100;
	m_field18 = 0;
	m_field1C = 0;
	pv->erase(pv->m_start, pv->m_finish);
	m_flag2C = false;
}
