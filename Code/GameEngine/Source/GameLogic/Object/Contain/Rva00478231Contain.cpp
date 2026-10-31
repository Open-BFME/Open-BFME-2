// cl: /DNDEBUG /MD
// ?rva00478231@Rva00478231@@QAEX_N@Z @0x00478231 (46B): GarrisonContain
// removeAllContained shape after the slot38-leaf precedent — the donor TU's
// class model has the wrong vtable slots, so this uses flat classes: a
// gap-templated vtable carrying recalcApparentControllingPlayer at slot 0x50
// and getContainCount(int) at slot 0x114; the rowed GarrisonContain
// validateRallyPoint is reached on this-0x20 through an address-honest pin
// (its true protection is inherited-only); OpenContain::removeAllContained
// is called non-virtually through its pin at 0x004635C0. All three guarded
// by getContainCount(0) > 0. Honest address name; owning class unproven.

template <int N> class Rva00478231Gaps : public Rva00478231Gaps<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00478231Gaps<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva00478231Low : public Rva00478231Gaps<20>
{
public:
	virtual void recalcApparentControllingPlayer() = 0; // slot 0x50
};

template <int N> class Rva00478231Mid : public Rva00478231Mid<N - 1>
{
public:
	virtual void mid(char (*)[N]) = 0;
};
template <> class Rva00478231Mid<1> : public Rva00478231Low
{
public:
	virtual void mid(char (*)[1]) = 0;
};

// The rally-point check is the rowed protected GarrisonContain::validateRallyPoint.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

enum ObjectID { INVALID_ID = 0 };

enum NameKeyType { NK_UNKNOWN = 0 };

// One garrison point record: 40 of them at +0x100, 0x14 bytes each (the
// constructor 0x00477F06 zeroes five dwords per record, the matched
// put/remove bodies store the object and target IDs and the place frame).
struct GarrisonPointData
{
	ObjectID objectID;
	ObjectID targetID;
	unsigned int placeFrame;
	unsigned int lastEffectFrame;
	int effect;
};

enum
{
	MAX_GARRISON_POINTS = 40,
	MAX_GARRISON_POINT_CONDITIONS = 3
};

// OpenContain's nine vftable-bearing bases, positional. The GarrisonContain
// constructor 0x00477F06 (and the destructor 0x00478067, which restores the
// same tables) stores nine vftables: +0x00 0x00C461F8 (28 slots), +0x0C
// 0x00C43528 (47), +0x10 0x00C46560 (3), +0x20 0x00C46080 (94), +0x24
// 0x00C46064 (6), +0x28 0x00C46F78 (1), +0x2C 0x00C463D8 (4), +0x30
// 0x00C46034 (12) and +0x34 0x00C48B28 (4), and its first own member is
// +0xFC. B0 holds the module's data and object pointers (+0x04, +0x08); B2
// the 12 update bytes before +0x20; B8 OpenContain's data to +0xFC. Only the
// slots a body of this TU needs are declared. The +0x20 table's slot 76 is
// calcBestGarrisonPosition (0x00478547), so B3 introduces it and its
// override is entered with the +0x20 this.
class B0 { public: virtual void b0(); int m_pad4; Object *m_object; };

class B1 { public: virtual void b1(); };

class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };

class B3 { public: virtual bool calcBestGarrisonPosition(Coord3D *, const Coord3D *); };

class B4 { public: virtual void b4(); };

class B5 { public: virtual void b5(); };

class B6 { public: virtual void b6(); };

class B7 { public: virtual void b7(); };

class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class Xfer;

// OpenContain's own virtuals as the bodies call them by name: xfer (primary
// slot 3) and loadPostProcess through explicit OpenContain:: calls, and
// removeAllContained, which the matched 0x00478231 calls on its +0x20
// receiver unchanged.
class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
    friend class Rva004697E1Contain;
public:
    virtual ~OpenContain();
    virtual void removeAllContained(bool exposeStealthUnits);
    Object *getObject() const { return m_object; }
protected:
    virtual void xfer(Xfer *xfer);
    virtual void loadPostProcess();
};

// GarrisonContain over the 0xFC-byte OpenContain. Offsets from the matched
// bodies: +0xFC original team id (xfer 0x00478260), +0x100 point records,
// +0x420 points in use, +0x424 the 3x40 garrison points (put 0x00477DA1,
// remove 0x00477E82, calcBestGarrisonPosition 0x00478547), +0x9C4 the
// per-condition point counts (findClosestFreeGarrisonPointIndex 0x00478445),
// +0x9D0 the exit rally point and the +0x9DC/+0x9DD/+0x9DE flags (xfer,
// validateRallyPoint 0x00478141). The primary table 0x00C461F8 holds the
// pool key at slot 4 (0x0047801C).
class GarrisonContain : public OpenContain
{
    friend class Rva00478231;
public:
    virtual NameKeyType getModuleNameKey() const;
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);
protected:
    enum { GARRISON_INDEX_INVALID = -1 };
    virtual void xfer(Xfer *xfer);
    void trackTargets();
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos);
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index);
    void validateRallyPoint();
private:
    unsigned int m_originalTeamID; // +0xFC
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS]; // +0x100
    int m_garrisonPointsInUse; // +0x420
    Coord3D m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS]; // +0x424
    int m_numGarrisonPoints[MAX_GARRISON_POINT_CONDITIONS]; // +0x9C4
    Coord3D m_exitRallyPoint; // +0x9D0
    bool m_garrisonPointsInitialized; // +0x9DC
    bool m_hideGarrisonedStateFromNonallies; // +0x9DD
    bool m_rallyValid; // +0x9DE
};

class Rva00478231 : public Rva00478231Mid<48>
{
public:
	virtual unsigned int getContainCount(unsigned int arg) = 0; // slot 0x114
	void rva00478231(bool exposeStealthUnits);
};

// ?validateRallyPoint@Rva00478231@@QAEXXZ @0x00478141 (pinned): the rowed
// GarrisonContain method is protected-only; this address-honest spelling
// carries the call. Declared, never defined here.

// ?rva00478231@Rva00478231@@QAEX_N@Z
void Rva00478231::rva00478231(bool exposeStealthUnits)
{
	if (getContainCount(0) > 0u) {
		((GarrisonContain *)((char *)this - 0x20))->validateRallyPoint();
		((OpenContain *)this)->OpenContain::removeAllContained(exposeStealthUnits);
		recalcApparentControllingPlayer();
	}
}
