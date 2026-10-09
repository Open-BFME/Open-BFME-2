// ?beginCampaign@LinearCampaign@@QAEXXZ
// partial score=0.85 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB AF93C0 names LinearCampaignManager::DoXfer (assert1365).
// Native1EBB73..1EBCC6 is complete339B RET4: Version1/1 and bool current
// precede load/save of the current campaign name, GameDifficulty and block
// CurrentCampaign. The owning pointer is at+10; WB's separate arrow/get
// accessors establish the inline CampaignSlot view that reproduces native.
// Native ctor1EBAEA is the existing137B two-word ABI and C4 allocation.
// Its record pointer4 and difficulty8 are caller-observed; the pointee's concrete class and
// unseen bases remain unknown. Its no-allocation constructor has already
// been consumed as nothrow by the verified99B1ECF03 sibling.
// Existing clearAD6F4/set575674 own slot replacement; no globals or pins.

#include "ascii_string.h"
#include <vector>
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct WallVersion
{
    WallVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual bool IsLoading() const;
virtual bool IsStoring() const;
virtual bool IsCRC() const;
virtual void slot04();
virtual int BeginBlock(const char*);
virtual void EndBlock();
virtual void SkipBlock(const char*);
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(WallVersion *);
virtual void slot11();
virtual Xfer &XferSnapshot(void*);
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
virtual Xfer &xferCoord3D(struct Coord3D *);
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual Xfer &xferUnsignedInt(unsigned int *);
virtual Xfer& xferInt(int*);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};


class Rva000AD6F4 {public: void clear();};
class Object;
class Rva00575674 {public: void rva00575674(Object*);};
class Rva001EB8D7 {public: void *rva001EB90C(const StringBase<char>&);};
class Rva001EBAEA {
public: Rva001EBAEA(int,int) throw();
 void *unknown0;
 const AsciiString *record4;
 int argument8;
 unsigned char opaque0c[0xc4-0xc];
};
void XferGameDifficulty(Xfer*,int*);
class CampaignSlot {
public:
 Rva001EBAEA *get() const { return pointer; }
 Rva001EBAEA *operator->() const { return pointer; }
 bool valid() const { return pointer!=0; }
private: Rva001EBAEA *pointer;
};
// One 0x24-byte campaign record, rowed under one address name per row: the
// vector element of push_back 0x001ED549, the destructor 0x001ED0DE and the
// name constructor 0x001ED0A9; its block parse 0x001ED338 (an initFromINI
// forward with the record's field table) is rowed under a fourth. The view
// chains them so one temporary reaches each row as retail's does.
class Rva001ED03C { public: unsigned char data[0x24]; };
class Rva001ED0DE : public Rva001ED03C { public: ~Rva001ED0DE(); };
class Rva001ED0A9 : public Rva001ED0DE { public: Rva001ED0A9(const AsciiString &name); };
class Rva001ED338 { public: void rva001ED338(void *ini); };
enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE };
class INI {
public: const char *getNextToken(const char *seps = 0);
 INILoadType getLoadType() const { return loadType; }
 unsigned char pad00[8]; INILoadType loadType; // +0x08, overwrite for the startup files
};
class INIException {
public: INIException(int code, const char *format, ...);
 INIException(const INIException &); ~INIException();
 char *failureMessage; int errorCode;
};
class LinearCampaignManager {
public: void DoXfer(Xfer*);
 static void parseLinearCampaignIniBlock(INI *ini);
private: unsigned char prefix00[0x10]; CampaignSlot current;
 _STL::vector<Rva001ED03C> campaigns; // +0x14
};
extern LinearCampaignManager *TheLinearCampaignManager;
void LinearCampaignManager::DoXfer(Xfer *xfer) {
 WallVersion version(1,1);
 xfer->xferVersion(&version);
 bool hasCurrent=current.valid();
 xfer->xferBool(&hasCurrent);
 if(xfer->IsLoading()) reinterpret_cast<Rva000AD6F4*>(&current)->clear();
 if(hasCurrent) {
  if(xfer->IsLoading()) {
   AsciiString name;
   xfer->xferAsciiString(&name);
   int difficulty;
   XferGameDifficulty(xfer,&difficulty);
   void *record=reinterpret_cast<Rva001EB8D7*>(this)->rva001EB90C(*reinterpret_cast<const StringBase<char>*>(&name));
   if(!record) xfer->SkipBlock("CurrentCampaign");
   else {
    xfer->BeginBlock("CurrentCampaign");
    Rva001EBAEA *state=new Rva001EBAEA(reinterpret_cast<int>(record),difficulty);
    reinterpret_cast<Rva00575674*>(&current)->rva00575674(reinterpret_cast<Object*>(state));
    xfer->XferSnapshot(current.get());
    xfer->EndBlock();
   }
  } else {
   AsciiString name=*current->record4;
   int difficulty=current->argument8;
   xfer->xferAsciiString(&name);
   XferGameDifficulty(xfer,&difficulty);
   xfer->BeginBlock("CurrentCampaign");
   xfer->XferSnapshot(current.get());
   xfer->EndBlock();
  }
 }
}

