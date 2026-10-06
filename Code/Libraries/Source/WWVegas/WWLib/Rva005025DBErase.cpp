// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// ?rva005025DB@Rva005025DB@@QAEXPAX@Z @0x005025DB 53B
// Evidence: Rb-node clear recursing on +0x0C then walking +0x08 with value dtor 0x0050174A at +0x10 and free 0x00030830; self-call at 0x005025ED; caller clear 0x00502787; neighbours stlport_map_int_vector_vector_pod88 and stlport_tree_erase_00502610.
struct Rva0050174A
{
	~Rva0050174A();
};

struct Rva005025DBNode
{
	int m_00;
	int m_04;
	Rva005025DBNode *m_08;
	Rva005025DBNode *m_0c;
};

extern "C" void __cdecl free(void *);

struct Rva005025DB
{
	void rva005025DB(void *p);
};

void Rva005025DB::rva005025DB(void *p)
{
	Rva005025DBNode *x = (Rva005025DBNode *)p;
	if (x == 0)
		return;
	while (x != 0)
	{
		rva005025DB(x->m_0c);
		Rva005025DBNode *y = x->m_08;
		((Rva0050174A *)((char *)x + 0x10))->~Rva0050174A();
		free(x);
		x = y;
	}
}
