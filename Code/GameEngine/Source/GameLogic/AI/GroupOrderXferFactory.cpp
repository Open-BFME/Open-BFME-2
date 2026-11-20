// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva00354EFCXfer@@YAPAVXfer@@PAV1@PAPAVGroupOrder@@@Z retail 0x00354EFC 410B.
//
// Polymorphic GroupOrder xfer (BFME 2 only; no Zero Hour counterpart).
// Version 1,1 through Xfer slot 0x28. Loading: the class key comes in
// through the NameKeyType xfer helper 0x00149101 and is compared, in this
// order, with the lazily-resolved name caches at 0x00DD211C
// ("MoveToFormationGroupOrder"), 0x00DD20D8 ("MoveToGroupOrder"),
// 0x00DD2094 ("AttackObjectGroupOrder"), 0x00DD2050
// ("GarrisonObjectGroupOrder"), 0x00DD200C ("ChangeStanceGroupOrder") and
// 0x00DD1FC8 ("SynchronizeGroupOrder") (Rva00148F5ECache::get 0x00148F5E);
// the matching class is newed (0x48/0x40/0x2C/0x28/0x1C/0x28 bytes, ctors
// 0x00547FF2/0x005479C3/0x00546F03/0x00546C57/0x00546AEF/0x00546982).
// Saving: the key is the order's virtual slot 0x30 and goes out through the
// same helper. Either way the order's snapshot then goes through Xfer slot
// 0x30. Caller 0x00355100 xfers a map entry's int key, then this for its
// GroupOrder* value. Name is the address name: the original is unknown.

#include "../../../Include/Common/ScalarTypes.h"





class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};


#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/NameKeyType.h"






Xfer &Rva00149101XferNameKey( Xfer &xfer, NameKeyType &key );

class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};

Rva00148F5ECache g_00DD211C = { NAMEKEY_INVALID, "MoveToFormationGroupOrder" };
Rva00148F5ECache g_00DD20D8 = { NAMEKEY_INVALID, "MoveToGroupOrder" };
Rva00148F5ECache g_00DD2094 = { NAMEKEY_INVALID, "AttackObjectGroupOrder" };
Rva00148F5ECache g_00DD2050 = { NAMEKEY_INVALID, "GarrisonObjectGroupOrder" };
Rva00148F5ECache g_00DD200C = { NAMEKEY_INVALID, "ChangeStanceGroupOrder" };
Rva00148F5ECache g_00DD1FC8 = { NAMEKEY_INVALID, "SynchronizeGroupOrder" };

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual NameKeyType getClassKey();
};

class MoveToFormationGroupOrder : public GroupOrder
{
public:
	MoveToFormationGroupOrder();
private:
	char m_pad[0x48 - 4];
public:
	virtual enum NameKeyType getClassKey();
};

class MoveToGroupOrder : public GroupOrder
{
public:
	MoveToGroupOrder();
private:
	char m_pad[0x40 - 4];
public:
	virtual enum NameKeyType getClassKey();
};

class AttackObjectGroupOrder : public GroupOrder
{
public:
	AttackObjectGroupOrder();
private:
	char m_pad[0x2C - 4];
public:
	virtual enum NameKeyType getClassKey();
};

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	GarrisonObjectGroupOrder();
private:
	char m_pad[0x28 - 4];
public:
	virtual enum NameKeyType getClassKey();
};

class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder();
private:
	char m_pad[0x1C - 4];
};

class SynchronizeGroupOrder : public GroupOrder
{
public:
	SynchronizeGroupOrder();
private:
	char m_pad[0x28 - 4];
};

Xfer *Rva00354EFCXfer(Xfer *xfer, GroupOrder **order)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == version;
	if (xfer->IsLoading())
	{
		NameKeyType key;
		Rva00149101XferNameKey(*xfer, key);
		if (key == g_00DD211C.get())
			*order = new MoveToFormationGroupOrder;
		else if (key == g_00DD20D8.get())
			*order = new MoveToGroupOrder;
		else if (key == g_00DD2094.get())
			*order = new AttackObjectGroupOrder;
		else if (key == g_00DD2050.get())
			*order = new GarrisonObjectGroupOrder;
		else if (key == g_00DD200C.get())
			*order = new ChangeStanceGroupOrder;
		else if (key == g_00DD1FC8.get())
			*order = new SynchronizeGroupOrder;
	}
	else
	{
		NameKeyType key = (*order)->getClassKey();
		Rva00149101XferNameKey(*xfer, key);
	}
	*xfer == reinterpret_cast<Snapshot &>(**order);
	return xfer;
}

// ?Rva00355100Xfer@@YAPAVXfer@@PAV1@PAURva00355100Pair@@@Z retail 0x00355100 27B.
// Map-entry xfer: the int key through Xfer slot 0x78, then the GroupOrder*
// value through the factory above on the Xfer that call returns. Shape of
// its rowed sibling Rva0035511BXfer (ObjectID key) at 0x0035511B.
struct Rva00355100Pair
{
	int m_key;
	GroupOrder *m_order;
};

Xfer *Rva00355100Xfer(Xfer *xfer, Rva00355100Pair *pair)
{
	return Rva00354EFCXfer(&(*xfer == reinterpret_cast<unsigned int &>(pair->m_key)), &pair->m_order);
}
