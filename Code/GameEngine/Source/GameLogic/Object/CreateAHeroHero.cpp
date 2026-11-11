// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHs /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroHero.cpp -- CreateAHeroHero members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names each function and
// its source file; retail supplies the bytes.
//
// Layout (target evidence): the hero's bling lists live in an STLport map
// whose header node pointer is at +0x74; each node keeps a vector of bling
// ids at +0x14/+0x18. The 31-byte lookup at 0x004079D5 (unnamed in WB) finds
// the node and reports whether it is not the end.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);	// 0x00234111
// Retail's __FILE__ for this unit; the call sites pass their original line.
#define CREATEAHEROHERO_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\CreateAHeroHero.cpp"

#include "ascii_string.h"
#include "unicode_string.h"

class GameState;
extern GameState *TheGameState;
class Rva002DC267 { public: UnicodeString rva002DC267() const; };
// The Win32 call cannot throw a C++ exception. State that explicitly under
// /EHs, which preserves the native bool-tree teardown's exception states.
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryW(const unsigned short *, void *) throw();
class HeroFile { public: virtual ~HeroFile(); virtual bool open(const char *, int); virtual void close(); };
class File;
File *Rva00409892(const AsciiString &name, bool systemFile);
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"
enum ObjectID { INVALID_ID=0 };

class XferSave {
public:
    XferSave();
    virtual ~XferSave();
    unsigned char Open(Xfer *, int, bool);
private:
    unsigned char opaque04[0x40-4];
};
typedef char WriterSizeCheck[sizeof(XferSave)==0x40?1:-1];
class Gen009D6DD0 { public: void Close(); };
class Rva00406EBF { public: void rva00406EBF(Xfer *); };


class CreateAHeroHero;
class CreateAHeroManager
{
public:
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt id);
	const AsciiString &GetClassUpgradeName(UnsignedInt heroClass);
	const AsciiString &GetSubClassUpgradeName(UnsignedInt heroClass, UnsignedInt heroSubclass);

	unsigned char m_pad00[0x184];
	Bool m_active;						// +0x184
	unsigned char m_pad185[3];
	AsciiString m_upgradeOn;			// +0x188
	AsciiString m_upgradeOff;			// +0x18C
	unsigned char m_pad190[0x1bc - 0x190];
	Int m_fullBlingKey;					// +0x1BC
	Real m_rollChance;			// +0x1C0, percent
	unsigned char m_pad1C4[4];
	AsciiString m_shortAnimation;		// +0x1C8
	AsciiString m_fullAnimation;		// +0x1CC
	unsigned char m_pad1D0[0x1dc - 0x1d0];
	AsciiString m_baseCommandSetName;	// +0x1DC
	unsigned char m_pad1E0[4];
	UnsignedInt m_animationFrameOffset;	// +0x1E4
};

extern CreateAHeroManager *TheCreateAHeroManager;
// Update reads its manager through the dword at VA 0x00DFE348 (the ledger's
// ColdGlobalDwordGetters.cpp name), which the manager's init sets to itself;
// the frame offset at +0x1E4 is read through TheCreateAHeroManager.
extern int g_Va00DFE348;
// Retail's int at VA 0x00DBA4E4 (initial value 5), the animation frame scale.
extern int BfmeLogicFramesPerSecond;

struct CreateAHeroBlingNode
{
	unsigned char m_pad00[0x14];
	Int *m_idsStart;			// +0x14
	Int *m_idsFinish;			// +0x18
};

class CreateAHeroHero;

// Same witnessed STLport bit-vector ABI as the rowed award-reset provider.
// operator[] returns the eight-byte bit reference by value (native6BE1F).
#include <vector>
#include <map>
// Keep the map<int,int> iterator step inline-only; retail's out-of-line copy
// lives in stlport_map_int_int.cpp (0x169ED0).
namespace _STL { template <> __declspec(dllimport) __forceinline _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++() { _M_node = _Rb_global_inst::_M_increment(_M_node); return *this; } }
#include <string.h>
#pragma intrinsic(memcpy)
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
namespace _STL { template <> map<unsigned int, bool>::map(); }
namespace _STL {
typedef _Rb_tree<unsigned, pair<const unsigned, bool>, _Select1st<pair<const unsigned, bool> >,
    less<unsigned>, allocator<pair<const unsigned, bool> > > HeroBoolTree;
typedef _Rb_tree_node<pair<const unsigned, bool> > HeroBoolNode;
// Keep the native free-based teardown inline without exporting allocator
// wrappers under names shared with donor units using another allocator.
template <> __declspec(dllimport) __forceinline HeroBoolNode *
allocator<HeroBoolNode>::allocate(size_t count, const void *) const {
    return count != 0 ? (HeroBoolNode *)allocator<char>::allocate(count * sizeof(HeroBoolNode), 0) : 0;
}
template <> __declspec(dllimport) __forceinline HeroBoolNode *
_STLP_alloc_proxy<HeroBoolNode *, HeroBoolNode, allocator<HeroBoolNode> >::allocate(size_t count) {
    return ((allocator<HeroBoolNode> &)*this).allocate(count, 0);
}
template <> __declspec(dllimport) __forceinline void
allocator<HeroBoolNode>::deallocate(HeroBoolNode *node, size_t) const {
    if (node != 0) ::free(node);
}
template <> __declspec(dllimport) __forceinline void
_STLP_alloc_proxy<HeroBoolNode *, HeroBoolNode, allocator<HeroBoolNode> >::deallocate(
    HeroBoolNode *node, size_t count) {
    ((allocator<HeroBoolNode> &)*this).deallocate(node, count);
}
}

