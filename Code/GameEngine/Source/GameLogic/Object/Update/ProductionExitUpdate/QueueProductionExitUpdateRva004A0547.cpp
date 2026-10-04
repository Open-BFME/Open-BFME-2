// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /O2 /Ob1 /O1 /arch:SSE
// ?rva004A0547@QueueProductionExitUpdate@@QAEXXZ @0x004A0547 297B chain via 0x4A0403.
// Evidence: QueueProductionExitUpdate rally logic via rowed bfmeQueryRallyOverride 0x4A0403; TheGameLogic findObjectByID row; setStatus rows; getControllingPlayer row; g_00DFEEF8 plus rva002A8AB1 pin; rva00346C53 pin; AI rva0036EBB8 row; v8 rally coord; v31/v4/v145 virtuals; neighbours SetRallyPoint /O1.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Object;
Object *bfmeQueryRallyOverride(Object *obj, const Coord3D *pos);
class Iface31
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30();
	virtual void *v31();
};
class Iface145
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(int x); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
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
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89(); virtual void v90(); virtual void v91();
	virtual void v92(); virtual void v93(); virtual void v94(); virtual void v95();
	virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109(); virtual void v110(); virtual void v111();
	virtual void v112(); virtual void v113(); virtual void v114(); virtual void v115();
	virtual void v116(); virtual void v117(); virtual void v118(); virtual void v119();
	virtual void v120(); virtual void v121(); virtual void v122(); virtual void v123();
	virtual void v124(); virtual void v125(); virtual void v126(); virtual void v127();
	virtual void v128(); virtual void v129(); virtual void v130(); virtual void v131();
	virtual void v132(); virtual void v133(); virtual void v134(); virtual void v135();
	virtual void v136(); virtual void v137(); virtual void v138(); virtual void v139();
	virtual void v140(); virtual void v141(); virtual void v142(); virtual void v143();
	virtual void v144();
	virtual void v145(const Coord3D *pos);
};
enum ObjectStatusTypes
{
	ST_2 = 2,
	ST_3 = 3,
	ST_78 = 78
};
enum CommandSourceType
{
	CS_2 = 2
};
class Player
{
public:
	char m_pad[0x5c];
	int m_5c;
};
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
};
extern Rva002A8F24 *g_00DFEEF8;
class AICommandInterface
{
public:
	void rva0036EBB8(Object *obj, CommandSourceType src);
};
class Object
{
public:
	void setStatus(ObjectStatusTypes s, bool b);
	void rva00346C53(ObjectStatusTypes s, bool b);
	Player *getControllingPlayer() const;
	char m_pad[0x250];
	Iface31 *m_250;
	char m_pad2[4];
	AICommandInterface *m_258;
};
enum ObjectID
{
	OID_NONE = 0
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
struct Unk1C
{
	char m_pad[0x32];
	bool m_32;
};
class QueueProductionExitUpdate
{
public:
	virtual void setRallyPoint(const Coord3D *pos);
	virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual const Coord3D *v8();
	void rva004A0547();
private:
	unsigned char m_pad[4];
	Coord3D m_rallyPoint;
	bool m_rallyPointExists;
	char m_pad2[11];
	int m_20;
};
void QueueProductionExitUpdate::rva004A0547()
{
	Object *top = TheGameLogic->findObjectByID((ObjectID)m_20);
	if (!top)
		return;
	m_20 = 0;
	Iface31 *iface = top->m_250;
	Iface145 *provider = (Iface145 *)iface->v31();
	if (!provider)
	{
		top->setStatus(ST_3, false);
		top->setStatus(ST_2, false);
		return;
	}
	Unk1C *unk1c = *(Unk1C **)((char *)this - 0x1c);
	if (unk1c)
	{
		Object *selfObj = *(Object **)((char *)this - 0x18);
		Player *player = selfObj->getControllingPlayer();
		if (!player || player->m_5c)
		{
			Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(player);
			if (!rec)
				provider->v4(0);
			else if (unk1c->m_32)
				provider->v4(0);
		}
		else if (unk1c->m_32)
			provider->v4(0);
	}
	top->setStatus(ST_3, false);
	top->setStatus(ST_2, false);
	if (!m_rallyPointExists)
		return;
	const Coord3D *rally = v8();
	Coord3D tmp;
	tmp.x = rally->x;
	Object *selfObj2 = *(Object **)((char *)this - 0x18);
	tmp.y = rally->y;
	tmp.z = rally->z;
	Object *overrideHost = bfmeQueryRallyOverride(selfObj2, &tmp);
	if (overrideHost)
	{
		top->setStatus((ObjectStatusTypes)78, true);
		top->setStatus(ST_3, true);
		top->rva00346C53(ST_3, true);
		AICommandInterface *aic = (AICommandInterface *)((char *)top->m_258 + 0x20);
		aic->rva0036EBB8(overrideHost, CS_2);
	}
	else
		provider->v145(&tmp);
}
