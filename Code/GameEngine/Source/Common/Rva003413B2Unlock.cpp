// cl: /O1 /DNDEBUG /MD
// ?rva003413B2@Rva003413B2@@QAE_NXZ, retail 0x003413B2, 75 bytes. Unlock lane.
// this+0x18 is TurretStateMachine (rowed getGoalObject 0x004D7726); its +0x14
// is the owner Object (rowed chooseBestWeapon 0x0028AF4A, pin-only rva0028DB3C).
// Flag byte at this+0x41 gates the early false when the goal is null. The
// +0x258 object provides the CommandSource int through virtual slot 0x23c.
// Callers 0x0034B574 0x0034F991. Honest address names; class unproven.
class Object;

enum WeaponChoiceCriteria
{
	WCC_0 = 0,
	WCC_5 = 5
};

enum CommandSourceType
{
	CST_0 = 0
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
	char m_pad[ 0x14 ];
	Object *m_14;
};

class Virt0028CmdSrc
{
public:
	virtual int v000(); virtual int v001(); virtual int v002(); virtual int v003();
	virtual int v004(); virtual int v005(); virtual int v006(); virtual int v007();
	virtual int v008(); virtual int v009(); virtual int v010(); virtual int v011();
	virtual int v012(); virtual int v013(); virtual int v014(); virtual int v015();
	virtual int v016(); virtual int v017(); virtual int v018(); virtual int v019();
	virtual int v020(); virtual int v021(); virtual int v022(); virtual int v023();
	virtual int v024(); virtual int v025(); virtual int v026(); virtual int v027();
	virtual int v028(); virtual int v029(); virtual int v030(); virtual int v031();
	virtual int v032(); virtual int v033(); virtual int v034(); virtual int v035();
	virtual int v036(); virtual int v037(); virtual int v038(); virtual int v039();
	virtual int v040(); virtual int v041(); virtual int v042(); virtual int v043();
	virtual int v044(); virtual int v045(); virtual int v046(); virtual int v047();
	virtual int v048(); virtual int v049(); virtual int v050(); virtual int v051();
	virtual int v052(); virtual int v053(); virtual int v054(); virtual int v055();
	virtual int v056(); virtual int v057(); virtual int v058(); virtual int v059();
	virtual int v060(); virtual int v061(); virtual int v062(); virtual int v063();
	virtual int v064(); virtual int v065(); virtual int v066(); virtual int v067();
	virtual int v068(); virtual int v069(); virtual int v070(); virtual int v071();
	virtual int v072(); virtual int v073(); virtual int v074(); virtual int v075();
	virtual int v076(); virtual int v077(); virtual int v078(); virtual int v079();
	virtual int v080(); virtual int v081(); virtual int v082(); virtual int v083();
	virtual int v084(); virtual int v085(); virtual int v086(); virtual int v087();
	virtual int v088(); virtual int v089(); virtual int v090(); virtual int v091();
	virtual int v092(); virtual int v093(); virtual int v094(); virtual int v095();
	virtual int v096(); virtual int v097(); virtual int v098(); virtual int v099();
	virtual int v100(); virtual int v101(); virtual int v102(); virtual int v103();
	virtual int v104(); virtual int v105(); virtual int v106(); virtual int v107();
	virtual int v108(); virtual int v109(); virtual int v110(); virtual int v111();
	virtual int v112(); virtual int v113(); virtual int v114(); virtual int v115();
	virtual int v116(); virtual int v117(); virtual int v118(); virtual int v119();
	virtual int v120(); virtual int v121(); virtual int v122(); virtual int v123();
	virtual int v124(); virtual int v125(); virtual int v126(); virtual int v127();
	virtual int v128(); virtual int v129(); virtual int v130(); virtual int v131();
	virtual int v132(); virtual int v133(); virtual int v134(); virtual int v135();
	virtual int v136(); virtual int v137(); virtual int v138(); virtual int v139();
	virtual int v140(); virtual int v141(); virtual int v142();
	virtual int cmdSrc();
};

class Object
{
public:
	bool chooseBestWeaponForTarget(const Object *target, WeaponChoiceCriteria criteria, CommandSourceType src);
	void rva0028DB3C();
	char m_pad[ 0x258 ];
	Virt0028CmdSrc *m_258;
};

class Rva003413B2
{
public:
	bool rva003413B2();
private:
	char m_pad[ 0x18 ];
	TurretStateMachine *m_18;
	char m_fill[ 0x41 - 0x18 - sizeof(void *) ];
	unsigned char m_41;
};

bool Rva003413B2::rva003413B2()
{
	Object *goal = m_18->getGoalObject();
	if (m_41 == 0)
		goto check;
	if (goal == 0)
		return false;
check:
	Object *owner = m_18->m_14;
	int src = owner->m_258->cmdSrc();
	bool ok = owner->chooseBestWeaponForTarget(goal, WCC_5, (CommandSourceType)src);
	owner->rva0028DB3C();
	return ok;
}
