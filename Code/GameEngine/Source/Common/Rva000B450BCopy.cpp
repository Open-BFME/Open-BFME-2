// cl: /DNDEBUG /MD
// ??0Rva000B450B@@QAE@ABV0@@Z @0x000B450B 33B
// Copy ctor: gslice member at +0 copy-constructed via pinned ??0gslice@_STL,
// Rva000B3F15 member at +0x14 assigned via rowed ??4Rva000B3F15; stride 0x18
// matches caller 0x000B690B array loop.
namespace _STL
{
class gslice
{
public:
	gslice(const gslice &o);
private:
	char m_pad[0x14];
};
}

class Rva000B3F15
{
public:
	Rva000B3F15 &operator=(const Rva000B3F15 &o);
private:
	void *m_ptr;
};

class Rva000B450B
{
public:
	Rva000B450B(const Rva000B450B &o);
private:
	_STL::gslice m_slice;
	Rva000B3F15 m_other;
};

Rva000B450B::Rva000B450B(const Rva000B450B &o) : m_slice(o.m_slice)
{
	m_other = o.m_other;
}
