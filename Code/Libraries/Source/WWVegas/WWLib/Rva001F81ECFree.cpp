// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F81EC@Rva001F81EC@@QAEXXZ @0x001F81EC 23B: clear list then free sentinel.
// Evidence: calls rowed clear 0x001F65AF ?rva001F65AF@Rva001F65AF@@QAEXXZ then null-checked free via rowed _free 0x00030830; callers at 0x001F9E81 0x001FA42C.
class Rva001F65AF
{
public:
	void rva001F65AF();
};

extern "C" void __cdecl free(void *block);

class Rva001F81EC
{
public:
	void rva001F81EC();

private:
	void *m_head;
};

void Rva001F81EC::rva001F81EC()
{
	((Rva001F65AF *)this)->rva001F65AF();
	void *head = m_head;
	if (head)
		free(head);
}
