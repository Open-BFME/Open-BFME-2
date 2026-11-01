// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
// ?Rva004E1BFCParse@@YAXPAVINI@@PAX1PBX@Z @0x004E1BFC 126B
// Native C61DB4 is the12-byte MoveArmy Snapshot record. Its complete table
// holds deleting destructor, empty post-load, name getter and DoXfer.
// Real FXList TracerFXNugget is unrelated and remains unchanged. Original
// C++ type spelling is unknown, so retain the established address name.

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};


struct _s__ThrowInfo;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00861830: 2 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C61830[3] = {
	{ "ArmyScriptingName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "TargetRegionName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ 0, 0, 0, 0 }
};

#include "ascii_string.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class Rva004E1B00 : public Snapshot
{
public:
 Rva004E1B00();
 virtual ~Rva004E1B00();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer &xfer);
private:
 AsciiString m_member04;
 AsciiString m_member08;
};

// Existing append ABI names this same12B Snapshot value by its copy-ctor RVA.
// Native566537 -> vector5662CC -> Construct52C34D -> copy52BDE6:
// stride12, vptrC61DB4 and AsciiStrings4/8. Only a reference is passed here;
// no field access, lifetime operation or new cast is introduced for this view.
typedef char MoveArmyNativeSize[sizeof(Rva004E1B00)==12?1:-1];
typedef char MoveArmyNativeAlignment[__alignof(Rva004E1B00)==4?1:-1];
class Rva0052BDE6;

class Rva00566537Owner
{
public:
	void append(const Rva0052BDE6 &record);
};


Rva004E1B00::Rva004E1B00() {}

Rva004E1B00::~Rva004E1B00() {}


const char *Rva004E1B00::GetSnapshotName() { return "MoveArmy"; }

void Rva004E1B00::LoadPostProcess() {}

// ?Rva004E1BFCParse@@YAXPAVINI@@PAX1PBX@Z
void Rva004E1BFCParse(INI *ini, void *instance, void *, const void *)
{
	if (ini && instance)
	{
		Rva004E1B00 record;
		ini->initFromINI(&record, g_00C61830);
		((Rva00566537Owner *)instance)->append(*(const Rva0052BDE6 *)&record);
	}
	else
	{
		INIException e(3, "ParseMoveArmyBlockAndAddToLivingWorldCampaignAct::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
}

// Native C6CD50 FieldParse registration uses the four-argument callback ABI.
// Preserve the witnessed body and existing address binding; both trailing
// parameters are unused. No function-pointer cast or alternate callee pin.
