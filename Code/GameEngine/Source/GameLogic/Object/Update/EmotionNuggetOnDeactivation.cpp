// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// EmotionNugget::OnDeactivation @ 0x004DD2C0 (457B). Identity: WorldBuilder
// EmotionNugget.cpp OnDeactivation (WB 0x010EAAC0, callgraph lead).
// Model condition 200 is cleared through Object's ModelConditionFlags words at
// +0x10C (WB inlines BitFlags::test/ClearBit; retail tests byte +0x125 bit 0).
// The attribute gate reads TheGameLogic->getFrame() and the entry delay
// through inline getters, as the WB body does (frame read first).
// Deactivation: folds entry delays into local frames through TheGameLogic,
// plays entry FX, nudges AI, applies weapon-set/condition changes and applies
// the entry attribute modifier by name. Evidence: callers at 0x004B0E12,
// 0x004B0EB2, 0x004B15F2, 0x004B1689 pass [EmotionTrackerUpdate+0x7c] as this;
// callees rowed map<int,int>::operator[] 0x0028932C, map<ushort,int> 0x004DD277,
// Object::rva0029439D, GameLogic::findObjectByID 0x00049DC5,
// FXList::doFXObj 0x000B2235, AIUpdateInterface::rva002632E1,
// Object::clearAndSetModelConditionFlagsForHorde/0x0028CFB2/0x0028AE6D, AsciiField::get 0x004DC8E7,
// StringBase::isEmpty 0x00001E2F/releaseBuffer 0x00036410,
// Object::addAttributeModifierToPool (pin); TheGameLogic 0x009FE78C.

#include <map>
#include "ascii_string.h"
template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}


struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};

class Object;
class FXList;
class AIUpdateInterface;

#include "../../../Common/GameLogicObjectLookupView.h"
// Suppress this TU's non-retail copy of ?_M_lower_bound@?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@UGe:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen_lt_00940b40;
namespace _STL { template <> _Rb_tree_node<pair<unsigned short const ,int> > * _Rb_tree<unsigned short,pair<unsigned short const ,int>,_Select1st<pair<unsigned short const ,int> >,Gen_lt_00940b40,allocator<pair<unsigned short const ,int> > >::_M_lower_bound(unsigned short const &) const; }
// Suppress this TU's non-retail copy of ??R?$less@G@_STL@@QBE_NABG0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<unsigned short>::operator()(unsigned short const &,unsigned short const &) const; }
// Suppress this TU's non-retail copy of ??A?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAEAAHABH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int & map<int,int,less<int>,allocator<pair<int const ,int> > >::operator[](int const &); }
// Suppress this TU's non-retail copy of ??0?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > >,bool>::pair(_Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > > const &,bool const &); }
// Suppress this TU's non-retail copy of ??E?$_Rb_tree_iterator@U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_STL@@@2@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > > & _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > >::operator++(); }
// Suppress this TU's non-retail copy of ??F?$_Rb_tree_iterator@U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_STL@@@2@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > > & _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > >::operator--(); }
// Suppress this TU's non-retail copy of ??0?$pair@$$CBGH@_STL@@QAE@ABGABH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> pair<unsigned short const ,int>::pair(unsigned short const &,int const &); }
// Suppress this TU's non-retail copy of ??R?$less@H@_STL@@QBE_NABH0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<int>::operator()(int const &,int const &) const; }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@UGen:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen_lt_00940b40;
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned short const ,int>,_Nonconst_traits<pair<unsigned short const ,int> > >,bool> _Rb_tree<unsigned short,pair<unsigned short const ,int>,_Select1st<pair<unsigned short const ,int> >,Gen_lt_00940b40,allocator<pair<unsigned short const ,int> > >::insert_unique(pair<unsigned short const ,int> const &); }
// Suppress this TU's copies of template members whose kept copy (first in link
// order) is another unit's. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_node<pair<unsigned short const,int> > * _Rb_tree<unsigned short,pair<unsigned short const,int>,_Select1st<pair<unsigned short const,int> >,Gen_lt_00940b40,allocator<pair<unsigned short const,int> > >::_M_create_node(pair<unsigned short const,int> const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<unsigned short const,int>,_Nonconst_traits<pair<unsigned short const,int> > > _Rb_tree<unsigned short,pair<unsigned short const,int>,_Select1st<pair<unsigned short const,int> >,Gen_lt_00940b40,allocator<pair<unsigned short const,int> > >::_M_insert(_Rb_tree_node_base *,_Rb_tree_node_base *,pair<unsigned short const,int> const &,_Rb_tree_node_base *); }
namespace _STL { template <> _Rb_tree_node<pair<unsigned short const,int> > * allocator<_Rb_tree_node<pair<unsigned short const,int> > >::allocate(unsigned int,void const *)const ; }
namespace _STL { template <> _Rb_tree_iterator<pair<unsigned short const,int>,_Nonconst_traits<pair<unsigned short const,int> > > _Rb_tree<unsigned short,pair<unsigned short const,int>,_Select1st<pair<unsigned short const,int> >,Gen_lt_00940b40,allocator<pair<unsigned short const,int> > >::insert_unique(_Rb_tree_iterator<pair<unsigned short const,int>,_Nonconst_traits<pair<unsigned short const,int> > >,pair<unsigned short const,int> const &); }

extern GameLogic *TheGameLogic;

class FXList
{
public:
	static void doFXObj(const FXList *, const Object *, const Object *);
	void doFXObj(const Object *primary, const Object *secondary) const;
};

class EmotionNugget;
class Object;
class AIUpdateInterface {
    friend class EmotionNugget;
protected:
    virtual void SetEmotionState(int, Object *);
public:
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual bool v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual bool v110();
    int getCurrentStateID() const;
    void rva00263298();
    void rva002632E1();
    char pad04[0x3c5-4]; unsigned char allow04;
};

