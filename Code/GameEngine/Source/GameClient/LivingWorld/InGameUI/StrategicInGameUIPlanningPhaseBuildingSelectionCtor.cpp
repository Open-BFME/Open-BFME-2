// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
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

#include "../../../../Include/GameClient/Rva005E683EMid.h"

// The building-observer interface at +0x08.
#include "../../../../Include/Common/LivingWorldObservers.h"

// Region views (placeholder-rowed members of the region at +0x18).
#include "../../../../Include/Common/Rva004E0625.h"
class Rva004E05F0 { public: CreateAHeroData *rva004E05F0(); };
#include "../../../../Include/Common/Rva004E0741.h"
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *listener); };

// UI getters on the owner passed as the third argument.
#include "../../../../Include/Common/Rva0042D6B4PtrChaseField.h"
#include "../../../../Include/Common/Rva0042D6E6PtrChaseField.h"
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

#define ICOORD2D_VIEW_COMPONENT_CTOR
#include "Lib/ICoord2D.h"
#undef ICOORD2D_VIEW_COMPONENT_CTOR

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
	virtual int slot2(void *);
	virtual int slot3(const void *, int);
	virtual void rva005CE10A();
	virtual bool slot5(int);
	virtual bool slot6(int);
	virtual int rva005CE7BF(int);
	virtual void event1_1(int);
	virtual void NotifyBuildingAboutToBeDestroyedByUI(int);

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

// ---------------------------------------------------------------------------
// ControlBar::populateCommand (retail 0x0053D355, 1790 B; WB 1117000 ControlBar::populateCommand).
// Hosted here because it builds its range payload with the rowed ICoord2D(int,int)
// ctor (0x0007E523). This whole unit selects the canonical component-constructor
// view before any coordinate header is included.
// U1 r8 levers: every for loop in its own scope (WB debug locals), !sciences.empty(),
// min(entryCount,range.count) through a reference, if/else overlay tail, named
// per-element ScienceType + barrier, ZH's two getScienceVec() calls.
#include <vector>
#include <map>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
namespace _STL { void __cdecl free(void *); }
#include <vector>
#include <map>
// Keep the inlined STLport __malloc_alloc<0>::deallocate without emitting an
// optimised out-of-line copy that would shadow retail's /Od body at 0x23A70
// (STLMallocAlloc0Deallocate.cpp).
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?reserve@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<ModuleData const *,allocator<ModuleData const *> >::reserve(unsigned int); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBUTemplateCountKey@@H@_STL@@V?$allocator@U?$pair@$$CBUTempla:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct TemplateCountKey;
namespace _STL { template <> _Rb_tree_base<pair<TemplateCountKey const ,int>,allocator<pair<TemplateCountKey const ,int> > >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_insert_overflow(const ModuleData **, const ModuleData *const &, const __true_type &, size_t, bool); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPBVModuleData@@PBV1@V?$allocator@PBVModuleData@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **_STLP_alloc_proxy<const ModuleData **, const ModuleData *, allocator<const ModuleData *> >::allocate(size_t); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVModuleData@@@_STL@@QBEPAPBVModuleData@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }
// Complete ZH ControlBarCommand.cpp is the semantic guide. Named target WB
// 11180A0, assert file ControlBarCommand.cpp1005..1216, and native
// 53CF65..53D3551008 establish the target deltas and ten-case jump table.
// WB's 11188D0 template-overlay helper always returns null, and retail
// retains the template-query side effect before resetting the overlay to0.
typedef unsigned int UnsignedInt;
class ThingTemplate;
class Player;
class ExitInterface;
#include "../../../../Include/GameClient/CommandSet.h"
enum ObjectStatusTypes { CommandPopulationStatus=100 };
enum ScienceType { CommandPopulationScienceInvalid=-1 };
// Nothing here calls the science vector's deallocation helpers out of line;
// their unreferenced copies differed from the first ones in link order.
// Declared imported and force-inlined, they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<ScienceType>::deallocate(ScienceType *__p, size_t __n) const
{ if (__p != 0) __sgi_alloc::deallocate((void *)__p, __n * sizeof(value_type)); }
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<ScienceType *, ScienceType, allocator<ScienceType> >::deallocate(ScienceType *__p, size_t __n)
{ __stl_alloc_rebind(__STATIC_CAST(_Base&, *this),(ScienceType*)0).deallocate(__p, __n); }
}
class Rva0029FCB4 { public: _STL::vector<ScienceType> rva0029FCB4(); };
#include "../../../../Include/Common/Rva0023C6A4.h"
class GameLogic; extern GameLogic *TheGameLogic;
#include "../../../../Include/Common/Player.h"
class Rva0037EE4C { public: int rva0037EE4C(const ThingTemplate *,int,int); };
class Image; class ModuleData;
class Rva0037EDC6 { public: const Image *rva0037EDC6(int); };
#include "../../../../Include/GameLogic/Module/Rva0037E421.h"
class Rva0033AC7F { public: bool rva0033ACC5(AsciiString&); };
class Rva0035B750 { public: void rva0035B750(const ModuleData *); };
class Rva0035B7D9 { public: void rva0035B7D9(Rva0035B7D9 *,bool); };
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
#include "../../../../Include/GameClient/Rva0053B914.h"
class Rva0031B60DOut { public: int start,count; };
class Rva0031B60DOwner { public: Rva0031B60DOut *rva0031B60D(Rva0031B60DOut *); };
struct BfmeE8 { int x,y; };
// The rowed retail copy (stlport_vector_e8_allocate_copy.cpp, 0x00057C80) serves the link.
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::_M_insert_overflow(BfmeE8 *, const BfmeE8 &, const __false_type &, unsigned int, bool); } namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &); }
struct TemplateCountKey { const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {} __forceinline TemplateCountKey(const ThingTemplate *p):pointer(p){}
 __forceinline bool operator<(const TemplateCountKey &other)const{return pointer<other.pointer;} };
