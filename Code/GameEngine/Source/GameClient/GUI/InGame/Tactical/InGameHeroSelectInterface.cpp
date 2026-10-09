// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /EHsc /MD /arch:SSE /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// InGameHeroSelectInterface.cpp -- InGameHeroSelectInterface::Impl members
// recovered from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug
// build names the function and asserts a valid hero id and template; retail
// supplies the bytes and skips missing heroes instead.
//
// Target evidence: the Impl reaches its hero list through the object at
// +0x10 (an STLport list at +0x10 there); each entry holds the hero's
// ObjectID (+0x00 of the payload) and its flash countdown (+0x08). The hero
// template's name is at ThingTemplate+0x64.
#include "ascii_string.h"
#include <list>
#include "Rva00525119.h"
#include "Coord3D.h"
struct Rva00525951Less
{
	bool operator()(Rva00525119 &, Rva00525119 &) const;
};
namespace _STL
{
	template<> void _S_sort(list<Rva00525119, allocator<Rva00525119> > &, Rva00525951Less);
}

typedef int Int;

enum ObjectID {};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x64];
	AsciiString m_name;				// +0x64
};

class Player {public:bool isLocalPlayer() const;};
class Drawable;
struct HeroContainer;

class Object
{
public:
	bool isSelectable() const;
 Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const;			// 0x005508E2

private:
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
public:
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_pos; // +0x38
 char pad44[0x74-0x44]; ObjectID id;
 char pad78[0x438-0x78]; unsigned char flags438;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);		// 0x00049DC5
};

extern GameLogic *TheGameLogic;

// IsBuilderOnScreen's view of the tactical view (VA 0x00DFEA3C, a View*):
// the slot +0x120 screen test takes a world position and a 1.0 scale.

typedef float Real;
typedef bool Bool;

class Drawable
{
public:
	const Coord3D *getPosition() const;		// 0x002763E6
	unsigned char pad00[0xFC]; HeroContainer *container;
 unsigned char pad100[0x43C-0x100];
	bool selected; // native readiness filter reads Drawable +0x43C
};

class View
{
public:
#define HERO_VIEW_SLOT(n) virtual void slot##n();
	HERO_VIEW_SLOT(00) HERO_VIEW_SLOT(01) HERO_VIEW_SLOT(02) HERO_VIEW_SLOT(03)
	HERO_VIEW_SLOT(04) HERO_VIEW_SLOT(05) HERO_VIEW_SLOT(06) HERO_VIEW_SLOT(07)
	HERO_VIEW_SLOT(08) HERO_VIEW_SLOT(09) HERO_VIEW_SLOT(10) HERO_VIEW_SLOT(11)
	HERO_VIEW_SLOT(12) HERO_VIEW_SLOT(13) HERO_VIEW_SLOT(14) HERO_VIEW_SLOT(15)
	HERO_VIEW_SLOT(16) HERO_VIEW_SLOT(17) HERO_VIEW_SLOT(18) HERO_VIEW_SLOT(19)
	HERO_VIEW_SLOT(20) virtual void lookAt(const Coord3D *); HERO_VIEW_SLOT(22) HERO_VIEW_SLOT(23)
	HERO_VIEW_SLOT(24) HERO_VIEW_SLOT(25) HERO_VIEW_SLOT(26) HERO_VIEW_SLOT(27)
	HERO_VIEW_SLOT(28) HERO_VIEW_SLOT(29) HERO_VIEW_SLOT(30) HERO_VIEW_SLOT(31)
	HERO_VIEW_SLOT(32) HERO_VIEW_SLOT(33) HERO_VIEW_SLOT(34) HERO_VIEW_SLOT(35)
	HERO_VIEW_SLOT(36) HERO_VIEW_SLOT(37) HERO_VIEW_SLOT(38) HERO_VIEW_SLOT(39)
	HERO_VIEW_SLOT(40) HERO_VIEW_SLOT(41) HERO_VIEW_SLOT(42) HERO_VIEW_SLOT(43)
	HERO_VIEW_SLOT(44) HERO_VIEW_SLOT(45) HERO_VIEW_SLOT(46) HERO_VIEW_SLOT(47)
	HERO_VIEW_SLOT(48) HERO_VIEW_SLOT(49) HERO_VIEW_SLOT(50) HERO_VIEW_SLOT(51)
	HERO_VIEW_SLOT(52) HERO_VIEW_SLOT(53) HERO_VIEW_SLOT(54) HERO_VIEW_SLOT(55)
	HERO_VIEW_SLOT(56) HERO_VIEW_SLOT(57) HERO_VIEW_SLOT(58) HERO_VIEW_SLOT(59)
	HERO_VIEW_SLOT(60) HERO_VIEW_SLOT(61) HERO_VIEW_SLOT(62) HERO_VIEW_SLOT(63)
	HERO_VIEW_SLOT(64) HERO_VIEW_SLOT(65) HERO_VIEW_SLOT(66) HERO_VIEW_SLOT(67)
	HERO_VIEW_SLOT(68) HERO_VIEW_SLOT(69)
	virtual void rvaSlot70(Coord3D *); // +0x118, camera-position output
	HERO_VIEW_SLOT(71)
#undef HERO_VIEW_SLOT
	virtual Bool isPointOnScreen(const Coord3D *pos, Real scale);	// +0x120, unnamed in WB
};

