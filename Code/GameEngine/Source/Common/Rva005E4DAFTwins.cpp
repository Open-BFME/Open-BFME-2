// cl: /MD
// Native5E4BB7 returns a reference to the four-byte SBServer map value;
// its key is the unchanged int argument. The following is a call-only view
// of that rowed STLport provider, with no additional map layout inferred.
struct SBServer;
namespace _STL {
template<class T> struct less;
template<class A, class B> struct pair;
template<class T> class allocator;
template<class K, class V, class C, class A> class map {
public: V &operator[](const K &);
};
}
typedef _STL::map<int, SBServer, _STL::less<int>,
 _STL::allocator<_STL::pair<const int, SBServer> > > Rva005E4BB7ServerMap;
class Rva005E4BB7 {};
struct Rva005F3F41Outer
{
	void set(unsigned char v);
};
#include "../../Include/GameClient/Rva005F22D2.h"
class Rva005F2406
{
public:
	void rva005F2406(int v);
};
class Rva005E4DAF
{
public:
	void Deselect(int v);
	void Select(int v);
private:
	char m_00[0x14];
	void *m_14;
	char m_pad18[0x1C - 0x18];
	Rva005E4BB7 m_1C;
	char m_pad1D[0x2C - 0x1D];
	bool m_2C;
};
void Rva005E4DAF::Deselect(int v)
{
	if (m_2C) {
		void *ret = &(*reinterpret_cast<Rva005E4BB7ServerMap *>(&m_1C))[v];
		void *server = *(void **)ret;
		void *virtualBaseTable = *(void **)server;
		int r = *(int *)((char *)virtualBaseTable + 4);
		((Rva005F3F41Outer *)(r + (int)server))->set(0);
	}
	((Rva005F22D2 *)m_14)->rva005F2295(v);
}
void Rva005E4DAF::Select(int v)
{
	if (m_2C) {
		void *ret = &(*reinterpret_cast<Rva005E4BB7ServerMap *>(&m_1C))[v];
		void *server = *(void **)ret;
		void *virtualBaseTable = *(void **)server;
		int r = *(int *)((char *)virtualBaseTable + 4);
		((Rva005F3F41Outer *)(r + (int)server))->set(1);
	}
	((Rva005F2406 *)m_14)->rva005F2406(v);
}
