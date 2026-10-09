// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00082A53@@QAE@HHHMPAHH@Z @ 0x00082A53 153B.
// Ctor with two vector members (E12 at +4 via rowed 0x0007FAEA, E16 at +0x18
// via rowed 0x00211E58), ints at +0/+0x10/+0x14, three ints from pointer at
// +0x24/+0x28/+0x2C, float at +0x30. Word resize at +4 via rowed 0x000824F9
// and Pod44 reserve at +0x18 via rowed 0x00081A75. Evidence: callees all
// rowed; caller 0x0008304A; prev/next OpaqueScalarDeletingDtors.
#include <vector>

struct BfmeE12 { float x, y, z; };
struct BfmeE16 { float x, y, z, w; };
struct BfmePod44 { int a[11]; };
struct BfmeWordVec : _STL::vector<unsigned short, _STL::allocator<unsigned short> >
{
	void resize(unsigned int n, unsigned short x);
};

class Rva00082A53
{
	int m_unk00;
	_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > m_vec04;
	int m_dim10;
	int m_dim14;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec18;
	int m_data24;
	int m_data28;
	int m_data2C;
	float m_val30;
public:
	Rva00082A53(int a1, int a2, int a3, float a4, int *a5, int a6);
 unsigned short rva00082E33(int x, int y);
};

Rva00082A53::Rva00082A53(int a1, int a2, int a3, float a4, int *a5, int a6)
	: m_unk00(a1)
	, m_vec04()
	, m_dim10(a2 + 1)
	, m_dim14(a3 + 1)
	, m_vec18()
	, m_data24(a5[0])
	, m_data28(a5[1])
	, m_data2C(a5[2])
	, m_val30(a4)
{
	int n = m_dim10 * m_dim14;
	((BfmeWordVec *)&m_vec04)->resize((unsigned int)n, (unsigned short)0xFFFF);
	((_STL::vector<BfmePod44, _STL::allocator<BfmePod44> > *)&m_vec18)->reserve((unsigned int)a6);
}

// Target82E33..82EB8 and WB740340 establish cached vertex lookup/append.
// Existing constructor proves cells04/dim10/records18/origin24/spacing30.
// Original nested class name remains a donor lead; neutral owner retained.
class Rva0008026B
{
public:
    void rva0008026B(BfmePod44 *record);
};

typedef _STL::vector<BfmePod44, _STL::allocator<BfmePod44> > BfmePod44Vector;

unsigned short Rva00082A53::rva00082E33(int x, int y)
{
    int index = y * m_dim10 + x;
    unsigned short *cells = *(unsigned short **)((char *)this + 4);
    unsigned short *cell = cells + index;
    register unsigned short old_value = *cell;
    if (old_value != 0xFFFF) return old_value;
    {
        char **vec = (char **)((char *)this + 0x18);
        *cell = (unsigned short)(((int)vec[1] - (int)vec[0]) / 44);
        ((BfmePod44Vector *)((char *)this + 0x18))->resize(((int)vec[1] - (int)vec[0]) / 44 + 1);
        BfmePod44 *record = (BfmePod44 *)((char *)*(char **)((char *)this + 0x1C) - 44);
        *(float *)((char *)record + 0) = (float)x * m_val30 + *(float *)((char *)this + 0x24);
        *(float *)((char *)record + 4) = (float)y * m_val30 + *(float *)((char *)this + 0x28);
        record->a[2] = m_data2C;
        ((Rva0008026B *)m_unk00)->rva0008026B(record);
    }
    return *cell;
}
