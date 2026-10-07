// ?removeServerFromMap@PeerThreadClass@@QAEHPAU_SBServer@@@Z
// partial score=0.8 date=2026-10-07
struct BfmeWordValue4
{
	unsigned int bits;
};

class Rva00388EAE
{
public:
	UnsignedInt rva00389913(const Int &key);
	void rva00389129();
};

struct PeerStagingServerMapView
{
	unsigned char beforeMap[0x278];
	std::map<Int, SBServer> servers;
};

// Retail addServerToMap reads the next key at +0x274 and the staging map at
// +0x278. Keep the retail map value type here so this TU also emits the
// matched map<int, SBServer> tree insertion helpers.
#define BFME_PEER_NEXTSTAGING(p) (*(Int *)((char *)(p) + 0x274))
#define BFME_PEER_STAGINGMAP(p)  (*(std::map<Int, SBServer> *)((char *)(p) + 0x278))
// ?addServerToMap@PeerThreadClass@@QAEHPAU_SBServer@@@Z present-unmatched
Int PeerThreadClass::addServerToMap( SBServer server )
{
	Int val = BFME_PEER_NEXTSTAGING(this)++;
	BFME_PEER_STAGINGMAP(this)[val] = server;
	return val;
}

template SBServer& std::map<Int, SBServer>::operator[]( const Int& );

// ?removeServerFromMap@PeerThreadClass@@ present-unmatched
Int PeerThreadClass::removeServerFromMap( SBServer server )
{
	_STL::_Deque_base<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > wordHandles(_STL::allocator<BfmeWordValue4>(), 0);
	PeerStagingServerMapView *view = (PeerStagingServerMapView *)this;
	for (std::map<Int, SBServer>::iterator it = view->servers.begin(); it != view->servers.end(); ++it)
	{
		if (it->second == server)
			((std::deque<void *> *)&wordHandles)->push_back(*(void **)&it->first);
	}

	Int result = 0;
	while (!((std::deque<void *> *)&wordHandles)->empty())
	{
		result = (Int)((std::deque<void *> *)&wordHandles)->front();
		server = reinterpret_cast<SBServer>(result);
		((Rva00388EAE *)&view->servers)->rva00389913(*(Int *)&server);
		((std::deque<void *> *)&wordHandles)->pop_front();
	}
	return result;
}

