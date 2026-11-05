// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003571B8@ScriptEngine@@QAE_NHABVAsciiString@@_NH@Z, retail 0x003571B8 98B unlock.
// Evidence: bounds 20 plus CRC 0x3ECA13 plus per-player lists at +0x1A268 from dtor,
// 8B entries key at +8 val at +0xC, conditional list<int> erase 0x438539.
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

#include "../../Common/BfmeSpecialPowerTimer8.h"
#include "../../../Include/GameLogic/ScriptEngine.h"

bool ScriptEngine::rva003571B8(int playerIndex, const AsciiString &asciiString, bool remove, int val)
{
	if (playerIndex < 0 || playerIndex >= 20)
		return false;
	_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> > &lst = m_triggeredSpecialPowers[playerIndex];
	unsigned long crc = Rva003ECA13Get(asciiString);
	for (_STL::list<BfmeSpecialPowerTimer8, _STL::allocator<BfmeSpecialPowerTimer8> >::iterator it = lst.begin(); it._M_node != lst.end()._M_node; ++it)
	{
		if (it->m_templateID == crc && (val == 0 || val == it->m_readyFrame))
		{
			if (remove)
				(( _STL::list<int, _STL::allocator<int> > *)&lst)->erase(( _STL::list<int, _STL::allocator<int> >::iterator &)it);
			return true;
		}
	}
	return false;
}
