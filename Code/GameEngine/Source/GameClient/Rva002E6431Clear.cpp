// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ?rva002E6431@Rva002E6431@@QAEXXZ 0x002E6431 32B
// Evidence: chain from 0x002E6158; clears +0x30 Rva002E6158 ptr via dtor plus scalar delete; callers none yet.
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

class Rva002E6431
{
public:
	void rva002E6431();

private:
	char m_pad[0x30];
	Rva002E6158 *m_ptr30;
};

void Rva002E6431::rva002E6431()
{
	Rva002E6158 *ptr = m_ptr30;
	if (ptr)
	{
		ptr->~Rva002E6158();
		::operator delete(ptr);
		m_ptr30 = 0;
	}
}
