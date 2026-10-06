// ??0Rva004E7D72@@QAE@PAX@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva004E7D72@@QAE@PAX@Z @ 0x004E7D72, 86 bytes.
// EH ctor (parent, 0, 0) plus list at +0xC via rowed _List_base 0x00280A8D,
// map<int,void*> at +0x10 via rowed 0x0033C432, member at +0x1C via pinned
// no-arg ctor 0x004E5610. Same shape as the rowed 0x004E6745 factory's
// new-expression target Rva004E7D72(void*) here defined in full.
#include <list>
#include <map>

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva004E5610
{
public:
	Rva004E5610();

private:
	char m_pad[0x0C];
};

struct Rva004E7D72Base
{
	void *m_00;
	int m_04;
	int m_08;
	Rva004E7D72Base(void *parent)
		: m_00(parent)
		, m_04(0)
		, m_08(0)
	{
	}
	~Rva004E7D72Base()
	{
	}
};

class Rva004E7D72 : public Rva004E7D72Base
{
public:
	Rva004E7D72(void *parent);

private:
	_STL::list<Coord3D> m_list0C;
	_STL::map<int, void *> m_map10;
	Rva004E5610 m_1C;
};

Rva004E7D72::Rva004E7D72(void *parent)
	: Rva004E7D72Base(parent)
	, m_list0C()
	, m_map10()
	, m_1C()
{
}
