// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /DNDEBUG /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?setShellMenuScheme@ShellMenuSchemeManager@@QAEXVAsciiString@@@Z @0x002005DE 124B.
// ShellMenuSchemeManager::setShellMenuScheme. Evidence: BFME1 donor
// GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp setShellMenuScheme
// (empty guard + toLower + list search + compare + store current); rowed
// StringBase<D> releaseBuffer 0x00036410 and toLower 0x00036A70 and compare
// 0x000069D6; caller 0x0035C49C passes Shell+0x64 manager with by-value string.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class ShellMenuScheme
{
public:
	AsciiString m_name;
};

class ShellMenuSchemeManager
{
public:
	void setShellMenuScheme(AsciiString name);
private:
	_STL::list<ShellMenuScheme *> m_schemeList;
	ShellMenuScheme *m_currentScheme;
};

void ShellMenuSchemeManager::setShellMenuScheme(AsciiString name)
{
	if (name.isEmpty()) {
		m_currentScheme = 0;
		return;
	}

	_STL::list<ShellMenuScheme *>::iterator it = m_schemeList.begin();
	((StringBase<char> &)name).toLower();
	while (it != m_schemeList.end()) {
		ShellMenuScheme *scheme = *it;
		if (scheme->m_name.compare(name) == 0) {
			m_currentScheme = scheme;
			break;
		}
		++it;
	}
}
