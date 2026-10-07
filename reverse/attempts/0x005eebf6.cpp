// ?rva005EEBF6@Rva005EEA20@@QAEXPAVRva005EE9CE@@PAVObject@@M@Z
// partial score=0.93 date=2026-10-05
// ?rva005EEBF6@Rva005EEA20@@QAEXPAURva005EE9CE@@PAVObject@@M@Z
// partial score=0.96 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
// ?Rva005EE317@@YGXPAVCoord3D@@@Z @ 0x005EE317 125B
// Random XY direction in AISPecialPowerTargetAoE.cpp (__FILE__ at 0x00878708
// line 150-151): GetGameLogicRandomValueReal(-1.0f at 0x007BB9AC, 1.0f) twice
// z=0 normalize then store to out. Callees rowed: GetGameLogicRandomValueReal
// 0x00234092 and Coord3D::normalize 0x000035B6. Gap between 0x005EE30C/0x005EE394.
//
// 0x005EE816: whether the AoE picker may use a point: its special power (+0x08,
// 0x0035B2C3) must accept it, and with +0x1A set no alive object of kind 7
// may stand within 150 of it (the PartitionFilter chain; /GX for its
// temporaries).
class Coord3D
{
public:
	void normalize();
	float x;
	float y;
	float z;
};

float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

void __stdcall Rva005EE317(Coord3D *out)
{
	Coord3D tmp;
	tmp.x = GetGameLogicRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISPecialPowerTargetAoE.cpp", 150);
	tmp.y = GetGameLogicRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISPecialPowerTargetAoE.cpp", 151);
	tmp.z = 0.0f;
	tmp.normalize();
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}

// BFME2's partition filters (the view AIStructureCreepTactic.cpp documents):
// a vptr, the +0x04 link to the next filter, then each filter's own members.
class Object;
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908: every kind of the first mask, none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BFAD10: the object is alive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class Player;

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class Rva0035B2C3
{
public:
	bool rva0035B2C3(void *source, int a, const Coord3D *pos, int b);
};

// The AoE special-power target picker (0x005EE8DD walks candidate points
// round the target and keeps the first this accepts).
class Rva005EE816
{
public:
	bool rva005EE816(void *source, const Coord3D *pos);
private:
	char m_pad00[8];
	Rva0035B2C3 *m_power;	// +0x08
	char m_pad0C[0x1A - 0x0C];
	bool m_1A;		// +0x1A
};

bool Rva005EE816::rva005EE816(void *source, const Coord3D *pos)
{
	if (m_power->rva0035B2C3(source, 0, pos, 0)) {
		bool check = m_1A;
		if (check) {
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, 150.0f, 0,
			Rva0026119DFilter().link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
				*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)), 1);
			if (hits.next() != 0)
				return false;
		}
		return true;
	}
	return false;
}

// The base filter's slot 2 is the trivial virtual retail shares across 68
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

// What Object +0x04 points at: 0x005EEBF6 tests kind bits at +0x108 and +0x113.
struct Rva005EEBF6Template
{
	char m_pad000[0x108];
	unsigned char m_108;	// +0x108
	char m_pad109[0x113 - 0x109];
	unsigned char m_113;	// +0x113
};

// The module at Object +0x254: slot 5 returns the float 0x005EEBF6 sums.
class Rva005EEBF6Module
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual float rva005EEBF6Value() const;	// slot 5
};

// What Object::rva0028C197 returns: slot 153 (+0x264) returns that float.
class Rva005EEBF6Owner
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void s131();
	virtual void s132();
	virtual void s133();
	virtual void s134();
	virtual void s135();
	virtual void s136();
	virtual void s137();
	virtual void s138();
	virtual void s139();
	virtual void s140();
	virtual void s141();
	virtual void s142();
	virtual void s143();
	virtual void s144();
	virtual void s145();
	virtual void s146();
	virtual void s147();
	virtual void s148();
	virtual void s149();
	virtual void s150();
	virtual void s151();
	virtual void s152();
	virtual float rva005EEBF6Value() const;	// slot 153
};

class Object
{
public:
	Player *getControllingPlayer() const;			// 0x0028AFA9
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	Object *rva002931F5(bool flag);				// 0x002931F5
	void *rva0028C197() const;				// 0x0028C197
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	Rva005EEBF6Template *m_04;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x254 - 0x44];
	Rva005EEBF6Module *m_254;	// +0x254
};

// The 16-byte tally 0x005EE9CE clears: per side a count and a value sum.
struct Rva005EE9CE
{
	unsigned int m_00;	// +0x00 enemies counted
	float m_04;		// +0x04 their summed value, then the mean
	unsigned int m_08;	// +0x08 the rest
	float m_0C;		// +0x0C
};

class Rva005EEA20
{
public:
	void rva005EEBF6(Rva005EE9CE *tally, Object *source, float radius);
};

void Rva005EEA20::rva005EEBF6(Rva005EE9CE *tally, Object *source, float radius)
{
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), radius, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 6)), 0);
	for (Object *obj = hits.next(); obj; obj = hits.next()) {
		Rva005EEBF6Template *tmpl = obj->m_04;
		if (tmpl->m_108 & 0x80)
			continue;
		if (!(tmpl->m_108 & 0x08) && !(tmpl->m_113 & 0x04))
			continue;
		if (source->getRelationship(obj) == ENEMIES) {
			tally->m_08++;
			if (obj->rva002931F5(false))
				tally->m_0C += ((Rva005EEBF6Owner *)obj->rva002931F5(false)->rva0028C197())->rva005EEBF6Value();
			else
				tally->m_0C += obj->m_254->rva005EEBF6Value();
		} else {
			tally->m_00++;
			if (obj->rva002931F5(false))
				tally->m_04 += ((Rva005EEBF6Owner *)obj->rva002931F5(false)->rva0028C197())->rva005EEBF6Value();
			else
				tally->m_04 += obj->m_254->rva005EEBF6Value();
		}
	}
	if (tally->m_08 > 0)
		tally->m_0C /= tally->m_08;
	if (tally->m_00 > 0)
		tally->m_04 /= tally->m_00;
}

