// ?rva004D6DF3@Rva004D6C9C@@QAEXPAVObject@@_N@Z
// partial score=0.975 date=2026-10-10
// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// ?rva004D6C9C@Rva004D6C9C@@QAEXW4ScienceType@@@Z @0x004D6C9C (16B):
// Frameless vector<ScienceType>::push_back wrapper, member at +0x04.
// ScienceType is the existing folded provider spelling, not a claim that
// object IDs collected below are science IDs. Retail +0x74 is the object ID.
// Retail lea eax,[esp+4]; push eax; add ecx,4; call push_back @0x002E01C6;
// ret 4. Single caller 0x002ACCA3 loops a ScienceType vector and pushes each
// element into the +0x730 object. Honest-address name: owner unproven.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

#include <vector>
#include <list>

class Team;
class Object;
template<class OBJCLASS> class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_state[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Object
{
public:
	char m_pad00[0x74];
	unsigned m_id74;
 char unknown78[0x250-0x78];
 class Rva004D6DF3Container *container;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class Rva004D6C9C
{
public:
	void rva004D6C9C(ScienceType science);
	void rva004D6D95(Team *team, bool clearAll);
 void rva004D6DF3(Object *object, bool clearAll);

private:
	char m_pad04[4];
	_STL::vector<ScienceType> m_vec;
};

void Rva004D6C9C::rva004D6C9C(ScienceType science)
{
	m_vec.push_back(science);
}

// ?rva004D6D95@Rva004D6C9C@@QAEXPAVTeam@@_N@Z @0x004D6D95 94B
// Evidence: vector<ScienceType> at +4 same as rva004D6C9C; erase range plus team iteration plus push_back of Object+0x74.
// Caller at 0x00350459.
void Rva004D6C9C::rva004D6D95(Team *team, bool clearAll)
{
	if (!team)
		return;
	if (clearAll) {
		_STL::vector<ScienceType> *vec = &m_vec;
		vec->erase(vec->begin(), vec->end());
	}
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	while (!iter.done()) {
		Object *object = iter.cur();
		ScienceType science = (ScienceType)object->m_id74;
		m_vec.push_back(science);
		iter.advance();
	}
}

class Rva004D6DF3Contents {
public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
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
 virtual void getItems(_STL::list<const Object *> *items);
};
class Rva004D6DF3Container {
public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
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
 virtual Rva004D6DF3Contents *getContents();
};
void Rva004D6C9C::rva004D6DF3(Object *object, bool clearAll)
{
 if (!object) return;
 if (clearAll) { _STL::vector<ScienceType> *vec = &m_vec; vec->erase(vec->begin(), vec->end()); }
 Rva004D6DF3Container *container = object->container;
 if (!container) return;
 Rva004D6DF3Contents *contents = container->getContents();
 if (!contents) return;
 _STL::list<const Object *> objects;
 contents->getItems(&objects);
 for (_STL::list<const Object *>::const_iterator i=objects.begin(); i!=objects.end(); ++i) {
  const Object *item = *i;
  if (item) { ScienceType value = (ScienceType)item->m_id74; m_vec.push_back(value); }
 }
}
