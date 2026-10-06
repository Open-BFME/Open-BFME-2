// cl: /DNDEBUG /MD
// ?rva0031AC39@Rva0031AC39@@QAEXXZ @0x0031AC39 22B: walk the +0x2C list calling
// rowed image resolve 0x0035B77D on each node via its +0x18 next. Evidence:
// chain lane callee rowed 0x0035B77D; same ECX-this plus ret plus 22B loop shape
// as packet; callers 0x0031C863 0x0031E850.
class CommandButton
{
public:
	void cacheButtonImage();
	char m_pad00[0x18];
	CommandButton *m_18next;
};

class Rva0031AC39
{
public:
	void rva0031AC39();
private:
	char m_pad00[0x2C];
	CommandButton *m_2C;
};

void Rva0031AC39::rva0031AC39()
{
	for (CommandButton *p = m_2C; p != 0; p = p->m_18next)
		p->cacheButtonImage();
}
