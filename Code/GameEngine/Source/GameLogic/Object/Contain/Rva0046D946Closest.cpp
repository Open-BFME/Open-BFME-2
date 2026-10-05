// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0046D946@Rva0046D946@@QAEPAVObject@@PAV2@@Z @ 0x0046D946 293B
// Closest-excluding-self over HordeContain members: virtual slot 70 at +0x20
// fills a list tmp chased via ListNode, then map at +0x170 via _M_increment
// with TheGameLogic findObjectByID; 2D dist vs global g_00BC6EA0.
// Evidence: TheGameLogic extern in use; rowed findObjectByID 0x00049DC5 and
// _M_increment 0x00024250; offsets +0x20/+0x38/+0x170 match HordeContain.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
class Object
{
public:
	char m_pad00[0x38];
	float m_x38;
	float m_y3C;
	float m_z40;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
extern float g_00BC6EA0;
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
	Object *m_val;
};
class Iface20
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
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Rva0046D946
{
public:
	Object *rva0046D946(Object *arg);
	char m_pad00[0x20];
	Iface20 m_20;
	char m_padAfter20[0x170 - 0x20 - 4];
	TreeHeader *m_170;
};
Object *Rva0046D946::rva0046D946(Object *arg)
{
	if (arg == 0)
		return 0;
	float best = g_00BC6EA0;
	Object *bestObj = 0;
	void *tmp[2];
	m_20.v70(tmp);
	ListNode *cur = *(ListNode **)*(ListNode **)tmp[1];
		if (cur != *(ListNode **)tmp[1]) {
		do {
			Object *cand = cur->m_val;
			if (cand != arg) {
				Coord3D pos = *(Coord3D *)&cand->m_x38;
				pos.x -= arg->m_x38;
				float dy = pos.y - arg->m_y3C;
				float d2 = pos.x * pos.x + dy * dy;
				if (d2 < best) {
					best = d2;
					bestObj = cand;
				}
			}
			cur = cur->m_next;
		} while (cur != *(ListNode **)tmp[1]);
	}
	TreeNode *bn = m_170->m_begin;
	if ((void *)bn != (void *)m_170) {
		do {
			ObjectID oid = bn->m_id;
			Object *obj = TheGameLogic->findObjectByID(oid);
			if (obj != 0 && obj != arg) {
				Coord3D pos = *(Coord3D *)&obj->m_x38;
				pos.x -= arg->m_x38;
				float dy = pos.y - arg->m_y3C;
				float d2 = pos.x * pos.x + dy * dy;
				if (d2 < best) {
					best = d2;
					bestObj = obj;
				}
			}
			bn = (TreeNode *)_STL::_Rb_global<bool>::_M_increment(bn);
		} while ((void *)bn != (void *)m_170);
	}
	return bestObj;
}
