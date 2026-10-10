// ??1LivingWorldArmy@@UAE@XZ
// partial score=0.9 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1LivingWorldArmy@@UAE@XZ, retail 0x00319D01..0x00319E76 (373 bytes,
// EH, eleven unwind states): LivingWorldArmy's destructor (WorldBuilder
// 0x0102A540 asserts in its LivingWorldArmy.cpp destructor). It tells its
// listeners through slot 0 (the generic vcall thunk), stops its audio
// (rowed 0x00318BEB), detaches from every region of TheLivingWorldLogic's
// region list (rowed 0x003F0FA3), ::deletes its +0x88 status object, kills
// its summary entries last to first (rowed KillSummaryEntry), and leaves
// TheLivingWorldLogic's +0x1C registry (rowed 0x002B7250). Then the members
// and bases die: +0x90, the record vector, the summary holder, the two
// UnicodeStrings, the four AsciiStrings, the listener base at +4 (table
// 0x00C0C824, reset to 0x00C62A20, its storage freed) and Snapshot.
// Layout follows LivingWorldArmy::xfer (Rva00318F42.cpp); field roles
// beyond what this body and the transfer touch are not asserted.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

void __cdecl Rva00030830GameFree(void *);

class Rva003197EEListener
{
public:
	virtual void notify00(void *owner);
};

class Rva003197EEList
{
public:
	~Rva003197EEList() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva003197EEListener::*notify)(void *), void *owner);
private:
	Rva003197EEListener **m_begin;
	Rva003197EEListener **m_end;
	Rva003197EEListener **m_capacity;
	unsigned int m_index;
};

// Retail's unwind map tracks three bases in construction order: Snapshot,
// the listener list (+8, null-checked conversion) and this observer (+4,
// table 0x00C0C824 reset to 0x00C62A20); MSVC lays the polymorphic
// observer out before the plain list.
class Rva00319D01ObserverBase
{
public:
	virtual __forceinline ~Rva00319D01ObserverBase() {}
};

class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};

class LivingWorldRegion
{
public:
	void rva003F0FA3(void *army);
};

struct Rva00319D01RegionOwner
{
	unsigned char m_pad00[0x2C];
	_STL::vector<LivingWorldRegion *> m_regions;	// +0x2C
};

struct Rva00319D01RegionHolder
{
	_STL::vector<LivingWorldRegion *> *regions()
	{
		if (m_owner)
			return &m_owner->m_regions;
		return 0;
	}
	unsigned char m_pad00[8];
	Rva00319D01RegionOwner *m_owner;		// +0x08
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0x1C];
	Rva002B7250 m_registry;				// +0x1C
	unsigned char m_pad20[0xB0 - 0x20];
	Rva00319D01RegionHolder *m_regions;		// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva00318BEB
{
public:
	void rva00318BEB();
};

struct ArmySummaryEntryRefView { void *control; void *entry; };
struct ArmySummaryView
{
	unsigned char m_pad00[0x40];
	_STL::vector<ArmySummaryEntryRefView> entries40;
	int size() const { return entries40.size(); }
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4();
	ArmySummaryView *m_summary;
};

class Rva00538F61
{
public:
	~Rva00538F61();
private:
	int m_00;
	void *m_04;
};

class Rva00319D01Status
{
public:
	virtual ~Rva00319D01Status();
};

struct BfmeVectorRecord00319C84 { unsigned int words[4]; };
namespace _STL {
template<> vector<BfmeVectorRecord00319C84>::~vector();
}

class LivingWorldArmy : public Snapshot, public Rva003197EEList, public Rva00319D01ObserverBase
{
public:
	virtual ~LivingWorldArmy();
	void KillSummaryEntry(int index);
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
private:
	AsciiString m_name18;			// +0x18
	AsciiString m_name1C;			// +0x1C
	int m_owner20;
	AsciiString m_name24;			// +0x24
	AsciiString m_name28;			// +0x28
	unsigned char m_pad2C[0x68 - 0x2C];
	UnicodeString m_text68;			// +0x68
	UnicodeString m_text6C;			// +0x6C
	unsigned char m_pad70[0x78 - 0x70];
	Rva000AD6F4 m_summary78;		// +0x78
	_STL::vector<BfmeVectorRecord00319C84> m_records7C;	// +0x7C
	Rva00319D01Status *m_status88;		// +0x88
	unsigned char m_pad8C[0x90 - 0x8C];
	Rva00538F61 m_member90;			// +0x90
};

LivingWorldArmy::~LivingWorldArmy()
{
	forEach(&Rva003197EEListener::notify00, this);
	reinterpret_cast<Rva00318BEB *>(this)->rva00318BEB();
	if (TheLivingWorldLogic->m_regions)
	{
		_STL::vector<LivingWorldRegion *> *regions = TheLivingWorldLogic->m_regions->regions();
		if (regions)
		{
			for (unsigned int i = 0; i < regions->size(); ++i)
				(*regions)[i]->rva003F0FA3(this);
		}
	}
	::delete m_status88;
	for (int i = m_summary78.m_summary->size() - 1; i >= 0; --i)
		KillSummaryEntry(i);
	TheLivingWorldLogic->m_registry.rva002B7250(
		reinterpret_cast<CreateAHeroData *>(static_cast<Rva00319D01ObserverBase *>(this)));
}
