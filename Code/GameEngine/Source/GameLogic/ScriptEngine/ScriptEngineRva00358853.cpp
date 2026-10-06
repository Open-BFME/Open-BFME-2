// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00358853@ScriptEngine@@QAEPAUBfmeStringRecord00204A30@@ABVAsciiString@@0M0H@Z @0x00358853 148B.
// ScriptEngine get-or-create helper over the vector<BfmeStringRecord00204A30>
// at +0x1A49C: CRCs the name via rowed Rva003ECA13Get, scans the 0x14-stride
// array for the CRC, returns the hit, else builds a temp record, push_backs
// it and destroys the temp. Class proven by caller 0x003BC9E0 (ecx is the
// ScriptEngine singleton g_Va009FE16C); layout matches the rowed dtor
// ??1BfmeStringRecord00204A30@@QAE@XZ (word text float text word = 0x14).
// Evidence: EH_prolog frame, loop cmp [eax],ebx stride 0x14 to end pointer,
// two StringBase::set calls, movss float, rowed push_back 0x0020A25E,
// ret 0x14 (5 stack args).
#include "ascii_string.h"

unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);
// ?Rva003ECA13Get@@YAKABVAsciiString@@@Z rowed realcrc one-arg in realcrc_one_arg.cpp

struct BfmeStringRecord00204A30
{
	unsigned long word0;
	AsciiString text0;
	float word1;
	AsciiString text1;
	int word2;
	~BfmeStringRecord00204A30();
};

namespace _STL {
template <typename T> class allocator
{
};
template <typename T, typename A> class vector
{
public:
	void push_back(const T &x);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class ScriptEngine
{
	char m_pad[0x1a49c];
public:
	_STL::vector<BfmeStringRecord00204A30, _STL::allocator<BfmeStringRecord00204A30> > m_vec;
	BfmeStringRecord00204A30 *rva00358853(const AsciiString &name, const AsciiString &text0, float word1, const AsciiString &text1, int word2);
};

BfmeStringRecord00204A30 *ScriptEngine::rva00358853(const AsciiString &name, const AsciiString &text0, float word1, const AsciiString &text1, int word2)
{
	unsigned long crc = Rva003ECA13Get(name);
	BfmeStringRecord00204A30 *begin = m_vec.m_start;
	BfmeStringRecord00204A30 *end = m_vec.m_finish;
	for (BfmeStringRecord00204A30 *p = begin; p != end; ++p) {
		if (p->word0 == crc)
			return p;
	}
	BfmeStringRecord00204A30 rec;
	((StringBase<char> *)&rec.text1)->set(*(const StringBase<char> *)&text1);
	rec.word1 = word1;
	rec.word0 = crc;
	((StringBase<char> *)&rec.text0)->set(*(const StringBase<char> *)&text0);
	rec.word2 = word2;
	m_vec.push_back(rec);
}
