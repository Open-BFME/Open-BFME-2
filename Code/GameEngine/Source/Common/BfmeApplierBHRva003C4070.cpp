// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x003C4070 (RVA 0x003C4070) size 213: BfmeApplierBH skirmish power sweep.
// Evidence: ScriptEngine 0xDFE16C getSkirmishEnemyPlayer then SpecialPowerStore 0xE02D4C findSpecialPowerTemplate then Overridable 0x54 range vs 50.0f then PlayerList mask loop then Player vtable+0x10 then bfmeApplyBH pin 0x3C069B.
#include "ascii_string.h"

class Player;
class Object;
class SpecialPowerTemplate;

class ScriptEngine
{
public:
	Player *getSkirmishEnemyPlayer();
	int rva00357475(const AsciiString &name, bool *flag);
};

extern class ScriptEngine *TheScriptEngine;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x54];
	float m_54;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

extern PlayerList *ThePlayerList;

class Player
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual bool v04(const SpecialPowerTemplate *tmpl, void *out, void *unk, float f);
};

class BfmeSubBH
{
public:
	char m_pad[16];
};

class BfmeApplierBH
{
public:
	void rva003C4070(const AsciiString &a, const AsciiString &b);
	bool bfmeApplyBH(void *owner, void *found, BfmeSubBH *sub) throw();
};

void BfmeApplierBH::rva003C4070(const AsciiString &a, const AsciiString &b)
{
	Player *enemy = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemy == 0)
		return;
	void *unk54 = *(void **)((char *)enemy + 0x54);
	const SpecialPowerTemplate *tmpl = TheSpecialPowerStore->findSpecialPowerTemplate(b);
	if (tmpl == 0)
		return;
	float f = 50.0f;
	const Overridable *ov = ((const Overridable *)tmpl)->friend_getFinalOverride();
	float g = ov->m_54;
	if (g > 50.0f) {
		ov = ((const Overridable *)tmpl)->friend_getFinalOverride();
		f = ov->m_54;
	}
	int mask = TheScriptEngine->rva00357475(a, 0);
	if (mask == 0)
		return;
	Player *p;
	do {
		p = ThePlayerList->getEachPlayerFromMask(mask);
		if (p != 0) {
			char out[12];
			p->v04(tmpl, out, unk54, f);
			if (bfmeApplyBH((void *)&a, (void *)tmpl, (BfmeSubBH *)out))
				return;
		}
	} while (mask != 0);
}