class Rva0029439DIface {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual Object *v19();
};

struct ModelConditionFlags {
 unsigned int words[19];
 // Returns the masked word (WB's BitFlags::test compares it with zero).
 unsigned int test(size_t bit) const { return words[bit/32] & (1UL << (bit%32)); }
 void set(int bit) { words[bit>>5] |= 1U << (bit & 0x1f); }
 void clear(int bit) { words[bit >> 5] &= ~(1 << (bit & 0x1f)); }
};

class ThingTemplate;
enum ObjectStatusTypes { STATUS_46 = 0x46 };
class Object {
public:
    void *rva0029439D();
    void clearAndSetModelConditionFlagsForHorde(const int *, const int *);
    void rva0028CFB2(const int *, const int *);
    void rva0028AE6D();
    bool isSignificantlyAboveTerrain() const;
    ObjectID getID() const { return id; }
    const ThingTemplate *getTemplate() const { return thingTemplate; }
    bool addAttributeModifierToPool(const AsciiString &name, int strength);
    AIUpdateInterface *getAI() const { return ai; }
    bool testStatus438() const { return (m_status438 & 1) != 0; }
    bool testStatus(ObjectStatusTypes status) const;
    bool rva0028AFBB() const;
    void *rva0028C197() const;
    bool rva0028C149(int attribute, float *value, int arg);
    char pad00[4]; ThingTemplate *thingTemplate;
    char pad08[0x74-8]; ObjectID id;
    char pad78[0x10c-0x78]; ModelConditionFlags modelConditions;
    char pad158[0x258-0x158]; AIUpdateInterface *ai; // +0x258
    char pad25C[0x438 - 0x25C];
    unsigned char m_status438; // +0x438
};

class Rva004DC8E7AsciiField
{
public:
	AsciiString get() const;
	int getDelay() const { return m_40; }
	char m_pad00[0x10];
	int m_10; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
	char m_pad1C[0x1C];
	const FXList *m_fx38; // +0x38
	AsciiString m_str3C; // +0x3C
	int m_40; // +0x40
	unsigned char m_flag44; // +0x44
	char m_pad45[0x3];
	int m_48; // +0x48
	int m_4C; // +0x4C
	char m_pad50[0x50];
	int m_a0; // +0xA0
	char m_padA4[0x94];
	int m_138; // +0x138
	char m_pad13C[0x48];
	unsigned char m_184; // +0x184
	char m_pad185[0x3];
};

class Rva004DC902AsciiField {
public:
    AsciiString get() const;
    char pad00[0xc]; unsigned duration0c;
    int m_10, m_14, m_18;
    char pad1C[0x30-0x1C]; const FXList *fx30;
    char pad34[4]; const FXList *m_fx38;
    AsciiString m_str3C; int m_40;
    unsigned char m_flag44; char pad45[3]; int m_48; int state4c;
    char pad50[4]; int set54[19], clearA0[19], clearec[19], set138[19];
    unsigned char flag184; char pad185[3]; AsciiString event188;
};

class EmotionNugget {
public:
    void OnActivation(Object *, int);
    void OnDeactivation();
    Rva004DC902AsciiField *getTemplate() const { return entry04; }
    Object *object00; Rva004DC902AsciiField *entry04; int id08;
    unsigned short template0c; char pad0e[2]; unsigned next10;
    _STL::map<int, int> targets14;
    _STL::map<unsigned short, int, Gen_lt_00940b40> templates20;
    unsigned until2c, activated30;
};

void EmotionNugget::OnDeactivation()
{
	if (entry04->m_10)
		next10 = TheGameLogic->getFrame() + entry04->m_10;
	if (entry04->m_14 && id08)
	{
		unsigned frame = TheGameLogic->getFrame();
		int duration = entry04->m_14;
		targets14[id08] = frame + duration;
	}
	if (entry04->m_18 && template0c)
	{
		unsigned int frame = TheGameLogic->getFrame();
		int duration = entry04->m_18;
		templates20[template0c] = duration + frame;
	}
	if (entry04->m_fx38)
	{
		Object *obj = object00;
		void *iface = obj->rva0029439D();
		if (iface)
			obj = ((Rva0029439DIface *)iface)->v19();
		int id = id08;
		Object *found = TheGameLogic->findObjectByID((ObjectID)id);
		if (found || !id)
		{
			if (!obj)
				obj = object00;
			FXList::doFXObj((object00 ? (entry04->m_fx38) : (entry04->m_fx38)), obj, found);
		}
	}
	AIUpdateInterface *ai = object00->ai;
	if (ai)
	{
		int kind = entry04->state4c;
		if (!kind || (kind > 1 && kind <= 5))
		{
			ai->rva002632E1();
			if (entry04->flag184)
				ai->allow04 = 0;
		}
	{
		void *iface = object00->rva0029439D();
		if (iface)
			object00->clearAndSetModelConditionFlagsForHorde(entry04->clearA0, entry04->set138);
		else
			object00->rva0028CFB2(entry04->clearA0, entry04->set138);
		Object *object = object00;
		if (object->modelConditions.test(200))
		{
			object->modelConditions.clear(200);
			object->rva0028AE6D();
		}
	}
	if (!((const StringBase<char> &)(((Rva004DC8E7AsciiField *)entry04)->get())).isEmpty() && TheGameLogic->getFrame() >= activated30 + ((Rva004DC8E7AsciiField *)entry04)->getDelay() && entry04->m_flag44)
	{
		object00->addAttributeModifierToPool(((Rva004DC8E7AsciiField *)entry04)->get(), entry04->m_48);
	}
	}
}
