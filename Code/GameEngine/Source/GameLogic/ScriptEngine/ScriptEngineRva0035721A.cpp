// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0035721A@ScriptEngine@@QAE_NHABVAsciiString@@_NH@Z, retail 0x0035721A 98B leaf.
// Evidence: same shape as ScriptEngine 0x003571B8 (bounds 20 CRC 0x3ECA13
// per-player lists 8B entries key +8 val +0xC conditional list<int> erase
// 0x438539); lists at +0x1A2B8 from ScriptEngine_dtor.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

class AsciiString;
unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

struct Rva0035721AEntry
{
	int m_key;
	int m_val;
};

class ScriptEngine
{
public:
	bool rva0035721A(int playerIndex, const AsciiString &s, bool remove, int val);

private:
	char m_pad[0x1A2B8];
	_STL::list<Rva0035721AEntry, _STL::allocator<Rva0035721AEntry> > m_lists[20]; // +0x1A2B8
};

bool ScriptEngine::rva0035721A(int playerIndex, const AsciiString &s, bool remove, int val)
{
	if (playerIndex < 0 || playerIndex >= 20)
		return false;
	_STL::list<Rva0035721AEntry, _STL::allocator<Rva0035721AEntry> > &lst = m_lists[playerIndex];
	unsigned long crc = Rva003ECA13Get(s);
	for (_STL::list<Rva0035721AEntry, _STL::allocator<Rva0035721AEntry> >::iterator it = lst.begin(); it != lst.end(); ++it)
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
