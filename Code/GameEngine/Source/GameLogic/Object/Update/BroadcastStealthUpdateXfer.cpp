// cl: /DNDEBUG /MD
//
// ?xfer@BroadcastStealthUpdate@@MAEXPAVXfer@@@Z, retail 0x004A3752, 202 bytes.
// Slot 3 of ??_7BroadcastStealthUpdate 0x00C52364 (slot-2 name getter
// returns "BroadcastStealthUpdate"; the rowed dtor 0x004A3555 installs it).
// The rowed UpdateModule::xfer 0x0044DF9F first, then the light-CRC out,
// Version(1,2), from version 2 the upgrade mux on the +0x20 subobject (rowed
// upgradeMuxXfer 0x004CE397), then the object-ID list at +0x28: count and
// ids when storing, count then XferObjectID plus the rowed list push_back
// 0x002A1B6F when loading (BridgeBehaviorXfer's list view).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

struct BridgeBehaviorObjectIDNode
{
	BridgeBehaviorObjectIDNode *m_next;
	BridgeBehaviorObjectIDNode *m_previous;
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
	BridgeBehaviorObjectIDNode *m_node;
};

// Declared, never defined here: the definition is the matched row
// ?append@Rva002A1B6FNativeList@@QAEXABQAX@Z at 0x002A1B6F
// (Code/GameEngine/Source/Common/Rva002A1316.cpp).
class Rva002A1B6FNativeList
{
public:
	void append(void *const &value);
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	char m_unrecovered04[0x20 - 0x04];
};

class UpgradeMux
{
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);
private:
	bool m_upgradeExecuted;
};

class BroadcastStealthUpdate : public UpdateModule, public UpgradeMux
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	BridgeBehaviorObjectIDList m_28;
};

// ?xfer@BroadcastStealthUpdate@@MAEXPAVXfer@@@Z @0x004A3752
void BroadcastStealthUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	if (version.m_minimum >= 2)
		UpgradeMux::upgradeMuxXfer(xfer);

	ObjectID id;
	if (xfer->IsStoring())
	{
		UnsignedInt count = m_28.size();
		*xfer == count;
		for (BridgeBehaviorObjectIDNode *it = m_28.m_node->m_next; it != m_28.m_node; it = it->m_next)
		{
			id = it->m_value;
			XferObjectID(xfer, &id);
		}
	}
	else
	{
		UnsignedInt count;
		*xfer == count;
		for (UnsignedInt i = 0; i < count; ++i)
		{
			XferObjectID(xfer, &id);
			reinterpret_cast<Rva002A1B6FNativeList *>(&m_28)->append(reinterpret_cast<void *const &>(id));
		}
	}
}
