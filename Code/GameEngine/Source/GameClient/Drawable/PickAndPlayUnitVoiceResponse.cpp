// stlport
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib
// PickAndPlayUnitVoiceResponse.cpp (WorldBuilder twin path
// GameEngine/Source/GameClient/Drawable/PickAndPlayUnitVoiceResponse.cpp).
//
// One unit because the file statics use MSVC same-TU private register
// conventions that reproduce in the genuine caller context. Moving each
// definition before or after the caller was tested and preserves these bytes:
//   0x004D9453  76 B  victim / enter-message helper: info in ECX, victim out
//                     in EAX, enter-message out in ESI, the rest on the stack
//   0x004D9596  28 B  record "is filled" predicate; callers keep ECX live
//                     across it (no mov ecx before the following call)
//   0x004D9CF3 642 B  attack voice selection; record in ESI
//   0x004DA36A 528 B  moveRequiresClimbingWalls (WB asserts 353..396);
//                     Object in ECX
//   0x004DA57A 1316 B doPickAndPlayForMoveCommand (WB asserts 653..666);
//                     record in EDI
//   0x004DAAFD 5284 B (5078 code +206 switch data) pickAndPlayUnitVoiceResponse (WB 0x1293980, asserts
//                     1270..1808), the only caller of the statics above.
// PickAndPlayInfo's constructor (0x004D92FE, 61 B) opens the same run and is
// defined here as well: pickAndPlayUnitVoiceResponse keeps EDX live across its
// calls to it, and with the constructor declared only, the caller moves that
// value to ESI instead.
#include <float.h>
#include <new>
#include <list>

// Keep typed list comparisons local, as in PlayerTemplate.cpp. STLport's
// base comparison tests the same node pointers but emits a conflicting COMDAT.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L> &a,
                              const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"
#include "Coord3D.h"
#include "Common/BfmeAudioEventPrefix136.h"

struct BfmeE16;
struct BfmePod340;
struct Rva004DA181Element;
struct Rva004DA329Element;
struct Rva004DAADEElement;
struct Rva004DA0B7OrderKey;
class Rva004D971D;
class GameWindow;
class WindowVideo;
class Image;
class ArmorTemplate;
class Drawable;
class Object;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr {};
};

namespace rts {
template <class T> struct hash {};
}

class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <class T> struct hash {};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	char *m_start;
	char *m_finish;
	char *m_end;
};
template <class T, class A> class vector : public _Vector_base<BfmeE16, allocator<BfmeE16> >
{
public:
	vector(const allocator<BfmeE16> &a = allocator<BfmeE16>()) : _Vector_base<BfmeE16, allocator<BfmeE16> >(a) {}
	~vector();
	void reserve(unsigned int n);
	void push_back(const T &x);
};
struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class B> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);
};
template <class V, class Tr> struct _Rb_tree_iterator
{
	_Rb_tree_iterator() {}
	_Rb_tree_node_base *_M_node;
};
template <class K, class V, class KoV, class C, class A> class _Rb_tree
{
public:
	pair<_Rb_tree_iterator<V, _Nonconst_traits<V> >, bool> insert_unique(const V &v);
};
template <class K, class C, class A> class set
{
public:
	set();
	_Rb_tree_node_base *m_header;
	unsigned int m_count;
	char m_pad08[4];
};
template <class K, class T, class C, class A> class map
{
public:
	map();
	_Rb_tree_node_base *m_header;
	unsigned int m_count;
	char m_pad08[4];
};
template <class V, class Tr, class K, class HF, class ExK, class EqK, class A> struct _Ht_iterator
{
	struct Node
	{
		Node *m_next;
		Object *m_key;
		int m_value;
	};
	_Ht_iterator() {}
	_Ht_iterator(const _Ht_iterator &o) : _M_cur(o._M_cur), _M_ht(o._M_ht) {}
	Node *_M_cur;
	void *_M_ht;
	_Ht_iterator &operator++();
};
template <class V, class K, class HF, class ExK, class EqK, class A> class hashtable
{
public:
	~hashtable();
	_Ht_iterator<V, _Nonconst_traits<V>, K, HF, ExK, EqK, A> begin();
};
template<> class vector<void *,allocator<void *> > {
public:
 void **begin, **end, **storage;
 ~vector();
};
}
class Rva004D9FB9ObjectIndex {
public:
 unsigned m_functors;
 _STL::vector<void *,_STL::allocator<void *> > m_buckets;
 unsigned m_num_elements;
 __declspec(noinline) ~Rva004D9FB9ObjectIndex();
};
namespace _STL {
template <class K, class T, class HF, class EqK, class A> class hash_map
{
public:
	hash_map();
	Rva004D9FB9ObjectIndex m_table;
};

}

namespace _STL {
template<> __declspec(noinline) _List_base<Drawable*,allocator<Drawable*> >::_List_base(const allocator<Drawable*>&a)
 : _M_node(allocator<_List_node<Drawable*> >(a), (_List_node<Drawable*>*)0) {
 _List_node<Drawable*> *n=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
 n->_M_next=n;n->_M_prev=n;_M_node._M_data=n;
}
template<> _List_base<Drawable*,allocator<Drawable*> >::~_List_base();
template<> _List_base<const Object*,allocator<const Object*> >::~_List_base();
}
namespace _STL {
template <> __declspec(noinline) _List_node<Drawable*>* list<Drawable*,allocator<Drawable*> >::_M_create_node(Drawable*const&value) {
 _List_node<Drawable*> *node=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
 new ((void*)&node->_M_data) Drawable*(value);
 return node;
}
}
typedef _STL::vector<Rva004DA181Element, _STL::allocator<Rva004DA181Element> > TempTemplateVector;
typedef _STL::vector<BfmePod340, _STL::allocator<BfmePod340> > TempTemplatePushView;

typedef _STL::pair<const GameWindow *const, WindowVideo *> VideoPair;
typedef _STL::hashtable<VideoPair, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr,
	_STL::_Select1st<VideoPair>, _STL::equal_to<const GameWindow *>, _STL::allocator<VideoPair> > VideoTable;
typedef _STL::_Ht_iterator<VideoPair, _STL::_Nonconst_traits<VideoPair>, const GameWindow *,
	WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<VideoPair>,
	_STL::equal_to<const GameWindow *>, _STL::allocator<VideoPair> > ObjectIndexIterator;
typedef _STL::hash_map<int, Rva004DAADEElement, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, Rva004DAADEElement> > > ObjectIndexMap;
typedef ObjectIndexMap ObjectIndexTable;
inline ObjectIndexIterator objectsBegin(ObjectIndexTable &objectIndexTable) { return ((VideoTable *)&objectIndexTable)->begin(); }

typedef _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > CrowdCountMap;
typedef _STL::pair<const unsigned int, Image *> CrowdPair;
typedef _STL::_Rb_tree<unsigned int, CrowdPair, _STL::_Select1st<CrowdPair>, _STL::less<unsigned int>,
	_STL::allocator<CrowdPair> > CrowdCountTree;
typedef _STL::pair<_STL::_Rb_tree_iterator<CrowdPair, _STL::_Nonconst_traits<CrowdPair> >, bool> CrowdInsertResult;
class Rva004D9A62 : public CrowdCountMap
{
public:
	~Rva004D9A62();
};

