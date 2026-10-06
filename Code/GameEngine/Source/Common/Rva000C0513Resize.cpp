// cl: /MD
//
// ?rva000C0513@Rva000C0513@@QAEXIUCoord3D@@@Z, retail 0x000C0513, 73 bytes.
// Resize-shaped helper over a 12-byte element vector at +0: when the count
// is below the size it erases the tail through the rowed Gen_p12pod erase
// 0x002A133B, otherwise it grows through the rowed Coord3D fill_insert
// 0x004E29C8. Both callees share the 12-byte POD layout.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Gen_p12pod
{
	char m_bytes[12];
};

namespace _STL
{

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <>
class vector<Coord3D, allocator<Coord3D> >
{
public:
	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_end;
	void _M_fill_insert(Coord3D *pos, unsigned int n, const Coord3D &val);
};

template <>
class vector<Gen_p12pod, allocator<Gen_p12pod> >
{
public:
	Gen_p12pod *m_start;
	Gen_p12pod *m_finish;
	Gen_p12pod *m_end;
	Gen_p12pod *erase(Gen_p12pod *first, Gen_p12pod *last);
};

}

class Rva000C0513
{
public:
	void rva000C0513(unsigned int n, Coord3D val);
private:
	_STL::vector<Coord3D, _STL::allocator<Coord3D> > m_vec;
};

void Rva000C0513::rva000C0513(unsigned int n, Coord3D val)
{
	Coord3D *start = m_vec.m_start;
	Coord3D *finish = m_vec.m_finish;
	unsigned int size = (unsigned int)(finish - start);
	if (n < size)
	{
		Gen_p12pod *efirst = (Gen_p12pod *)(start + n);
		Gen_p12pod *elast = (Gen_p12pod *)finish;
		((_STL::vector<Gen_p12pod, _STL::allocator<Gen_p12pod> > *)&m_vec)->erase(efirst, elast);
	}
	else
	{
		m_vec._M_fill_insert(m_vec.m_finish, n - (unsigned int)(m_vec.m_finish - start), val);
	}
}
