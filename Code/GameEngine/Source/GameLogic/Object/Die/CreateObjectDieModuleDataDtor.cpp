// cl: /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1CreateObjectDieModuleData@@UAE@XZ, retail 0x00485DDA, 63 bytes.
// CreateObjectDieModuleData destructor: destroys the CreationList vector at
// +0x40 through the rowed AsciiString vector dtor 0x0002CC70 (state 1) then
// the UpgradeRequired string at +0x3C through the folded 0x00036410
// (AsciiString pin sharing the StringBase address; state 0) then restores
// the Snapshot base vtable 0x00BBB554. Layout from the rowed ctor 0x00485D88
// (base 0x38 via Rva00253510 plus DebrisPortion int +0x38 plus string +0x3C
// plus vector +0x40 size 0x4C via factory 0x0024C8C1) and the rowed
// buildFieldParse proc 0x00485A74 with table 0x00C4A928. Own vtable
// 0x00C4A988 installed by the ctor. Callers are the slot-0 ??_G at
// 0x00485E50 and 0x00485EB1 plus the Unwind funclet at 0x0078C022. Donor is
// BFME1 CreateObjectDieModuleDataCtorThunk.cpp:79 plus CreateObjectDie.cpp:57.
// Shape follows CivilianSpawnUpdateModuleDataDtor (TU-local Snapshot with
// inline BBB554-restoring dtor plus novtable derived suppressing the entry
// store retail lacks plus vector plus string members).
#include <vector>
class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};
inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}
class AsciiString
{
public:
	~AsciiString();
private:
	void *m_data;
};
class __declspec(novtable) CreateObjectDieModuleData : public Snapshot
{
public:
	virtual ~CreateObjectDieModuleData();
private:
	unsigned char m_pad04[0x38 - 4];
	int m_debrisPortion;
	AsciiString m_upgradeRequired;
	_STL::vector<AsciiString> m_creationList;
};
CreateObjectDieModuleData::~CreateObjectDieModuleData()
{
}
