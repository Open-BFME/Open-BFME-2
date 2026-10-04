// cl: /O1 /DNDEBUG /MD
// ?rva00344598@Rva00344598@@QAEHXZ @0x00344598 157B
// Evidence: unlock lane, caller 0x00347EA8 tail-jmp same this, callees rowed getGoalObject 0x004D7726 plus setOrientation 0x0030AB9D plus winPrevTab 0x000D43D0 plus pin rva000B4542, virtuals 0x244 0x7c 0x19c 0x1a0 0x1d0
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing
{
public:
	void setOrientation(float angle);
};

class Object
{
public:
	float rva000B4542(const Coord3D *pos) const;
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class GameWindow
{
public:
	int winPrevTab();
};

class C258Holder
{
public:
	virtual void d000(); virtual void d001(); virtual void d002(); virtual void d003(); virtual void d004();
	virtual void d005(); virtual void d006(); virtual void d007(); virtual void d008(); virtual void d009();
	virtual void d010(); virtual void d011(); virtual void d012(); virtual void d013(); virtual void d014();
	virtual void d015(); virtual void d016(); virtual void d017(); virtual void d018(); virtual void d019();
	virtual void d020(); virtual void d021(); virtual void d022(); virtual void d023(); virtual void d024();
	virtual void d025(); virtual void d026(); virtual void d027(); virtual void d028(); virtual void d029();
	virtual void d030(); virtual void d031(); virtual void d032(); virtual void d033(); virtual void d034();
	virtual void d035(); virtual void d036(); virtual void d037(); virtual void d038(); virtual void d039();
	virtual void d040(); virtual void d041(); virtual void d042(); virtual void d043(); virtual void d044();
	virtual void d045(); virtual void d046(); virtual void d047(); virtual void d048(); virtual void d049();
	virtual void d050(); virtual void d051(); virtual void d052(); virtual void d053(); virtual void d054();
	virtual void d055(); virtual void d056(); virtual void d057(); virtual void d058(); virtual void d059();
	virtual void d060(); virtual void d061(); virtual void d062(); virtual void d063(); virtual void d064();
	virtual void d065(); virtual void d066(); virtual void d067(); virtual void d068(); virtual void d069();
	virtual void d070(); virtual void d071(); virtual void d072(); virtual void d073(); virtual void d074();
	virtual void d075(); virtual void d076(); virtual void d077(); virtual void d078(); virtual void d079();
	virtual void d080(); virtual void d081(); virtual void d082(); virtual void d083(); virtual void d084();
	virtual void d085(); virtual void d086(); virtual void d087(); virtual void d088(); virtual void d089();
	virtual void d090(); virtual void d091(); virtual void d092(); virtual void d093(); virtual void d094();
	virtual void d095(); virtual void d096(); virtual void d097(); virtual void d098(); virtual void d099();
	virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104();
	virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109();
	virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114();
	virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
	virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124();
	virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129();
	virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134();
	virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139();
	virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144();
	virtual void t258();
};

class C250Holder
{
public:
	virtual void e000(); virtual void e001(); virtual void e002(); virtual void e003(); virtual void e004();
	virtual void e005(); virtual void e006(); virtual void e007(); virtual void e008(); virtual void e009();
	virtual void e010(); virtual void e011(); virtual void e012(); virtual void e013(); virtual void e014();
	virtual void e015(); virtual void e016(); virtual void e017(); virtual void e018(); virtual void e019();
	virtual void e020(); virtual void e021(); virtual void e022(); virtual void e023(); virtual void e024();
	virtual void e025(); virtual void e026(); virtual void e027(); virtual void e028(); virtual void e029();
	virtual void e030();
	virtual void *t250();
};

class CEdi
{
public:
	virtual void f000(); virtual void f001(); virtual void f002(); virtual void f003(); virtual void f004();
	virtual void f005(); virtual void f006(); virtual void f007(); virtual void f008(); virtual void f009();
	virtual void f010(); virtual void f011(); virtual void f012(); virtual void f013(); virtual void f014();
	virtual void f015(); virtual void f016(); virtual void f017(); virtual void f018(); virtual void f019();
	virtual void f020(); virtual void f021(); virtual void f022(); virtual void f023(); virtual void f024();
	virtual void f025(); virtual void f026(); virtual void f027(); virtual void f028(); virtual void f029();
	virtual void f030(); virtual void f031(); virtual void f032(); virtual void f033(); virtual void f034();
	virtual void f035(); virtual void f036(); virtual void f037(); virtual void f038(); virtual void f039();
	virtual void f040(); virtual void f041(); virtual void f042(); virtual void f043(); virtual void f044();
	virtual void f045(); virtual void f046(); virtual void f047(); virtual void f048(); virtual void f049();
	virtual void f050(); virtual void f051(); virtual void f052(); virtual void f053(); virtual void f054();
	virtual void f055(); virtual void f056(); virtual void f057(); virtual void f058(); virtual void f059();
	virtual void f060(); virtual void f061(); virtual void f062(); virtual void f063(); virtual void f064();
	virtual void f065(); virtual void f066(); virtual void f067(); virtual void f068(); virtual void f069();
	virtual void f070(); virtual void f071(); virtual void f072(); virtual void f073(); virtual void f074();
	virtual void f075(); virtual void f076(); virtual void f077(); virtual void f078(); virtual void f079();
	virtual void f080(); virtual void f081(); virtual void f082(); virtual void f083(); virtual void f084();
	virtual void f085(); virtual void f086(); virtual void f087(); virtual void f088(); virtual void f089();
	virtual void f090(); virtual void f091(); virtual void f092(); virtual void f093(); virtual void f094();
	virtual void f095(); virtual void f096(); virtual void f097(); virtual void f098(); virtual void f099();
	virtual void f100(); virtual void f101(); virtual void f102();
	virtual void t19c(Object *o);
	virtual void t1a0(int v);
	virtual void f105(); virtual void f106(); virtual void f107(); virtual void f108(); virtual void f109();
	virtual void f110(); virtual void f111(); virtual void f112(); virtual void f113(); virtual void f114();
	virtual void f115();
	virtual void t1d0();
};

class Rva00344598
{
public:
	int rva00344598();
private:
	char m_pad00[0x18];
	TurretStateMachine *m_turret; // +0x18
};

struct ObjectLayout
{
	char pad0[0x44];
	float m44; // +0x44
	char pad44[0x250 - 0x48];
	C250Holder *m250; // +0x250
	char pad254[0x258 - 0x254];
	C258Holder *m258; // +0x258
};

struct TurretLayout
{
	char pad0[0x14];
	Object *m_obj; // +0x14
};

int Rva00344598::rva00344598()
{
	TurretStateMachine *turret = m_turret;
	Object *esi = ((TurretLayout *)turret)->m_obj;
	if (esi == 0)
		return -2;
	Object *ebx = turret->getGoalObject();
	if (ebx == 0)
		return -2;
	ObjectLayout *ol = (ObjectLayout *)esi;
	C258Holder *c258 = ol->m258;
	if (c258 == 0)
		return -2;
	c258->t258();
	C250Holder *c250 = ol->m250;
	CEdi *edi = c250 ? (CEdi *)c250->t250() : 0;
	if (edi != 0) {
		edi->t19c(ebx);
		edi->t1a0(1);
		edi->t1d0();
	} else {
		const Coord3D *pos = (const Coord3D *)((char *)ebx + 0x38);
		float ang = esi->rva000B4542(pos) + ol->m44;
		((Thing *)esi)->setOrientation(ang);
	}
	((GameWindow *)this)->winPrevTab();
	return 0;
}
