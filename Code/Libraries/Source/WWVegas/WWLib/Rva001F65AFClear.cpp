// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001F65AF@Rva001F65AF@@QAEXXZ @0x001F65AF 51B: list clear over Rva001F63C9Node.
// Evidence: same node layout as rowed erase 0x001F63C9 (Next +0 Prev +4 12B value +8 via rowed destroyDelete 0x0004CCFF flags 0 free via rowed _free 0x00030830); caller 0x001F81EC frees sentinel after this; empty check plus sentinel reset matches _List_base clear shape.
class Rva0004CCFF
{
public:
	void *destroyDelete(unsigned int flags);
};

struct Rva001F65AFNode
{
	void *m_next;
	void *m_prev;
	Rva0004CCFF m_value;
};

extern "C" void __cdecl free(void *block);

class Rva001F65AF
{
public:
	void rva001F65AF();

private:
	Rva001F65AFNode *m_head;
};

void Rva001F65AF::rva001F65AF()
{
	Rva001F65AFNode *cur = (Rva001F65AFNode *)m_head->m_next;
	if (cur == m_head)
		goto empty;
	do
	{
		Rva001F65AFNode *tmp = cur;
		cur = (Rva001F65AFNode *)tmp->m_next;
		tmp->m_value.destroyDelete(0);
		free(tmp);
	} while (cur != m_head);
empty:
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
}
