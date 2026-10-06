// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Gen_001DB2C0@@QAE@H@Z at 0x004DE5A4 (44B). Caller 0x004DE6AD allocates
// 0x14 bytes and passes the key; adjacent matched destructor 0x004DE5D0
// proves the three-pointer header at +0 and fields at +0xC/+0x10. The Gen
// name follows the donor-supported destructor layout; this body's calls and
// stores are taken from BFME2 retail bytes.
#include <vector>

struct GenVec
{
	void **m_begin;
	void **m_end;
	void **m_capacity;
};
// The 16-byte stand-in emits the rowed ICF-folded Vector_base constructor;
// retail proves the call and three-pointer header, not the element type.
struct BfmeE16 { float x, y, z, w; };
typedef _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > BfmeE16VecBase;

struct Gen_001DB2C0
{
	GenVec m_vec;
	int m_key;
	Gen_001DB2C0 *m_next;
	Gen_001DB2C0(int key);
	~Gen_001DB2C0();
};

Gen_001DB2C0::Gen_001DB2C0(int key)
{
	((BfmeE16VecBase &)m_vec)._STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >::_Vector_base(_STL::allocator<BfmeE16>());
	_STL::vector<void *> *v = (_STL::vector<void *> *)&m_vec;
	m_key = key;
	v->erase(v->begin(), v->end());
	m_next = 0;
}
