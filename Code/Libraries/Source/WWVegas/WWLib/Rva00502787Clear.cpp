// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// ?rva00502787@Rva00502787@@QAEXXZ @0x00502787 41B
// Evidence: chain from 0x005025DB which you just landed; clear resetting header parent/left/right and count via rowed erase 0x005025DB; callers at 0x005029A2 0x00503693 0x00502988; neighbours stlport_map_int_vector_vector_pod88 and stlport_tree_erase_00502610.
struct Rva005025DB
{
	void rva005025DB(void *p);
};

struct Rva00502787Header
{
	int m_00;
	void *m_04;
	void *m_08;
	void *m_0c;
};

struct Rva00502787
{
	Rva00502787Header *m_00;
	int m_04;
	void rva00502787();
};

void Rva00502787::rva00502787()
{
	if (m_04 == 0)
		return;
	((Rva005025DB *)this)->rva005025DB(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0c = m_00;
	m_04 = 0;
}
