// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?rva00405684@Rva00404D70@@QAEPAUBfmeStringRecord00404BF3@@ABVAsciiString@@@Z @0x00405684 105B
// Evidence: calls rowed find 0x00404D70 tests 0x7fffffff scales 0x18 from start at +0x120; else ctor row 0x00404BC5 push_back row 0x004055BB releaseBuffer row 0x00036410 returns finish-0x18; caller 0x00215D96 passes AsciiString for initFromINI.
// The retail provider calls the established record-vector push_back55B
// at4055BB; this TU needs only its declaration and the native three-pointer
// indexed/back accessors. Importing vector's unused growth machinery emitted
// allocator/cleanup copies that diverged from the existing kept providers.
// This bounded template view preserves element24B and vector12B without
// defining those out-of-line workers again.
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
	int rva00404D70(const AsciiString &s);
	BfmeStringRecord00404BF3 *rva00405684(const AsciiString &s);
private:
	char m_pad[0x120];
	_STL::vector<BfmeStringRecord00404BF3> m_vec;
};

BfmeStringRecord00404BF3 *Rva00404D70::rva00405684(const AsciiString &s)
{
	int idx = rva00404D70(s);
	if (idx != 0x7fffffff)
		return &m_vec[idx];
	m_vec.push_back(BfmeStringRecord00404BF3(s));
	return &m_vec.back();
}
