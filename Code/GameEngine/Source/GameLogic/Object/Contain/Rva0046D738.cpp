// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0046D738@HordeContain@@QAEXXZ, RVA 0x0046D738 size 119.
// Unlock lane Contain body via TheGameLogic findObjectByID row; evidence:
// +0x11C iface virtual +0x138 and +0x2C8 target virtual +0x14 match
// HordeContainIface11CSlots neighbours; +0x2A0 ObjectID +0x08 Object
// +0x274 redirect cmovne +0x38 Coord3D +0x44 float via Thing orientation row.
enum ObjectID
{
	INVALID_ID = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object;
class Thing
{
public:
	void setOrientation(float ang);
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class Object : public Thing
{
public:
	float rva000B4542(const Coord3D *pos) const;
};
class HordeContainIface11C
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
};
class HordeContainTarget2C8
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05(Object *obj);
};
class HordeContain
{
public:
	void rva0046D738();
private:
	char m_pad00[0x08];
	Object *m_obj08;
	char m_pad0C[0x110];
	HordeContainIface11C m_iface11C;
	char m_pad120[0x180];
	ObjectID m_id2A0;
	char m_pad2A4[0x24];
	HordeContainTarget2C8 *m_target2C8;
};
void HordeContain::rva0046D738()
{
	if (m_id2A0 == INVALID_ID)
		return;
	Object *found = TheGameLogic->findObjectByID(m_id2A0);
	if (found == 0)
	{
		m_iface11C.v78();
		m_id2A0 = INVALID_ID;
		return;
	}
	m_target2C8->w05(found);
	Object *redir = *(Object **)((char *)found + 0x274);
	Object *base = m_obj08;
	if (redir != 0)
		found = redir;
	float add = *(float *)((char *)base + 0x44);
	const Coord3D *pos = (const Coord3D *)((char *)found + 0x38);
	float ang = base->rva000B4542(pos) + add;
	((Thing *)base)->setOrientation(ang);
}
