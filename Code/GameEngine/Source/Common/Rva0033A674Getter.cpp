// cl: /O1 /MD
// ?rva0033A674@Rva0033A674@@QAEPAXXZ @0x0033A674 22B
// Evidence: same 22B fallback-getter shape as sibling Rva0033A65EGetter 0x0033A65E; callers use result as ptr; falls back to global at 0x00E030B8 via rowed rva00419154 0x00419154.
class Rva0041811D
{
public:
	void *rva00419154();
};

extern class Rva0041811D *g_Va00E030B8;

class Rva0033A674
{
public:
	void *rva0033A674();
private:
	char m_pad[0x498];
	void *m_ptr;
};

void *Rva0033A674::rva0033A674()
{
	if (m_ptr != 0)
		return m_ptr;
	Rva0041811D *table = g_Va00E030B8;
	return table->rva00419154();
}
