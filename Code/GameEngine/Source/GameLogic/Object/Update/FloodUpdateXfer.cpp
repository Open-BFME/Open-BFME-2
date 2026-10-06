// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?xfer@FloodUpdate@@MAEXPAVXfer@@@Z, retail 0x0048E4E2, 289 bytes.
// Slot 3 of ??_7FloodUpdate 0x00C4C948 (slot-2 name getter returns
// "FloodUpdate"; installed by the rowed ctor 0x0048E09F). The rowed
// UpdateModule::xfer 0x0044DF9F first, then the light-CRC out, Version(1,1),
// the element count of the pointer list at +0x20 (int, Xfer slot 0x7C).
// Loading news 0x14-byte records through the rowed ctor 0x0048E16C and
// pushes them (list push_back 0x0005548F); each record is an ObjectID
// (rowed XferObjectID), the coord vector at +4 (rowed
// Rva00390911XferCoordVector) and an int at +0x10. Saving walks the list
// with the same three transfers. Finally the bool at +0x24. Member names
// not recovered.

#include <list>

// Retail calls the separately rowed four-byte-element append at 0x5548F.
// The list<void*> instance owned by the 3D pool TU is 0x526103 and calls
// a different insertion provider. Preserve it, but select the retail call.
// The int-element view selects that verified four-byte ABI instance.
// The target sample/record remains a pointer; no int-container identity is claimed.


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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};

struct AICommandCoordVector
{
	void *m_start;
	void *m_finish;
	void *m_end;
};

void XferObjectID(Xfer *xfer, ObjectID *id);
void Rva00390911XferCoordVector(Xfer *xfer, AICommandCoordVector *vec);

class Rva0048E16C
{
public:
	Rva0048E16C();

	ObjectID m_00;
	AICommandCoordVector m_vec;
	int m_10;
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	char m_unrecovered04[0x20 - 0x04];
};

class FloodUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	_STL::list<void *> m_20;
	bool m_24;
};

// ?xfer@FloodUpdate@@MAEXPAVXfer@@@Z @0x0048E4E2
void FloodUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	int count = m_20.size();
	*xfer == count;

	if (xfer->IsLoading())
	{
		for (int i = 0; i < count; ++i)
		{
			Rva0048E16C *record = new Rva0048E16C;
			XferObjectID(xfer, &record->m_00);
			Rva00390911XferCoordVector(xfer, &record->m_vec);
			*xfer == record->m_10;
			reinterpret_cast<_STL::list<int> *>(&m_20)->push_back(reinterpret_cast<const int &>(record));
		}
	}
	else if (xfer->IsStoring())
	{
		for (_STL::list<void *>::iterator it = m_20.begin(); it != m_20.end(); ++it)
		{
			Rva0048E16C *record = (Rva0048E16C *)*it;
			XferObjectID(xfer, &record->m_00);
			Rva00390911XferCoordVector(xfer, &record->m_vec);
			*xfer == record->m_10;
		}
	}

	*xfer == m_24;
}