extern View *TheTacticalView;

// The common Drawable interpolation getter at2763E6 is currently provided
// under this legacy BFME1 view name. Use that kept definition, as the generic
// GameClient drawable walker does, rather than a second unresolved spelling.
class BFMERopeDrawable { public: const Coord3D *getPosition() const; };

struct HeroContainer {char pad00[0x274]; Object *owner;};
struct HeroButtonInfo
{
	ObjectID m_heroID;				// +0x00
	Int m_unknown04;
	Int m_flashFrames;				// +0x08
};

// STLport list<HeroButtonInfo> view: the list holds its header node.
struct HeroButtonNode
{
	HeroButtonNode *m_next;
	HeroButtonNode *m_prev;
	HeroButtonInfo m_data;
};

struct HeroButtonList
{
	HeroButtonNode *begin() const { return m_header->m_next; }
	HeroButtonNode *end() const { return m_header; }

	HeroButtonNode *m_header;
};

struct HeroSelectData
{
	unsigned char m_pad00[0x10];
	HeroButtonList m_heroButtons;
 HeroButtonList m_builders;			// +0x10
};

struct BuilderSelectionData;
class InGameUI;
extern InGameUI *TheInGameUI;
struct SelectedNode {SelectedNode *next,*prev;};
struct SelectedList {SelectedNode *head;};
class BuilderUISelectionView {public:
#define BUILDER_SLOT(N) virtual void slot##N();
 BUILDER_SLOT(0) BUILDER_SLOT(1) BUILDER_SLOT(2) BUILDER_SLOT(3) BUILDER_SLOT(4) BUILDER_SLOT(5) BUILDER_SLOT(6) BUILDER_SLOT(7)
 BUILDER_SLOT(8) BUILDER_SLOT(9) BUILDER_SLOT(10) BUILDER_SLOT(11) BUILDER_SLOT(12) BUILDER_SLOT(13) BUILDER_SLOT(14) BUILDER_SLOT(15)
 BUILDER_SLOT(16) BUILDER_SLOT(17) BUILDER_SLOT(18) BUILDER_SLOT(19) BUILDER_SLOT(20) BUILDER_SLOT(21) BUILDER_SLOT(22) BUILDER_SLOT(23)
 BUILDER_SLOT(24) BUILDER_SLOT(25) BUILDER_SLOT(26) BUILDER_SLOT(27) BUILDER_SLOT(28) BUILDER_SLOT(29) BUILDER_SLOT(30) BUILDER_SLOT(31)
 BUILDER_SLOT(32) BUILDER_SLOT(33) BUILDER_SLOT(34) BUILDER_SLOT(35) BUILDER_SLOT(36) BUILDER_SLOT(37) BUILDER_SLOT(38) BUILDER_SLOT(39)
 BUILDER_SLOT(40) BUILDER_SLOT(41) BUILDER_SLOT(42) BUILDER_SLOT(43) BUILDER_SLOT(44) BUILDER_SLOT(45) BUILDER_SLOT(46) BUILDER_SLOT(47)
 BUILDER_SLOT(48) BUILDER_SLOT(49) BUILDER_SLOT(50) BUILDER_SLOT(51) BUILDER_SLOT(52) BUILDER_SLOT(53) BUILDER_SLOT(54) BUILDER_SLOT(55)
 BUILDER_SLOT(56) BUILDER_SLOT(57) BUILDER_SLOT(58) BUILDER_SLOT(59) BUILDER_SLOT(60) BUILDER_SLOT(61) BUILDER_SLOT(62) BUILDER_SLOT(63)
 BUILDER_SLOT(64) BUILDER_SLOT(65) virtual void selectDrawable(Drawable *); BUILDER_SLOT(67) virtual void clearSelection(); BUILDER_SLOT(69) BUILDER_SLOT(70) BUILDER_SLOT(71)
 BUILDER_SLOT(72)
#undef BUILDER_SLOT
 virtual const SelectedList *selection();
 char padVptr[0x8BA-4];bool additiveSelection;
};
unsigned char __stdcall Rva00524FEDCheck(Object *);
class InGameHeroSelectInterface
{
public:
	class Impl
	{
	public:
		void SelectAllHeroes();

