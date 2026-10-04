// cl: /O1 /MD /EHsc
// ?rva005E30CE@Rva005E30CE@@QAEXXZ @0x005E30CE 26B
// Frees owned Rva005E2DEB pointer at +0: tmp = m_ptr; m_ptr = 0; if (tmp) delete tmp.
// Caller 0x005E3258 tail-jmps here. Callee dtor 0x005E2DEB just landed plus rowed delete 0x0002FD60.
// Evidence: chain lane after 0x005E2DEB; prev/next same flags.
class Rva005E2DEB
{
public:
	~Rva005E2DEB();
};

class Rva005E30CE
{
public:
	void rva005E30CE();
private:
	Rva005E2DEB *m_00;
};
void Rva005E30CE::rva005E30CE()
{
	Rva005E2DEB *tmp = m_00;
	m_00 = 0;
	if (tmp)
		delete tmp;
}
