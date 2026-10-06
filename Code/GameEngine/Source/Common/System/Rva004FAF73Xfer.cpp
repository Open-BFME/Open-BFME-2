// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva004FAF73@Rva004FAF73@@QAEXPAVXfer@@@Z @0x004FAF73 67B evidence: chain via just-landed Rva004FACD0Xfer 0x004FACD0; callees rowed rva004CE6E4 0x004CE6E4 plus Rva004FACD0Xfer plus Xfer slots 0x28 version and 0x7c; vector Science at +0x20 member at +0x2c.
// Honest Rva thiscall taking Xfer returning void ret-4.
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_0 = 0
};

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
	virtual Xfer &xferVersion(XferVersion &version);
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
	virtual void xferAsciiString(void *value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual void slot31(void *value);
};

class Rva004CE6E4
{
public:
	void rva004CE6E4(Xfer *xfer);
};

typedef _STL::vector<ScienceType> ScienceTypeVector;

extern Xfer * __cdecl Rva004FACD0Xfer(Xfer *xfer, ScienceTypeVector *vec);

class Rva004FAF73
{
public:
	void rva004FAF73(Xfer *xfer);
	char m_pad[0x20];
	ScienceTypeVector m_vec;
	int m_2c;
};

void Rva004FAF73::rva004FAF73(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	((Rva004CE6E4 *)this)->rva004CE6E4(xfer);

	xfer->slot31(&m_2c);

	Rva004FACD0Xfer(xfer, &m_vec);
}
