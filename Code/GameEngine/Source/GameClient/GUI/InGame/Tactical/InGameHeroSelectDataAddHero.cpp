// stlport
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Native 0x00525CC5..0x00525D9A: add the imaged object to the hero list at +0x10,
// suppressing duplicate object IDs. Frames < 6 insert by template rank (+0x638);
// subsequent frames append. Notify slot zero with the new iterator by value.
// Target evidence: dispatcher 0x00526309 and remove counterpart 0x005259B9
// establish the holder prefix, Object template +4 and ID +0x74. The three-word
// record and insert/push_back calls use the existing BfmePod12 STL footprint.
// WorldBuilder 0x013BD680 supplies the source-shape lead privateOnHeroAdded;
// the retail name and complete class layouts remain unreconstructed.
#include <list>
#include <hash_map>


// Inline the hash-map accessors without emitting conflicting /O1 COMDATs.
namespace _STL {
template <> __declspec(dllimport) __forceinline void *const *vector<void*>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline size_t vector<void*>::size() const { return size_t(this->_M_finish-this->_M_start); }
template <> __declspec(dllimport) __forceinline void *const &vector<void*>::operator[](size_t n) const { return *(begin()+n); }
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class Object;class ThingTemplate;class Image;
#include "../../../../Common/GameLogicObjectLookupView.h"
const Image *getButtonImage(ThingTemplate *,Object *);
int ComputeObjectRank(const Object *);
class ThingTemplate {public:char pad[0x638];int rank638;};
class Object {public:void *vptr;ThingTemplate *templ;char pad08[0x74-8];int id; ThingTemplate*getTemplate()const{return templ;} };
extern GameLogic *TheGameLogic;
struct BfmePod12 {int id,unknown,flash;};
struct HeroButtonInfo {int id,unknown,flash;};
typedef _STL::list<BfmePod12> HeroInfoList;
namespace _STL { template<> HeroInfoList::iterator list<BfmePod12>::insert(HeroInfoList::iterator,const BfmePod12 &); template<> void list<BfmePod12>::push_back(const BfmePod12 &); }
class Rva005259B9Listener {public:virtual void addHero(void *);};
typedef void(Rva005259B9Listener::*HeroNotify)(void *);
class Holder00525D9A {
public:
 template<class T,class Traits> __declspec(noinline) void Rva005258F8(int,_STL::_List_iterator<T,Traits>);
private:void *begin,*end,*capacity;unsigned int index;
};
struct Obj00526309;
class Holder00526309 : public Holder00525D9A {
public:
 __declspec(noinline) void Rva00525CC5(Obj00526309 *);
 HeroInfoList heroes;char builders[12];
};

void Holder00526309::Rva00525CC5(Obj00526309 *heroObject)
{
	Object *obj = reinterpret_cast<Object *>(heroObject);
	ThingTemplate *templ = obj->templ;
	if (!getButtonImage(templ, obj))
		return;
	for (HeroInfoList::iterator it = heroes.begin(); it != heroes.end(); ++it)
	{
		if (it->id == obj->id)
			return;
	}
	int id = obj->id;
	HeroButtonInfo record;
	int objectRank = ComputeObjectRank(obj);
	record.flash = 0;
	record.id = id;
	GameLogic *logic = TheGameLogic;
	if (logic->getFrame() < 6)
	{
		record.unknown = objectRank;
		templ = obj->templ;
		// This home and the visible lookup body retain retail's register allocation.
		volatile int rank = templ->rank638;
		HeroInfoList::iterator it = heroes.begin();
		bool found = false;
		while (!found && it != heroes.end())
		{
			Object *other = TheGameLogic->findObjectByID((ObjectID)it->id);
			if (other && rank < other->getTemplate()->rank638)
				found = true;
			else
				++it;
		}
		union { HeroNotify method; int fn; } binding;
		binding.method = &Rva005259B9Listener::addHero;
		Rva005258F8(binding.fn, heroes.insert(it, reinterpret_cast<const BfmePod12 &>(record)));
	}
	else
	{
		record.unknown = objectRank;
		heroes.push_back(reinterpret_cast<const BfmePod12 &>(record));
		union { HeroNotify method; int fn; } binding;
		binding.method = &Rva005259B9Listener::addHero;
		Rva005258F8(binding.fn, --heroes.end());
	}
}


typedef _STL::hash_map<ObjectID,Object*,_STL::hash<int>,_STL::equal_to<ObjectID> > ObjectPtrHash;
inline Object *GameLogic::findObjectByID(ObjectID id) {
 if(id==INVALID_OBJECT_ID)return 0;
 ObjectPtrHash &hash=*reinterpret_cast<ObjectPtrHash*>(&m_map);
 ObjectPtrHash::iterator it=hash.find(id);
 if(it==hash.end())return 0;
 return (*it).second;
}