// Native 407FB2 uses the unsigned-key lower bound 4FF3B6, which reads node
// links and keys only. Keep its real algorithm visible: a declaration-only
// view changes VC7.1's side-effect summary and the 687-byte caller's frame.
typedef _STL::pair<const unsigned, void *> HeroLowerPair;
typedef _STL::_Rb_tree<unsigned, HeroLowerPair, _STL::_Select1st<HeroLowerPair>,
    _STL::less<unsigned>, _STL::allocator<HeroLowerPair> > HeroLowerTree;
namespace _STL {
// ?_M_lower_bound@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBIPAX@_STL@@@2@ABI@Z
template <> __declspec(noinline) inline HeroLowerTree::_Link_type
HeroLowerTree::_M_lower_bound(const unsigned &key) const {
    _Link_type result = this->_M_header._M_data;
    _Link_type node = _M_root();
    while (node != 0)
        if (!_M_key_compare(_S_key(node), key))
            result = node, node = _S_left(node);
        else node = _S_right(node);
    return result;
}
template <> __forceinline map<unsigned,bool>::iterator
map<unsigned,bool>::lower_bound(const unsigned &key) {
    return iterator((_Rb_tree_node<value_type> *)((const HeroLowerTree *)this)->lower_bound(key)._M_node);
}
}

// Native 4075A8 calls the already recovered clear 40748D. Expand this typed
// bridge while emitting the genuine STLport destructor, including its EH.
class Rva004070D4 { public: void rva0040748D(); };
namespace _STL {
template <> __declspec(dllimport) __forceinline void HeroBoolTree::clear() {
    ((Rva004070D4 *)this)->rva0040748D();
}
}
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> __declspec(dllimport) __forceinline _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--() { _M_node = _Rb_global_inst::_M_decrement(_M_node); return *this; } }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Rb_tree@IU?$pair@$$CBI_N@_STL@@U?$_Select1st@U?$pair@$$CBI_N@_STL@@@2@U?$less@I@2@V?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<unsigned int,pair<unsigned int const ,bool>,_Select1st<pair<unsigned int const ,bool> >,less<unsigned int>,allocator<pair<unsigned int const ,bool> > >::_Rb_tree(less<unsigned int> const &,allocator<pair<unsigned int const ,bool> > const &); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBI_N@_STL@@V?$allocator@U?$pair@$$CBI_N@_STL@@@2@@_STL@@QAE@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<unsigned int const ,bool>,allocator<pair<unsigned int const ,bool> > >::_Rb_tree_base(allocator<pair<unsigned int const ,bool> > const &); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@IU?$pair@$$CBI_N@_STL@@U?$_Select1st@U?$pair@$$CBI_N@_STL@@@2@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Rb_tree<unsigned int,pair<unsigned int const ,bool>,_Select1st<pair<unsigned int const ,bool> >,less<unsigned int>,allocator<pair<unsigned int const ,bool> > >::_M_erase(_Rb_tree_node<pair<unsigned int const ,bool> > *); }
// Both insert_unique overloads and _M_insert must remain visible together.
// Hiding any of the three moves the subscript's default-bool store ahead of
// its iterator copy; the complete chain reproduces the native 69-byte body.
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }
#pragma intrinsic(memset)

namespace _STL {
template<class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L> &a, const _Rb_tree_iterator<T,R> &b) { return a._M_node != b._M_node; }
template <> vector<AsciiString,allocator<AsciiString> >::~vector();
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}

// Reads the operand through a volatile view: retail reloads the bling id
// from the map node on both arms of Update's id select.
template<class T> static __forceinline T BlingOperand(const T &v) { return *(const volatile T *)&v; }
class Rva0021937DTarget { public: void rva00407E94(); };
class Rva00406E7D { public: int rva00406E7D(); };
class Rva00406E8F { public: int rva00406E8F(unsigned int); };
struct BfmePod40;
#include "../../../Include/GameClient/Rva0040AAD5.h"
extern Rva0040AAD5 *TheAwardSystemManager;
class InGameUI
{
public:
    void notifyHeroEarnedAward(CreateAHeroHero *, int);
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void __cdecl message(AsciiString text, ...);
};
extern InGameUI *TheInGameUI;
// Retain the timeline provider's existing scalar ABI spelling. Its ScienceType
// label is provisional: this call's word is the rowed GetAwardNameKey result,
// not independent evidence that award keys are science identifiers.
enum ScienceType { SCIENCE_FIRST = 0, SCIENCE_FORCE_LONG = 0x7fffffff };
void NotifyHeroEarnedAward(void *, ScienceType);

// The twelve-byte per-level button record (CreateAHeroElementCopy.cpp's
// BfmeHeroElement005C39DE): the button name, its experience level and a
// third word. SetButtonForLevel 0x0040737F stores one into the fifteen at
// +0x80.
struct BfmeHeroElement005C39DE
{
	AsciiString text;
	unsigned word4, word8;
	BfmeHeroElement005C39DE(const AsciiString &name, unsigned level, unsigned value);
	BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};

