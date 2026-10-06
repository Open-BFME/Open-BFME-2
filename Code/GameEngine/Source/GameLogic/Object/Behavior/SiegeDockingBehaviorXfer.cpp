// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?xfer@SiegeDockingBehavior@@MAEXPAVXfer@@@Z, retail 0x0045A02F, 318 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008414DC. xfer shape with Version1 then UpdateModule base then IsStoring branch.
// Evidence: donor game/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehaviorXfer.cpp (BFME1 0x00206FF0) direct reuse with Version1 repair; base model from PoisonedBehaviorXfer UpdateModule 0x20 plus secondary at 0x20; callers none; callees Version1 0x53EE UpdateModule xfer 0x44DF9F IsStoring slot8 XferSiegeTypeEnum 0x306112 XferObjectID 0x3060B2 stopDocking 0x459C27 new 0x2FDA0 push_back 0x4DFCB0 rowed.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
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
class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);
void XferSiegeTypeEnum(Xfer *xfer, int *value);
class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};
class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};
class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};
class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};
class UpdateModuleInterface
{
public:
	virtual void update();
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};
class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot();
};
struct SiegeDockEntry00206FF0
{
	Int m_int00;
	Int m_enum04;
	Coord3DBase m_coord08;
	Coord3DBase m_coord14;
	ObjectID m_objectID20;
};
class SiegeDockingBehavior : public UpdateModule, public SiegeDockingBehaviorSecondaryBase
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	void stopDocking();
	_STL::vector<SiegeDockEntry00206FF0 *> m_entries;
	Bool m_bool30;
};
void SiegeDockingBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	if (xfer->IsStoring())
	{
		UnsignedInt count = m_entries.size();
		*xfer == count;
		for (UnsignedInt index = 0; index < count; ++index)
		{
			XferSiegeTypeEnum(xfer, &m_entries[index]->m_enum04);
			*xfer == m_entries[index]->m_int00;
			*xfer == m_entries[index]->m_coord08;
			*xfer == m_entries[index]->m_coord14;
			XferObjectID(xfer, &m_entries[index]->m_objectID20);
		}
	}
	else
	{
		UnsignedInt count = 0;
		*xfer == count;
		for (UnsignedInt index = 0; index < count; ++index)
		{
			stopDocking();
			SiegeDockEntry00206FF0 *entry = new SiegeDockEntry00206FF0;
			XferSiegeTypeEnum(xfer, &entry->m_enum04);
			*xfer == entry->m_int00;
			*xfer == entry->m_coord08;
			*xfer == entry->m_coord14;
			XferObjectID(xfer, &entry->m_objectID20);
			((_STL::vector<const ModuleData *> *)&m_entries)->push_back((const ModuleData *&)entry);
		}
	}
	*xfer == m_bool30;
}
