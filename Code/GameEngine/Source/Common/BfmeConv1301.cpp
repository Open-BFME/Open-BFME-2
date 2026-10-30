// cl: /Od /Gy
// stlport46
// Open-BFME5 conversions.
// ?bfmeOneSUA@BfmeThingSUA@@QAEXD@Z, retail 0x00028BF0 (27B) and
// ?bfmeTwoSUA@BfmeThingSUA@@QAEXD@Z, retail 0x0002A090 (27B). Ported from
// Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1301.cpp (BFME1 0x0082F700
// and 0x00830390). Trimmed to the placed forwarders; Four is
// declared-only here. Callee notes: bfmeFwdOneSUA is defined below for retail
// 0x000274D0 (107B; Ghidra body; int return since the body yields an index or
// -1 through a shared epilogue). The Two-body's target is the rowed
// bfmeAssignV16 at 0x00029490 (same B1 body 0x0082FB10), spelled with its
// rowed BfmeStrV16 name; zero bytes differ either way.

// The byte search is STLport 4.6 find_if<const char *, _Eq_char_bound> at
// 0x00026C60; the predicate is passed as its single char.
#include <string>

// Its body lives in BfmeTwoHundredFiftySeven_FindByte.cpp; do not instantiate
// a second /Od copy here.
extern template const char *_STL::find_if(const char *, const char *,
	_STL::_Eq_char_bound<_STL::char_traits<char> >);

typedef const char *(__cdecl *FindIfEqChar1301Fn)(const char *first, const char *last,
	_STL::_Eq_char_bound<_STL::char_traits<char> > pred);
typedef char *(__cdecl *FindByte1301Fn)(char *first, char *last, char wanted);

class BfmeThingSUA
{
public:
	char *m_begin;
	char *m_end;
	void bfmeOneSUA(char a);
	void bfmeTwoSUA(char a);
	void bfmeThreeSUA(char a, int b);
	void bfmeFourSUA(int a, int b);
	int bfmeFwdOneSUA(char a, int b);
	void bfmeFwdThreeSUA(char a, int b);
};

class BfmeStrV16
{
public:
	BfmeStrV16 *bfmeAssignV16(unsigned int id, char tag);
};

// ?bfmeOneSUA@BfmeThingSUA@@QAEXD@Z
void BfmeThingSUA::bfmeOneSUA(char a)
{
	bfmeFwdOneSUA(a, 0);
}

// ?bfmeTwoSUA@BfmeThingSUA@@QAEXD@Z
void BfmeThingSUA::bfmeTwoSUA(char a)
{
	((BfmeStrV16 *)this)->bfmeAssignV16(1, a);
}

// ?bfmeThreeSUA@BfmeThingSUA@@QAEXDH@Z
void BfmeThingSUA::bfmeThreeSUA(char a, int b)
{
	bfmeFwdThreeSUA(a, b);
}

// ?bfmeFwdOneSUA@BfmeThingSUA@@QAEHDH@Z
int BfmeThingSUA::bfmeFwdOneSUA(char a, int b)
{
	if ((unsigned int)b >= (unsigned int)(m_end - m_begin))
		return -1;
	char ch = a;
	char *found = reinterpret_cast<FindByte1301Fn>(static_cast<FindIfEqChar1301Fn>(
		&_STL::find_if))(m_begin + b, m_end, ch);
	return (found != m_end) ? (int)(found - m_begin) : -1;
}
