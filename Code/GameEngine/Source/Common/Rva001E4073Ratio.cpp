// cl: /O1 /G7 /arch:SSE /MD
//
// ?rva001E4073@Rva001E4073@@QAEMPAVObject@@PAM@Z, retail 0x001E4073, 102 bytes.
// Turn ratio: v1 = [this+4]->+0x28 * [obj+0x258]->+0x1F8 * g_secondsPerLogicFrame
// (0x001E3F08), maxTurn = Locomotor::getMaxTurnRate(obj) (0x001E3E9F); ratio =
// v1/maxTurn when maxTurn > 0 else the 99999.0f .rdata constant at 0x007DDAD8;
// out, when given, gets ratio/v1 or 0 when v1 <= 0. Called from 0x001E7D1E.
// The caller keeps this in EDX across the 0x001E3F08 call because both callee
// bodies are visible in this unit at /O1 (the callee preserves EDX; the /O2
// form clobbers it and the caller then spills to ESI). Owner identity unproven,
// honest address-derived names for receiver and callees.
extern float g_secondsPerLogicFrame;

struct Rva001E3F08MidA
{
	int m_pad00[10]; // +0x00..+0x27
	float m_val28; // +0x28
};

struct Rva001E3F08MidB
{
	int m_pad00[126]; // +0x00..+0x1F7
	float m_val1F8; // +0x1F8
};

struct Rva001E3F08Arg
{
	int m_pad00[150]; // +0x00..+0x257
	Rva001E3F08MidB *m_p258; // +0x258
};

class Rva001E3F08
{
public:
	float rva001E3F2E(Rva001E3F08Arg *p);
	float rva001E3F08(Rva001E3F08Arg *p);
	char m_pad00[0x4];
private:
	Rva001E3F08MidA *m_p04; // +0x04
};

// This unit owns the existing 0x001E3F08 row; the redundant definition in
// Rva001E3F08Calc.cpp was removed.
// Retail keeps this 31-byte body as a call, so the definition here is noinline;
// its /O1 register shape (EAX/ECX, EDX preserved) is what the caller relies on.
__declspec(noinline) float Rva001E3F08::rva001E3F08(Rva001E3F08Arg *p)
{
	return p->m_p258->m_val1F8 * m_p04->m_val28 * g_secondsPerLogicFrame;
}

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLYDAMAGED = 2,
	BODY_RUBBLE = 3
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual BodyDamageType getDamageState() const;
};

#include "../GameLogic/Object/object.h"

#include "../../Include/GameLogic/LocomotorTemplate.h"

#include "../../Include/Common/GlobalData.h"

#define TheGlobalData TheWritableGlobalData
extern GlobalData *TheWritableGlobalData;

#include "../../Include/GameLogic/LocomotorClass.h"

// Locomotor::getMaxTurnRate(Object *) (0x001E3E9F) is defined in LocomotorGetMaxTurnRate.cpp.

class Rva001E4073
{
public:
	float rva001E4073(Object *obj, float *out);
};

float Rva001E4073::rva001E4073(Object *obj, float *out)
{
	Rva001E4073 *self = this;
	Object *object = obj;
	float v1 = ((Rva001E3F08 *)self)->rva001E3F08((Rva001E3F08Arg *)object);
	float maxTurn = ((const Locomotor *)self)->getMaxTurnRate(object);
	float ratio;
	if (maxTurn > 0.0f)
		ratio = v1 / maxTurn;
	else
		ratio = 99999.0f;
	if (out)
	{
		float t = ratio / v1;
		if (!(v1 > 0.0f))
			t = 0.0f;
		*out = t;
	}
	return ratio;
}
