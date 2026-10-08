// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?rva004055F2@Rva00404D70@@QAEXXZ @0x004055F2 146B
// Evidence: chain lane calls just-landed 0x00404BC5 ctor; reads ecx thiscall void; constructs AsciiString Default via rowed 0x00037BA0 then record via rowed 0x00404BC5 then push_back rowed 0x004055BB with releaseBuffer rowed 0x00036410; floats from 0x00BBB8D8 0x00BC2428 0x00BC7A54; vector at +0x120; neighbours share Rva00404D70 layout.
// Like the sibling parameter lookup, retain calls to the existing native
// record-vector push_back worker; only the witnessed12B vector layout is
// needed here. Avoid instantiating unused allocator and growth machinery.
#include "ascii_string.h"
namespace _STL {
 template<class T>class allocator {};
 template<class T,class A=allocator<T> >class vector {
 public:
  void push_back(const T &);
  T &operator[](unsigned int n){return m_start[n];}
  T &back(){return m_finish[-1];}
 private:T *m_start;T *m_finish;T *m_end;
 };
}
extern float g_Va00BBB8D8;
extern float g_Va00BC2428;
extern float g_00BC7A54;
// g_00BC7A54: matched references place it at VA 0xbc7a54 (retail .rdata value 5e+02f).
float g_00BC7A54 = 5e+02f;

struct BfmeStringRecord00404BF3
{
	AsciiString text;
	float f0;
	float f1;
	float f2;
	float f3;
	float f4;
	BfmeStringRecord00404BF3(const AsciiString &s);
};

class Rva00404D70
{
public:
	void rva004055F2();
private:
	char m_pad[0x120];
	_STL::vector<BfmeStringRecord00404BF3> m_vec;
};

void Rva00404D70::rva004055F2()
{
	BfmeStringRecord00404BF3 rec(AsciiString("Default"));
	float a = g_Va00BC2428;
	float b = g_Va00BBB8D8;
	float c = g_00BC7A54;
	rec.f4 = a;
	rec.f0 = b;
	rec.f1 = b;
	rec.f3 = c;
	rec.f2 = b;
	m_vec.push_back(rec);
}

// ?g_Va00BC2428@@3MA: matched references place it at VA 0xbc2428; also referenced as ?g_cloudBreakRadiusDefault@@3MA.
float g_Va00BC2428 = 1e+01f;
#pragma comment(linker, "/alternatename:?g_cloudBreakRadiusDefault@@3MA=?g_Va00BC2428@@3MA")
