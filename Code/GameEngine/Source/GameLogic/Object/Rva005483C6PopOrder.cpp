// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva005483C6@Rva005483C6@@QAEXXZ, retail 0x005483C6 (68 bytes): pop the
// last NameKeyType of the list<int> at +4. With an entry present, clear
// +0x0C when +0x08 is empty, clear +0x10, forget +0x08 when it names the
// popped key, hand the key to the rowed cdecl rva005480E8 0x005480E8 with
// the object at +0 and 1, then tail-call the rowed list<int>::pop_back
// 0x00053D4F. Field meanings and the owner's name are not established.
#include <list>
// list<int>'s iterator operator-- is inlined here; imported, this unit emits no
// non-retail out-of-line copy of it (STLport body verbatim).
namespace _STL {
template <> __declspec(dllimport) __forceinline
_List_iterator<int, _Nonconst_traits<int> > &_List_iterator<int, _Nonconst_traits<int> >::operator--()
{
	this->_M_decr();
	return *this;
}
}

namespace _STL {
template <> void list<int, allocator<int> >::pop_back();
}

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/NameKeyType.h"




void __cdecl rva005480E8(void *first, NameKeyType key, int third);

class Rva005483C6
{
public:
	void rva005483C6();
private:
	void *m_owner;			// +0x00
	_STL::list<int> m_keys;		// +0x04
	int m_current;			// +0x08
	int m_0C;
	int m_10;
};

void Rva005483C6::rva005483C6()
{
	if (m_keys.empty())
		return;
	int last = m_keys.back();
	if (m_current == 0)
		m_0C = 0;
	m_10 = 0;
	if (last == m_current)
		m_current = 0;
	rva005480E8(m_owner, (NameKeyType)m_keys.back(), 1);
	m_keys.pop_back();
}
