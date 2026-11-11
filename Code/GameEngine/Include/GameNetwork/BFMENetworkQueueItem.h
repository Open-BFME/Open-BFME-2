// BFMENetworkQueueItem: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMENETWORKQUEUEITEM_H
#define CANONICAL_BFMENETWORKQUEUEITEM_H

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem(const BFMENetworkQueueItem &that);
};

#endif // CANONICAL_BFMENETWORKQUEUEITEM_H
