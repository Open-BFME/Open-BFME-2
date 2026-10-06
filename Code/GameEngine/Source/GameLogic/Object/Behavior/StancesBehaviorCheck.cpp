// cl: /DNDEBUG /MD
// ?changeStanceFromXfer@StancesBehavior@@QAE_NH@Z @0x0045EDD5 87B evidence: chain via rowed map-find 0x4260DE plus StancesBehavior neighbours Xfer-NameKey share /O1 plus caller 0x4751E5 plus vtable slots 0x7c and 0x260 plus global g_00E031D4
class Thing;
class ModuleData;

struct IfaceBig
{
	virtual void v000(), v001(), v002(), v003(), v004(), v005(), v006(), v007();
	virtual void v008(), v009(), v010(), v011(), v012(), v013(), v014(), v015();
	virtual void v016(), v017(), v018(), v019(), v020(), v021(), v022(), v023();
	virtual void v024(), v025(), v026(), v027(), v028(), v029(), v030(), v031();
	virtual void v032(), v033(), v034(), v035(), v036(), v037(), v038(), v039();
	virtual void v040(), v041(), v042(), v043(), v044(), v045(), v046(), v047();
	virtual void v048(), v049(), v050(), v051(), v052(), v053(), v054(), v055();
	virtual void v056(), v057(), v058(), v059(), v060(), v061(), v062(), v063();
	virtual void v064(), v065(), v066(), v067(), v068(), v069(), v070(), v071();
	virtual void v072(), v073(), v074(), v075(), v076(), v077(), v078(), v079();
	virtual void v080(), v081(), v082(), v083(), v084(), v085(), v086(), v087();
	virtual void v088(), v089(), v090(), v091(), v092(), v093(), v094(), v095();
	virtual void v096(), v097(), v098(), v099(), v100(), v101(), v102(), v103();
	virtual void v104(), v105(), v106(), v107(), v108(), v109(), v110(), v111();
	virtual void v112(), v113(), v114(), v115(), v116(), v117(), v118(), v119();
	virtual void v120(), v121(), v122(), v123(), v124(), v125(), v126(), v127();
	virtual void v128(), v129(), v130(), v131(), v132(), v133(), v134(), v135();
	virtual void v136(), v137(), v138(), v139(), v140(), v141(), v142(), v143();
	virtual void v144(), v145(), v146(), v147(), v148(), v149(), v150(), v151();
	virtual void doIt(int value);
};

struct IfaceA
{
	virtual void w00(), w01(), w02(), w03(), w04(), w05(), w06(), w07();
	virtual void w08(), w09(), w10(), w11(), w12(), w13(), w14(), w15();
	virtual void w16(), w17(), w18(), w19(), w20(), w21(), w22(), w23();
	virtual void w24(), w25(), w26(), w27(), w28(), w29(), w30();
	virtual IfaceBig *get();
};

struct Holder250
{
	char m_pad[0x250];
	IfaceA *m_250;
};

struct Holder04
{
	char m_pad[8];
	int m_08;
};

class Rva004260DE
{
public:
	int *rva004260DE(int key);
};

extern Rva004260DE *g_00E031D4;

class StancesBehavior
{
	char m_00[4];
	Holder04 *m_04;
	Holder250 *m_08;
	char m_0C[0x28];
public:
	bool changeStanceFromXfer(int arg);
};

bool StancesBehavior::changeStanceFromXfer(int arg)
{
	IfaceA *iface = m_08->m_250;
	IfaceBig *b;
	if (iface != 0)
		b = iface->get();
	else
		b = 0;
	if (b != 0)
	{
		int key = m_04->m_08;
		if (key == 0)
			return false;
		int *found = g_00E031D4->rva004260DE(key);
		if (found == 0)
			return false;
		b->doIt(found[arg * 2 + 2]);
	}
	return true;
}
