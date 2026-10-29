// stlport
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc  /O1 /G7 /EHs /MD /arch:SSE /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// InGameHeroSelectInterface.cpp -- InGameHeroSelectInterface::Impl members
// recovered from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug
// build names the function and asserts a valid hero id and template; retail
// supplies the bytes and skips missing heroes instead.
//
// Target evidence: the Impl reaches its hero list through the object at
// +0x10 (an STLport list at +0x10 there); each entry holds the hero's
// ObjectID (+0x00 of the payload) and its flash countdown (+0x08). The hero
// template's name is at ThingTemplate+0x64.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
// Keep math.h's inline floorf local: retail's object exposes no _floorf.
extern "C" { static float __cdecl floorf(float); }
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
// malloc.h supplies the non-import allocation declarations used by the game
// allocator. Keep stdlib.h's parser imports, including atoi, above.
#undef _CRTIMP
#define _CRTIMP
#include <malloc.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <list>
#include "Rva00525119.h"
#include "Coord3D.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
static inline const int &max(const int &a,const int &b){return a<b?b:a;}

template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
struct Rva00525951Less
{
	bool operator()(Rva00525119 &, Rva00525119 &) const;
};
namespace _STL
{

	template<> void _S_sort(list<Rva00525119, allocator<Rva00525119> > &, Rva00525951Less);
	// Retail's builder-list node allocation (0x005258C0) calls the shared
	// one-word copy out of line; same select-any body as StlSweepW5Rva00526103.cpp.
	template<> void _Construct<Rva00525119>(Rva00525119 *, const Rva00525119 &);
	template<> inline __declspec(noinline) _List_node<Rva00525119> *list<Rva00525119, allocator<Rva00525119> >::_M_create_node(const Rva00525119 &x)
	{
		_List_node<Rva00525119> *p = (_List_node<Rva00525119> *)allocator<char>::allocate(sizeof(_List_node<Rva00525119>), 0);
		_Construct(&p->_M_data, x);
		return p;
	}
}

typedef int Int;

#include "../../../../Common/GameLogicObjectLookupView.h"

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
 char pad78[0x254-0x78];class BodyModuleInterface *m_body;
 char pad258[0x274-0x258];Object *containerOwner;char pad278[0x438-0x278]; unsigned char flags438;
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

struct HeroContainer {char pad00[0x274]; Object *owner;};
struct HeroButtonInfo
{
	ObjectID m_heroID;				// +0x00
	Int m_rank;					// +0x04, last rank seen by Update
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
 HeroButtonNode *headerNode() const {const HeroButtonNode*const*p=(const HeroButtonNode*const*)this;return (HeroButtonNode*)*p;}

	HeroButtonNode *m_header;
};

struct HeroSelectData
{
	unsigned char m_pad00[0x10];
	HeroButtonList m_heroButtons;
 HeroButtonList m_builders;			// +0x14
 Int m_builderFlashFrames; // +0x18
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
 BUILDER_SLOT(64) BUILDER_SLOT(65) virtual void selectDrawable(Drawable *); virtual void deselectDrawable(Drawable *); virtual void clearSelection(); BUILDER_SLOT(69) BUILDER_SLOT(70) BUILDER_SLOT(71)
 BUILDER_SLOT(72)
#undef BUILDER_SLOT
 virtual const SelectedList *selection();
 char padVptr[0x8BA-4];bool additiveSelection;
};
unsigned char __stdcall Rva00524FEDCheck(Object *);
unsigned char __stdcall Rva00525162Check(Object *);
class Image;
bool ComputeObjectRankValues(const Object &obj, Int &rank, Real &progress);
const Image *getButtonImage(ThingTemplate *thing, Object *obj);

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual Real getHealthRatio() const; // +0x14
};

AsciiString __cdecl Rva00222834Get(int val);

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

__forceinline const char *GetStr(const AsciiString &asciiString)
{
	char *t = *(char **)(void *)&asciiString;
	return t ? t + 8 : "";
}


class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);
__declspec(noinline) inline int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 1, GetStr(Rva00222834Get(*a5)), 0, 0, 0, 0);
}

__declspec(noinline) inline int __cdecl Rva00525235Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, int *a6)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 2, GetStr(Rva00222834Get(*a5)), (void *)GetStr(Rva00222834Get(*a6)), 0, 0, 0);
}

int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const int &a0, const char *const &a1);
__declspec(noinline) inline int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 2, GetStr(Rva00222834Get(*a5)), a6, 0, 0, 0);
}