// Target offsets read by native4078A8; WB names the command-button,
// special-power and upgrade paths. The two command values remain numeric.
#include "../../../Include/Common/SpecialPower.h"
#include "../../../Include/Common/Upgrade.h"
#include "../../../Include/GameClient/CommandButton.h"
// The button's first needed upgrade (+0x28).
static inline const UpgradeTemplate *getNeededUpgrade(const CommandButton *button) { return button->m_neededBegin[0]; }
// The command set UpdateCommandSet builds, with its reset (0x00409F83, WB
// CommandSet::ResetCommandSet) and button setter (0x00409FA0, WB
// CommandSet::SetCommandButton; the ledger spells the button argument as an
// int); ControlBar's 0x0031E8D5 returns it.
#include "../../../Include/GameClient/CommandSet.h"
#include "../../../Include/Common/Overridable.h"
// ControlBar's command-set lookup by name (0x0031D5F8), rowed under its
// address-named class.
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);		// 0x0031D5F8
};
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
	CommandSet *rva0031E8D5(const AsciiString &name, Int create);	// 0x0031E8D5

	unsigned char m_pad00[0x28];
	Bool m_commandSetsChanged;		// +0x28
};
extern ControlBar *TheControlBar;
enum ModelConditionFlagType { MODEL_CONDITION_UNKNOWN = -1 };
class Drawable;
class Object
{
public:
	const AsciiString &rva00292330(const AsciiString &);
	Drawable *getDrawable() const;
	void rva00293077(const void *upgrade);
	void removeUpgrade(const UpgradeTemplate *upgrade);
	void setSpecialModelConditionState(ModelConditionFlagType type, UnsignedInt frames);

	unsigned char m_pad00[0x88];
	AsciiString m_templateName;			// +0x88
	unsigned char m_pad8C[0x264 - 0x8c];
	class Rva004074B6 *m_experience;		// +0x264
	unsigned char m_pad268[0x41c - 0x268];
	AsciiString m_commandSetStringOverride;	// +0x41C
};
class Rva004076EE { public: Object *rva004076EE(); void rva00407AE6(ModelConditionFlagType type, UnsignedInt frames); };
extern UpgradeCenter *TheUpgradeCenter;
class Rva0021BFD8 { public: Bool rva0021BFD8(const StringBase<char> &name); };
// The hero colour record Update hands the drawable (0x00406D67 fills it).
class Rva00406D67 { public: Rva00406D67 *rva00406D67(unsigned red, unsigned green, unsigned blue); unsigned data[4]; };
#include "../../../Include/GameClient/Drawable.h"
// The drawable's null-terminated draw-module array (rowed get 0x002B224B).
class Rva002B224BDwordField
{
public:
	int get() const;
};
// Draw-module and draw-interface views: only the virtual slots the two
// animation helpers call are named.
class CreateAHeroAnimInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08();
	virtual int v24();
	virtual AsciiString v28(int unused);
	virtual void v11(); virtual void v12(); virtual void v13();
	virtual bool v38(void *animation, void *frameCount);
};
class CreateAHeroDrawModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41();
	virtual CreateAHeroAnimInterface *vA8();
};
#include "../../../Include/GameLogic/ExperienceLevelStore.h"
class ExperienceLevelSystem;
class Rva004074B6 { public: void rva004074B6(const AsciiString &); };
enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/GameLogic/Module/Rva0028951F.h"
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// WorldBuilder's CAH_MAX_EXP_LEVELS (the SetButtonForLevel assert).
enum { CAH_MAX_EXP_LEVELS = 15 };

// Award record; 0x0040AA27 (unnamed in WB) tests every requirement against
// the hero.
class CreateAHeroAward
{
public:
	Bool rva0040AA27(const CreateAHeroHero *hero) const;
};

// The award-count map's mapped word (rowed operator[] 0x002C6F8C spelling).
struct TreeHintPayload001F8ACB
{
	unsigned long value;
};
namespace _STL {
template <> TreeHintPayload001F8ACB &map<AsciiString, TreeHintPayload001F8ACB, less<AsciiString>,
	allocator<pair<const AsciiString, TreeHintPayload001F8ACB> > >::operator[](const AsciiString &key);
}
class Rva00406E53 { public: int rva00406E53(); };
class Rva00406E65 { public: int rva00406E65(unsigned int); };
class Rva0040B0D0 { public: bool isContributor(const void *); };
#include "../../../Include/GameLogic/Module/Rva0040BAD0.h"
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva004088F0GameLogicView { unsigned char m_pad00[0x110]; int m_mode; };

class Rva00407137;
class Rva004071AAVirt;
// Native CRC initialization clears byte zero, then the word and flag.
class Rva00406FBF { public: unsigned crc; bool flag; Rva00406FBF() { memset(&crc,0,1); crc=0; flag=false; } };
void Rva00407099Update(Xfer *,ObjectID *,void *,Rva00406FBF *);
void Rva004071AAForward(Rva004071AAVirt *,const UnicodeString &,int,Rva00407137 *);
void Rva0040707EUpdate(void *,void *,void *,Rva00406FBF *);
void Rva004070B6Update(void *,void *,void *,Rva00406FBF *);
void Rva0040718FForward(void *,const AsciiString &,int,Rva00407137 *);
class Rva00407218 { public: void rva00407218(void *,void *); };
class Rva00407E28 { public: bool rva00407E53(int); bool rva00407DE0(int,int); };
class CreateAHeroData { public: bool WriteNamedHeroAtRva004074CF(); bool rva00408A55(); };
#include "../../Common/debug.h"
extern Debug *theDebug;
void _bfme_debugRecordCallsite(int);

// The existing lookup row uses a char result and a scalar node output.
class Rva004079D5 { public: char rva004079D5(int, int *); };

