// cl: /MD /Oy-
// ?xferSTLObjectIDList@@YAPAVXfer@@PAV1@PAVBridgeBehaviorObjectIDList@@@Z @0x00331F2D 196B
// Free ObjectID-list Xfer helper for BridgeBehaviorObjectIDList.
// Evidence: pinned name; callers BezierProjectileBehavior::xfer 0x0045CB23 ArrowStormUpdate::xfer DamageFieldUpdate::xfer RousingSpeechUpdate::xfer GloriousChargeUpdate::xfer; retail strings "std::list" "List must be empty on load"; rowed XferObjectID 0x003060B2 pin push_back 0x002A1B6F FormatText 0x0060C36E Throw 0x00629094; donor ZH Xfer::xferSTLObjectIDList plus BFME2 XferListInt 0x00206861 skeleton.
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_prev;
	ObjectID m_value;
};

class BridgeBehaviorObjectIDList
{
public:
	UnsignedInt size() const
	{
		UnsignedInt n = 0;
		for (BridgeBehaviorObjectIDNode *bridgeBehaviorObjectIDNode = m_node->m_next; bridgeBehaviorObjectIDNode != m_node; bridgeBehaviorObjectIDNode = bridgeBehaviorObjectIDNode->m_next)
			++n;
		return n;
	}
	Bool empty() const
	{
		return m_node->m_next == m_node;
	}
	BridgeBehaviorObjectIDNode *m_node;
};

#include "../../Include/Common/Rva002A1B6FNativeList.h"

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see System/XferException.cpp).
#include "../../Include/Common/XferException.h"


Xfer *xferSTLObjectIDList(Xfer *xfer, BridgeBehaviorObjectIDList *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = list->size();
	(*xfer == "std::list") == count;

	if (xfer->IsStoring()) {
		BridgeBehaviorObjectIDNode *sentinel = list->m_node;
		BridgeBehaviorObjectIDNode *node = sentinel->m_next;
		while (node != sentinel) {
			XferObjectID(xfer, &node->m_value);
			node = node->m_next;
		}
	} else {
		if (!list->empty()) {
			throw XferException(4, "List must be empty on load");
		}
		ObjectID value;
		while (count != 0) {
			--count;
			XferObjectID(xfer, &value);
			((Rva002A1B6FNativeList *)list)->append((void *const &)value);
		}
	}
	return xfer;
}
