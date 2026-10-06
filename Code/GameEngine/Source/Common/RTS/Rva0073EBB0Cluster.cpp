// cl: /MD
//
// ?xfer@ShroudManagerImpl008FBA40Element@@QAEXPAVXfer@@@Z, retail 0x0073EBB0
// (134 B).  ShroudManagerImpl008FBA40Element::xfer: write version 1.2 through
// the Xfer vtable slot +0x28, then for each of the 20 player states transfer
// its status short (slot +0x80) and its three counter shorts.  On load of a
// pre-1.2 save (isLoading slot +4 and the stored current version below 2) only
// the two legacy counters are read, through the N=2 helper 0x0073EA90, and the
// third counter is zeroed; otherwise the N=3 helper 0x0073EB00 fills all three.
// The element layout (cellNodes at +0, 8-byte PlayerState array at +4) and the
// helper twins match Rva0073EB00Xfer.cpp below; the N=2 helper is pinned.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

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
	virtual Xfer &xferVersion(void *version);
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
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual void slot31();
	virtual Xfer &xferShort(unsigned short *value);
};

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

struct ShroudManagerImpl008FBA40PlayerState
{
	UnsignedShort status;
	UnsignedShort counters[3];
};

class ShroudManagerImpl008FBA40Element
{
public:
	void xfer(Xfer *xfer);

private:
	void *cellNodes;
	ShroudManagerImpl008FBA40PlayerState playerStates[20];
};

extern Xfer *Rva0073EB00Xfer(Xfer *xfer, UnsignedShort *values);
extern Xfer *rva0073ea90(Xfer *xfer, UnsignedShort *values);

void ShroudManagerImpl008FBA40Element::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);

	for (int i = 0; i < 20; ++i)
	{
		xfer->xferShort(&playerStates[i].status);
		if (xfer->isLoading() && version.m_currentVersion < 2)
		{
			UnsignedShort values[2];
			rva0073ea90(xfer, values);
			playerStates[i].counters[0] = values[0];
			playerStates[i].counters[1] = values[1];
			playerStates[i].counters[2] = 0;
		}
		else
		{
			Rva0073EB00Xfer(xfer, playerStates[i].counters);
		}
	}
}
