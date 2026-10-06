// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??0Rva00502909Sub@@QAE@ABU0@@Z, retail 0x005026EE 153B.
// Subobject copy ctor: 4 ints then 5 vector<ScienceType> then map<int Rva00501130Mapped>.
// Evidence: rowed vector copy 0x0054878E x5 and rowed rb_tree copy 0x00501E88; element copy 0x00502909 tail-calls it; neighbours share stlport /O1 /EHsc flags.
#include <map>
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

struct Rva00501130Mapped
{
	int a[5];
};

struct Rva00502909Sub
{
	Rva00502909Sub(const Rva00502909Sub &o);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	_STL::vector<ScienceType> m_10;
	_STL::vector<ScienceType> m_1c;
	_STL::vector<ScienceType> m_28;
	_STL::vector<ScienceType> m_34;
	_STL::vector<ScienceType> m_40;
	_STL::map<int, Rva00501130Mapped> m_4c;
};

Rva00502909Sub::Rva00502909Sub(const Rva00502909Sub &o)
	: m_00(o.m_00)
	, m_04(o.m_04)
	, m_08(o.m_08)
	, m_0c(o.m_0c)
	, m_10(o.m_10)
	, m_1c(o.m_1c)
	, m_28(o.m_28)
	, m_34(o.m_34)
	, m_40(o.m_40)
	, m_4c(o.m_4c)
{
}
