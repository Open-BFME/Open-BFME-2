// cl: /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Gen_001DB2C0@@QAE@XZ retail 0x004DE5D0 36B
// Evidence: leaf lane; pin ??1Gen_001DB2C0; callers 0x004DE5F7 0x004DE646 0x004DE66E; callee erase 0x0031BD55 plus _free 0x00030830; prev Rva004DC9EDEntryDtor same /O1; donor BFME1 Bfme5SelfRangeDtor Gen layout begin end capacity key next.
#include <vector>
extern "C" void __cdecl free(void *block);
struct GenVec
{
	void **m_begin;
	void **m_end;
	void **m_capacity;
};
struct Gen_001DB2C0
{
	GenVec m_vec;
	int m_key;
	Gen_001DB2C0 *m_next;
	~Gen_001DB2C0();
};
Gen_001DB2C0::~Gen_001DB2C0()
{
	m_key = 0;
	_STL::vector<void *> *v = (_STL::vector<void *> *)&m_vec;
	v->erase(v->begin(), v->end());
	m_next = 0;
	void **storage = v->begin();
	if (storage != 0)
		free(storage);
}