typedef _STL::set<Rva004DA329Element, _STL::less<Rva004DA329Element>, _STL::allocator<Rva004DA329Element> > VoiceSet;
typedef _STL::_Rb_tree<unsigned int, Rva004D971D, Rva004DA0B7OrderKey, _STL::less<unsigned int>,
	_STL::allocator<Rva004D971D> > VoiceSetTree;
class Rva004DA149Tree : public VoiceSet
{
public:
	~Rva004DA149Tree();
};
class Rva004D9B4B
{
public:
	void rva004D9FF2();
};

struct NameKeyBucket
{
	NameKeyBucket *next;
	int key;
	void *value;
};
struct NameKeyBucketTable
{
	NameKeyBucket **start;
	NameKeyBucket **finish;
	NameKeyBucket **storageEnd;
	unsigned size() const { return (unsigned)(finish - start); }
	NameKeyBucket *&at(unsigned n) { return *(start + n); }
};
struct NameKeyHashInt
{
	unsigned operator()(int x) const { return (unsigned)x; }
};
struct NameKeyEqualInt
{
	bool operator()(int a, int b) const { return a == b; }
};
struct BucketAlloc
{
	static void *allocate(unsigned int n, const void *hint);
};
namespace _STL
{
template <class Element>
void _Construct(Element *slot, const Element &source);
}
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	class KeyToBucketMap
	{
	public:
		struct value_type
		{
			value_type(const Object *object, int i) : first((int)object), second((void *)i) {}
			int first;
			void *second;
		};
		typedef NameKeyBucket Bucket;
		struct insert_result
		{
			Bucket *first;
			KeyToBucketMap *second;
			bool inserted;
			insert_result(Bucket *bucket, KeyToBucketMap *keyToBucketMap, bool i)
				: first(bucket), second(keyToBucketMap), inserted(i)
			{
			}
		};
		__declspec(noinline) insert_result insert(const value_type &value)
		{
			resize(m_count + 1);
			return do_insert(value);
		}
	private:
		NameKeyHashInt m_hash;
		NameKeyEqualInt m_equals;
		char pad2[2];
		NameKeyBucketTable m_table;
		unsigned m_count;
		void resize(unsigned);
		__declspec(noinline) void *allocateNode(const value_type &value)
		{
			Bucket *node = (Bucket *)BucketAlloc::allocate(sizeof(Bucket), 0);
			node->next = 0;
			_STL::_Construct((value_type *)&node->key, value);
			return node;
		}
		__declspec(noinline) insert_result do_insert(const value_type &value)
		{
			const unsigned n = bkt_num(value);
			Bucket *first = (Bucket *)tableAt(n);
			for (Bucket *cur = first; cur != 0; cur = cur->next)
			{
				if (keysEqual(cur->key, lookupKey(value)))
				{
					return insert_result(cur, this, false);
				}
			}
			Bucket *tmp = (Bucket *)allocateNode(value);
			tmp->next = first;
			tableAt(n) = tmp;
			++m_count;
			return insert_result(tmp, this, true);
		}
		static int lookupKey(const value_type &v) { return v.first; }
		unsigned tableSize() const { return m_table.size(); }
		Bucket *&tableAt(unsigned n) { return m_table.at(n); }
		unsigned bkt_num_key(int key) const { return m_hash(key) % tableSize(); }
		unsigned bkt_num(const value_type &obj) const { return bkt_num_key(lookupKey(obj)); }
		bool keysEqual(int a, int b) const { return m_equals(a, b); }
	};
};
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/Common/Overridable.h"

class LocomotorTemplate
{
public:
	LocomotorTemplate(const LocomotorTemplate &o);
	virtual ~LocomotorTemplate();
	LocomotorTemplate rva001E67BF();
	Overridable *m_next;
	char m_pad08[0x08];
	AsciiString m_name;
	char m_pad14[0x154 - 0x14];
};

inline LocomotorTemplate *finalOverrideOf(LocomotorTemplate *locomotorTemplate)
{
	if (locomotorTemplate->m_next)
		return (LocomotorTemplate *)locomotorTemplate->m_next->friend_getFinalOverride();
	return locomotorTemplate;
}

class LocomotorSet
{
public:
	void addLocomotor(const LocomotorTemplate *t, bool b);
};

class BfmeTmpCF
{
public:
	BfmeTmpCF();
	~BfmeTmpCF();
private:
	char m_pad[0x24];
};

struct LocoTemplateFlags
{
	char m_pad[0x150];
	bool m_canScaleWalls;
	bool getCanScaleWalls() const { return m_canScaleWalls; }
};

struct Rva0028AC4EEntry
{
	void *m_vtbl;
	const LocoTemplateFlags *m_template;
};

class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int key);
};
extern LocomotorStore *TheLocomotorStore;

class Locomotor
{
public:
	AsciiString getTemplateName() const;
};

struct LocomotorVectorView
{
	int size() const { return m_end - m_begin; }
	Locomotor **begin() const { return m_begin; }
	Locomotor *const &operator[](unsigned int i) const { return *(begin() + i); }
	Locomotor **m_begin;
	Locomotor **m_end;
	Locomotor **m_cap;
};

class AIUpdateInterface
{
public:
	bool isMoving() const;
	char m_pad[0x1D0];
	LocomotorVectorView m_locomotors;
	char m_pad1DC[0x3B1 - 0x1DC];
	bool m_3B1;
};
typedef AIUpdateInterface AIUpdateView;

class Player
{
public:
	bool isLocalPlayer() const;
	char m_pad[0x54];
	int m_playerIndex;
	char m_pad58[0x750 - 0x58];
	enum State { State2 = 2 };
	int m_750;
	int getState() const { return m_750; }
};

class CrowdResponseTemplate
{
public:
	int *getCrowdResponseDataForThreshold(int threshold);
 int getWeight() const { return m_04; }
	int m_00;
	int m_04;
};

struct ThingTemplateView
{
	template <int B> unsigned int isKindOf() const { return m_kindOf[B >> 5] & (1u << (B & 31)); }
	float getMaxHeight() const { return m_524; }
	char m_pad00[0x64];
	AsciiString m_name;
	char m_pad68[0x108 - 0x68];
	unsigned int m_kindOf[2];
	unsigned int m_110;
	char m_pad114[0x49C - 0x114];
	CrowdResponseTemplate *m_crowdResponse;
	char m_pad4A0[0x524 - 0x4A0];
	float m_524;
};
typedef ThingTemplateView DrawableTemplateView;

enum ObjectStatusTypes { OBJECT_STATUS_NONE = 0 };
enum SpecialPowerType { SPECIAL_POWER_INVALID = 0 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };

struct ExperienceLevelNode;
class ExperienceLevelList;
struct ExperienceLevelIterator
{
	ExperienceLevelNode *m_node;
};
struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}
	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class ExperienceLevelStore
{
public:
	static ExperienceLevelStore *get() { return reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem); }
	bool IsValid(ExperienceLevelHandle handle) const;
	int GetLevelRank(ExperienceLevelHandle handle) const;
};
class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &o);
	~Rva002390CB()
	{
		if (m_ref.referent)
			m_ref.referent->Release_Ref();
	}
	bool isBound() const { return m_ref.referent != 0; }
	int m_id;
	OpaqueRefElement4 m_ref;
};

struct Rva002C99FB
{
	int m_id;
	OpaqueRefCounted *m_ref;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};