class CreateAHeroHero
{
public:
	void DoXfer(Xfer &xfer);
	void rva00407C6B();	// 0x00407C6B: clears m_bling and m_priorBling
	Bool HasEarnedAward(const CreateAHeroAward *award) const;
	Int GetBlingCount(Int blingKey) const;
	Int GetBlingId(Int blingKey, UnsignedInt index) const;
	Bool SetButtonForLevel(const AsciiString &button, UnsignedInt experienceLevel, UnsignedInt value);
	void UpdateAwardEarnedFlags();
	void rva004088F0(const void *thing, Int unused);
	Bool AddCommandButtonLevel(UnsignedInt index, const AsciiString &source,
		const AsciiString &name, const AsciiString &experience);
	Bool UpdateCommandSet(UnsignedInt rank);
	Bool RegisterExperienceLevels();
	Bool Update(Int flags);
	Bool rva004098BE(const AsciiString &name, Bool isSystem);
	AsciiString rva004073DC(const Rva002B224BDwordField *drawable);
	Bool GetAnimationFameCount(const Rva002B224BDwordField *drawable, void *animation, void *frameCount);

private:

	void *m_vtable;
	ObjectID m_id; // +0x04, DoXfer ID tag
	UnicodeString m_name; // +0x08, DoXfer Name tag
	UnsignedInt m_heroClass;				// +0x0C
	UnsignedInt m_heroSubclass;				// +0x10
	_STL::map<Int, Int> m_bling;			// +0x14
	_STL::map<Int, Int> m_priorBling;		// +0x20
	UnsignedInt m_red, m_green, m_blue;		// +0x2C
	UnsignedInt m_state38;
	unsigned char m_pad3C[0x48 - 0x3C];
	Bool m_systemHero; // +0x48, witnessed by retail4098BE/4099CA
	unsigned char m_pad49[3];
	AsciiString m_className;				// +0x4C
	_STL::map<AsciiString, TreeHintPayload001F8ACB> m_awardCounts;	// +0x50
	_STL::vector<bool> m_awardEarnedFlags; // +0x5C
	Bool m_flag70, m_updateAwards; // +0x70, +0x71
	unsigned char m_pad72[2];
	CreateAHeroBlingNode *m_blingHeader;	// +0x74, map end node
	unsigned char m_pad78[0x80 - 0x78];
	BfmeHeroElement005C39DE m_buttons[CAH_MAX_EXP_LEVELS];	// +0x80
	unsigned m_savedCRC; // +0x134, DoXfer version-eight CRC
	Int m_animationState;					// +0x138
	Int m_animationState2;					// +0x13C
};

// WB10828C0 identifies this member; native407F05..407FB2 supplies the
// incremental award loop, state bit9 reset and both notification calls.
void CreateAHeroHero::UpdateAwardEarnedFlags()
{
	if (!m_updateAwards)
		return;
	if (m_state38 & 0x200)
	{
		m_state38 &= ~0x200;
		((Rva0021937DTarget *)this)->rva00407E94();
	}
	UnsignedInt count = ((Rva00406E7D *)this)->rva00406E7D();
	for (UnsignedInt i = 0; i < count; ++i)
	{
		if (m_awardEarnedFlags[i])
			continue;
		Int key = ((Rva00406E8F *)this)->rva00406E8F(i);
		BfmePod40 *award = TheAwardSystemManager->rva0040AAD5(key);
		if (award && HasEarnedAward((const CreateAHeroAward *)award))
		{
			m_awardEarnedFlags[i] = true;
			if (TheInGameUI)
				TheInGameUI->notifyHeroEarnedAward(this, key);
			NotifyHeroEarnedAward(this, (ScienceType)key);
		}
	}
}

// Native 4088F0..4089C5 (ret 8, EH). WB 107CBF0 (unnamed, callgraph):
// outside game mode 3 it walks the award list (0x00406E53 count, 0x00406E65
// key), asks the award statistic 0x0040AAF8 on the award table at 0x00E02F74
// whether the thing contributed (0x0040B0D0, WB IsContributor), counts each
// hit in the +0x50 map under the award's key name, and refreshes the earned
// flags when anything counted. The name and second argument are unknown.
void CreateAHeroHero::rva004088F0(const void *thing, Int unused)
{
	if (((Rva004088F0GameLogicView *)TheGameLogic)->m_mode == 3)
		return;
	Bool counted = false;
	for (UnsignedInt i = 0; i < (UnsignedInt)((Rva00406E53 *)this)->rva00406E53(); ++i)
	{
		Int key = ((Rva00406E65 *)this)->rva00406E65(i);
		Rva0040B0D0 *statistic = (Rva0040B0D0 *)((Rva0040BAD0 *)TheAwardSystemManager)->rva0040AAF8(key);
		if (statistic && statistic->isContributor(thing))
		{
			AsciiString name(TheNameKeyGenerator->keyToName((NameKeyType)key));
			unsigned long count = m_awardCounts[name].value + 1;
			m_awardCounts[name].value = count;
			counted = true;
		}
	}
	if (counted)
		UpdateAwardEarnedFlags();
}

// CreateAHeroHero::HasEarnedAward, retail 0x00406EA7.
Bool CreateAHeroHero::HasEarnedAward(const CreateAHeroAward *award) const
{
	if (award == 0)
		return false;
	return award->rva0040AA27(this);
}