 void BuildLocalBuilderList(_STL::list<Rva00525119> *,int);
		void FlashHeroButton(const AsciiString &templateName, Int frames);
		Bool IsBuilderOnScreen(const Object *builder);
		void rva00526E8B(_STL::list<Rva00525119> *list);
		BuilderSelectionData *FindReadyLocalBuilder(_STL::list<Rva00525119> *list);

	private:
		unsigned char m_pad00[0x10];
		HeroSelectData *m_data;			// +0x10
 char pad14[0x48-0x14];
 struct HeroSlot {HeroButtonNode *node;char unknown[20];};
 HeroSlot slots[16];
 char pad1C8[0x1DA-0x1C8];bool builderUsed;
 char pad1DB;unsigned int builderDeadline;
	};
};

// InGameHeroSelectInterface::Impl::FlashHeroButton, retail 0x00525E07:
// raise the flash countdown of every hero button whose hero has the given
// template name.
void InGameHeroSelectInterface::Impl::FlashHeroButton(const AsciiString &templateName, Int frames)
{
	HeroButtonList &list = m_data->m_heroButtons;
	for (HeroButtonNode *it = list.begin(); it != list.end(); it = it->m_next)
	{
		Object *hero = TheGameLogic->findObjectByID(it->m_data.m_heroID);
		if (hero == 0)
			continue;
		if (hero->getTemplate()->m_name.compare(templateName) != 0)
			continue;
		if (frames > it->m_data.m_flashFrames)
			it->m_data.m_flashFrames = frames;
	}
}

// InGameHeroSelectInterface::Impl::IsBuilderOnScreen, retail 0x00525040 (47
// bytes): WB asserts the builder and its drawable exist; the tactical view
// tests the drawable's position at scale 1.
Bool InGameHeroSelectInterface::Impl::IsBuilderOnScreen(const Object *builder)
{
	return TheTacticalView->isPointOnScreen(reinterpret_cast<const BFMERopeDrawable *>(builder->getDrawable())->getPosition(), 1.0f);
}

// The verified sort/comparator use a one-word Rva00525119 handle. Retail
// reaches the builder state at handle->m_ptr +8; its original type is unknown.
struct BuilderSelectionData
{
	ObjectID id;
	bool used;
	unsigned char m_pad05[3];
	float distance;
};

// Native 526E8B..526F0B (128B); WB13C1A90 establishes this Impl's camera
// distance sort. The earlier list<short> provider was replaced by the verified
// pointer/float sort at 52611D. Keep the unnamed method address-derived.
void InGameHeroSelectInterface::Impl::rva00526E8B(_STL::list<Rva00525119> *list)
{
	Coord3D camera;
	TheTacticalView->rvaSlot70(&camera);
	for (_STL::list<Rva00525119>::iterator j = list->begin(); j._M_node != list->end()._M_node; ++j)
	{
		BuilderSelectionData *entry = reinterpret_cast<BuilderSelectionData *>((char *)j->m_ptr + 8);
		Object *builder = TheGameLogic->findObjectByID(entry->id);
		if (builder)
		{
			float dx = builder->m_pos.x - camera.x;
			float dy = builder->m_pos.y - camera.y;
			float square = dx * dx;
			square += dy * dy;
			entry->distance = square;
		}
	}
	Rva00525951Less compare;
	_STL::_S_sort(*list, compare);
}

// WB13C1BD0 names FindReadyLocalBuilder. Native526008..5260B1 is169B.
// The existing validity provider is recorded as a stdcall free function and
// does not read ECX. Retail nevertheless supplies Impl in ECX at this call.
// VC7's four-byte single-inheritance member-pointer adapter preserves that
// observed call setup without assigning another name to the provider.
BuilderSelectionData *InGameHeroSelectInterface::Impl::FindReadyLocalBuilder(_STL::list<Rva00525119> *list)
{
	BuilderSelectionData *result = 0;
	bool oneSelected = false;
	const SelectedList *selected = reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selection();
	unsigned int count = 0;
	for (SelectedNode *j = selected->head->next; j != selected->head; j = j->next)
		++count;
	if (count == 1)
		oneSelected = true;
	for (_STL::list<Rva00525119>::iterator j = list->begin(); j._M_node != list->end()._M_node; ++j)
	{
		BuilderSelectionData *entry = reinterpret_cast<BuilderSelectionData *>((char *)j->m_ptr + 8);
		if (entry->used)
			continue;
		Object *builder = TheGameLogic->findObjectByID(entry->id);
		union
		{
			unsigned char (__stdcall *fn)(Object *);
			unsigned char (Impl::*method)(Object *);
		} ready = { Rva00524FEDCheck };
		if (!(this->*ready.method)(builder))
			continue;
		if (oneSelected && builder->getDrawable()->selected && IsBuilderOnScreen(builder))
			continue;
		result = entry;
		break;
	}
	return result;
}