inline const Rva002C99FB &asStruct(const Rva002390CB &v) { return *(const Rva002C99FB *)&v; }

class SpecialPowerModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual Rva002390CB getInitiateSound();
};

class Rva0029439DModule
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005();
	virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017();
	virtual void s018(); virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029();
	virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039(); virtual void s040(); virtual void s041();
	virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053();
	virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065();
	virtual void s066(); virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071();
	virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075(); virtual void s076(); virtual void s077();
	virtual void s078(); virtual void s079(); virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083();
	virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087(); virtual void s088(); virtual void s089();
	virtual void s090(); virtual void s091(); virtual void s092(); virtual void s093(); virtual void s094(); virtual void s095();
	virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099(); virtual void s100(); virtual void s101();
	virtual void s102(); virtual void s103(); virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111(); virtual void s112(); virtual void s113();
	virtual void s114(); virtual void s115(); virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123(); virtual void s124(); virtual void s125();
	virtual void s126(); virtual void s127(); virtual void s128(); virtual void s129(); virtual void s130(); virtual void s131();
	virtual void s132(); virtual void s133(); virtual void s134(); virtual void s135(); virtual void s136();
	virtual Rva002390CB getEnterSound(Object *victim);
};

class Rva0028C1A9Module
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	virtual Rva002390CB getSound();
};

class ContainModuleView
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004(); virtual void s005();
	virtual void s006(); virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015(); virtual void s016(); virtual void s017();
	virtual void s018(); virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027(); virtual void s028(); virtual void s029();
	virtual void s030(); virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039(); virtual void s040(); virtual void s041();
	virtual void s042(); virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051(); virtual void s052(); virtual void s053();
	virtual void s054(); virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063(); virtual void s064(); virtual void s065();
	virtual void s066();
	virtual void getContainedItems(_STL::list<const Object *, _STL::allocator<const Object *> > *items);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Weapon;

class Object : public Thing
{
public:
 const ThingTemplateView*getTemplate() const {return m_template;}
	const Rva0028AC4EEntry *rva0028AC4E() const;
	Object *rva002931F5(bool b);
	Player *getControllingPlayer() const;
	bool rva0029493F(Object *other, int kind);
	bool testStatus(ObjectStatusTypes s) const;
	void *rva0028C197() const;
	void *rva0029439D();
	void *rva0028C1A9() const;
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType t) const;
	float getVisionRange() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void *m_vtbl;
	const ThingTemplateView *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	NameKeyType m_id;
	char m_pad78[0x258 - 0x78];
	AIUpdateView *m_ai;
	char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_experienceTracker;
};

struct WeaponTemplateView
{
	char m_pad[0xD0];
	Rva002C99FB m_D0;
	Rva002C99FB m_D8;
};
class Weapon
{
public:
	void *m_vtbl;
	const WeaponTemplateView *m_template;
};

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int locoSet);
};

class AttackPriorityInfo;
class PartitionFilter;
class AI
{
public:
	Pathfinder *getPathfinder() { return m_pathfinder; }
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers, const AttackPriorityInfo *info, PartitionFilter *filter, int unk);
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;
class Rva002FFFCA
{
public:
	void *rva002FFFCA(Object *me, const Coord3D *pos, float range, unsigned int qualifiers, int a, int b, int c);
};

extern unsigned char g_00E01EA8;

struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString() {}
	operator AsciiString();
	const char *m_text;
	int m_len;
	const AsciiString *m_right;
};
Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right);

class Rva004D977D
{
public:
	__declspec(noinline) void rva004D977D(const Rva002C99FB &a, const Rva002C99FB &b)
	{
		if (m_00.m_ref == 0 && m_00.m_id == -1)
			m_00 = a;
		if (m_18 != 0 && m_08.m_ref == 0)
			m_08 = b;
	}
private:
	Rva002C99FB m_00;
	Rva002C99FB m_08;
	char m_pad10[8];
	int m_18;
};

class Rva004D9750
{
public:
	Rva002390CB rva004D9750(int index);
};

class Rva00271BDE
{
public:
	bool rva00271BDE();
};
class Rva00271C1C
{
public:
	void rva00271C1C();
};

class Drawable
{
public:
	bool rva00276805(int index);
	Rva002390CB rva00274CD8(const AsciiString &name);
	Rva002390CB rva0027675F(int index);
	bool rva002766AE(const int *ref);
	void rva002766F8(const OpaqueRefElement4 &ref);
	int rva00274D6F();
	const Coord3D *getPosition() const;
	const DrawableTemplateView *getTemplate() const { return m_template; }
	Object *getObject() const { return m_object; }
	void *m_vtbl;
	const DrawableTemplateView *m_template;
	char m_pad08[0xFC - 0x08];
	Object *m_object;
};

// The parameter type of pickAndPlayUnitVoiceResponse and its helpers. A list
// built here is a plain list<Drawable *>: retail destroys it with the base
// destructor 0x00239AF4 on the normal path and with the list<Drawable *>
// destructor thunk 0x00239BAB in the unwind funclet.
class DrawableList : public _STL::list<Drawable *, _STL::allocator<Drawable *> >
{
};

class Rva004D9596
{
public:
	bool rva004D9596();
	int rva004D9586();

private:
	int m_00;
	int m_04;
	char m_pad08[4];
	int m_0c;
	char m_pad10[8];
	int m_18;
};

class Rva0041541B { public: const Rva002390CB &rva0041541B(const AsciiString &); };
class Rva004D97B0
{
public:
 Object *getObject() const { return m_obj; }
	// The record's two setters are owned by Rva004D97B0Record.cpp; declaring
	// them here drops this TU's duplicate COMDATs and lets the owned body win.
	void rva004D97B0(int index);
	void rva004D9874(const AsciiString &name);
	bool isFilled() { return ((Rva004D9596 *)this)->rva004D9596(); }
	bool hasVoice() { return (char)((Rva004D9596 *)this)->rva004D9586() != 0; }
	void setSounds(const Rva002390CB &a, const Rva002390CB &b) { ((Rva004D977D *)this)->rva004D977D(asStruct(a), asStruct(b)); }
	int m_00;
	int m_04;
	char m_pad08[4];
	int m_0C;
	Object *m_obj;
	Drawable *m_drawable;
	Rva004D9750 *m_extra;
	int m_1C;
	bool m_20;
};

struct VoiceNode
{
	_STL::_Rb_tree_node_base m_base;
	int m_key;
	Rva004D97B0 m_record;
};

class Rva004D99FF
{
public:
	~Rva004D99FF();
	int m_ids[6];
	AsciiString m_crush;
	AsciiString m_salvage;
};

struct MiscAudioView
{
	char m_pad[0xE0];
	OpaqueRefElement4 m_E0;
};

#define SLOT(n) virtual void slot##n();
class AudioManager
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
	virtual void addAudioEvent(BfmeAudioEventPrefix136 *ev);
	SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
	virtual bool isValidAudioEvent(BfmeAudioEventPrefix136 *ev);
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77)
	virtual const MiscAudioView *getMiscAudio();
};
#undef SLOT
extern AudioManager *TheAudio;

class Rva002D9531
{
public:
	void rva002D9531(int id);
};

