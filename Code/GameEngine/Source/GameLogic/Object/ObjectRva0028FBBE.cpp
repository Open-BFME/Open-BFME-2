// cl: /O1 /DNDEBUG /MD /GX-
// ?rva0028FBBE@Object@@QAEHXZ, retail 0x0028FBBE, 90 bytes.
// Object contain-sum: template byte at +0x5F1 via +4, contain module at
// +0x250 checked through slot5 then slot70 fill of 8B temp, walk of
// sentinel list (next at +0, object at +8) summing recursive self.
// Evidence: thiscall int return, virtuals 0x14/0x118, offsets 0x250/0x5F1.

struct ThingTemplate
{
	char m_pad[0x5F1];
	signed char m_5F1;
};

struct Tmp;
struct Node;
struct List
{
	Node *head;
};
struct Tmp
{
	int _a;
	List *list;
};
struct Node
{
	Node *next;
	int _pad;
	class Object *obj;
};

class ContainModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual bool v05(); virtual void v06(); virtual void v07();
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
	virtual void v68(); virtual void v69(); virtual void v70(Tmp *tmp);
};

class Object
{
public:
	int rva0028FBBE();
private:
	void *m_vptr;
	ThingTemplate *m_template;
	char m_pad08[0x250 - 8];
	ContainModule *m_contain;
};

int Object::rva0028FBBE()
{
	ThingTemplate *tmpl = m_template;
	ContainModule *contain = m_contain;
	int v = tmpl->m_5F1;
	if (contain == 0)
		return v;
	if (!contain->v05())
		return v;
	int total = 0;
	Tmp tmp;
	contain->v70(&tmp);
	Node *cur = tmp.list->head->next;
	while (cur != tmp.list->head) {
		total += cur->obj->rva0028FBBE();
		cur = cur->next;
	}
	return total;
}