// CreateAHeroHero::GetAnimationFameCount, retail 0x00406F51 75B (WorldBuilder
// 0x0107FA30 names it and asserts frameCount at CreateAHeroHero.cpp line
// 1150; Update's call at 0x0040877A sets ECX, the body ignores it). Asks each
// draw module's interface (slot 42) for the animation's frame count (slot 14).
Bool CreateAHeroHero::GetAnimationFameCount(const Rva002B224BDwordField *drawable, void *animation, void *frameCount)
{
	if (frameCount == 0)
		return false;
	CreateAHeroDrawModule **modules = (CreateAHeroDrawModule **)drawable->get();
	for (; *modules; ++modules) {
		CreateAHeroDrawModule *module = *modules;
		CreateAHeroAnimInterface *di = module->vA8();
		if (!di)
			continue;
		if (di->v38(animation, frameCount))
			return true;
	}
	return false;
}

// CreateAHeroHero::GetBlingCount, retail 0x004079F4.
Int CreateAHeroHero::GetBlingCount(Int blingKey) const
{
	CreateAHeroBlingNode *node = 0;
	if (((Rva004079D5 *)this)->rva004079D5(blingKey, (int *)&node) && node != m_blingHeader)
		return node->m_idsFinish - node->m_idsStart;
	return 0;
}

// CreateAHeroHero::GetBlingId, retail 0x00407A29.
Int CreateAHeroHero::GetBlingId(Int blingKey, UnsignedInt index) const
{
	CreateAHeroBlingNode *node = 0;
	if (((Rva004079D5 *)this)->rva004079D5(blingKey, (int *)&node) && node != m_blingHeader
		&& index < (UnsignedInt)(node->m_idsFinish - node->m_idsStart))
		return node->m_idsStart[index];
	return 0;
}

// Retail 0x00406DE3 (WorldBuilder pairs it unnamed, CreateAHeroHero.cpp line
// 160): a client-random percent roll against the manager's chance.
Bool rva00406DE3RollChance()
{
	Real roll = GetGameClientRandomValueReal(0.0f, 100.0f, CREATEAHEROHERO_FILE, 160);
	return roll <= TheCreateAHeroManager->m_rollChance;
}

// Retail 0x004071D7, 32 bytes (unnamed in WorldBuilder, called from
// SetButtonForLevel): the per-level record's constructor.
BfmeHeroElement005C39DE::BfmeHeroElement005C39DE(const AsciiString &name, unsigned level, unsigned value)
	: text(name), word4(level), word8(value)
{
}

// CreateAHeroHero::SetButtonForLevel, retail 0x0040737F (WorldBuilder,
// CreateAHeroHero.cpp line 1029; wb-name-unverified).
Bool CreateAHeroHero::SetButtonForLevel(const AsciiString &button, UnsignedInt experienceLevel, UnsignedInt value)
{
	if (experienceLevel < CAH_MAX_EXP_LEVELS)
	{
		BfmeHeroElement005C39DE record(button, experienceLevel, value);
		m_buttons[experienceLevel] = record;
	}
	return true;
}

// Retail 0x004073DC 177B (unnamed in WorldBuilder; its twin 0x0107F910 moves
// ECX into this, and Update's sole call at 0x004086D2 sets ECX): the first
// non-empty animation name a draw module's interface reports (slot 9 test,
// slot 10 name by value). Retail's unwind map tracks the return slot, the
// local result and the by-value temporary.
AsciiString CreateAHeroHero::rva004073DC(const Rva002B224BDwordField *drawable)
{
	AsciiString result;
	CreateAHeroDrawModule **cursor = (CreateAHeroDrawModule **)drawable->get();
	while (result.isEmpty() && *cursor)
	{
		CreateAHeroAnimInterface *thing = (*cursor)->vA8();
		if (thing && thing->v24())
			result = thing->v28(0);
		++cursor;
	}
	return result;
}

// WB107E250 supplies the identity; native4078A8..4079D0 supplies this
// RET16 body and every field offset. CreateNewExpLevel's native28A473
// RET20 and WB BE9C10 show five string references: the third is pushed into
// vector<AsciiString>, and the last two go to SplitUpgrades/SplitString.
Bool CreateAHeroHero::AddCommandButtonLevel(UnsignedInt index, const AsciiString &source,
	const AsciiString &name, const AsciiString &experience)
{
	Object *object = ((Rva004076EE *)this)->rva004076EE();
	const CommandButton *button = TheControlBar->findCommandButton(m_buttons[index].text);
	if (!button)
		return false;
	if (button->m_command == 0x18 || button->m_command == 0x25)
	{
		const SpecialPowerTemplate *power = button->m_specialPower;
		if (!power)
			return false;
		power = (const SpecialPowerTemplate *)power->friend_getFinalOverride();
		AsciiString upgradeName = object->rva00292330(power->m_name);
		if (upgradeName.isEmpty())
			return false;
		((ExperienceLevelStore *)TheExperienceLevelSystem)->CreateNewExpLevel(
			source, name, experience, upgradeName, AsciiString());
		return true;
	}
	if (button->m_options & 0x40)
	{
		if ((UnsignedInt)(button->m_neededEnd - button->m_neededBegin) != 1)
			return false;
		const AsciiString &upgradeName = getNeededUpgrade(button)->getUpgradeName();
		if (((const StringBase<char> *)&upgradeName)->isEmpty())
			return false;
		((ExperienceLevelStore *)TheExperienceLevelSystem)->CreateNewExpLevel(
			source, name, experience, upgradeName, AsciiString());
		return true;
	}
	return false;
}