class InGameUI
{
public:
	char m_pad[0x8B0];
	bool m_8B0;
	char m_pad8B1[8];
	bool m_8B9;
};
extern InGameUI *TheInGameUI;

struct Rva004DA57AVictimSource
{
	char m_pad[0xFC];
	Object *m_FC;
};

struct Rva004DA57ATarget
{
	char m_pad[4];
	Rva004DA57AVictimSource *m_04;
	char m_pad08[0x0C];
	Coord3D m_pos;
};

class Rva0035B456Owner
{
public:
	Rva002390CB rva0035B456();
	Rva002390CB rva0035B495();
	Rva002390CB rva0035B4D4();
	char m_pad[0x14];
	int m_14;
};

struct SourceThingView
{
	void *m_vtbl;
	const ThingTemplateView *m_template;
};

struct SpecialPowerTemplateView
{
	char m_pad[0x1C];
	SpecialPowerType m_type;
	char m_pad20[0x3C - 0x20];
	AsciiString m_initiateVoice;
	AsciiString m_atLocationVoice;
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();
	bool m_air;
	Drawable *m_drawTarget;
	SourceThingView *m_source;
	int *m_weaponSlot;
	const Overridable *m_specialPowerTemplate;
	Coord3D m_pos;
	Rva0035B456Owner *m_commandButton;
};

class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
};

class ActionManager
{
public:
	GameMessage::Type getEnterMessage(const Object *obj, const DrawableList *list);
};
extern ActionManager *TheActionManager;

class ArmorTemplate;

class Rva0035516C
{
public:
	const ArmorTemplate *rva0035516C(NameKeyType key) const;
};
class Rva00355B61
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
};
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

typedef _STL::list<NameKeyType, _STL::allocator<NameKeyType> > PlannedOrderList;
typedef PlannedOrderList::const_reverse_iterator PlannedOrderReverseIterator;
struct PlannedOrders
{
	void *m_vtbl;
	PlannedOrderList m_list;
	NameKeyType m_current;
};
class PlannedCommand
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A();
	virtual bool getPickAndPlayInfo(int *type, PickAndPlayInfo *info);
};

struct Rva004D9367Key
{
 Rva004D9367Key() {m0=0;m4=0;m8=0x80000000;mC=0x7fffffff;m10=0x80000000;}
	int m0;
	unsigned char m4;
	char m_pad[3];
	int m8;
	int mC;
	int m10;
};
__declspec(noinline) unsigned char __cdecl Rva004D9367Less(Rva004D9367Key const *a, Rva004D9367Key const *b)
{
	if (a->m0 < b->m0)
		return 1;
	if (a->m0 > b->m0)
		return 0;
	if (a->m4 != 0) {
		if (b->m4 == 0)
			return 0;
		if (a->m8 < b->m8)
			return 1;
		if (a->m8 <= b->m8)
			return (unsigned char)(a->mC > b->mC);
		return 0;
	}
	if (b->m4 != 0)
		return 1;
	return (unsigned char)(a->m10 < b->m10);
}

__declspec(noinline) int __cdecl Rva004D93B5NotEqual(Rva004D9367Key const *a, Rva004D9367Key const *b)
{
	if (Rva004D9367Less(a, b) || Rva004D9367Less(b, a))
		return 1;
	return 0;
}

__declspec(noinline) int __cdecl Rva004D93E2Equal(Rva004D9367Key const *a, Rva004D9367Key const *b)
{
	return !(unsigned char)Rva004D93B5NotEqual(a, b);
}

class Rva0036CA00Str;
class Rva004D964E;
class Rva004D9A44
{
public:
	Rva004D9A44(const Rva0036CA00Str &a, const Rva004D964E &b);
	char m_pad[0x28];
};
class Rva004D960C : public Rva004D9A44
{
public:
	Rva004D960C(const Rva0036CA00Str &a, const Rva004D964E &b) : Rva004D9A44(a, b) {}
	~Rva004D960C();
};

enum EvaEventID{EVA_NONE=0};
class Eva
{
public:
	bool reportEvaEvent(EvaEventID message,const Coord3D*pos,const Coord3D*other);
};
extern Eva *TheEva;

class Rva00395561
{
	int m_count;
public:
	Rva00395561();
	~Rva00395561();
};

class Rva004D9539
{
public:
	Rva004D9539(int obj, int drawable, int crowd);
	int m_00;
	int m_04;
	char m_pad08[8];
	Object *m_obj;
	Drawable *m_drawable;
	Rva004D9750 *m_extra;
	int m_1C;
	bool m_20;
};

class Rva004D95CE : public Rva004D9539
{
public:
	Rva004D95CE(Object *obj, Drawable *drawable, int *crowd) : Rva004D9539((int)obj, (int)drawable, (int)crowd) {}
	~Rva004D95CE();
	Rva004D97B0 *record() { return (Rva004D97B0 *)this; }
};

// The "no position" default, VA 0x00DCFC18 (.data): FLT_MAX, -FLT_MAX,
// FLT_MAX. The constructor copies it into m_pos and the voice routing tests a
// position against it through Coord3D::equals.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
Coord3DBase g_bfmeCoordDefault = { FLT_MAX, -FLT_MAX, FLT_MAX };

// ??0PickAndPlayInfo@@QAE@XZ @0x004D92FE 61B
__declspec(noinline) PickAndPlayInfo::PickAndPlayInfo()
{
 m_air=false; m_drawTarget=0; m_source=0; m_weaponSlot=0; m_specialPowerTemplate=0;
 m_pos.x=((const Coord3D*)&g_bfmeCoordDefault)->x;
 m_pos.y=((const Coord3D*)&g_bfmeCoordDefault)->y;
 m_pos.z=((const Coord3D*)&g_bfmeCoordDefault)->z;
 m_commandButton=0;
}


struct BfmePointFD;
bool __cdecl Rva004D933BIs(int command);
bool __cdecl rva004D94FC(Object *obj);
unsigned char __cdecl countsAsMoveIntoCamp(unsigned int mask, const BfmePointFD *from, const BfmePointFD *to);
void __cdecl Rva004D990E(int command, Object *obj, Rva004D97B0 *out, const Coord3D *location);

// 0x004D9453: the victim is the target drawable's object; an enter command
// asks the ActionManager which enter message the selection would send.
static void getVictimAndEnterMessage(const DrawableList *list, GameMessage::Type type, PickAndPlayInfo *info,
	Object **victim, GameMessage::Type *enterMessage, bool *isAttackOrMove)
{
	*victim = 0;
	if (info && info->m_drawTarget)
		*victim = info->m_drawTarget->getObject();
	*enterMessage = (GameMessage::Type)-1;
	if (*victim && type == 0x42C)
		*enterMessage = TheActionManager->getEnterMessage(*victim, list);
	*isAttackOrMove = Rva004D933BIs(type);
}

bool Rva004D9596::rva004D9596()
{
	if (m_00 != -1 || (m_04 != 0 && (m_18 == 0 || m_0c != 0)))
		return true;
	return false;
}

struct AttackVoiceIds
{
	int m_ids[5];
	AsciiString m_bombard;
};

