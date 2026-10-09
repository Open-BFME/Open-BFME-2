// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD
// ??0PlanningPhaseBuildingSelection@StrategicInGameUI@@QAE@PAX0PAVPlanningUI@1@0PAVLivingWorldRegion@@@Z
// Retail 0x005CE5B3..0x005CE7A3 (496 bytes).
//
// StrategicInGameUI::PlanningPhaseBuildingSelection's constructor (WB twin
// 0x015C1380, StrategicInGameUIPlanningPhaseBuildingSelection.cpp, which
// asserts region != NULL). Bases: the rowed 0x005E67FE holder (owner) at
// +0x00 and the building-observer interface at +0x08; members context
// +0x0C, UI +0x10, extra +0x14, region +0x18, the owned build helper +0x1C
// (rowed reset 0x005CE236) and +0x20. For a region without its 0x004E0625
// state it just forwards (region +0x24, hero data) through rowed 0x005E683E;
// otherwise it registers itself as an observer of the region (+0x08 list,
// rowed append 0x005A0B4C), creates the build helper (rowed 0x005E8CB0),
// gives command slot 5 a hero callback and the second command panel a
// region callback (ref-counted handles from 0x005CE2A1 / 0x005CE3F9,
// released through rowed 0x0007DEEF), and sets up the region panel (image
// from rowed 0x005D232D, callback handle 0x005CE4B2, show).
// The UI accessors and region queries are rowed under placeholder classes
// (casts below); the 2-int payload is built with the ICoord2D ctor fold
// 0x0007E523.
// PINS: the two callback creators return their handle by value (retail
// builds the temporary through the hidden pointer and only then enters its
// unwind state), but their placeholder rows spell an explicit out pointer:
//   ?Rva005CE2A1Create@@YA?AVRva005CE2A1@@PBUPayload@Rva005CE259@@@Z -> 0x005CE2A1
//   ?Rva005CE3F9Create@@YA?AVRva005CE3F9@@PBUPayload@Rva005CE327@@@Z -> 0x005CE3F9

class CreateAHeroData;
class LivingWorldRegion;

// The base at +0x00 (holds its constructor argument at +0x04).
class Rva005E67FE
{
public:
	Rva005E67FE(void *held);
	virtual ~Rva005E67FE();
	void *m_held;
};

class Rva005E683EMid
{
public:
	void fwd(int a, int b);
};

// The building-observer interface at +0x08.
class LivingWorldBuildingObserver
{
public:
	virtual ~LivingWorldBuildingObserver();
	virtual void onBuildingChanged();
};

// Region views (placeholder-rowed members of the region at +0x18).
class Rva004E0625 { public: int rva004E0625() const; };
class Rva004E05F0 { public: CreateAHeroData *rva004E05F0(); };
class Rva004E0741 { public: void rva004E0741() const; };
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *listener); };

// UI getters on the owner passed as the third argument.
class Rva0042D6B4PtrChaseField { public: int get() const; };
class Rva0042D6E6PtrChaseField { public: int get() const; };
class Rva0042D69DPtrChaseField { public: int get() const; };
class Rva0042D6FDPtrChaseField { public: int get() const; };
class Rva0042D703PtrChaseField { public: int get() const; };

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva005CE259 { public: struct Payload { int v[2]; }; };
class Rva005CE327 { public: struct Payload { int v[3]; }; };

// Reference-counted callback handles: the creators return them by value.
class Rva005CE2A1
{
public:
	~Rva005CE2A1() { if (m_00) ReleaseTreeHintRef00217D4C(m_00); }
	TargetRef00217D4C *m_00;
};
class Rva005CE3F9
{
public:
	~Rva005CE3F9() { if (m_00) ReleaseTreeHintRef00217D4C(m_00); }
	TargetRef00217D4C *m_00;
};
class Rva005CE4B2
{
public:
	Rva005CE4B2(const int *value);
	~Rva005CE4B2() { if (m_00) ReleaseTreeHintRef00217D4C(m_00); }
	TargetRef00217D4C *m_00;
};
Rva005CE2A1 Rva005CE2A1Create(const Rva005CE259::Payload *src);	// 0x005CE2A1
Rva005CE3F9 Rva005CE3F9Create(const Rva005CE327::Payload *src);	// 0x005CE3F9

struct ICoord2D
{
	ICoord2D(int ax, int ay);
	int x, y;
};

struct Rva005E8C54Source;
class Rva005E8CB0
{
public:
	Rva005E8CB0(void *a, int b, void *c, const Rva005E8C54Source *source);
	void *m_object;
};
class Rva005E893E;
class Rva005CE236
{
public:
	Rva005CE236() : m_p(0) {}
	~Rva005CE236();
	void reset(Rva005E893E *p);
	Rva005E893E *m_p;
};

class Image;
struct Rva005D232DIn;

