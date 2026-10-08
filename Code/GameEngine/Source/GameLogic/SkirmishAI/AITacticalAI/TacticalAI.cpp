// cl: /O1 /G7 /arch:SSE /GX /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0x002C63A1..0x002C64D0, 303 bytes. WB TacticalAI::DoXfer name lead
// is independently retained by its SkirmishAI caller at +0x164. Native reads
// player+8, chooser+C, generator+10 and the interest-zone vector+20.
// Xfer slots and the two serializer providers agree with matched siblings.
// The 32-byte zone's existing serializer retains its address-derived name.
// Its constructor signature follows complete target 0x002C6234..0x002C6354:
// coordinate address, float, player; member initialization proves 32 bytes.
#include <vector>
class AsciiString;
struct Coord3DBase;
// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


struct Coord3DBase
{
public:
    Coord3DBase() { x=0.0f; y=0.0f; z=0.0f; }
    // Native retains a temporary cleanup state with no destructor instruction.
    ~Coord3DBase() {}
    float x,y,z;
};
class Player;
class Team;
class Rva002C5EF0
{
public:
    Rva002C5EF0(const Coord3DBase &,float,Player *);
    void rva002C5EF0(Xfer *);
private:
    unsigned int id;
    float position[3];
    unsigned int state;
    float radius,value;
    unsigned int frame;
};
class AITargetChooser { public: void xfer(Xfer *); };
class Rva00506909
{
public:
    void xfer(Xfer *);
    void rva005059A1(Team *);
    void rva00505A56(Team *);
};
class TacticalAI
{
public:
    void DoXfer(Xfer *);
    __declspec(noinline) void Register(Team *);
    __declspec(noinline) void UnRegister(Team *);
private:
    char prefix00[8];
    Player *player;
    AITargetChooser *chooser;
    Rva00506909 *generator;
    char gap14[0x20-0x14];
    _STL::vector<Rva002C5EF0 *> interestZones;
};
void TacticalAI::DoXfer(Xfer *xfer)
{
    Xfer::Version version(1,1);
    *xfer==version;
    bool hasChooser=chooser!=0;
    *xfer==hasChooser;
    if(chooser) chooser->xfer(xfer);
    generator->xfer(xfer);
    unsigned int count=interestZones.size();
    *xfer==count;
    if(xfer->IsStoring())
    {
        Rva002C5EF0 **end=interestZones.end();
        for(Rva002C5EF0 **i=interestZones.begin();i!=end;++i)
            (*i)->rva002C5EF0(xfer);
    }
    else if(xfer->IsLoading())
    {
        for(unsigned int i=0;i<count;++i)
        {
            Rva002C5EF0 *zone=new Rva002C5EF0(Coord3DBase(),0.0f,player);
            zone->rva002C5EF0(xfer);
            interestZones.push_back(zone);
        }
    }
}

// Complete eight-byte generator forwarding tails, formerly in SkirmishAI.cpp.
void TacticalAI::Register(Team *team)
{
    generator->rva005059A1(team);
}

void TacticalAI::UnRegister(Team *team)
{
    generator->rva00505A56(team);
}