// 0x004D9CF3: attack-command voices (WB twin 0x1298380).
static void doPickAndPlayForAttackCommand(GameMessage::Type type, PickAndPlayInfo *info, bool forced, Rva004D97B0 *record)
{
	AttackVoiceIds ids;
	Object *obj = record->m_obj;
	Drawable *drawable = record->m_drawable;
	Player *player = obj->getControllingPlayer();
	bool isSiege = Rva004D933BIs(type);
	record->m_20 = true;
	if (isSiege)
	{
		ids.m_ids[0] = 0x16;
		ids.m_ids[1] = 0x17;
		ids.m_ids[2] = 0x18;
		ids.m_ids[3] = 0x19;
		ids.m_ids[4] = 0x1A;
	}
	else
	{
		ids.m_ids[0] = 6;
		ids.m_ids[1] = 7;
		ids.m_ids[2] = 0xC;
		ids.m_ids[3] = 0x12;
		ids.m_ids[4] = 0x13;
		ids.m_bombard = "VoiceBombard";
	}

	if (!isSiege && player && player->getState() == 2 && !forced)
	{
		Rva002390CB sound;
		sound.m_ref = TheAudio->getMiscAudio()->m_E0;
		((Rva004D977D *)record)->rva004D977D(asStruct(sound), asStruct(Rva002390CB()));
		return;
	}

	if (type == 0x427)
		record->rva004D9874(ids.m_bombard);

	if (!record->isFilled() && info && info->m_drawTarget)
	{
		const ThingTemplateView *thingTemplateView = info->m_drawTarget->getTemplate();
		if (thingTemplateView)
		{
			const AsciiString &asciiString=thingTemplateView->m_name;
			AsciiString name(isSiege ? "VoiceEnterStateAttackUnit" : "VoiceAttackUnit");
			name += asciiString;
			record->rva004D9874(name);
			if (!record->isFilled())
			{
				if (thingTemplateView->isKindOf<7>())
					record->rva004D97B0(ids.m_ids[3]);
				else if (thingTemplateView->isKindOf<11>())
					record->rva004D97B0(ids.m_ids[4]);
			}
		}
	}

	if (!record->isFilled())
	{
		const Weapon *weapon = obj->getCurrentWeapon(0);
		if (weapon) {
const WeaponTemplateView *weaponTemplate=weapon->m_template;
if (weaponTemplate) {
			if (isSiege)
				((Rva004D977D *)record)->rva004D977D(weaponTemplate->m_D8, asStruct(Rva002390CB()));
			else
				((Rva004D977D *)record)->rva004D977D(weaponTemplate->m_D0, asStruct(Rva002390CB()));
		}
	}

}
	if (!record->isFilled() && ((Rva00271BDE *)drawable)->rva00271BDE())
		record->rva004D97B0(ids.m_ids[1]);

	if (!record->isFilled() && info && info->m_air)
		record->rva004D97B0(ids.m_ids[2]);

	if (!record->isFilled())
		record->rva004D97B0(ids.m_ids[0]);
}

static bool moveRequiresClimbingWalls(Object *obj, const Coord3D *pos)
{
	if (!obj->rva0028AC4E() || !obj->rva0028AC4E()->m_template->getCanScaleWalls())
		return false;
	Object *horde = obj->rva002931F5(true);
	if (!horde)
		horde = obj;
	if (!horde->rva0028AC4E())
		return false;
	if (!TheAI->getPathfinder()->QuickDoesPathExist(horde, &horde->m_pos, pos, 0))
		return false;
	AIUpdateView *ai = horde->m_ai;
	if (!ai)
		return false;

	BfmeTmpCF locoSet;
	TempTemplateVector temps;
	int count = ai->m_locomotors.size();
	temps.reserve(count);
	g_00E01EA8 = 1;
	for (int i = 0; i < count; ++i)
	{
		Locomotor *loco = ai->m_locomotors[i];
		LocomotorTemplate *lt = TheLocomotorStore->findLocomotorTemplate(TheNameKeyGenerator->nameToKey(loco->getTemplateName()));
		if (!lt)
			continue;
		lt = finalOverrideOf(lt);
		((TempTemplatePushView *)&temps)->push_back((const BfmePod340 &)lt->rva001E67BF());
		((LocomotorTemplate *)temps.m_finish - 1)->m_name = "TempVoiceMoveOverWallTesting_" + lt->m_name;
		((LocomotorSet *)&locoSet)->addLocomotor((const LocomotorTemplate *)((LocomotorTemplate *)temps.m_finish - 1), true);
	}
	g_00E01EA8 = 0;
	if (!TheAI->getPathfinder()->QuickDoesPathExist(horde, &horde->m_pos, pos, (int)&locoSet))
		return true;
	return false;
}


static void doPickAndPlayForMoveCommand(int command, Rva004DA57ATarget *target, bool forced, int *pending, Rva004D97B0 *record, int *voiceType)
{
	Rva004D99FF ids;
	Object *obj = record->m_obj;
	Drawable *drawable = record->m_drawable;
	Player *player = obj->getControllingPlayer();
	Rva004D9750 *extra = record->m_extra;
	bool isSiege = Rva004D933BIs(command);
	if (isSiege)
	{
		ids.m_ids[0] = 0x1B;
		ids.m_ids[1] = 0x1E;
		ids.m_ids[2] = 0x1F;
		ids.m_ids[3] = 0x20;
		ids.m_ids[4] = 0x1C;
		ids.m_ids[5] = 0x1D;
	}
	else
	{
		ids.m_ids[0] = 3;
		ids.m_ids[1] = 0x10;
		ids.m_ids[2] = 0x11;
		ids.m_ids[3] = 0x14;
		ids.m_ids[4] = 4;
		ids.m_ids[5] = 5;
		ids.m_crush = "VoiceCrush";
		ids.m_salvage = "VoiceSalvage";
	}

	if (!isSiege && player && player->m_750 == 2 && !forced)
	{
		Rva002390CB sound;
		sound.m_ref = TheAudio->getMiscAudio()->m_E0;
		((Rva004D977D *)record)->rva004D977D(asStruct(sound), asStruct(Rva002390CB()));
		return;
	}

	if (!isSiege && TheInGameUI->m_8B9 && !(player && player->m_750 == 2))
	{
		if (target && target->m_04)
		{
			Object *victim = target->m_04->m_FC;
			if (victim && obj->rva0029493F(victim, 2))
			{
				record->rva004D9874(ids.m_crush);
				if (record->m_04 != 0)
					*voiceType = 1;
			}
		}
	}
	else if (command == 0x442)
	{
		record->rva004D9874(ids.m_salvage);
		if (record->m_04 != 0)
			*voiceType = 2;
	}

	int garrison = 2;
	bool hasPos = target && !(target->m_pos == *(const Coord3D *)&g_bfmeCoordDefault);
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return;
	bool moving = ai->isMoving() || ai->m_3B1;
	if (!isSiege && TheInGameUI->m_8B0 && moving)
		return;
	if (*pending > 0)
		return;

	if (hasPos)
	{
		Rva004D990E(command, obj, record, &target->m_pos);
		if (!record->isFilled())
		{
			Object *container = obj->rva002931F5(false);
			if (container)
				Rva004D990E(command, container, record, &target->m_pos);
		}
	}

	if (!record->isFilled() && hasPos)
	{
		bool hasMoveCamp = drawable->rva00276805(ids.m_ids[2]);
		bool hasGarrison = drawable->rva00276805(ids.m_ids[1]);
		if (extra)
		{
			hasMoveCamp = hasMoveCamp || extra->rva004D9750(ids.m_ids[2]).isBound();
			hasGarrison = hasGarrison || extra->rva004D9750(ids.m_ids[1]).isBound();
		}
		if ((hasMoveCamp || hasGarrison) && player
			&& countsAsMoveIntoCamp(1 << player->m_playerIndex, (const BfmePointFD *)&obj->m_pos, (const BfmePointFD *)&target->m_pos))
		{
			if (hasGarrison)
			{
				if (garrison == 2)
					garrison = rva004D94FC(obj) ? 1 : 0;
				if (garrison == 1)
					record->rva004D97B0(ids.m_ids[1]);
			}
			if (!record->isFilled())
				record->rva004D97B0(ids.m_ids[2]);
		}
		if (!record->isFilled())
		{
			const DrawableTemplateView *drawableTemplateView = drawable->getTemplate();
			if (drawableTemplateView && drawableTemplateView->getMaxHeight() > 0.0f)
			{
				float heightDiff = target->m_pos.z - drawable->getPosition()->z;
				if (heightDiff > drawableTemplateView->getMaxHeight())
					record->rva004D97B0(ids.m_ids[4]);
			}
		}
	}

	if (!record->isFilled())
	{
		Rva002390CB first = drawable->rva0027675F(ids.m_ids[3]);
		Rva002390CB second;
		if (extra)
			extra->rva004D9750(ids.m_ids[3]);
		if (first.isBound() || second.isBound())
		{
			if (garrison == 2)
				garrison = rva004D94FC(obj) ? 1 : 0;
			if (garrison == 1)
				((Rva004D977D *)record)->rva004D977D(asStruct(first), asStruct(second));
		}
	}

	if (!record->isFilled() && hasPos)
	{
		bool hasClimb = drawable->rva00276805(ids.m_ids[5]);
		if (extra)
			hasClimb = hasClimb || extra->rva004D9750(ids.m_ids[5]).isBound();
		if (hasClimb && moveRequiresClimbingWalls(obj, &target->m_pos))
			record->rva004D97B0(ids.m_ids[5]);
	}

	if (!record->isFilled())
		record->rva004D97B0(ids.m_ids[0]);
}