class GameMessage {public:void appendBooleanArgument(bool);void appendObjectIDArgument(ObjectID);};
class MessageStream {public:
#define MSLOT(N) virtual void v##N();
 MSLOT(0) MSLOT(1) MSLOT(2) MSLOT(3) MSLOT(4) MSLOT(5) MSLOT(6) MSLOT(7)
 MSLOT(8) MSLOT(9) MSLOT(10) MSLOT(11) MSLOT(12) MSLOT(13) MSLOT(14) MSLOT(15)
 MSLOT(16) MSLOT(17)
#undef MSLOT
 virtual GameMessage *createMessage(int);
};
extern MessageStream *TheMessageStream;
// WB13C13F0 names SelectAllHeroes; complete native525E55..526008 is435B.
// Native establishes16 slots of24B at+48, Object id+74/flags438,
// Drawable container+FC/selection43C, container owner274 and template bit115/20.
// UI additive-selection8BA and virtual slots108/110; message IDs3E9/3EA.
// BFME1 control-bar source shares the command label but has no matching body;
// reconstruction follows the named WB flow and native target layout/call sites.
void InGameHeroSelectInterface::Impl::SelectAllHeroes()
{
 bool clear = !reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->additiveSelection;
 int last = 0;
 for(int i=0;i<16;++i) {
  HeroButtonNode *it=slots[i].node;
  if(it==m_data->m_heroButtons.end())continue;
  Object *hero=TheGameLogic->findObjectByID(it->m_data.m_heroID);
  if(!hero || !hero->isSelectable() || (hero->flags438&1))continue;
  if(!hero->getDrawable() || (!clear && hero->getDrawable()->selected))continue;
  last=i;
 }
 for(int i=0;i<last+1;++i) {
  HeroButtonNode *it=slots[i].node;
  if(it==m_data->m_heroButtons.end())continue;
  Object *hero=TheGameLogic->findObjectByID(it->m_data.m_heroID);
  if(!hero || !hero->isSelectable() || (hero->flags438&1))continue;
  Drawable *draw=hero->getDrawable();
  if(!draw || (!clear && draw->selected))continue;
  HeroContainer *container=draw->container;
  if(container) {
   Object *owner=container->owner;
   if(owner && (((const unsigned char *)owner->getTemplate())[0x115]&0x20)) {
    hero=owner;draw=owner->getDrawable();
   }
  }
  if(clear)reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->clearSelection();
  GameMessage *message=TheMessageStream->createMessage(i==last?0x3E9:0x3EA);
  message->appendBooleanArgument(clear);
  message->appendObjectIDArgument(hero->id);
  reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selectDrawable(draw);
  clear=false;
 }
}

// WB13C0BF0 names BuildLocalBuilderList. Native526421..5264AD is142B.
// Native list at data+14 stores nodes with id+8 and used+C; output list
// contains one pointer per node. Mode is a DWORD compared with1, not bool.
// The same verified readiness callback and four-byte handle serve sorting.
void InGameHeroSelectInterface::Impl::BuildLocalBuilderList(_STL::list<Rva00525119> *list,int mode)
{
 list->clear();
 if(m_data->m_builders.begin()!=m_data->m_builders.end()) {
  for(HeroButtonNode *it=m_data->m_builders.begin();it!=m_data->m_builders.end();it=it->m_next) {
   Object *builder=TheGameLogic->findObjectByID(it->m_data.m_heroID);
   BuilderSelectionData *entry=reinterpret_cast<BuilderSelectionData *>(&it->m_data);
   if(builder && builder->getControllingPlayer()->isLocalPlayer()) {
    if(entry->used)builderUsed=true;
    union {unsigned char (__stdcall *fn)(Object *);unsigned char (Impl::*method)(Object *);} ready={Rva00524FEDCheck};
    if(mode!=1 || (this->*ready.method)(builder)) {
     Rva00525119 handle;handle.m_ptr=reinterpret_cast<Rva00525119Inner *>(it);
     list->push_back(handle);
    }
   } else entry->used=false;
  }
 }
}
