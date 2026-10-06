// cl: /DNDEBUG /MD
// ?rva00475EA2@Rva00475EA2@@QAEXXZ retail 0x00475EA2 136B
// Chain on just-landed 0x00298E6A: -0xFC slot-70 fill plus list chase calling it then +0x54 RB map via TheGameLogic findObjectByID calling it plus -0x114 pool EraseRange clear.
// Evidence: callees rowed 0x00298E6A 0x00049DC5 0x00024250 0x0028BDD7 0x002983DA; TheGameLogic extern in use 72 TUs; prev HordeContainModuleDataParse next HorseHordeContainCtor.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
class Object;
class Rva00298E6A
{
public:
	void rva00298E6A();
};
class Rva00297360Element
{
};
class Rva002983DAVector
{
public:
	Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);
	Rva00297360Element *m_first;
	Rva00297360Element *m_last;
};
class AttributeModifierPoolUpdate
{
public:
	char m_pad[0x20];
	Rva002983DAVector m_vec;
};
class Object
{
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	friend class Rva00475EA2;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
namespace _STL
{
	struct _Rb_tree_node_base
	{
		bool _M_color;
		_Rb_tree_node_base *_M_parent;
		_Rb_tree_node_base *_M_left;
		_Rb_tree_node_base *_M_right;
	};
	template <class D> class _Rb_global
	{
	public:
		static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
	};
}
struct TreeNode : public _STL::_Rb_tree_node_base
{
	ObjectID m_id;
};
struct TreeHeader
{
	char m_pad[8];
	TreeNode *m_begin;
};
struct ListNode
{
	ListNode *m_next;
	ListNode *m_prev;
	Rva00298E6A *m_val;
};
class IfaceFC
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
	virtual void v70(void *out);
};
class Rva00475EA2
{
public:
	void rva00475EA2();
	char m_pad[0x54];
	TreeHeader *m_54;
};
void Rva00475EA2::rva00475EA2()
{
	void *tmp[2];
	((IfaceFC *)((char *)this - 0xFC))->v70(tmp);
	ListNode *cur = *(ListNode **)*(ListNode **)tmp[1];
	if (cur != *(ListNode **)tmp[1]) {
		do {
			cur->m_val->rva00298E6A();
			cur = cur->m_next;
		} while (cur != *(ListNode **)tmp[1]);
	}
	TreeNode *bn = m_54->m_begin;
	if ((void *)bn != (void *)m_54) {
		do {
			ObjectID oid = bn->m_id;
			Object *obj = TheGameLogic->findObjectByID(oid);
			if (obj)
				((Rva00298E6A *)obj)->rva00298E6A();
			bn = (TreeNode *)_STL::_Rb_global<bool>::_M_increment(bn);
		} while ((void *)bn != (void *)m_54);
	}
	Object *o = *(Object **)((char *)this - 0x114);
	AttributeModifierPoolUpdate *pool = o->findAttributeModifierPoolUpdate();
	if (pool) {
		Rva002983DAVector *vec = &pool->m_vec;
		vec->EraseRange(vec->m_first, vec->m_last);
	}
}
