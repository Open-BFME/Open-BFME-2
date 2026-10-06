// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva003323AD@@QAE@ABV?$StringBase@D@@@Z @0x003323AD 37B
// retail 0x003323AD 37 bytes unlock ctor StringBase at +0 flag +4 vector BfmeE16 at +8
// via pinned StringBase copy 0x000365F0 and rowed Vector_base 0x00211E58 callers 0x00337E48 0x00337F39
// neighbours prev 0x00331FF1 Destroy and next 0x003323D2 Assign

#include <vector>

template <class T> class StringBase
{
public:
private:
	void *m_data;
private:
	StringBase(const StringBase &other);
	friend class BfmeE16;
	friend class Rva003323AD;
};

struct BfmeE16 { float x; float y; float z; float w; };

class Rva003323AD
{
public:
	Rva003323AD(const StringBase<char> &s);
private:
	StringBase<char> m_str;
	bool m_flag;
	unsigned char m_pad05[3];
	_STL::vector<BfmeE16> m_vec;
};

Rva003323AD::Rva003323AD(const StringBase<char> &s) : m_str(s), m_flag(true), m_vec()
{
}
