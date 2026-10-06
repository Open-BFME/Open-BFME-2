// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva00355096Xfer@@YAPAVXfer@@PAV1@PAPAVRva0054840A@@@Z retail 0x00355096 106B.
// Chain lane: calls rowed 0x0054840A which you just landed; version 1,1 via slot 0x28 plus isLoading slot 4 plus news 0x14.
// Evidence: callers at 0x00355130 pass obj and obj+4 proving Xfer plus out-pointer; callees rowed ctor 0x0054829B plus xfer 0x0054840A plus new 0x0002FDA0.

typedef unsigned char UnsignedByte;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedShort(unsigned int *value);
};

class Rva0054840A
{
public:
	Rva0054840A();
	void rva0054840A(Xfer *xfer);
private:
	char m_pad[0x14];
};

Xfer *Rva00355096Xfer(Xfer *xfer, Rva0054840A **out)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);
	if (xfer->isLoading())
		*out = new Rva0054840A;
	(*out)->rva0054840A(xfer);
	return xfer;
}
