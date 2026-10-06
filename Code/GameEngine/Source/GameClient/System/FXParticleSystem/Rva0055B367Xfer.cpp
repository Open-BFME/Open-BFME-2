// cl: /MD
// ?rva0055B367@Rva0055B367@@QAEXPAVXfer@@@Z @0x0055B367 53B
// Unlock FX xfer loop 8x via Version1 plus Xfer slots 0x70/0x78.
// Evidence: thiscall 1 Xfer arg ret 4; push 8 pop ebx countdown plus add edi 8;
// lea [edi-4] push plus push edi for Region2D/RealRange; Version1 row 0x53EE;
// callers 0x0055B3EC in 0x0055B3D9; neighbours parse/ctor same subsystem;
// unblocks 0x0055B3D9. Xfer decl verbatim order from PoisonedBehaviorXfer.
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

struct Rva0055B367Pair
{
	float f;
	unsigned int u;
};

class Rva0055B367
{
public:
	void rva0055B367(Xfer *xfer);
private:
	char m_pad[4];
	Rva0055B367Pair m_pairs[8];
};

void Rva0055B367::rva0055B367(Xfer *xfer)
{
	xfer->Version1();
	unsigned int *pu = (unsigned int *)((char *)this + 8);
	for (int n = 8; n > 0; --n)
	{
		xfer->operator==(*(float *)(pu - 1));
		xfer->operator==(*pu);
		pu += 2;
	}
}
