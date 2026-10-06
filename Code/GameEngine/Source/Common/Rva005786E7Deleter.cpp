// cl: /MD
// ?rva005786E7@Rva005786E7@@QAEXXZ @0x005786E7 26B
// Evidence: chain via rowed dtor 0x005D3731 and operator delete 0x0002FD60;
// member at +0 nulled then deleted; callers 0x00578939 0x00578CA4
class Rva005D3731
{
public:
	~Rva005D3731();
};

void __cdecl operator delete(void *p);

class Rva005786E7
{
public:
	void rva005786E7();
private:
	Rva005D3731 *m_ptr;
};

void Rva005786E7::rva005786E7()
{
	Rva005D3731 *tmp = m_ptr;
	m_ptr = 0;
	delete tmp;
}
