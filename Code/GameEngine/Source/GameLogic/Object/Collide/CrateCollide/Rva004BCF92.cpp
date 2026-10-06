// cl: /DNDEBUG /MD
//
// ?rva004BCF92@Rva004BCF92@@QAEXPBVObject@@H@Z, retail 0x004BCF92, 94 bytes.
// CrateCollide-family helper: copies a world position from the object held
// at +8 (Vec3 at +0x38), lifts Z by the global float, resolves the caller's
// controlling player color and forwards (arg, pos, color) to the InGameUI
// virtual at slot 0x1A0. Evidence: direct call to rowed
// ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ, globals g_Va00BC2428 and
// TheInGameUI as annotated, ret 8 with two stack args.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Player
{
public:
	char m_pad[0x280];
	int m_unk280;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

extern float g_Va00BC2428;

class InGameUI
{
public:
	virtual void d000(); virtual void d001(); virtual void d002(); virtual void d003();
	virtual void d004(); virtual void d005(); virtual void d006(); virtual void d007();
	virtual void d008(); virtual void d009(); virtual void d010(); virtual void d011();
	virtual void d012(); virtual void d013(); virtual void d014(); virtual void d015();
	virtual void d016(); virtual void d017(); virtual void d018(); virtual void d019();
	virtual void d020(); virtual void d021(); virtual void d022(); virtual void d023();
	virtual void d024(); virtual void d025(); virtual void d026(); virtual void d027();
	virtual void d028(); virtual void d029(); virtual void d030(); virtual void d031();
	virtual void d032(); virtual void d033(); virtual void d034(); virtual void d035();
	virtual void d036(); virtual void d037(); virtual void d038(); virtual void d039();
	virtual void d040(); virtual void d041(); virtual void d042(); virtual void d043();
	virtual void d044(); virtual void d045(); virtual void d046(); virtual void d047();
	virtual void d048(); virtual void d049(); virtual void d050(); virtual void d051();
	virtual void d052(); virtual void d053(); virtual void d054(); virtual void d055();
	virtual void d056(); virtual void d057(); virtual void d058(); virtual void d059();
	virtual void d060(); virtual void d061(); virtual void d062(); virtual void d063();
	virtual void d064(); virtual void d065(); virtual void d066(); virtual void d067();
	virtual void d068(); virtual void d069(); virtual void d070(); virtual void d071();
	virtual void d072(); virtual void d073(); virtual void d074(); virtual void d075();
	virtual void d076(); virtual void d077(); virtual void d078(); virtual void d079();
	virtual void d080(); virtual void d081(); virtual void d082(); virtual void d083();
	virtual void d084(); virtual void d085(); virtual void d086(); virtual void d087();
	virtual void d088(); virtual void d089(); virtual void d090(); virtual void d091();
	virtual void d092(); virtual void d093(); virtual void d094(); virtual void d095();
	virtual void d096(); virtual void d097(); virtual void d098(); virtual void d099();
	virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
	virtual void unk1A0(int a, Coord3D *pos, int color);
};

extern InGameUI *TheInGameUI;

struct Holder
{
	char m_pad[0x38];
	Coord3D m_pos;
};

class Rva004BCF92
{
public:
	void rva004BCF92(const Object *obj, int arg);
	char m_pad0[8];
	Holder *m_holder;
};

void Rva004BCF92::rva004BCF92(const Object *obj, int arg)
{
	const Object *heldObj = obj;
	Coord3D *p = (Coord3D *)((char *)m_holder + 0x38);
	Coord3D tmp;
	tmp.x = p->x;
	tmp.y = p->y;
	tmp.z = p->z + g_Va00BC2428;
	Player *player = heldObj->getControllingPlayer();
	int color = player->m_unk280 | 0xe6000000;
	TheInGameUI->unk1A0(arg, &tmp, color);
}
