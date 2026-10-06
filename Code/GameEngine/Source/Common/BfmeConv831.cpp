// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class BfmeMgrF07
{
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
	virtual void* vfn26(void *key);
	int findSomething(void *key, int zero);
};
// 0x012F076C is retail's ScriptEngine singleton (defined once in
// GameLogic/ScriptEngine/ScriptEngine.cpp). This TU only needs its vtable
// slice, so it reaches it by casting at each use; DIR32 relocations are
// masked by the byte gate, so the emitted bytes are unchanged.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static inline BfmeMgrF07 *mgr12F076C() { return (BfmeMgrF07 *)TheScriptEngine; }

class BfmeLinkedObj
{
public:
	void link(BfmeLinkedObj *other, int zero);
};

class BfmeLinkedObjBE
{
public:
	void notifyOther(BfmeLinkedObjBE *other, void *p3);
};

struct BfmeObjAF0_2
{
	unsigned char pad[0x230];
	void *m_sub230;
};

class BfmeMgrD74_Linked
{
public:
	BfmeLinkedObj* findObj(int id);
	BfmeLinkedObjBE* findObjBE(int id);
	BfmeObjAF0_2* findObjAF(int id);
};
// 0x012ED748 is retail's PlayerList singleton (game/GameEngine/Source/Common/RTS/PlayerList.cpp
// defines `PlayerList *ThePlayerList`); only the address-derived lookups this TU
// spells are still unnamed, so the global keeps its real spelling and the reads are cast.
class PlayerList;

extern PlayerList *ThePlayerList;	// retail [0x012ED748]

void __stdcall bfmeLinkObjectsA70(void *k1, void *k2)
{
	int id2 = mgr12F076C()->findSomething(k2, 0);
	int id1 = mgr12F076C()->findSomething(k1, 0);
	BfmeLinkedObj *obj2 = ((BfmeMgrD74_Linked *)ThePlayerList)->findObj(id2);
	BfmeLinkedObj *obj1 = ((BfmeMgrD74_Linked *)ThePlayerList)->findObj(id1);
	if (obj2 && obj1) {
		obj2->link(obj1, 0);
	}
}
