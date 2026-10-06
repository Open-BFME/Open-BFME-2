// cl: /MD
// ?rva0055B266@Rva0055B266@@UAEXPAVXfer@@@Z @0x0055B266 54B
// Unlock FX DoXfer loop 8x via Version1 plus xferRandomVariable plus Xfer slot 0x78.
// Evidence: thiscall 1 Xfer arg ret 4; push 8 pop ebx countdown plus add esi 0x10;
// lea [esi-0xc] for GameClientRandomVariable plus push esi for second slot;
// Version1 row 0x53EE; xferRandomVariable row 0x306183; vtable slot 5 of 0x0081BF08
// plus slot 3 of 0x0081BA60; neighbours parse/ctor same subsystem;
// unblocks 0x0055B30F. Xfer decl verbatim order from PoisonedBehaviorXfer.
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

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

struct Rva0055B266Elem
{
	GameClientRandomVariable m_var;
	unsigned int m_val;
};

class Rva0055B266
{
public:
	virtual void rva0055B266(Xfer *xfer);
private:
	Rva0055B266Elem m_elems[8];
};

void Rva0055B266::rva0055B266(Xfer *xfer)
{
	xfer->Version1();
	unsigned int *pVal = &m_elems[0].m_val;
	int n = 8;
	do {
		xferRandomVariable(*xfer, *(GameClientRandomVariable *)(pVal - 3));
		*xfer == *pVal;
		pVal += 4;
	} while (--n != 0);
}
