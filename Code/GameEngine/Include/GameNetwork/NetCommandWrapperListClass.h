// NetCommandWrapperList: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_NETCOMMANDWRAPPERLIST_H
#define CANONICAL_NETCOMMANDWRAPPERLIST_H

class NetCommandList;
class NetCommandRef;

class NetCommandWrapperList
{
public:
	int getPercentComplete(unsigned short wrappedCommandID);
	NetCommandList *getReadyCommands();
	void processWrapper(NetCommandRef *ref);
};

#endif // CANONICAL_NETCOMMANDWRAPPERLIST_H