// The Impl's button image registry at +0x38.
class Rva00524306
{
public:
	void rva00524306(const StringBase<char> &name);
	void rva00524725(const AsciiString &name, const Image *image);
};

class Rva00525783
{
public:
	void rva00525783();
};

static __forceinline long fast_float2long_round(float f)
{
	long i;
	__asm fld f
	__asm fistp i
	return i;
}

static __forceinline float fast_float_floor(float f)
{
	return (float)floor(f);
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

static __forceinline Int getHeroHealth(Object *obj)
{
	BodyModuleInterface *body = obj->m_body;
	if (body)
	{
		Int health = (Int)(body->getHealthRatio() * 100.0f + 0.5f);
		if (health > 100)
			return 100;
		if (health < 0)
			return 0;
		return health;
	}
	return 100;
}

// The Apt wrappers receive their scalar arguments by address; retail passes
// compiler temporaries, as a by-reference wrapper parameter would.
template <class T> static __forceinline T *aptArg(const T &value)
{
	return const_cast<T *>(&value);
}
class InGameHeroSelectInterface
{
public:
	class Impl
	{
	public:
		void SelectAllHeroes();
 void OnButtonPressed(const char*);
 void SelectNearestBuilder(bool noCamera);

 void BuildLocalBuilderList(_STL::list<Rva00525119> *,int);
		void FlashHeroButton(const AsciiString &templateName, Int frames);
		Bool IsBuilderOnScreen(const Object *builder);
		void rva00526E8B(_STL::list<Rva00525119> *list);
		BuilderSelectionData *FindReadyLocalBuilder(_STL::list<Rva00525119> *list);
		void Update();
		void ShowSelectAllHeroesBttn();

	private:
		Bool isSelectableHero(Object *obj)
		{
			union
			{
				unsigned char (__stdcall *fn)(Object *);
				unsigned char (Impl::*method)(Object *);
			} check = { Rva00525162Check };
			return (this->*check.method)(obj) != 0;
		}
		const char *name() const { return m_name.str(); }

		unsigned char m_pad00[0x08];
		void *m_level;				// +0x08, Apt level
		AsciiString m_name;			// +0x0C, Apt movie name
		HeroSelectData *m_data;			// +0x10
 char pad14[0x38-0x14];
 Rva00524306 m_images;			// +0x38, button image registry
 char pad39[0x44-0x39];
 Bool m_shown;				// +0x44
 // 16 slots of 24 bytes at +0x48: slot 0 holds the builders when any exist.
 struct HeroSlot
 {
  HeroButtonNode *node;			// +0x00
  const Image *image;			// +0x04
  Int rank;				// +0x08
  Int rankProgress;			// +0x0C
  Int health;				// +0x10
  Bool selected;			// +0x14
  Bool flash;				// +0x15
  Bool builderSlot;			// +0x16
 };
 HeroSlot slots[16];
 char pad1C8[0x1DA-0x1C8];bool builderUsed;
 char pad1DB;unsigned int builderDeadline;
	};
};

// InGameHeroSelectInterface::Impl::FlashHeroButton, retail 0x00525E07:
// raise the flash countdown of every hero button whose hero has the given
// template name.
void InGameHeroSelectInterface::Impl::FlashHeroButton(const AsciiString &asciiString, Int frames)
{
	HeroButtonList &list = m_data->m_heroButtons;
	for (HeroButtonNode *it = list.begin(); it != list.end(); it = it->m_next)
	{
		Object *hero = TheGameLogic->findObjectByID(it->m_data.m_heroID);
		if (hero == 0)
			continue;
		if (hero->getTemplate()->m_name.compare(asciiString) != 0)
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
	return TheTacticalView->isPointOnScreen(reinterpret_cast<const Drawable *>(builder->getDrawable())->getPosition(), 1.0f);
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

class Keyboard {public:bool isShift();};extern Keyboard *TheKeyboard;
class GameClient;
extern GameClient *TheGameClient;
class HeroGameClientView {public:
#define CSLOT(N) virtual void c##N();
 CSLOT(0) CSLOT(1) CSLOT(2) CSLOT(3) CSLOT(4) CSLOT(5) CSLOT(6) CSLOT(7)
 CSLOT(8) CSLOT(9) CSLOT(10) CSLOT(11) CSLOT(12) CSLOT(13) CSLOT(14) CSLOT(15)
 CSLOT(16) CSLOT(17) CSLOT(18) CSLOT(19) CSLOT(20) CSLOT(21) CSLOT(22) CSLOT(23)
 CSLOT(24) CSLOT(25) CSLOT(26) CSLOT(27) CSLOT(28) CSLOT(29) CSLOT(30)
#undef CSLOT
 virtual unsigned int frame();
};
struct Rva00525611Node
{
	Rva00525611Node *m_next;
	unsigned char m_pad[8];
	unsigned char m_flag;
};

struct Rva00525611Mid
{
	unsigned char m_pad[0x14];
	Rva00525611Node *m_head;
};

class Rva00525611
{
public:
	unsigned char m_pad[0x10];
	Rva00525611Mid *m_10;
	unsigned char m_pad2[0x1da - 0x14];
	unsigned char m_1da;
	void rva00525611();
};

__declspec(noinline) void Rva00525611::rva00525611()
{
	for (Rva00525611Node *cur = m_10->m_head->m_next; cur != m_10->m_head; cur = cur->m_next)
		cur->m_flag = 0;
	m_1da = 0;
}

class Rva00524FA7 {public:void rva00524FA7();};
// WB13C1750 names SelectNearestBuilder; native526F85..52710C is391B.
// Low-byte noCamera argument, selection-list size, builder-used1DA and
// deadline1DC, UI slots108/110/124, client7C and view54 are native facts.
// The reset34B helper is homed here so VC7 sees ECX preserved across it;
// the list destructor remains an external specialization, matching EH state.
void InGameHeroSelectInterface::Impl::SelectNearestBuilder(bool noCamera)
{
 if(TheKeyboard->isShift())noCamera=true;
 const SelectedList *selected=reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selection();
 unsigned int count=reinterpret_cast<const _STL::list<Drawable *> *>(selected)->size();
 if(count>1)reinterpret_cast<Rva00525611 *>(this)->rva00525611();
 else if(builderUsed && reinterpret_cast<HeroGameClientView *>(TheGameClient)->frame()>=builderDeadline)
  reinterpret_cast<Rva00525611 *>(this)->rva00525611();
 _STL::list<Rva00525119> builders;
 BuildLocalBuilderList(&builders,true);
 rva00526E8B(&builders);
 BuilderSelectionData *entry=FindReadyLocalBuilder(&builders);
 if(!entry && builderUsed) {
  reinterpret_cast<Rva00525611 *>(this)->rva00525611();
  entry=FindReadyLocalBuilder(&builders);
 }
 if(entry) {
  Object *builder=TheGameLogic->findObjectByID(entry->id);
  Drawable *draw=builder->getDrawable();
  reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->clearSelection();
  GameMessage *message=TheMessageStream->createMessage(0x3EB);
  message->appendBooleanArgument(true);
  message->appendObjectIDArgument(builder->id);
  reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selectDrawable(draw);
  if(!noCamera && !IsBuilderOnScreen(builder))
   TheTacticalView->lookAt(reinterpret_cast<Drawable *>(draw)->getPosition());
  entry->used=true;
  builderUsed=true;
  reinterpret_cast<Rva00524FA7 *>(this)->rva00524FA7();
 }
}

void InGameHeroSelectInterface::Impl::OnButtonPressed(const char *params) {
 if(strncmp(params,"Hero",4))return;
 int index=atoi(params+4)-1;
 if(index<0 || index>=16)return;
 if(slots[index].builderSlot){SelectNearestBuilder(false);return;}
 HeroButtonNode *it=slots[index].node;
 if(it==m_data->m_heroButtons.end())return;
 Object *obj=TheGameLogic->findObjectByID(it->m_data.m_heroID);
 if(!obj)return;
 if((((const unsigned char *)obj->getTemplate())[0x113]&4) && obj->containerOwner)obj=obj->containerOwner;
 if(!obj || !obj->isSelectable())return;
 Drawable *draw=obj->getDrawable();
 if(!draw)return;
 HeroContainer *container=draw->container;
 if(container){
 Object *horde=container->owner;
 if(horde && (((const unsigned char *)horde->getTemplate())[0x115]&0x20)){obj=horde;draw=horde->getDrawable();}
 }
 const _STL::list<Drawable*> *selected=reinterpret_cast<const _STL::list<Drawable*> *>(reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selection());
 if(!reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->additiveSelection || selected->size()==0 || (selected->size()==1 && selected->front()==draw)) {
  if(selected->size()==1 && selected->front()==draw)TheTacticalView->lookAt(draw->getPosition());
  else {
   reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->clearSelection();
   GameMessage *message=TheMessageStream->createMessage(0x3E9);
   message->appendBooleanArgument(true);
   message->appendObjectIDArgument(obj->id);
   reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selectDrawable(draw);
  }
 }else{
  bool found=false;
  _STL::list<Drawable*>::const_iterator pos=selected->begin();
  while(pos!=selected->end() && !found) {
   if(*pos==draw)found=true;
   else ++pos;
  }
  if(found) {
   GameMessage *message=TheMessageStream->createMessage(0x3ED);
   message->appendObjectIDArgument(obj->id);
   reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->deselectDrawable(draw);
  }else {
   GameMessage *message=TheMessageStream->createMessage(0x3E9);
   message->appendBooleanArgument(false);
   message->appendObjectIDArgument(obj->id);
   reinterpret_cast<BuilderUISelectionView *>(TheInGameUI)->selectDrawable(draw);
  }

 }
}

// WB13BF0C0 and native5264F5..526E8B establish Update and2454B extent.
// Visible exact Apt wrappers preserve independent scalar result homes.
// /EHs retains the target list-cleanup state store; no union result alias.
void InGameHeroSelectInterface::Impl::Update()
{
	_STL::list<Rva00525119> builders;
	BuildLocalBuilderList(&builders, 1);

	if (!m_shown)
	{
		HeroButtonList *heroes = &m_data->m_heroButtons;
		for (HeroButtonNode *it = heroes->begin(); it != heroes->headerNode(); it = it->m_next)
		{
			Object *hero = TheGameLogic->findObjectByID(it->m_data.m_heroID);
			if (hero && isSelectableHero(hero))
			{
				Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_level, name(), "Show");
				m_shown = true;
			}
		}
		if (!m_shown && !builders.empty())
		{
			Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_level, name(), "Show");
			m_shown = true;
		}
		return;
	}

	Int slotIndex = 0;
	if (!builders.empty())
	{
		HeroSlot *slot = &slots[slotIndex];
		if (slot->builderSlot != 1)
		{
			if (slot->node != m_data->m_heroButtons.headerNode())
			{
				Rva0052519DFire(g_bfmeAptWindowManager, m_level, name(), "KillButtonEffects", aptArg(slotIndex + 1));
				slot->node = m_data->m_heroButtons.headerNode();
			}
			slot->builderSlot = 1;

			Object *localBuilder = TheGameLogic->findObjectByID(((HeroButtonNode *)builders.front().m_ptr)->m_data.m_heroID);
			const Image *image = getButtonImage(const_cast<ThingTemplate *>(localBuilder->getTemplate()), localBuilder);
			if (slot->image == 0)
			{
				Rva00525338Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonState", aptArg(slotIndex + 1), (void *)"_up");
			}
			AsciiString imageName;
			imageName.format("_level%d.%s_Hero%dImage", m_level, name(), slotIndex + 1);
			m_images.rva00524725(imageName, image);
			slot->image = image;

			Rva00525235Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonRankProgress", aptArg(slotIndex + 1), aptArg(1));
			slot->rankProgress = 1;

			Rva00525235Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonHealthBar", aptArg(slotIndex + 1), aptArg(100));
			slot->health = 100;
		}

		Int count = builders.size();
		if (slot->rank != count)
		{
			AsciiString rankName;
			rankName.format("APT:_level%d.%s_Hero%dRank", m_level, name(), slotIndex + 1);
			UnicodeString rankText;
			rankText.format((const unsigned short *)L"%d", count);
			g_bfmeAptWindowManager->bfmeSetText(rankName, rankText, false);
			slot->rank = count;
		}

		Bool selected = false;
		for (_STL::list<Rva00525119>::iterator b = builders.begin(); b != builders.end(); ++b)
		{
			Object *builder = TheGameLogic->findObjectByID(((HeroButtonNode *)b->m_ptr)->m_data.m_heroID);
			if (builder->getDrawable()->selected)
			{
				selected = true;
				break;
			}
		}
		if (selected != slot->selected)
		{
			Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_level, name(), "SetButtonSelectedHighlightState", slotIndex + 1, selected ? "_show" : "_hide");
			slot->selected = selected;
		}

		Bool flash = m_data->m_builderFlashFrames > 0;
		if (flash != slot->flash)
		{
			Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_level, name(), "SetButtonFlashEffectState", slotIndex + 1, flash ? "_show" : "_hide");
			slot->flash = flash;
		}
		++slotIndex;
	}
	else
	{
		slots[slotIndex].builderSlot = 0;
	}

	Bool anyHero = false;
	HeroButtonList *heroes = &m_data->m_heroButtons;
	for (HeroButtonNode *it = heroes->begin(); it != heroes->headerNode(); it = it->m_next)
	{
		Object *hero = TheGameLogic->findObjectByID(it->m_data.m_heroID);
		if (hero == 0)
			continue;

		Real progress;
		Int rank = 0;
		progress = 0.0f;
		ComputeObjectRankValues(*hero, rank, progress);
		Bool levelUp = it->m_data.m_rank > 0 && rank > it->m_data.m_rank;
		it->m_data.m_rank = rank;

		if (isSelectableHero(hero) && slotIndex < 16)
		{
			HeroSlot *slot = &slots[slotIndex];
			if (it != slot->node)
			{
				Rva0052519DFire(g_bfmeAptWindowManager, m_level, name(), "KillButtonEffects", aptArg(slotIndex + 1));
				slot->node = it;
			}

			const Image *image = getButtonImage(const_cast<ThingTemplate *>(hero->getTemplate()), hero);
			if (image != slot->image)
			{
				if (slot->image == 0)
				{
					Rva00525338Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonState", aptArg(slotIndex + 1), (void *)"_up");
				}
				AsciiString imageName;
				imageName.format("_level%d.%s_Hero%dImage", m_level, name(), slotIndex + 1);
				m_images.rva00524725(imageName, image);
				slot->image = image;
			}

			if (rank != slot->rank)
			{
				AsciiString rankName;
				rankName.format("APT:_level%d.%s_Hero%dRank", m_level, name(), slotIndex + 1);
				UnicodeString rankText;
				rankText.format((const unsigned short *)L"%d", rank);
				g_bfmeAptWindowManager->bfmeSetText(rankName, rankText, false);
				slot->rank = rank;
			}

			Int rankProgress = progress >= 0.0f ? _STL::max(REAL_TO_INT_FLOOR(progress * 100.0f + 0.5f), 1L) : 1;
			if (rankProgress != slot->rankProgress)
			{
				Rva00525235Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonRankProgress", aptArg(slotIndex + 1), aptArg(rankProgress));
				slot->rankProgress = rankProgress;
			}

			Int health = _STL::max(getHeroHealth(hero), 1);
			if (health != slot->health)
			{
				Rva00525235Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonHealthBar", aptArg(slotIndex + 1), aptArg(health));
				slot->health = health;
			}

			Drawable *draw = hero->getDrawable();
			Bool selected = draw && draw->selected;
			if (selected != slot->selected)
			{
				Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_level, name(), "SetButtonSelectedHighlightState", slotIndex + 1, selected ? "_show" : "_hide");
				slot->selected = selected;
			}

			Bool flash = it->m_data.m_flashFrames > 0;
			if (flash != slot->flash)
			{
				Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager, m_level, name(), "SetButtonFlashEffectState", slotIndex + 1, flash ? "_show" : "_hide");
				slot->flash = flash;
			}

			if (levelUp)
			{
				Rva0052519DFire(g_bfmeAptWindowManager, m_level, name(), "PlayButtonLevelUpEffect", aptArg(slotIndex + 1));
			}

			++slotIndex;
			anyHero = true;
		}

		if (it->m_data.m_flashFrames > 0)
			--it->m_data.m_flashFrames;
	}

	for (; slotIndex < 16; ++slotIndex)
	{
		HeroSlot *slot = &slots[slotIndex];
		if (slot->node != heroes->headerNode())
		{
			Rva0052519DFire(g_bfmeAptWindowManager, m_level, name(), "KillButtonEffects", aptArg(slotIndex + 1));
			slot->node = heroes->headerNode();
		}
		if (slot->image != 0)
		{
			Rva00525338Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonState", aptArg(slotIndex + 1), (void *)"_unused");
			AsciiString imageName;
			imageName.format("_level%d.%s_Hero%dImage", m_level, name(), slotIndex + 1);
			m_images.rva00524306(*(const StringBase<char> *)&imageName);
			slot->image = 0;
		}
		slot->rank = -1;
		slot->rankProgress = -1;
		slot->health = -1;
		slot->selected = false;
		if (slot->flash)
		{
			Rva00525338Fire(g_bfmeAptWindowManager, m_level, name(), "SetButtonFlashEffectState", aptArg(slotIndex + 1), (void *)"_hide");
			slot->flash = false;
		}
	}

	if (anyHero)
		ShowSelectAllHeroesBttn();
	else
		reinterpret_cast<Rva00525783 *>(this)->rva00525783();

	if (m_data->m_builderFlashFrames > 0)
		--m_data->m_builderFlashFrames;
}
