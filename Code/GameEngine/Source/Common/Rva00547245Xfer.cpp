// cl: /O1 /MD
// ?Rva00547245Xfer@@YAPAVXfer@@PAV1@PAURva00547245Pair@@@Z @0x00547245 30B free xfer helper moving ObjectID plus Coord.
// Evidence: calls rowed ?XferObjectID@@YAXPAVXfer@@PAW4ObjectID@@@Z 0x003060B2 then Xfer slot 0x60 (Coord3DBase) reusing eax as Xfer* same as Rva0035511BXfer precedent; callers 0x005475CB 0x00547625 in 0x0054755B; prev 0x00547223 setter plus next 0x00547297 wrapper share /O1 /MD.
enum ObjectID
{
	INVALID_ID = 0
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;

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

	virtual void SkipBadBlock(class Snapshot &snapshot, unsigned int size);
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
	virtual Xfer &operator==(struct ICoord3D &value);
	virtual Xfer &operator==(struct Region3D &value);
	virtual Xfer &operator==(struct IRegion3D &value);
	virtual Xfer &operator==(class Coord2D &value);
	virtual Xfer &operator==(struct ICoord2D &value);
	virtual Xfer &operator==(struct Region2D &value);
	virtual Xfer &operator==(struct IRegion2D &value);
	virtual Xfer &operator==(struct RealRange &value);
	virtual Xfer &operator==(struct RGBColor &value);
	virtual Xfer &operator==(struct RGBAColorReal &value);
	virtual Xfer &operator==(struct RGBAColorInt &value);
	virtual Xfer &operator==(class Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

struct Rva00547245Pair
{
	ObjectID m_id;
	Coord3DBase m_coord;
};

Xfer *Rva00547245Xfer(Xfer *xfer, Rva00547245Pair *pair)
{
	// Rowed XferObjectID is declared void but its body tail-calls XferEnum
	// which returns Xfer& in eax; retail reuses that eax as the xfer for the
	// Coord call, same as Rva0035511BXfer precedent.
	return &(*((Xfer *(__cdecl *)(Xfer *, ObjectID *))XferObjectID)(xfer, &pair->m_id) == pair->m_coord);
}