// WB AF96F0 names LinearCampaignManager::parseLinearCampaignIniBlock and the
// retail diagnostic names the 'LinearCampaign' block. Native1ED580..1ED62E:
// only the startup files may define one (INIException 8); with a manager the
// next token names a new record that is appended and then parses the rest of
// the block in place.
void LinearCampaignManager::parseLinearCampaignIniBlock(INI *ini) {
 if(ini->getLoadType()!=INI_LOAD_OVERWRITE)
  throw INIException(8,"Sorry, you cannot define a 'LinearCampaign' block anywhere but the main INI files.");
 if(TheLinearCampaignManager) {
  {
   AsciiString name(ini->getNextToken());
   TheLinearCampaignManager->campaigns.push_back(Rva001ED0A9(name));
  }
  reinterpret_cast<Rva001ED338*>(&TheLinearCampaignManager->campaigns.back())->rva001ED338(ini);
 }
}

// LinearCampaign::beginCampaign, retail 0x001ECDB3 (229 bytes): WB AF7DE0
// names it (asserts LinearCampaignManager.cpp:806..840). The object is the
// 0xC4-byte state Rva001EBAEA above (campaign record at +4, the flag at
// +0xC3 inside its extent). It sizes the 0xAC-byte carryover-unit vector
// (+0xA4, rowed one-argument resize 0x001ECCF3) to the record's unit list
// (+0x0C), names each unit from the record (0x001EAFFE, pinned from its
// REL32), marks its +0x90 and counts at +0xB0 the units whose template
// (0x0037DC52) has KindOf bit 0x5A, as WB's bitset test spells it. It
// reserves the +0xB4 vector, plays the record's +8 movie through
// TheDisplay's slot 67 when one is named, clears +0x0C and +0xC3 and
// continues in 0x001EB456 (1, 1). Argument meanings past WB's are opaque.
class CarryoverUnitView
{
public:
	void *rva0037DC52();	// 0x0037DC52, WB CarryoverUnit::GetThingTemplate
};

struct CarryoverUnitRecord
{
	void *m_vtable;
	AsciiString m_name;		// +0x04
	unsigned char m_pad08[0x90 - 0x08];
	int m_90;
	unsigned char m_pad94[0xAC - 0x94];
};

class Rva001EC9BDVector
{
public:
	void resize(unsigned int newSize);
	CarryoverUnitRecord &operator[](unsigned int i) { return m_start[i]; }

private:
	CarryoverUnitRecord *m_start;
	CarryoverUnitRecord *m_finish;
	CarryoverUnitRecord *m_endOfStorage;
};

struct BfmeAssignRecord172 { unsigned char bytes[172]; };

struct CarryoverThingTemplateView
{
	unsigned char m_pad00[0x108];
	unsigned char m_kindOf[0x14];	// +0x108
};

struct CarryoverNameVectorView
{
	int size() const { return m_finish - m_start; }
	void **m_start;
	void **m_finish;
	void **m_endOfStorage;
};

class Rva001EAFFE
{
public:
	const AsciiString &rva001EAFFE(int index);	// 0x001EAFFE

	unsigned char m_pad00[0x08];
	AsciiString m_movie;			// +0x08
	CarryoverNameVectorView m_units;	// +0x0C
};

class Display
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual void slot67(AsciiString movieName, int a, int b);	// +0x10C
};

extern Display *TheDisplay;

class LinearCampaign
{
public:
	void beginCampaign();
	void rva001EB456(int a, int b);		// 0x001EB456

private:
	void *m_vtable;
	Rva001EAFFE *m_campaign;			// +0x04
	unsigned char m_pad08[0x0C - 0x08];
	int m_0c;
	unsigned char m_pad10[0xA4 - 0x10];
	Rva001EC9BDVector m_carryoverUnits;	// +0xA4
	int m_numFlaggedCarryovers;			// +0xB0
	_STL::vector<BfmeAssignRecord172> m_b4;	// +0xB4
	unsigned char m_padC0[0xC3 - 0xC0];
	bool m_c3;
};

void LinearCampaign::beginCampaign()
{
	int count = m_campaign->m_units.size();
	Rva001EC9BDVector &units = m_carryoverUnits;
	units.resize(count);
	m_numFlaggedCarryovers = 0;
	for (int i = 0; i < count; ++i)
	{
		const AsciiString &name = m_campaign->rva001EAFFE(i);
		units[i].m_name = name;
		units[i].m_90 = 1;
		const CarryoverThingTemplateView *thing = static_cast<const CarryoverThingTemplateView *>(
			reinterpret_cast<CarryoverUnitView *>(&units[i])->rva0037DC52());
		if (thing && (thing->m_kindOf[0x5A >> 3] & (1 << (0x5A & 7))))
			++m_numFlaggedCarryovers;
	}
	m_b4.reserve(count);
	const AsciiString &movie = m_campaign->m_movie;
	if (!reinterpret_cast<const StringBase<char> *>(&movie)->isEmpty())
		TheDisplay->slot67(movie, 1, 0);
	m_0c = 0;
	m_c3 = false;
	rva001EB456(1, 1);
}
