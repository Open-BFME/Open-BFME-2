// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// ??1Rva0037BB53@@UAE@XZ retail 0x0037BB53 69B virtual dtor over Rva00382FA7
// base (0xDC) with 8x0x1AC BfmeSaveElement002295D7 array at +0xDC destroyed via
// eh vector destructor iterator then pinned base dtor. Identity from deleting
// dtor caller 0x0037BD0F and member call at 0x0037BBED+0x42 (this+0x24 of outer
// with TheGameInfo fclose UnicodeStrings GameEngineDeletingBase base) and array
// shape pushes dtor 0x2294FD count 8 size 0x1AC base+0xDC.

class Rva00382FA7
{
public:
	virtual ~Rva00382FA7();
	char m_pad[0xDC - 4];
};

class BfmeSaveElement002295D7
{
public:
	virtual ~BfmeSaveElement002295D7();
	char m_pad[0x1AC - 4];
};

class __declspec(novtable) Rva0037BB53 : public Rva00382FA7
{
public:
	virtual ~Rva0037BB53();
private:
	BfmeSaveElement002295D7 m_items[8];
};

Rva0037BB53::~Rva0037BB53()
{
}