// CreateAHeroHero::UpdateCommandSet, retail 0x00407705 (WorldBuilder
// 0x0107DDF0, CreateAHeroHero.cpp lines 740..792; wb-name-unverified):
// names the hero object's command set after its template, the hero class and
// the rank, rebuilds it from the manager's base set, then lays each level
// button into its slot (a later level only while below the rank) and the
// attack-move button into slot 16.
Bool CreateAHeroHero::UpdateCommandSet(UnsignedInt rank)
{
	Object *object = ((Rva004076EE *)this)->rva004076EE();
	if (!object)
		return false;

	AsciiString commandSetName;
	commandSetName.format("CommandSet_%s_%s_rank_%d", object->m_templateName.str(), m_className.str(), rank);
	object->m_commandSetStringOverride = commandSetName;
	CommandSet *commandSet = TheControlBar->rva0031E8D5(commandSetName, 1);
	commandSet->ResetCommandSet();

	const CommandSet *baseSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(
		&TheCreateAHeroManager->m_baseCommandSetName);
	if (baseSet)
	{
		for (UnsignedInt i = 0; i < 32; ++i)
		{
			const CommandButton *button = baseSet->getCommandButton(i);
			if (button)
				commandSet->SetCommandButton((Int)button, i);
		}
	}

	for (UnsignedInt slot = 0; slot < 32; ++slot)
	{
		Bool found = false;
		for (Int i = 0; !((const StringBase<char> *)&m_buttons[i].text)->isEmpty(); ++i)
		{
			UnsignedInt buttonSlot = m_buttons[i].word8;
			if (buttonSlot != slot)
				continue;
			if (found && m_buttons[i].word4 >= rank)
				continue;
			const CommandButton *button = TheControlBar->findCommandButton(m_buttons[i].text);
			if (!button)
				continue;
			found = true;
			commandSet->SetCommandButton((Int)button, buttonSlot);
		}
	}

	AsciiString attackMove("Command_AttackMove");
	const CommandButton *button = TheControlBar->findCommandButton(attackMove);
	if (button)
		commandSet->SetCommandButton((Int)button, 0x10);
	TheControlBar->m_commandSetsChanged = true;
	return true;
}

Bool CreateAHeroHero::RegisterExperienceLevels()
{
 Object *object = ((Rva004076EE *)this)->rva004076EE();
 if (!object) return false;
 AsciiString source;
 source.format("%s_%s", "CreateAHero", m_className.str());
 object->m_experience->rva004074B6(source);
 unsigned int index = 0;
 AsciiString level;
 level.format("CreateAHeroLevel%d", index+1);
 const Overridable *info = ((Rva0028951F *)TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(level));
 _STL::map<unsigned int, bool> completed;
 do {
  ++index;
  level.format("CreateAHeroLevel%d", index);
  info = ((Rva0028951F *)TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(level));
  if (info) completed[index] = false;
 } while(info);
 index = 0;
 while (!((const StringBase<char> *)&m_buttons[index].text)->isEmpty()) {
  AsciiString name;
  level.format("CreateAHeroLevel%d", index+1);
  name.format("%s_%s", level.str(), m_className.str());
  if (AddCommandButtonLevel(index, level, name, source)) completed[index+1] = true;
  ++index;
  level.format("CreateAHeroLevel%d", index);
 }
 for (_STL::map<unsigned int,bool>::iterator it=completed.begin();it!=completed.end();++it) {
  if (!it->second) {
   level.format("CreateAHeroLevel%d", it->first);
   AsciiString name;
   name.format("%s_%s", level.str(), m_className.str());
   ((ExperienceLevelStore *)TheExperienceLevelSystem)->CreateNewExpLevel(level,name,source,AsciiString(),AsciiString());
  }
 }
 return true;
}

