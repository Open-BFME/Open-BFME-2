// ?rva00509F3A@Made002CC8A4@@QAEEPAXPAVObject@@PAVDamageInfo@@@Z
// partial score=0.9485 date=2026-10-09
// ?rva00509F3A@Made002CC8A4@@QAEEPAXPAVObject@@PAVDamageInfo@@@Z
// partial score=0.89174 date=2026-10-09
// ?rva0050A1E9@Made002CC8A4@@QAEXPAXPAVObject@@@Z
// partial score=0.88 date=2026-10-04
// cl: /ICode/Libraries/Include/Lib /O1 /MD /EHsc /DNDEBUG /arch:SSE
//
// ?rva0050A1E9@Made002CC8A4@@QAEXPBXH@Z @ 0x0050A1E9 (434B).
// Slot 15 (0x3C) of Made002CC8A4 vtable 0x008649A0 (MetaImpactNugget).
// Evidence: vtable slot 15; callers none; callees rowed findObjectByID,
// isValid, getControllingPlayer, kill, rva0028C149, GetGameLogicRandomValueReal,
// testStatus; pins bfmeHas1026, report, attemptDamage; TheGameLogic,
// BfmeZeroRange, g_00C6499C, string literal.

#include "Coord3D.h"
#include <math.h>
class Object;
class Player;
class GameLogic;
enum ObjectID
{
	INVALID_ID = 0
};
enum DamageType
{
	DT_8 = 8
};
enum DeathType
{
	DT_0 = 0
};
enum ObjectStatusTypes
{
	ST_26 = 0x26
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ObjectFilter
{
public:
	bool isValid() const;
};
class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};
class Player { public: char prefix[0x54]; int index; };
class DamageInfo {
public:
 unsigned char prefix[8]; unsigned int sourceID; unsigned int sourceMask;
 unsigned char prefix10[0x18]; float amount; unsigned int reserved2c;
 unsigned int auxID; Coord3D direction; float wave40;
 float wave44,wave48,wave4c; bool wave50; unsigned char pad51[3];
 float wave54,wave58; Coord3D center; float wave68;
};
class Object
{
public:
	Player *getControllingPlayer() const;
	void kill(DamageType a, DeathType b);
	bool rva0028C149(int attr, float *value, int arg);
	bool testStatus(ObjectStatusTypes s) const;
	void attemptDamage(DamageInfo *info);
public:
	char m_pad00[4];
	void *m_04;
	char m_prefix08[0x30];
	Coord3D position;
	char m_prefix44[0x30];
	unsigned int objectID;
};
extern float BfmeZeroRange;
extern float g_00C6499C;
float __cdecl GetGameLogicRandomValueReal(float a, float b, char *name, int line);

class Rva00263653
{
public:
	Rva00263653() throw();
	char m_data[0x68];
};
class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();
private:
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};
class Rva00294D61
{
public:
	void report(Object *o, int v);
};
class DamageInfoish
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
	virtual void *v14();
	virtual void v15(void *a);
};
class TargetIface
{
public:
	virtual void v00();
	virtual void *v01();
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
	virtual void *v31(Object *o);
};
class SelfIface
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
	virtual unsigned char v14(const void *a, Object *b, const void *c);
};

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_009FEFA4;
class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};
class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	char m_pad[0x128 - 4];
};
class Made002CC8A4 : public Rva00507823
{
public:
	Made002CC8A4();
	void rva0050A1E9(void *a, Object *b);
	unsigned char rva00509F3A(void *weapon, Object *victim, DamageInfo *info);
private:
	float m_128;
	float m_12C;
	float m_130;
	bool m_134;
	char m_pad135[3];
	float m_138;
	float m_13C;
	float m_140;
	float m_144;
	unsigned int m_148;
	bool m_14C;
	bool m_14D;
	char m_pad14E[2];
	float m_150;
	bool m_154;
	bool m_155;
	char m_pad156[2];
	float m_158;
	float m_15C;
	Rva003623E5Member m_160;
};


static inline const float &bfmeMin(const float &a, const float &b) { return a > b ? b : a; }
unsigned char Made002CC8A4::rva00509F3A(void *weapon, Object *victim, DamageInfo *info)
{
 const Made002CC8A4 *self = this;
 Object *source;
 if (!weapon || !victim) goto failed;
 source = TheGameLogic->findObjectByID((ObjectID)*(int *)((char *)weapon + 8));
 float dx,dy,dz;
 if (!source) goto failed;
 info->wave40 = m_128;
 if (!m_155 && m_14C) {
  dy = source->position.y - victim->position.y;
  dz = source->position.z - victim->position.z;
  dx = source->position.x - victim->position.x;
 } else {
  dy = victim->position.y - source->position.y;
  dz = victim->position.z - source->position.z;
  dx = victim->position.x - source->position.x;
 }
 Coord3D delta = {dx,dy,dz};
 if (m_144 != 0.0f) {
  const float side = bfmeMin(m_144, 1.0f);
  float perpendicularY = -side * delta.x;
  const float normal = 1.0f - side;
  const float perpendicularX = delta.y * side;
  delta.x = delta.x * (normal + perpendicularX * side);
  delta.y *= normal + perpendicularY * side;
 }
 if (fabs(delta.x) < 0.0001f && fabs(delta.y) < 0.0001f && fabs(delta.z) < 0.0001f) {
  if (m_155) {
   float angle = GetGameLogicRandomValueReal(0.0f, 6.2831855f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\MetaImpactNugget.cpp", 0x15B);
   delta.x = (float)cos(angle); delta.y = (float)sin(angle);
  } else delta.z = 1.0f;
 }
 info->direction = delta;
 info->wave44 = self->m_12C; info->wave48 = self->m_138; info->wave4c = self->m_140;
 info->wave50 = self->m_155; info->wave54 = self->m_158; info->wave58 = self->m_15C;
 if (self->m_155) info->center = source->position;
 info->amount = (float)self->m_148;
 info->wave68 = self->m_144;
 if (self->m_13C > BfmeZeroRange) info->amount += delta.length() / self->m_13C;
 info->auxID = source->objectID;
 if (source->getControllingPlayer()) info->sourceMask = 1u << source->getControllingPlayer()->index;
 info->sourceID = *(unsigned int *)((char *)weapon + 8);
 info->sourceMask = source ? (1u << source->getControllingPlayer()->index) : 0;
 return 1;
failed:
 return 0;
}
