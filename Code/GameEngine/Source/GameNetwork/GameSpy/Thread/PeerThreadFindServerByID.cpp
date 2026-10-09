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

// The int-keyed map's find (pinned view 0x00388F63, the folded STLport
// _M_find<int>): it takes the key's address and returns the node or the
// header, which is end().
struct Rva00388F63Map
{
	void *find(int *key);
	Rva003896BDNode *end() { return m_header; }
	Rva003896BDNode *m_header;
};

class PeerThreadClass
{
public:
	SBServer findServerByID(int id);

private:
	char m_pad00[0x278];
	Rva00388F63Map m_stagingServers; // +0x278
};

SBServer PeerThreadClass::findServerByID(int id)
{
	Rva003896BDNode *it = (Rva003896BDNode *)m_stagingServers.find(&id);
	if (it != m_stagingServers.end())
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
