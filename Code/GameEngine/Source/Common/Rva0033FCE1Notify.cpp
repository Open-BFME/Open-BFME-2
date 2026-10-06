// cl: /DNDEBUG /MD
// ?notify@BfmeSubVfn1A6@@QAEHHPAX@Z @0x0033FCE1 150B
// Evidence: linkbody lane; callers in AIUpdateInterfacePrivateCommands; internalGetState row; vtable slots 0x14 0x10 0x220; globals g_Va00DBA4E4 TheGameLogic
struct State;

class StateMachine
{
public:
	State *internalGetState(int id);
};

struct State
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual State *v04();
	virtual void v05(int x);
};

class BigObj
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094(); virtual void v095();
	virtual void v096(); virtual void v097(); virtual void v098(); virtual void v099();
	virtual void v100(); virtual void v101(); virtual void v102(); virtual void v103();
	virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107();
	virtual void v108(); virtual void v109(); virtual void v110(); virtual void v111();
	virtual void v112(); virtual void v113(); virtual void v114(); virtual void v115();
	virtual void v116(); virtual void v117(); virtual void v118(); virtual void v119();
	virtual void v120(); virtual void v121(); virtual void v122(); virtual void v123();
	virtual void v124(); virtual void v125(); virtual void v126(); virtual void v127();
	virtual void v128(); virtual void v129(); virtual void v130(); virtual void v131();
	virtual void v132(); virtual void v133(); virtual void v134(); virtual void v135();
	virtual void v136();
};

class MidObj
{
public:
	char m_pad00[0x258];
	BigObj *m_258;
};

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

extern int g_Va00DBA4E4; // ?g_Va00DBA4E4@@3HA
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

class BfmeSubVfn1A6
{
public:
	int notify(int id, void *param);
private:
	char m_pad00[0x14];
	MidObj *m_14;
	char m_pad18[0x50 - 0x18];
	State *m_50;
	int m_54;
};

int BfmeSubVfn1A6::notify(int id, void *param)
{
	State *st = ((StateMachine *)this)->internalGetState(id);
	if (m_50) {
		m_50->v05(1);
		m_50 = 0;
	}
	if (st) {
		BigObj *big = m_14->m_258;
		if (big)
			big->v136();
		m_50 = st;
		State *cur = st->v04();
		if (cur) {
			m_50->v05(0);
			m_50 = 0;
			return (int)cur;
		}
		int limit = g_Va00DBA4E4 * 60;
		int v = (int)param;
		v = v >= limit ? limit : v;
		int res;
		if (v == -2)
			res = -2;
		else if (v < 0)
			res = -1;
		else
			res = TheGameLogic->m_40 + v;
		m_54 = res;
		return 0;
	} else {
		return -2;
	}
}
