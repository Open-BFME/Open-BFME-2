// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /Gy
// stlport
//
// ?GetBlingIndex@CreateAHeroSubClass@CreateAHeroManager@@QAEHHABVAsciiString@@@Z
// @0x0021BD41 106B (WorldBuilder CreateAHeroManager::CreateAHeroSubClass::
// GetBlingIndex): looks the bling key up through the rowed map find 0x0021BC0D
// and returns the index of the first bling whose name (+8, rowed
// StringBase::compare) equals the given name, else -1.
//
// Evidence: retail walks the found node's vector (+0x14/+0x18) with the size
// computed begin-first (`end - begin`, begin kept in eax for the element push),
// and keeps the node in esi with no copy of `this`: the compiler knew the find
// leaves ecx alone. MSVC only knows that for an out-of-line callee defined
// earlier in the same TU, so the find body owns its row here ahead of the
// caller. The redundant standalone definition has been removed.
#include <map>
#include <vector>
#include "ascii_string.h"

// Take less<int> inline so no external COMDAT copy is emitted.
// Keep the library accessors inline without emitting unused alternate COMDATs.
// These bodies are the STLport 4.5.3 _vector.h definitions; call sites remain
// byte-exact and no __imp_ reference may survive.
namespace _STL {
template <> __declspec(dllimport) __forceinline
unsigned int *vector<unsigned int>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
unsigned int *vector<unsigned int>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
unsigned int &vector<unsigned int>::operator[](size_type n) { return *(begin() + n); }
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

#include "../../../Include/GameLogic/CreateAHeroManager.h"

extern CreateAHeroManager *TheCreateAHeroManager;

struct MapNodeVec2
{
	char hdr[0x14];
	_STL::vector<unsigned int> m_vec;
};

struct CreateAHeroManager::CreateAHeroSubClass
{
	char pad[0x24];
	_STL::map<int, _STL::vector<unsigned int> > m_map;
	unsigned char rva0021BC0D(int key, void **out);
	int GetBlingIndex(int key, const AsciiString &name);
};

unsigned char CreateAHeroManager::CreateAHeroSubClass::rva0021BC0D(int key, void **out)
{
	// the original standalone copy saw the same tree as map<int, int>:
	// preserve that view so the helper calls the same _M_find instantiation
	_STL::map<int, int> &tree = *(_STL::map<int, int> *)&m_map;
	_STL::map<int, int>::iterator it = tree.find(key);
	*out = it._M_node;
	return it._M_node != tree.end()._M_node;
}

int CreateAHeroManager::CreateAHeroSubClass::GetBlingIndex(int key, const AsciiString &name)
{
	void *node = 0;
	if (rva0021BC0D(key, &node))
	{
		MapNodeVec2 *mapNodeVec2 = (MapNodeVec2 *)node;
		for (unsigned int i = 0; i < (unsigned int)(mapNodeVec2->m_vec.end() - mapNodeVec2->m_vec.begin()); ++i) {
			void *elem = TheCreateAHeroManager->GetBling(mapNodeVec2->m_vec[i]);
			if (elem && ((const StringBase<char> *)((const char *)elem + 8))->compare(*(const StringBase<char> *)&name) == 0)
				return (int)i;
		}
	}
	return -1;
}
