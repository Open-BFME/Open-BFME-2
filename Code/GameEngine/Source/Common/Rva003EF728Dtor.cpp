// cl: /DNDEBUG /MD /EHs
//
// ??1Rva003EF728@@QAE@XZ @ 0x003EF728 (86B).
// Non-virtual dtor freeing three heap blocks at +0x20/+0x14/+0x0 via
// rowed _free 0x00030830 with null guards and EH states 1/0/-1 (reverse
// member order). Uses /EHs like NarrowStringRecord0041A5D2Dtor (the /EHsc
// sibling drops those states). Callers: deleting-dtor 0x0020E32A (28B,
// test al+delete pattern) plus 0x00210895.
extern "C" void __cdecl free(void *block);

struct Rva003EF728Ptr
{
	char *m_p;
	~Rva003EF728Ptr()
	{
		if (m_p)
			free(m_p);
	}
};

class Rva003EF728
{
public:
	~Rva003EF728();

private:
	Rva003EF728Ptr m_00;
	char m_pad04[0x10];
	Rva003EF728Ptr m_14;
	char m_pad18[0x08];
	Rva003EF728Ptr m_20;
};

Rva003EF728::~Rva003EF728()
{
}
