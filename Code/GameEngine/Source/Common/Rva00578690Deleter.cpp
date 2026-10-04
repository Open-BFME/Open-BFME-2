// cl: /O1 /MD
// ?rva00578690@Rva00578690@@QAEXXZ @0x00578690 26B: nulling deleter via explicit virtual dtor plus global operator delete.
// Evidence: callees rowed 0x005D25F2 ??1Rva005D25F2@@UAE@XZ and rowed 0x0002FD60 ??3@YAXPAX@Z; callers 0x005787FB 0x00578CBC; same 26B shape as Rva005786E7Deleter sibling.
class Rva005D25F2
{
public:
	virtual ~Rva005D25F2();
};

void __cdecl operator delete(void *p);

class Rva00578690
{
public:
	void rva00578690();
private:
	Rva005D25F2 *m_ptr;
};

void Rva00578690::rva00578690()
{
	Rva005D25F2 *tmp = m_ptr;
	m_ptr = 0;
	if (tmp == 0)
		return;
	tmp->Rva005D25F2::~Rva005D25F2();
	operator delete(tmp);
}