// CreateAHeroHero::Update, retail 0x004083FF..0x00408839 1082B (WorldBuilder
// 0x01081810 by callgraph; CreateAHeroHero.cpp lines 1446..1531): applies the
// manager's on/off upgrades, the changed bling upgrades (state bit 2), the
// class and subclass upgrades (bits 0-1), the colour rebuild (bit 3) and the
// award refresh (bit 9), then rolls a bling animation and records the
// drawable's animation state. An unsigned frame count converts with the
// 2^32 fix-up; the float product promoted to double keeps retail's fmul
// before the fimul by the frame scale.
Bool CreateAHeroHero::Update(Int flags)
{
	CreateAHeroManager *manager = (CreateAHeroManager *)g_Va00DFE348;
	Object *object = 0;
	if (manager) object = ((Rva004076EE *)this)->rva004076EE();
	if (!object) return false;
	AsciiString on = manager->m_upgradeOn;
	AsciiString off = manager->m_upgradeOff;
	const UpgradeTemplate *onUpgrade = TheUpgradeCenter->findUpgrade(on);
	const UpgradeTemplate *offUpgrade = TheUpgradeCenter->findUpgrade(off);
	Drawable *drawable = object->getDrawable();
	Bool useShort = false, useFull = false;
	if (onUpgrade && offUpgrade) {
		if (manager->m_active) { object->rva00293077(onUpgrade); object->removeUpgrade(offUpgrade); }
		else { object->rva00293077(offUpgrade); object->removeUpgrade(onUpgrade); }
	}
	Int changes = 0;
	m_state38 |= flags;
	if (m_state38 & 4) {
		for (_STL::map<Int, Int>::iterator it = m_bling.begin(); it != m_bling.end(); it++) {
			UnsignedInt id = (TheUpgradeCenter ? BlingOperand(it->second) : BlingOperand(it->second));
			Int key = it->first;
			AsciiString upgrade = manager->GetBlingUpgradeName(key, this, id);
			object->rva00293077(TheUpgradeCenter->findUpgrade(upgrade));
			if (m_priorBling[key] != id) {
				m_priorBling[key] = id;
				++changes;
				if (changes == 1) { if (manager->m_fullBlingKey == key) useFull = true; else useShort = true; }
				else if (changes > 1) { useShort = false; useFull = false; }
			}
		}
		m_state38 &= ~4;
		m_state38 |= 8;
	}
	if (m_state38 & 3) {
		AsciiString classUpgradeName = manager->GetClassUpgradeName(m_heroClass);
		const UpgradeTemplate *classUpgrade = TheUpgradeCenter->findUpgrade(classUpgradeName);
		if (classUpgrade) {
			object->rva00293077(classUpgrade);
			AsciiString subclassUpgradeName = manager->GetSubClassUpgradeName(m_heroClass, m_heroSubclass);
			const UpgradeTemplate *subclassUpgrade = TheUpgradeCenter->findUpgrade(subclassUpgradeName);
			if (subclassUpgrade) object->rva00293077(subclassUpgrade);
		}
		if (drawable) drawable->rva00274176(false);
		m_state38 &= ~3;
		m_state38 |= 0x80;
		if (manager->m_active) {
			useFull = useShort = false;
			Object *object = ((Rva004076EE *)this)->rva004076EE();
			if (object) object->setSpecialModelConditionState((ModelConditionFlagType)0x20f, 1);
		}
	}
	if ((m_state38 & 8) && drawable) {
		Rva00406D67 color;
		color.rva00406D67(m_red, m_green, m_blue);
		_STL::vector<AsciiString> names;
		m_state38 &= ~8;
		drawable->rva0027248A((int)&color, (int)&names);
		if (changes == 0) useShort = true;
	}
	if (m_state38 & 0x200) {
		m_state38 &= ~0x200;
		((Rva0021937DTarget *)this)->rva00407E94();
	}
	AsciiString current = rva004073DC((const Rva002B224BDwordField *)drawable);
	if (manager->m_active) {
		if (((Rva0021BFD8 *)manager)->rva0021BFD8(*(const StringBase<char> *)&current)) return true;
		if (m_state38 & 0x100) m_state38 &= ~0x100;
		else if (rva00406DE3RollChance() && (useShort || useFull)) {
			AsciiString animation("#(MODEL)");
			Int frames = 0;
			Int condition;
			if (useShort) { condition = 0x224; animation.concat(manager->m_fullAnimation); }
			else { animation.concat(manager->m_shortAnimation); condition = 0x226; }
			if (GetAnimationFameCount((const Rva002B224BDwordField *)drawable, &animation, &frames)) {
				frames -= TheCreateAHeroManager->m_animationFrameOffset;
				frames = (Int)((double)(float)((float)(UnsignedInt)frames * (1.0f / 30.0f)) * BfmeLogicFramesPerSecond);
				frames = _STL::max(0, frames);
				((Rva004076EE *)this)->rva00407AE6((ModelConditionFlagType)condition, frames);
			}
		}
	}
	if (drawable) { m_animationState = drawable->rva00272709(); m_animationState2 = drawable->rva0027272B(); }
	return true;
}

// Retail4098BE..4099CA includes the inline catch at40997E and shared tail.
// FuncInfo931BE0 -> TryBlockMap931BCC -> HandlerType931BBC names catch80997E;
// the state-one interval contains Open only. WB1080780 places this method
// in CreateAHeroHero.cpp; matched manager21A428 pins its current signature.
// Target facts: system flag48, save-directory getter2DC267, wrapper409892,
// transfer406EBF, writer ctor60D1F7/dtor60D0B3 and close60C8CD. XferSave's
// spelling remains donor-derived, as in the audited existing providers.
bool CreateAHeroHero::rva004098BE(const AsciiString &name, bool isSystem)
{
    m_systemHero=isSystem;
    CreateDirectoryW(((const Rva002DC267 *)TheGameState)->rva002DC267().str(),0);
    HeroFile *file=(HeroFile *)Rva00409892(name,m_systemHero);
    if(!file) {
        TheInGameUI->message(AsciiString("GUI:Error"));
        return false;
    }
    XferSave writer;
    try {
        writer.Open((Xfer *)file,1,false);
    } catch(...) {
        file->close();
        TheInGameUI->message(AsciiString("GUI:Error"));
        return false;
    }
    ((Rva00406EBF *)this)->rva00406EBF((Xfer *)&writer);
    ((Gen009D6DD0 *)&writer)->Close();
    file->close();
    return true;
}

