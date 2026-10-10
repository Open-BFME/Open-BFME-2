// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?getRappellerCount@@YAHPAVObject@@@Z  Native 0x0053BC7E..0x0053BCC4 (70 bytes)
// ControlBar getRappellerCount: counts the contained objects whose template is
// KindOf 43 (bit 3 of the template byte 0x10D). The contain module sits at
// Object +0x250 and its vtable slot 70 (0x118) returns the contained-items
// list handle by hidden pointer (an unused word then the list pointer).
// Evidence: ZH ControlBarCommand.cpp getRappellerCount (same loop over
// ContainedItemsList) and the WB twin 0x111BE20 (contain +0x258 slot 69 then
// Thing::getTemplate and BitFlags test 0x2B). The only retail caller is
// ControlBar::getCommandAvailability 0x0053BD66 which passes the object in EAX
// (a private convention of this static helper); the dummy caller below
// carries the absent-from-retail marker and only gives cl a call site.

typedef int Int;

class ThingTemplate {
public:
	bool isKindOf43() const { return (m_kindOf[5] & 8) != 0; }
	char m_pad000[0x108];
	unsigned char m_kindOf[32];
};

struct ContainedNode {
	ContainedNode *m_next;
	ContainedNode *m_prev;
	class Object *m_data;
};
struct ContainedList {
	ContainedNode *m_node;
};
struct ContainedItems {
	ContainedItems();
	void *m_unused;
	const ContainedList *m_list;
};

class ContainModule {
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
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69();
	virtual ContainedItems getContainedItemsList() const;
};

class Object {
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ContainModule *getContain() const { return m_contain; }
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x250 - 8];
	ContainModule *m_contain;
};

static Int getRappellerCount(Object *obj)
{
	ContainModule *contain = obj->getContain();
	if (contain == 0)
		return 0;
	Int num = 0;
	ContainedItems items = contain->getContainedItemsList();
	ContainedNode *end = items.m_list->m_node;
	for (ContainedNode *it = end->m_next; it != end; it = it->m_next)
	{
		if (it->m_data->getTemplate()->isKindOf43())
			++num;
	}
	return num;
}

// ?getRappellerCountCaller absent-from-retail
Int getRappellerCountCaller(Object *const *objects, Int count)
{
	Int total = 0;
	for (Int i = 0; i < count; ++i)
	{
		if (getRappellerCount(objects[i]) > 0)
			++total;
	}
	return total;
}
