// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?CanBeActivatedFor@EmotionNugget@@QAE_NHHPAURva004DD018Arg@@@Z @ 0x004DD018 (494B, RET 0xC).
// Method identity: WorldBuilder EmotionNugget.cpp assertion/callgraph lead; member offsets, vtable
// slots, frame comparisons and call targets are retail evidence; entry getter names stay unresolved.
// The two per-target expiry maps are real STLport maps; their erase(iterator) calls go to the
// ICF-folded POD tree erase 0x005530A8 (this unit emits the ushort-key instantiation out of line).
// Chain from just-landed Object::rva0028C149: Emotion predicate over entry
// delays, map expiry, attribute 4/5 via the pool and AI state 0x2D.
// Evidence: same Emotion/Entry/maps family as banked 0x004DD2C0;
// callees rowed testStatus 0x0004E536, rva0028AFBB, map find/erase,
// rva0028C197, rva0028C149, getCurrentStateID 0x00262FC3,
// TheGameLogic 0x009FE78C, g_Va007C26F0; callers at 0x004B10E3, 0x004B14B0,
// 0x004B1572, 0x004B1ABE, 0x004B1B69 pass (int,int,ptr) with ret 0xC.
#include <functional>
// This /O1 unit inlines these compares; imported, it emits no non-retail copies of them.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<int>::operator()(const int &x, const int &y) const { return x < y; }
template <> __declspec(dllimport) __forceinline bool less<unsigned short>::operator()(const unsigned short &x, const unsigned short &y) const { return x < y; }
}
#include <map>
// Compare tree nodes locally so this TU does not emit an iterator-base operator!= copy.
namespace _STL {
template <class V, class Traits>
static inline bool operator!=(const _Rb_tree_iterator<V, Traits> &a, const _Rb_tree_iterator<V, Traits> &b)
{ return a._M_node != b._M_node; }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const unsigned short, int>, _Nonconst_traits<pair<const unsigned short, int> > >::_Rb_tree_iterator(
	const _Rb_tree_iterator<pair<const unsigned short, int>, _Nonconst_traits<pair<const unsigned short, int> > > &x)
	{ _M_node = x._M_node; }
}
#include "ascii_string.h"
enum ObjectStatusTypes

{
 STATUS_46 = 0x46
 
}
;
class Object;
class AttributeModifierPoolUpdate;
class AIUpdateInterface;
class Player;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "../../../../Include/GameLogic/Module/AttributeModifierPoolUpdate.h"
class AIUpdateInterface

{
 public:
 virtual void v00();
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
 
}
;
class Rva0028C197Provider

{
 public:
 virtual void v00();
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
 virtual Object *v68();
 
}
;
#include "../object.h"
struct Rva004DD018Inner

{
 char m_pad00[0x5D8];
 unsigned short m_5D8;
 
}
;
struct Rva004DD018Arg

{
 char m_pad00[0x04];
 Rva004DD018Inner *m_04;
 char m_pad08[0x74 - 0x08];
 int m_id;
 
}
;
class EmotionEntry

{
 public:
 char m_pad00[0x04];
 int m_04;
 unsigned char m_08;
 unsigned char m_09;
 char m_pad0A[0x10 - 0x0A];
 int m_10;
 int m_14;
 int m_18;
 int m_1C;
 int m_20;
 int m_24;
 int m_28;
 unsigned char m_2C;
 unsigned char m_2D;
 char m_pad2E[0x38 - 0x2E];
 const void *m_fx38;
 AsciiString m_str3C;
 int m_40;
 unsigned char m_flag44;
 char m_pad45[3];
 int m_48;
 int m_4C;
 
}
;
class EmotionNugget

{
 public:
 bool CanBeActivatedFor(int a, int b, Rva004DD018Arg *arg);
 private:
 Object *m_object;
 EmotionEntry *m_entry;
 int m_id08;
 unsigned short m_key0C;
 char m_pad0E[2];
 unsigned int m_frame10;
 _STL::map<int, unsigned int> m_map14x;
 _STL::map<unsigned short, int, _STL::less<unsigned short> > m_map20x;
 int m_2C;
 int m_start30;
 
}
;
bool EmotionNugget::CanBeActivatedFor(int a, int b, Rva004DD018Arg *arg)
{
	Object *obj = m_object;
	if (obj->testStatus(STATUS_46))
		return false;
	if (m_entry->m_08 || m_entry->m_09) {
		AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)obj + 0x258);
		if (!ai)
			return false;
		if (ai->v110() && !ai->v91()) {
			if (m_entry->m_08)
				return false;
		} else if (m_entry->m_09)
			return false;
	}
	if (m_entry->m_2C || m_entry->m_2D) {
		if (m_object->rva0028AFBB()) {
			if (m_entry->m_2D)
				return false;
		} else if (m_entry->m_2C)
			return false;
	}
	EmotionEntry *entry = m_entry;
	if (entry->m_1C * a + entry->m_20 >= 0)
		return false;
	if (entry->m_24 * b + entry->m_28 >= 0)
		return false;
	unsigned int frame = TheGameLogic->getFrame();
	if (frame < m_frame10)
		return false;
	if (arg) {
		int id = arg->m_id;
		_STL::map<int, unsigned int>::iterator it = m_map14x.find(id);
		if (it != m_map14x.end()) {
			if (frame < (unsigned int)it->second)
				return false;
			m_map14x.erase(it);
		}
		unsigned short kind = arg->m_04->m_5D8;
		_STL::map<unsigned short, int, _STL::less<unsigned short> >::iterator it2 = m_map20x.find(kind);
		if (it2 != m_map20x.end()) {
			if (TheGameLogic->getFrame() < (unsigned int)it2->second)
				return false;
			m_map20x.erase(it2);
		}
	}
	if (m_entry->m_04 >= 4 && m_entry->m_04 <= 7) {
		int attrKind = 4 + (m_entry->m_04 == 6 ? 1 : 0);
		bool use = true;
		float value = 0.0f;
		Object *target = m_object;
		if (target) {
			void *tpl = *(void **)((char *)target + 4);
			if (*(unsigned char *)((char *)tpl + 0x115) & 0x20)
				target = ((Rva0028C197Provider *)target->rva0028C197())->v68();
			if (target) {
				if (target->rva0028C149(attrKind, &value, 0)) {
					if (0.5f > value)
						use = true;
					else
						use = false;
				}
				AIUpdateInterface *aai = *(AIUpdateInterface **)((char *)target + 0x258);
				if (aai) {
					if (aai->getCurrentStateID() == 0x2D)
						use = false;
				}
				if (!use)
					return false;
			}
		}
	}
	return true;
}