// WB107D500 names DoXfer; native408C11..4091E2 supplies the full RET4
// body, tagged fields, two bling loops, version gates and CRC. Helper types
// retain their existing provider spellings; field layouts come from retail.
void CreateAHeroHero::DoXfer(Xfer &xfer)
{
    if(xfer.IsCRC())return;
    Rva00406FBF crc;
    // Retail passes two version bytes in a four-byte-aligned local.
    struct __declspec(align(4)) Version { unsigned char minimum,current; } version={1,8};
    xfer.operator==((Xfer::Version &)version);
    { AsciiString tag("ID"); Rva00407099Update(&xfer,&m_id,&tag,&crc); }
    { AsciiString tag("Name"); Rva004071AAForward((Rva004071AAVirt*)&xfer,m_name,(int)&tag,(Rva00407137*)&crc); }
    { AsciiString tag("ClassIndex"); Rva0040707EUpdate(&xfer,&m_heroClass,&tag,&crc); }
    { AsciiString tag("SubClassIndex"); Rva0040707EUpdate(&xfer,&m_heroSubclass,&tag,&crc); }
    unsigned dummy=0;
    { AsciiString tag("Dummy"); Rva0040707EUpdate(&xfer,&dummy,&tag,&crc); }
    { AsciiString tag("Dummy"); Rva0040707EUpdate(&xfer,&dummy,&tag,&crc); }
    { AsciiString tag("PrimaryColor"); Rva0040707EUpdate(&xfer,&m_red,&tag,&crc); }
    { AsciiString tag("SecondaryColor"); Rva0040707EUpdate(&xfer,&m_green,&tag,&crc); }
    { AsciiString tag("TertiaryColor"); Rva0040707EUpdate(&xfer,&m_blue,&tag,&crc); }
    for(unsigned i=0;i<15;++i)((Rva00407218*)&m_buttons[i])->rva00407218(&xfer,&crc);
    if(xfer.IsLoading()) {
        rva00407C6B();
        unsigned count=0;
        { AsciiString tag("BlingCount"); Rva0040707EUpdate(&xfer,&count,&tag,&crc); }
        for(unsigned i=0;i<count;++i) {
            AsciiString group;
            { AsciiString tag("GroupName"); Rva0040718FForward(&xfer,group,(int)&tag,(Rva00407137*)&crc); }
            if(group.isNone() || group.isEmpty()) {
                _bfme_debugRecordCallsite(1); theDebug->SkipNext();
                (theDebug->CrashBegin(0, 0, 0) << "Fatal error in CreateAHeroHero::DoXfer(Xfer& xfer). Invalid or empty bling group name.").CrashDone(1);
            }
            NameKeyType key=TheNameKeyGenerator->nameToKey(group);
            unsigned index=0;
            { AsciiString tag("BlingIndex"); Rva0040707EUpdate(&xfer,&index,&tag,&crc); }
            ((Rva00407E28*)this)->rva00407E53(key);
            ((Rva00407E28*)this)->rva00407DE0(key,index);
        }
    } else {
        unsigned count=m_bling.size();
        { AsciiString tag("BlingCount"); Rva0040707EUpdate(&xfer,&count,&tag,&crc); }
        for(_STL::map<int,int>::iterator i=m_bling.begin();i!=m_bling.end();++i) {
            AsciiString group(TheNameKeyGenerator->keyToName((NameKeyType)i->first));
            if(group.isNone() || group.isEmpty()) {
                _bfme_debugRecordCallsite(1); theDebug->SkipNext();
                (theDebug->CrashBegin(0, 0, 0) << "Fatal error in CreateAHeroHero::DoXfer(Xfer& xfer). Invalid or empty bling group name.").CrashDone(1);
            }
            { AsciiString tag("GroupName"); Rva0040718FForward(&xfer,group,(int)&tag,(Rva00407137*)&crc); }
            unsigned index=i->second;
            { AsciiString tag("BlingIndex"); Rva0040707EUpdate(&xfer,&index,&tag,&crc); }
        }
    }
    if(version.current>6) {
        xfer.operator==(m_className);
        if(m_flag70 && !m_className.isEmpty()) {
            if(xfer.IsLoading())((CreateAHeroData*)this)->rva00408A55();
            else if(xfer.IsStoring())((CreateAHeroData*)this)->WriteNamedHeroAtRva004074CF();
        }
    }
    if(version.current>7) {
        { AsciiString tag("IsSystemHero"); Rva004070B6Update(&xfer,&m_systemHero,&tag,&crc); }
        if(xfer.IsLoading()) { xfer.operator==(m_savedCRC); m_updateAwards=crc.crc==m_savedCRC; }
        else { m_savedCRC=crc.crc; xfer.operator==(m_savedCRC); }
    } else { m_updateAwards=true; m_savedCRC=crc.crc; }
    if(xfer.IsLoading())m_state38=0x2ff;
}

// Define the native constructor chain after its callers, keeping their
// verified out-of-line calls while replacing incompatible donor providers.

namespace _STL {
template <> __declspec(noinline) inline
_Rb_tree_base<pair<const unsigned, bool>, allocator<pair<const unsigned, bool> > >::_Rb_tree_base(
    const allocator<pair<const unsigned, bool> > &a)
    : _M_header(allocator<HeroBoolNode>(a), (HeroBoolNode *)0) {
    _M_header._M_data = _M_header.allocate(1);
}
// ??0?$_Rb_tree@IU?$pair@$$CBI_N@_STL@@U?$_Select1st@U?$pair@$$CBI_N@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBI_N@_STL@@@2@@_STL@@QAE@ABU?$less@I@1@ABV?$allocator@U?$pair@$$CBI_N@_STL@@@1@@Z
template <> __declspec(noinline) inline
HeroBoolTree::_Rb_tree(const less<unsigned> &compare, const allocator_type &a)
    : _Rb_tree_base<pair<const unsigned, bool>, allocator<pair<const unsigned, bool> > >(a),
      _M_node_count(0), _M_key_compare(compare) {
    _M_empty_initialize();
}
template <> __declspec(noinline) inline map<unsigned, bool>::map()
    : _M_t(key_compare(), allocator_type()) {}
}
