// PortNegotiationSchema: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_PORTNEGOTIATIONSCHEMA_H
#define CANONICAL_PORTNEGOTIATIONSCHEMA_H

class PortNegotiationSchema
{
public:
	int GetConnectionState(unsigned short x, unsigned short y);
	int getActionID(unsigned short, unsigned short);
	void negotiationStarted(unsigned short a, unsigned short b, int cookie, bool started);
	void *peekPing(unsigned short x, unsigned short y);
	bool receivedAPong(unsigned short, unsigned short, int);
	bool rva005DBA9C(bool);
	bool setPingStats(unsigned short, unsigned short, float, float, float);
};

#endif // CANONICAL_PORTNEGOTIATIONSCHEMA_H
