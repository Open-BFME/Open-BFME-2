// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0035727C@ScriptEngine@@QAE_NHABVAsciiString@@_NH@Z, retail 0x0035727C 98B leaf.
// Evidence: same shape as ScriptEngine 0x003571B8 (bounds 20 CRC 0x3ECA13
// per-player lists 8B entries key +8 val +0xC conditional list<int> erase
// 0x438539); lists at +0x1A308 from ScriptEngine_dtor.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}
#include <algorithm>

class AsciiString;
unsigned long __cdecl Rva003ECA13Get(const AsciiString &s);

struct Rva0035727CEntry
{
	int m_key;
	int m_val;
};

class ScriptEngine
{
public:
	bool rva0035727C(int playerIndex, const AsciiString &s, bool remove, int val);

private:
	char m_pad[0x1A308];
	_STL::list<Rva0035727CEntry, _STL::allocator<Rva0035727CEntry> > m_lists[20]; // +0x1A308
};

bool ScriptEngine::rva0035727C(int playerIndex, const AsciiString &s, bool remove, int val)
{
	if (playerIndex < 0 || playerIndex >= 20)
		return false;
	_STL::list<Rva0035727CEntry, _STL::allocator<Rva0035727CEntry> > &lst = m_lists[playerIndex];
	unsigned long crc = Rva003ECA13Get(s);
	for (_STL::list<Rva0035727CEntry, _STL::allocator<Rva0035727CEntry> >::iterator it = lst.begin(); it._M_node != lst.end()._M_node; ++it)
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
