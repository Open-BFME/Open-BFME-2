// cl: /O1 /DNDEBUG /MD
//
// PeerThreadClass::findServerByID (0x003896BD, 42B), ported from the Zero
// Hour donor (GameSpy/Thread/PeerThread.cpp; PeerThread.cpp here is /O1 too).
// Thread_Function 0x0038EDD7's join-staging and extended-info arms call it on
// the thread object with the request id (the pinned name). Retail looks the id
// up in the staging-server map at +0x278 and, as the donor does, returns null
// for a server without keyvals (+0x18); the release build has no DEBUG_CRASH.
// Returning it->second when the server is null reuses the zero already in
// eax, which is retail's direct branch to the ret.
//
// Target facts: the +0x278 map offset, the +0x14 node value and +0x18 field
// come from the retail bytes. Carried from the donor: the names and the map's
// int key -> SBServer type.
struct _SBServer
{
	char m_pad[0x18];
	void *keyvals; // +0x18
};
typedef _SBServer *SBServer;

struct Rva003896BDNode
{
	char m_pad[0x10];
	int first;			// +0x10
	SBServer second;	// +0x14
};

#include "../../../../Include/GameNetwork/GameSpy/PeerThreadClass.h"

// The int-keyed map's lookup is the rowed STLport map<int,int> _M_find<int>
// 0x00388F63: it takes the key's address and returns the node or the
// header, which is end().
namespace _STL {
template <class T1, class T2> struct pair { T1 first; T2 second; };
template <class P> struct _Select1st {};
template <class T> struct less {};
template <class T> class allocator {};
template <class V> struct _Rb_tree_node;
template <class K, class V, class KOV, class Cmp, class Alloc> class _Rb_tree
{
	friend class ::PeerThreadClass;
	typedef _Rb_tree_node<V> *_Link_type;
private:
	template <class KT> _Link_type _M_find(const KT &) const;
};
}

typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;

struct Rva003896BDServerMap
{
	Rva003896BDNode *end() { return m_header; }
	Rva003896BDNode *m_header;
};

// Staging-server map view at +0x278 (the canonical m_278).
struct Rva003896BDState
{
	char m_pad00[0x278];
	Rva003896BDServerMap m_stagingServers; // +0x278
};

SBServer PeerThreadClass::findServerByID(int id)
{
	Rva003896BDServerMap &stagingServers = reinterpret_cast<Rva003896BDState *>(this)->m_stagingServers;
	Rva003896BDNode *it = (Rva003896BDNode *)((MapIntIntTree *)&stagingServers)->_M_find(id);
	if (it != stagingServers.end())
	{
		SBServer server = it->second;
		if (server && !server->keyvals)
		{
			return 0;
		}
		return it->second;
	}
	return 0;
}
