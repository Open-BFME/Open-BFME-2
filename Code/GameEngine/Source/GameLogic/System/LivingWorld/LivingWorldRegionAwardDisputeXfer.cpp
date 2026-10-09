// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FBDF7@RegionAwardDispute@@QAEXPAVXfer@@@Z, retail 0x004FBDF7..0x004FBE7A
// (131B, RET 4): the dispute's Xfer. Version {1,2}; region id at +4 through
// the rowed 0x003EFE82; the dispute type at +0x14 is read through the
// rowed enum helper 0x004FBDDF for the old version (1 keeps 0x20, anything
// else becomes 0x22) and through the rowed 0x002B24F0 otherwise; a 4-byte
// member at +0x1C through Xfer slot 0x90; then the disputant vector at +8
// through the rowed LivingWorld 0x002B8DFC. Layout beyond these fields is
// opaque. Evidence: retail frame and callees read at the REL32s; field
// roles other than the vector (+8, the pointer vector of
// LivingWorldRegionAwardDispute.cpp) are unnamed.
#include <vector>

typedef unsigned char UnsignedByte;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09();
	virtual void xferVersion(XferVersion *version);
	virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
	virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
	virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
	virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35();
	virtual void xferMember(void *value);
};

struct Rva003EFE82Obj;
struct Rva002B24F0Obj;
class ModuleData;
int Rva003EFE82Get(Rva003EFE82Obj *xfer, void *value);
int Rva002B24F0Get(Rva002B24F0Obj *xfer, void *value);
void XferRegionAwardDisputeDisputeType(Xfer *xfer, void *value);

class Rva002BA8F1Logic
{
public:
	void rva002B8DFC(Xfer *xfer, _STL::vector<const ModuleData *> *vec);
};
extern Rva002BA8F1Logic *TheLivingWorldLogic;

class RegionAwardDispute
{
public:
	void rva004FBDF7(Xfer *xfer);

private:
	int m_00;
	int m_regionID;				// +0x04
	_STL::vector<const ModuleData *> m_disputants;	// +0x08
	int m_disputeType;			// +0x14
	int m_18;
	int m_1C;				// +0x1C
};

void RegionAwardDispute::rva004FBDF7(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	xfer->xferVersion(&version);

	Rva003EFE82Get((Rva003EFE82Obj *)xfer, &m_regionID);
	if (version.m_currentVersion < 2) {
		int old = 1;
		XferRegionAwardDisputeDisputeType(xfer, &old);
		m_disputeType = old != 1 ? 0x22 : 0x20;
	} else {
		Rva002B24F0Get((Rva002B24F0Obj *)xfer, &m_disputeType);
	}
	xfer->xferMember(&m_1C);
	TheLivingWorldLogic->rva002B8DFC(xfer, &m_disputants);
}
