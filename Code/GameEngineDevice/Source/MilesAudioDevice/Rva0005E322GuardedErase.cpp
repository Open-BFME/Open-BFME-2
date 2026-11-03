// cl: /O1 /G7 /MD /EHsc
// MilesAudioManager slot 45 guards the per-view name sets at +0xA14.
// The mutex at +0x9D4 protects the indexed erase through the rowed tree.

class AsciiString;

#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"

// LINK: the 12-byte tree is rowed as the STLport red-black tree over
// Rva0005B5EAElement keys (0x0005B5EA); the key is the AsciiString words.
struct Rva0005B5EAElement;
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class T> struct _Select1st;
template <class K, class V, class S, class C, class A> class _Rb_tree
{
public:
	unsigned erase(const K &key);
private:
	char m_space[0x0C];
};
}
typedef _STL::_Rb_tree<Rva0005B5EAElement, _STL::pair<const Rva0005B5EAElement, int>,
	_STL::_Select1st<_STL::pair<const Rva0005B5EAElement, int> >, _STL::less<Rva0005B5EAElement>,
	_STL::allocator<_STL::pair<const Rva0005B5EAElement, int> > > Rva0005E322TreeView;

class MilesAudioManager
{
public:
	virtual void rva0005E322(const AsciiString *key, int idx);
private:
	char m_pad[0x9D4 - 4];
	char m_mutexzone[4]; // +0x9D4
};

void MilesAudioManager::rva0005E322(const AsciiString *key, int idx)
{
	MilesMutexGuard guard(m_mutexzone, 0);
	Rva0005E322TreeView *names = reinterpret_cast<Rva0005E322TreeView *>(
		reinterpret_cast<char *>(this) + (idx + 0xA14 / sizeof(Rva0005E322TreeView)) * sizeof(Rva0005E322TreeView));
	names->erase(*reinterpret_cast<const Rva0005B5EAElement *>(key));
}