// 0x004DAAFD pickAndPlayUnitVoiceResponse. Picks the voice the selection
// plays for a command: every selected object (and the contents of selected
// containers) is scored, the best-ranked voice record wins and its sounds are
// played. Returns whether a voice was played.
bool pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type msgType, PickAndPlayInfo *info)
{
	Rva00395561 guard;
	if (!list)
		return false;

	GameMessage::Type type = msgType;
	Object *victim;
	GameMessage::Type enterMessage;
	bool isAttackOrMove;
	getVictimAndEnterMessage(list, type, info, &victim, &enterMessage, &isAttackOrMove);
	bool forced = msgType == 0x46A;

	Rva004DA149Tree voices;
	Rva004D9367Key bestKey;
	bestKey.m0 = 0;
	bestKey.m4 = 0;
	bestKey.m8 = 0x80000000;
	bestKey.mC = 0x7FFFFFFF;
	bestKey.m10 = 0x80000000;

	ObjectIndexTable objects;
	int index = 0;
	for (DrawableList::const_iterator it = list->begin(); it != list->end(); ++it)
	{
		Object *obj = (*it)->getObject();
		++index;
		if (!obj || obj->getTemplate()->isKindOf<0x2F>())
			continue;
		ContainModuleView *contain = (ContainModuleView *)obj->rva0028C197();
		if (contain)
		{
			_STL::list<const Object *, _STL::allocator<const Object *> > items;
			contain->getContainedItems(&items);
			_STL::list<const Object*,_STL::allocator<const Object*> >::iterator itemsEnd = items.end();
			for (_STL::list<const Object*,_STL::allocator<const Object*> >::iterator c = items.begin(); c != itemsEnd; ++c)
			{
				const Object *rider = *c;
				if (rider && !rider->getTemplate()->isKindOf<0x2F>())
					((NameKeyGenerator::KeyToBucketMap *)&objects)->insert(NameKeyGenerator::KeyToBucketMap::value_type(rider, index));
			}
		}
		else if (!isAttackOrMove || !obj->testStatus((ObjectStatusTypes)0x26))
		{
			((NameKeyGenerator::KeyToBucketMap *)&objects)->insert(NameKeyGenerator::KeyToBucketMap::value_type(obj, index));
		}
	}

	ObjectIndexIterator oit = objectsBegin(objects);
	Rva004D9A62 crowds;
	while (oit._M_cur != 0)
	{
		Drawable *drawable = oit._M_cur->m_key->getDrawable();
		++oit;
		if (!drawable || !drawable->m_template)
			continue;
		CrowdResponseTemplate *crowd = drawable->m_template->m_crowdResponse;
		if (!crowd)
			continue;
		CrowdInsertResult result = ((CrowdCountTree *)&crowds)->insert_unique(CrowdPair((unsigned int)crowd, (Image*)0));
		int &weight = *(int *)((char *)result.first._M_node + 0x14);
		weight += crowd->getWeight();
	}

	int *crowdData = 0;
	{
		CrowdResponseTemplate *bestCrowd = 0;
		int best = 0;
		_STL::_Rb_tree_node_base *crowdsEnd = crowds.m_header;
		for (_STL::_Rb_tree_node_base *n = crowdsEnd->_M_left; n != crowdsEnd; n = _STL::_Rb_global<bool>::_M_increment(n))
		{
			if ((int)n[1]._M_parent > best)
			{
				best = (int)n[1]._M_parent;
				bestCrowd = (CrowdResponseTemplate *)n[1]._M_color;
			}
		}
		if (bestCrowd)
			crowdData = bestCrowd->getCrowdResponseDataForThreshold(objects.m_table.m_num_elements);
	}

	PickAndPlayInfo plannedInfo;
	oit = objectsBegin(objects);
	while (oit._M_cur != 0)
	{
		Object *obj = oit._M_cur->m_key;
		int objIndex = oit._M_cur->m_value;
		++oit;
		Drawable *drawable = obj->getDrawable();
		if (drawable) {

		Rva004D95CE record(obj, drawable, crowdData);
		Rva004D9367Key key;
		key.m0 = 0;
		key.m8 = 0x80000000;
		key.mC = objIndex;
		key.m10 = drawable->rva00274D6F();
		key.m4 = (obj->getTemplate()->m_110 >> 26) & 1;
		if (key.m4)
		{
			ExperienceLevelHandle handle = obj->m_experienceTracker->rva0039AC0C();
			if (ExperienceLevelStore::get()->IsValid(handle))
				key.m8 = ExperienceLevelStore::get()->GetLevelRank(handle);
		}

		if (forced)
		{
			const PlannedOrders *planned = (const PlannedOrders *)((Rva0035516C *)TheAiOrdersManager)->rva0035516C(obj->m_id);
			if (!planned)
			{
				Object *horde = obj->rva002931F5(true);
				if (horde)
					planned = (const PlannedOrders *)((Rva0035516C *)TheAiOrdersManager)->rva0035516C(horde->m_id);
			}
			if (!planned)
				continue;
			if (planned->m_list.empty())
				continue;
			if (!planned->m_current)
				continue;
			PlannedOrderReverseIterator rit = planned->m_list.rbegin();
			PlannedOrderReverseIterator rend = planned->m_list.rend();
			bool reachedCurrent = false;
			bool found = false;
			while (rit != rend && !reachedCurrent && !found)
			{
				NameKeyType id = *rit;
				if (id == planned->m_current)
					reachedCurrent = true;
				PlannedCommand *command = (PlannedCommand *)((Rva00355B61 *)TheAiOrdersManager)->rva00355155(id);
				if (!command)
				{
					++rit;
					continue;
				}
				PickAndPlayInfo commandInfo;
				if (command->getPickAndPlayInfo((int *)&type, &commandInfo))
				{
					plannedInfo = commandInfo;
					found = true;
					info = &plannedInfo;
				}
				_STL::list<Drawable *> single;
				single.push_back(drawable);
				getVictimAndEnterMessage(static_cast<const DrawableList *>(&single), type, info, &victim, &enterMessage, &isAttackOrMove);
				++rit;
			}
			if (!found)
			{
				type = (GameMessage::Type)0x7EE;
				continue;
			}
		}

		Rva004D97B0 *rec = record.record();
		switch (type)
		{
		case 0x42D:
		case 0x42E:
		{
			AsciiString voice("VoiceSupply");
			rec->rva004D9874(voice);
			break;
		}
		case 0x423:
			if (info->m_drawTarget)
			{
				Rva0029439DModule *module = (Rva0029439DModule *)obj->rva0029439D();
				if (module)
					rec->setSounds(module->getEnterSound(info->m_drawTarget->getObject()), Rva002390CB());
				if (!rec->isFilled())
					rec->rva004D97B0(0x15);
			}
			break;
		case 0x3E9:
		case 0x3EB:
		case 0x3F8:
		case 0x3F9:
		case 0x3FA:
		case 0x3FB:
		case 0x3FC:
		case 0x3FD:
		case 0x3FE:
		case 0x3FF:
		case 0x400:
		case 0x401:
		case 0x461:
			if (type == 0x3EB)
			{
				AsciiString voice("VoiceSelectIdleWorker");
				rec->rva004D9874(voice);
			}
			if (!rec->isFilled() && rva004D94FC(obj))
				rec->rva004D97B0(2);
			if (!rec->isFilled() && obj->testStatus((ObjectStatusTypes)2))
				rec->rva004D97B0(1);
			if (!rec->isFilled())
				rec->rva004D97B0(0);
			break;
		case 0x41E:
		case 0x41F:
		{
			AsciiString voice("VoiceUnload");
			rec->rva004D9874(voice);
			break;
		}
		case 0x42A:
		{
			AsciiString voice("VoiceRepair");
			rec->rva004D9874(voice);
			break;
		}
		case 0x421:
		case 0x422:
		{
			AsciiString voice("VoiceCombatDrop");
			rec->rva004D9874(voice);
			break;
		}
		case 0x42C:
		{
			Player *player = obj->getControllingPlayer();
			if (player && player->m_750 == 2 && !forced)
			{
				Rva002390CB sound;
				sound.m_ref = TheAudio->getMiscAudio()->m_E0;
				rec->setSounds(sound, Rva002390CB());
				break;
			}
			if (victim) {
			const ThingTemplateView* victimTemplate=victim->getTemplate();
			if (victimTemplate)
			{
				AsciiString voice = "VoiceEnterUnit" + victimTemplate->m_name;
				rec->rva004D9874(voice);
			}
			}
			if (rec->isFilled())
				break;
			if (victim)
			{
				switch (enterMessage)
				{
				case 0xB0:
				{
					AsciiString voice("VoiceEnterHostile");
					rec->rva004D9874(voice);
					break;
				}
				case 0xC1:
				case 0xC2:
					if (enterMessage == 0xC2)
					{
						AsciiString voice("VoiceDeliverRing");
						rec->rva004D9874(voice);
					}
					else
					{
						AsciiString voice("VoiceSendToSlaughterhouse");
						rec->rva004D9874(voice);
					}
					if (!rec->isFilled())
						rec->rva004D97B0(0x11);
					if (!rec->isFilled() && rva004D94FC(obj))
						rec->rva004D97B0(0x14);
					if (!rec->isFilled())
						rec->rva004D97B0(3);
					break;
				case 0xAF:
					if (victim->getTemplate()->isKindOf<0x20>())
					{
						AsciiString voice("VoiceGetHealed");
						rec->rva004D9874(voice);
					}
					else if (victim->getTemplate()->isKindOf<7>())
					{
						AsciiString voice("VoiceGarrison");
						rec->rva004D9874(voice);
					}
					else
					{
						AsciiString voice("VoiceEnter");
						rec->rva004D9874(voice);
					}
					break;
				default:
				{
					AsciiString voice("VoiceEnter");
					rec->rva004D9874(voice);
					break;
				}
				}
			}
			else
			{
				AsciiString voice("VoiceEnter");
				rec->rva004D9874(voice);
			}
			break;
		}
		case 0x430:
		case 0x7E8:
		{
			Object *enemy = TheAI->findClosestEnemy(obj, obj->getVisionRange(), 0x6E, 0, 0, 1);
			if (!enemy && info && !(info->m_pos == *(const Coord3D *)&g_bfmeCoordDefault))
				enemy = (Object *)((Rva002FFFCA *)TheAI)->rva002FFFCA(obj, &info->m_pos, obj->getVisionRange() * 0.5, 0x6E, 0, 0, 1);
			if (enemy)
			{
				PickAndPlayInfo attackInfo;
				if (info)
					attackInfo = *info;
				attackInfo.m_drawTarget = enemy->getDrawable();
				doPickAndPlayForAttackCommand(type, &attackInfo, forced, rec);
			}
			else
			{
				doPickAndPlayForMoveCommand(type, (Rva004DA57ATarget *)info, forced, &bestKey.m0, rec, &key.m0);
			}
			break;
		}
		case 0x428:
		case 0x429:
		case 0x42F:
		case 0x442:
		case 0x464:
		case 0x7E7:
			doPickAndPlayForMoveCommand(type, (Rva004DA57ATarget *)info, forced, &bestKey.m0, rec, &key.m0);
			break;
		case 0x419:
		case 0x41A:
		case 0x42B:
		{
			AsciiString voice("VoiceBuildResponse");
			rec->rva004D9874(voice);
			break;
		}
		case 0x43A:
			if (info && info->m_weaponSlot)
			{
				switch (*info->m_weaponSlot)
				{
				case 0:
				{
					AsciiString voice("VoicePrimaryWeaponMode");
					rec->rva004D9874(voice);
					break;
				}
				case 1:
				{
					AsciiString voice("VoiceSecondaryWeaponMode");
					rec->rva004D9874(voice);
					break;
				}
				case 2:
				{
					AsciiString voice("VoiceTertiaryWeaponMode");
					rec->rva004D9874(voice);
					break;
				}
				}
			}
			break;
		case 0x40E:
		case 0x40F:
		case 0x425:
		case 0x426:
		case 0x427:
		case 0x7E6:
			doPickAndPlayForAttackCommand(type, info, forced, rec);
			break;
		case 0x433:
		case 0x434:
			rec->rva004D97B0(0xD);
			break;
		case 0x410:
		case 0x411:
		case 0x412:
		case 0x456:
			if (info && info->m_specialPowerTemplate)
			{
				SpecialPowerModuleInterface *module = obj->findSpecialPowerModuleInterface(
					((const SpecialPowerTemplateView *)info->m_specialPowerTemplate->friend_getFinalOverride())->m_type);
				if (module)
					rec->setSounds(module->getInitiateSound(), Rva002390CB());
				if (!rec->isFilled())
					rec->rva004D9874(((const SpecialPowerTemplateView *)info->m_specialPowerTemplate->friend_getFinalOverride())->m_initiateVoice);
			}
			break;
		case 0x7EC:
			if (info && info->m_specialPowerTemplate)
				rec->rva004D9874(((const SpecialPowerTemplateView *)info->m_specialPowerTemplate->friend_getFinalOverride())->m_atLocationVoice);
			break;
		case 0x7DA:
		{
			if (info && info->m_source) {
			const ThingTemplateView *thingTemplateView = info->m_source->m_template;
			if (thingTemplateView)
			{
				AsciiString voice("VoiceCreatedFrom");
				voice += thingTemplateView->m_name;
				rec->rva004D9874(voice);
			}
			}
			if (!rec->isFilled())
				rec->rva004D97B0(9);
			break;
		}
		case 0x7DB:
		{
			AsciiString voice("VoiceDesperateAttack");
			rec->rva004D9874(voice);
			break;
		}
		case 0x7DC:
		{
			AsciiString voice("VoiceRapidFire");
			rec->rva004D9874(voice);
			break;
		}
		case 0x7DD:
		{
			AsciiString voice("VoiceCaptureBuildingComplete");
			rec->rva004D9874(voice);
			break;
		}
		case 0x7DE:
			rec->rva004D97B0(0xA);
			break;
		case 0x7DF:
			rec->rva004D97B0(0xB);
			break;
		case 0x7E0:
			rec->rva004D97B0(8);
			break;
		case 0x7E1:
			rec->rva004D97B0(0xE);
			break;
		case 0x7E2:
		{
			if (info && info->m_source) {
			const ThingTemplateView *thingTemplateView = info->m_source->m_template;
			if (thingTemplateView)
			{
				AsciiString voice("VoiceFullyCreatedFrom");
				voice += thingTemplateView->m_name;
				rec->rva004D9874(voice);
			}
			}
			if (!rec->isFilled())
				rec->rva004D97B0(0xF);
			break;
		}
		case 0x7EA:
		{
			AsciiString voice("VoiceStartCharging");
			rec->rva004D9874(voice);
			break;
		}
		case 0x7E9:
		{
			Rva0028C1A9Module *module = (Rva0028C1A9Module *)obj->rva0028C1A9();
			if (!module)
			{
				Object *horde = obj->rva002931F5(false);
				if (!horde)
					break;
				module = (Rva0028C1A9Module *)horde->rva0028C1A9();
				if (!module)
					break;
			}
			rec->setSounds(module->getSound(), Rva002390CB());
			break;
		}
		case 0x7E3:
			if (info && info->m_commandButton)
			{
				if (info->m_commandButton->m_14 == 0x39)
				{
					Player *player = obj->getControllingPlayer();
					if (player && player->m_750 == 2 && !forced)
					{
						Rva002390CB sound;
						sound.m_ref = TheAudio->getMiscAudio()->m_E0;
						rec->setSounds(sound, Rva002390CB());
						break;
					}
				}
				rec->setSounds(info->m_commandButton->rva0035B456(), Rva002390CB());
			}
			break;
		case 0x7E4:
			if (info && info->m_commandButton)
				rec->setSounds(info->m_commandButton->rva0035B495(), Rva002390CB());
			break;
		case 0x7E5:
			if (info && info->m_commandButton)
				rec->setSounds(info->m_commandButton->rva0035B4D4(), Rva002390CB());
			break;
		case 0x7EB:
		{
			AsciiString voice("VoiceNoBuild");
			rec->rva004D9874(voice);
			break;
		}
		}

		if (rec->hasVoice())
		{
			if (Rva004D9367Less(&bestKey, &key))
			{
				((Rva004D9B4B *)&voices)->rva004D9FF2();
				bestKey = key;
			}
			if ((char)Rva004D93E2Equal(&bestKey, &key))
			{
				Rva004D960C entry(*(const Rva0036CA00Str *)&rec->m_04, *(const Rva004D964E *)rec);
				_STL::pair<_STL::_Rb_tree_iterator<Rva004D971D, _STL::_Nonconst_traits<Rva004D971D> >, bool> inserted = ((VoiceSetTree *)&voices)->insert_unique(*(const Rva004D971D *)&entry);
                ++*(int *)((char *)inserted.first._M_node + 0x30);
			}
		}
 }
	}

	if (voices.m_count == 0)
		return false;
	VoiceNode *best = (VoiceNode *)voices.m_header->_M_left;
	for (_STL::_Rb_tree_node_base *n = _STL::_Rb_global<bool>::_M_increment(&best->m_base); n != voices.m_header; n = _STL::_Rb_global<bool>::_M_increment(n))
	{
		if (((VoiceNode *)n)->m_record.m_1C > best->m_record.m_1C)
			best = (VoiceNode *)n;
	}
	if (isAttackOrMove && best->m_record.m_04 != 0 && best->m_record.m_drawable->rva002766AE(&best->m_record.m_04))
		return false;
	// Keep the selected reference in its post-precheck lifetime (WB129636B).
	const int &sound = best->m_record.m_04;
	if (best->m_record.hasVoice())
	{
		bool remember = isAttackOrMove && sound != 0;
		bool flag20 = best->m_record.m_20;
		if (remember || flag20)
		{
			for (oit = objectsBegin(objects); oit._M_cur != 0; ++oit)
			{
				Object *object = oit._M_cur->m_key;
				if (object) {
				Drawable *d = object->getDrawable();
				if (d) {
				if (remember)
					d->rva002766F8(*(const OpaqueRefElement4 *)&sound);
				if (flag20)
					((Rva00271C1C *)d)->rva00271C1C();
 } }
			}
		}
	}
	if (best->m_record.m_00 != -1)
	{
		const Coord3D *pos = 0;
		bool local = false;
		if (best->m_record.getObject())
		{
			if (best->m_record.getObject()->getControllingPlayer() && best->m_record.getObject()->getControllingPlayer()->isLocalPlayer())
				local = true;
			const Object *positionObject=best->m_record.getObject();
			pos=&positionObject->m_pos;
		}
		bool reported = false;
		if (local || isAttackOrMove)
			reported = TheEva->reportEvaEvent((EvaEventID)best->m_record.m_00, pos, 0);
		if (sound == 0)
			return reported;
	}
	BfmeAudioEventPrefix136 first(*(const OpaqueRefElement4 *)&sound, 0);
	BfmeAudioEventPrefix136 second(*(const OpaqueRefElement4 *)&best->m_record.m_0C, 0);
	if (!TheAudio->isValidAudioEvent(&first))
		return false;
	if (best->m_record.getObject())
	{
        const Object *firstObject=best->m_record.getObject();
		((Rva002D9531 *)&first)->rva002D9531(firstObject->m_id);
        const Object *secondObject=best->m_record.getObject();
		((Rva002D9531 *)&second)->rva002D9531(secondObject->m_id);
	}
	TheAudio->addAudioEvent(&first);
	TheAudio->addAudioEvent(&second);
	return true;
}
