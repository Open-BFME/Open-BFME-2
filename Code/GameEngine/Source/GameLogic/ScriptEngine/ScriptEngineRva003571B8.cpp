// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003571B8@ScriptEngine@@QAE_NHABVAsciiString@@_NH@Z, retail 0x003571B8 98B unlock.
// Evidence: bounds 20 plus CRC 0x3ECA13 plus per-player lists at +0x1A268 from dtor,
// 8B entries key at +8 val at +0xC, conditional list<int> erase 0x438539.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

class AsciiString;
unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

struct Rva003571B8Entry
{
	int m_key;
	int m_val;
};

class ScriptEngine
{
public:
	bool rva003571B8(int playerIndex, const AsciiString &s, bool remove, int val);

private:
	char m_pad[0x1A268];
	_STL::list<Rva003571B8Entry, _STL::allocator<Rva003571B8Entry> > m_lists[20]; // +0x1A268
};

bool ScriptEngine::rva003571B8(int playerIndex, const AsciiString &s, bool remove, int val)
{
	if (playerIndex < 0 || playerIndex >= 20)
		return false;
	_STL::list<Rva003571B8Entry, _STL::allocator<Rva003571B8Entry> > &lst = m_lists[playerIndex];
	unsigned long crc = Rva003ECA13Get(s);
	for (_STL::list<Rva003571B8Entry, _STL::allocator<Rva003571B8Entry> >::iterator it = lst.begin(); it._M_node != lst.end()._M_node; ++it)
	{
		if (it->m_key == (int)crc && (val == 0 || val == it->m_val))
		{
			if (remove)
				(( _STL::list<int, _STL::allocator<int> > *)&lst)->erase(( _STL::list<int, _STL::allocator<int> >::iterator &)it);
			return true;
		}
	}
	return false;
}