class CommandSlots
{
public:
	virtual void s00();
	virtual void createButtonInSlot(int slot, const Rva005CE2A1 &callback);	// +0x04
};
class CommandSlots2
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual void setCallback(const Rva005CE3F9 &callback);			// +0x0C
};
class RegionPanel
{
public:
	virtual void s00();
	virtual void setImage(const Image *image);				// +0x04
	virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05();
	virtual void setCallback(const Rva005CE4B2 &callback);			// +0x18
	virtual void s07();
	virtual void show();							// +0x20
};

namespace StrategicInGameUI
{
	class PlanningUI;
	class PlanningPhaseBuildingSelection;
	const Image *GetSelectionPortrait(Rva005D232DIn *in);	// 0x005D232D
}

class StrategicInGameUI::PlanningPhaseBuildingSelection : public Rva005E67FE, public LivingWorldBuildingObserver
{
public:
	class DetailsPanel;
	friend class DetailsPanel;
	PlanningPhaseBuildingSelection(void *owner, void *context, PlanningUI *ui, void *extra, LivingWorldRegion *region);
	virtual ~PlanningPhaseBuildingSelection();
	virtual void onBuildingChanged();

private:
	void *m_context;		// +0x0C
	PlanningUI *m_ui;		// +0x10
	void *m_extra;			// +0x14
	LivingWorldRegion *m_region;	// +0x18
	Rva005CE236 m_build;		// +0x1C
	int m_20;			// +0x20
};

// WB 0x015C12B0 names this panel method and asserts its owner relationship.
// Native 0x005CE0DF..0x005CE10A, virtual pointer at 0x00875120: owner +0x0C,
// region at owner +0x18, selected region ID +0x24, then the existing hero
// query and owner forwarding thunk. Other panel fields are opaque here.
class StrategicInGameUI::PlanningPhaseBuildingSelection::DetailsPanel
{
public:
	virtual void SelectRegion();
private:
	char m_pad04[0x08];
	PlanningPhaseBuildingSelection *m_owner;
};

void StrategicInGameUI::PlanningPhaseBuildingSelection::DetailsPanel::SelectRegion()
{
	if (m_owner)
	{
		int regionId = *(int *)((char *)m_owner->m_region + 0x24);
		if (regionId)
		{
			CreateAHeroData *hero = ((Rva004E05F0 *)m_owner->m_region)->rva004E05F0();
			if (hero)
				((Rva005E683EMid *)m_owner)->fwd(regionId, (int)hero);
		}
	}
}

StrategicInGameUI::PlanningPhaseBuildingSelection::PlanningPhaseBuildingSelection(void *owner, void *context,
	PlanningUI *ui, void *extra, LivingWorldRegion *region)
	: Rva005E67FE(owner), m_context(context), m_ui(ui), m_extra(extra), m_region(region), m_20(0)
{
	if (!((const Rva004E0625 *)m_region)->rva004E0625())
	{
		int regionId = *(int *)((char *)m_region + 0x24);
		((Rva005E683EMid *)this)->fwd(regionId, (int)((Rva004E05F0 *)m_region)->rva004E05F0());
		return;
	}

	((const Rva004E0741 *)m_region)->rva004E0741();
	((Rva005A0B4CList *)((char *)m_region + 8))->append((Rva002BA8F1Listener *)static_cast<LivingWorldBuildingObserver *>(this));

	int commandUI = ((const Rva0042D6B4PtrChaseField *)m_ui)->get();
	if (commandUI)
	{
		int builder = ((const Rva0042D6E6PtrChaseField *)m_ui)->get();
		if (builder)
			m_build.reset((Rva005E893E *)new Rva005E8CB0((void *)builder, commandUI, context, (const Rva005E8C54Source *)m_region));

		CreateAHeroData *hero = ((Rva004E05F0 *)m_region)->rva004E05F0();
		if (hero)
		{
			CommandSlots *slots = (CommandSlots *)((const Rva0042D69DPtrChaseField *)m_ui)->get();
			if (slots)
				slots->createButtonInSlot(5, Rva005CE2A1Create((const Rva005CE259::Payload *)&ICoord2D(commandUI, (int)hero)));
		}

		if (((const Rva004E0625 *)m_region)->rva004E0625())
		{
			CommandSlots2 *slots2 = (CommandSlots2 *)((const Rva0042D6FDPtrChaseField *)m_ui)->get();
			if (slots2)
			{
				Rva005CE327::Payload payload = { commandUI, (int)m_region, (int)this };
				slots2->setCallback(Rva005CE3F9Create(&payload));
			}
		}
	}

	RegionPanel *panel = (RegionPanel *)((const Rva0042D703PtrChaseField *)m_ui)->get();
	if (panel)
	{
		panel->setImage(StrategicInGameUI::GetSelectionPortrait((Rva005D232DIn *)m_region));
		{
			int regionValue = (int)m_region;
			Rva005CE4B2 callback(&regionValue);
			panel->setCallback(callback);
		}
		panel->show();
	}
}
