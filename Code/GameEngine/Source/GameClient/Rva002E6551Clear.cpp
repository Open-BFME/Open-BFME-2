// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ?rva002E6551@Rva002E6551@@QAEXXZ 0x002E6551 96B
// Evidence: chain from 0x002E6158 and 0x002E5711; clears +0x2c +0x30 Rva002E6158 ptrs plus +0x24 Rva002E5711 list then byte +0x1d; caller 0x002E6710.
class Rva002E5791
{
public:
	~Rva002E5791();
};

class Rva002E6158
{
public:
	~Rva002E6158();
};

class Rva002E5711
{
public:
	~Rva002E5711();
};

class Rva002E6551
{
public:
	void rva002E6551();

private:
	char m_pad00[0x1d];
	unsigned char m_flag1d;
	char m_pad1e[0x06];
	Rva002E5711 *m_list24;
	char m_pad28[0x04];
	Rva002E6158 *m_ptr2c;
	Rva002E6158 *m_ptr30;
};

void Rva002E6551::rva002E6551()
{
	Rva002E6158 *ptr = m_ptr2c;
	if (ptr)
	{
		ptr->~Rva002E6158();
		::operator delete(ptr);
		m_ptr2c = 0;
	}
	ptr = m_ptr30;
	if (ptr)
	{
		ptr->~Rva002E6158();
		::operator delete(ptr);
		m_ptr30 = 0;
	}
	Rva002E5711 *cur = m_list24;
	if (cur)
	{
		do
		{
			Rva002E5711 *next = *(Rva002E5711 **)cur;
			cur->~Rva002E5711();
			::operator delete(cur);
			cur = next;
		} while (cur);
	}
	m_list24 = 0;
	m_flag1d = 0;
}
