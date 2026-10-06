// cl: /MD
//
// ?rva000C18E3@Rva000C18E3@@QAEXPAUSrcArg000C18E3@@@Z, retail 0x000C18E3, 186 bytes.
// Chain of the landed 0x000C0513 resize: if the source block is null it
// erases the six 12-byte vectors at +0xC8 through the rowed Gen erase
// 0x002A133B, otherwise it resizes each through the rowed 0x000C0513
// helper and zeroes the Coord3D range. Src stride 0x3C, dst stride 0xC.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Dst12
{
	int a;
	float b;
	float c;
};

struct Src60
{
	char m_bytes[60];
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
};

template <>
class vector<Src60, allocator<Src60> >
{
public:
	Src60 *m_start;
	Src60 *m_finish;
	Src60 *m_end;
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

template <>
class vector<Dst12, allocator<Dst12> >
{
public:
	Dst12 *m_start;
	Dst12 *m_finish;
	Dst12 *m_end;
};

}

class Rva000C0513
{
public:
	void rva000C0513(unsigned int n, Coord3D val);
};

struct SrcArg000C18E3
{
	char m_pad[0xAC];
	_STL::vector<Src60, _STL::allocator<Src60> > m_src[6];
};

class Rva000C18E3
{
public:
	void rva000C18E3(SrcArg000C18E3 *p);
private:
	char m_pad[0xC8];
	_STL::vector<Dst12, _STL::allocator<Dst12> > m_dst[6];
};

void Rva000C18E3::rva000C18E3(SrcArg000C18E3 *p)
{
	if (!p)
	{
		for (int i = 0; i < 6; ++i)
		{
			_STL::vector<Dst12, _STL::allocator<Dst12> > &v = m_dst[i];
			((_STL::vector<Gen_p12pod, _STL::allocator<Gen_p12pod> > *)&v)->erase((Gen_p12pod *)v.m_start, (Gen_p12pod *)v.m_finish);
		}
		return;
	}
	for (int i = 0; i < 6; ++i)
	{
		_STL::vector<Src60, _STL::allocator<Src60> > &s = p->m_src[i];
		_STL::vector<Dst12, _STL::allocator<Dst12> > &d = m_dst[i];
		unsigned int sn = (unsigned int)(s.m_finish - s.m_start);
		unsigned int dn = (unsigned int)(d.m_finish - d.m_start);
		if (dn != sn)
		{
			Dst12 zero;
			zero.a = 0;
			zero.b = 0;
			zero.c = 0;
			((Rva000C0513 *)&d)->rva000C0513(sn, *(Coord3D *)&zero);
		}
		for (Dst12 *q = d.m_start; q != d.m_finish; ++q)
		{
			q->a = 0;
			q->b = 0;
			q->c = 0;
		}
	}
}