// Bind the count-map helpers to their rowed ControlBar providers.
namespace _STL {
template <> _Rb_tree_base<pair<const TemplateCountKey, int>, allocator<pair<const TemplateCountKey, int> > >::_Rb_tree_base(const allocator<pair<const TemplateCountKey, int> > &);
template <> _Rb_tree<TemplateCountKey, pair<const TemplateCountKey, int>, _Select1st<pair<const TemplateCountKey, int> >, less<TemplateCountKey>, allocator<pair<const TemplateCountKey, int> > >::~_Rb_tree();
}
struct CommandPopulationEntry { char unknown[216]; };
struct CommandPlayerView { char unknown00[0x73C]; CommandPopulationEntry *begin,*end,*capacity; };
struct CommandIncrement { int *value; CommandIncrement(int &v):value(&v){} ~CommandIncrement(){ ++*value; } };
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D368E { public: void rva002D368E(); };
#include "../../../../Include/GameClient/Rva002D363EOwner.h"
class WindowList;
class Rva0053ED1A { public: void rva0053EFC7(WindowList&); void rva0053EF2E(); };
class CommandExitView {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual const Coord3D *getRallyPoint() const;
};
#include <string.h>

#include "../../../../Include/GameClient/Bfme2GameWindow.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class CommandContainView {
public:
    virtual void slot0();
    virtual void *asOpenContain();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
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
    virtual int getContainMax();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual bool displayedOnControlBar();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual int getContainCount(int);
};
#include "../../../GameLogic/Object/object.h"
struct CommandObjectView {
    char unknown00[4]; const char *objectTemplate;
    char unknown08[0x250-8]; CommandContainView *contain;
};
struct CommandDrawableView { char unknown00[0xFC]; Object *object; };
#include "../../../../Include/Common/BfmeMemberRV.h"
class PlayerList;
extern PlayerList *ThePlayerList;
struct CommandPlayerListView { char unknown00[0x10]; BfmeMemberRV *localPlayer; };
#include "../../../../Include/GameClient/CommandButton.h"
void *GadgetButtonGetData(GameWindow *);
void GadgetButtonSetDisallowed(GameWindow *, int);
void GadgetCheckLikeButtonSetVisualCheck(GameWindow *, bool);
void Rva003284ED(GameWindow *, int);
void Rva003284B9(GameWindow *, int, int);
class Rva002A7DDEArg;
#include "../../../../Include/Common/Rva002A7DDE.h"
class ControlBar;
extern ControlBar *TheControlBar;
class ControlBar {
public:
    protected: void updateContextCommand(); public:
    void populateCommand(Object *,bool);
    void doTransportInventoryUI(Object *,CommandSet *);
    void setControlCommand(GameWindow *,const CommandButton *);
    const CommandButton *findCommandButton(const AsciiString &);
    void showRallyPoint(const Coord3D *);
    void rva0031D230();
    int rva0053BD66(const CommandButton *, GameWindow *, Object *, float *, bool) const;
private:
    char unknown00[0x50]; GameWindow *queueParent;
    char unknown54[0x6C-0x54]; CommandDrawableView *selected;
    char unknown70[0x80-0x70]; int lastInventoryCount;
    char unknown84[0xDC-0x84]; GameWindow *windows[32];
    char unknown15C[0x208-0x15C]; int clockColor;
    char unknown20C[0x2A0-0x20C]; Rva0053ED1A *overlaySink;
    char unknown2A4[4]; _STL::vector<BfmeE8> ranges;
};
// Complete named WB1117000/ControlBarCommand.cpp391..579 and clean BFME1
// ba7ddda7 populateCommand guide the workflow. Native53D355..53DA531790
// independently establishes the target ranges, two revival passes and offsets.
void ControlBar::populateCommand(Object *obj,bool refresh)
{
    Player *player=obj->getControllingPlayer();
    ((Rva0053B914 *)this)->rva0053B914();
    CommandSet *set=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
    ThingTemplate *overrideRecord=obj->rva002911B7();
    if(overrideRecord) set=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8((AsciiString *)((char *)overrideRecord+0x70));
    if(!set){ if(theRadarWindowOverrideSource)((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E(); return; }
    if(ranges.empty()) {
        ranges.push_back(reinterpret_cast<const BfmeE8 &>(ICoord2D(0,*(int *)((char *)set+0x94))));
    }
    Rva0031B60DOut range;
    ((Rva0031B60DOwner *)this)->rva0031B60D(&range);
    {for(int i=0;i<32;++i){
        if(windows[i]){
            const CommandButton *button=0;
            if(i<range.count) button=set->getCommandButton(i+range.start);
            if(!button) windows[i]->winHide(true);
            else {
                if(obj->testStatus(CommandPopulationStatus)){
                    AsciiString *name=(AsciiString *)((char *)button+0x48);
                    if(!((StringBase<char> *)name)->isEmpty()){
                        const CommandButton *alternate=TheControlBar->findCommandButton(*name);
                        if(alternate)button=alternate;
                    }
                }
                ((CommandButton *)button)->rva0035B5C2(obj,false);
            }
            setControlCommand(windows[i],button);
        }
    }}
    CommandContainView *contain=((CommandObjectView *)obj)->contain;
    if(contain&&contain->displayedOnControlBar())doTransportInventoryUI(obj,set);
    int revivalIndex=0,templateIndex=0;
    CommandPlayerView *pv=(CommandPlayerView *)player;
    int entryCount=((_STL::vector<CommandPopulationEntry> *)((char *)player+0x73C))->size();
    unsigned char used[32];
    memset(used,0,32);
    _STL::map<TemplateCountKey,int> counts;
    {for(int i=0;i<range.count;++i){
        const CommandButton *button=set->getCommandButton(i+range.start);
        char *b=(char *)button;
        if(!button||!*(bool *)(b+0x106))continue;
        if(button->getOptions()&0x80000){if(windows[i])windows[i]->winHide(true);continue;}
        if(contain&&*(bool *)(b+0x107)){
            void *open=contain->asOpenContain();
            if(open&&!*(bool *)((char *)open+0xDE))continue;
        }
        if(button->getCommandType()==0x2E){
            CommandIncrement increment(templateIndex);
            if(!((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)obj)){
                if(windows[i])windows[i]->winHide(true);continue;
            }
            const ThingTemplate *key=player->rva002AA857(templateIndex);
            int nth=counts[*(TemplateCountKey *)&key]; counts[*(TemplateCountKey *)&key]=nth+1;
            int index=-1;
            if(key)index=((Rva0037EE4C *)((char *)player+0x738))->rva0037EE4C(key,-1,nth);
            const Image *image=((Rva0037EDC6 *)((char *)player+0x738))->rva0037EDC6(index);
            Rva0033AC7F *textTemplate=(Rva0033AC7F *)((Rva0037E421 *)((char *)player+0x738))->rva0037E7A5(index);
            if(image&&textTemplate&&!((Rva0023C6A4 *)TheGameLogic)->rva00200084()){
                used[index]=1;
                ((Rva0035B750 *)button)->rva0035B750((const ModuleData *)image);
                AsciiString text;
                if(textTemplate->rva0033ACC5(text))*(AsciiString *)(b+0x7C)=text;
                if(windows[i])setControlCommand(windows[i],button);
                ((AsciiString *)(b+0x7C))->clear();
                *(int *)(b+0xC0)=index;
            }else *(int *)(b+0xC0)=-1;
            ++revivalIndex;
        }
        if(button->getCommandType()==0x10)continue;
        if(windows[i]){
            windows[i]->winHide(false);windows[i]->winEnable(true);
            if(*(bool *)(b+0x101))windows[i]->winSetStatus(0x4000000);
            else windows[i]->winClearStatus(0x4000000);
        }
        if((button->getOptions()&0x80)&&*(void **)(b+0x44)){
            _STL::vector<ScienceType> sciences=((Rva0029FCB4 *)*(void **)(b+0x44))->rva0029FCB4();
            if(!sciences.empty()){
                if(!player->hasAnyRequiredSciences(sciences)){if(windows[i])windows[i]->winHide(true);}
                else{
                    int best=-1;
                    _STL::vector<ScienceType> &list=*(_STL::vector<ScienceType> *)(b+0xA4);
                    for(unsigned j=0;j<list.size();++j){_ReadWriteBarrier();ScienceType s=list[j];if(player->hasScience(s))best=j;else break;}
                    if(best!=-1){
                        ScienceType science=list[best];
                        const CommandButton *candidate=*(const CommandButton **)((char *)this+0x2C);
                        for(;candidate;candidate=*(const CommandButton **)((char *)candidate+0x18)){
                                                        if(candidate->getCommandType()==0x19){ 
 if(candidate->getScienceVec().empty()){} else if(candidate->getScienceVec()[0]==science) ((Rva0035B7D9 *)button)->rva0035B7D9((Rva0035B7D9 *)candidate,true);}
                        }
                    }
                }
            }
        }
    }}
    if(((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)obj)){
        revivalIndex=0;
        int limit=((Rva0023C6A4 *)TheGameLogic)->rva00200084()?range.count:(*(entryCount<range.count?&entryCount:&range.count));
        {for(int i=0;i<limit;++i){
            const CommandButton *button=set->getCommandButton(i+range.start);
            char *b=(char *)button;
            if(!button||!*(bool *)(b+0x106)||button->getCommandType()!=0x2E)continue;
            if(((Rva0023C6A4 *)TheGameLogic)->rva00200084()&&(button->getOptions()&0x40))continue;
            CommandIncrement increment(revivalIndex);
            if(used[revivalIndex])continue;
            const Image *image=((Rva0037EDC6 *)((char *)player+0x738))->rva0037EDC6(revivalIndex);
            Rva0033AC7F *textTemplate=(Rva0033AC7F *)((Rva0037E421 *)((char *)player+0x738))->rva0037E7A5(revivalIndex);
            if(image&&textTemplate){
                ((Rva0035B750 *)button)->rva0035B750((const ModuleData *)image);
                AsciiString text;
                if(textTemplate->rva0033ACC5(text))*(AsciiString *)(b+0x7C)=text;
                if(windows[i])setControlCommand(windows[i],button);
                ((AsciiString *)(b+0x7C))->clear();
                *(int *)(b+0xC0)=revivalIndex;
            }else *(int *)(b+0xC0)=-1;
        }}
    }
    if(obj->isLocallyControlled()||!((CommandPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()){
        ExitInterface *exit=obj->getObjectExitInterface();
        if(exit)showRallyPoint(((CommandExitView *)exit)->getRallyPoint());
    }
    updateContextCommand();
    ((Rva002D363EOwner *)theRadarWindowOverrideSource)->rva002D363E((int)obj);
    if(overlaySink){
        if(!obj->isLocallyControlled()&&((CommandPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()){
            overlaySink->rva0053EF2E();
        } else {
        _STL::vector<GameWindow *> list;
        ((_STL::vector<const ModuleData *> *)&list)->reserve(32);
        for(int k=0;k<32;++k){GameWindow *window=windows[k];if(window)
            ((_STL::vector<const ModuleData *> *)&list)->push_back(reinterpret_cast<const ModuleData *const &>(window));}
        overlaySink->rva0053EFC7(*(WindowList *)&list);
        }
    }
}


class Rva005E57A2Callback { public: int invoke(); };

void StrategicInGameUI::PlanningPhaseBuildingSelection::event1_1(int)
{
	((Rva005E57A2Callback *)this)->invoke();
}

int StrategicInGameUI::PlanningPhaseBuildingSelection::slot2(void *) { return 0; }
int StrategicInGameUI::PlanningPhaseBuildingSelection::slot3(const void *, int) { return -1; }
bool StrategicInGameUI::PlanningPhaseBuildingSelection::slot5(int) { return false; }
bool StrategicInGameUI::PlanningPhaseBuildingSelection::slot6(int) { return false; }
