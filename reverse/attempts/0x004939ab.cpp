// ?rva004939AB@Rva004939AB@@QAEXPBX@Z
// partial score=0.8465 date=2026-10-05
// ?rva004939AB@Rva004939AB@@QAEXPBX@Z
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
// ?rva004939AB@Rva004939AB@@QAEXPBX@Z @0x004939AB 268B: __thiscall method
// using ObjectModule layout (data at +4, object at +8); orders timer via
// ScriptEngine 0x00357E7B then two BfmeAudioEventPrefix136 temporaries
// through CondSetter and TheAudio slot 0x64. Evidence: all callees rowed,
// ObjectID at +0x74, player index at +0x54, FO+0x10 name, FO+0x34/0x38
// audio refs, caller 0x0049420B in 0x004941F3, prev/next neighbours.
#include "ascii_string.h"

struct OpaqueRefElement4;
class ScriptEngine;
class AudioManager;
class Object;
class Player;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
private:
	char m_pad[0x10];
};

struct OpaqueRefElement4
{
	char m_body[4];
};

class SpecialPowerTemplate : public Overridable
{
public:
	AsciiString m_name; // +0x10
	char m_pad20[0x34 - 0x14];
	OpaqueRefElement4 m_34; // +0x34
	OpaqueRefElement4 m_38; // +0x38
	char m_pad3C[0x58 - 0x3C];
	bool m_publicTimer; // +0x58 (from dtor TU)
};

class SpecialPowerModuleData
{
public:
	void *vptr; // ModuleData vptr +0
	char m_pad04[4]; // +4
	const SpecialPowerTemplate *m_template; // +8
};

class Player
{
public:
	Player *getControllingPlayer() const;
private:
	char m_pad[0x54];
public:
	int m_playerIndex; // +0x54
};

class Object
{
public:
	Player *getControllingPlayer() const;
private:
	char m_pad[0x74];
public:
	int m_id74; // +0x74 ObjectID
};

class ScriptEngine
{
public:
	void rva00357E7B(int a, const AsciiString &name, int b);
};

extern ScriptEngine *g_Va009FE16C;

class BfmeStringTailRecord144
{
public:
	virtual ~BfmeStringTailRecord144();
};

class BfmeAudioEventPrefix136 : public BfmeStringTailRecord144
{
public:
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &o, int v);
private:
	char m_pad[136 - sizeof(BfmeStringTailRecord144)];
};

class Rva002D9531
{
public:
	void rva002D9531(int v);
};

class Rva002D9508
{
public:
	void rva002D9508(const void *p);
};

class Rva0033F15DDwordSlot
{
public:
	void set(int v);
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24();
	virtual int v25(BfmeAudioEventPrefix136 *p);
};

extern AudioManager *TheAudio;

class Rva004939AB
{
public:
	void rva004939AB(const void *p);
private:
	void *m_vptr; // +0
	SpecialPowerModuleData *m_data; // +4
	Object *m_object; // +8
};

// ?rva004939AB@Rva004939AB@@QAEXPBX@Z present-unmatched
void Rva004939AB::rva004939AB(const void *p)
{
	Object *obj = m_object;
	int objId = obj->m_id74;
	Player *player = obj->getControllingPlayer();
	const SpecialPowerTemplate *tmpl = m_data->m_template;
	int playerIdx = player->m_playerIndex;
	const Overridable *fo = tmpl->friend_getFinalOverride();
	const SpecialPowerTemplate *foT = (const SpecialPowerTemplate *)fo;
	g_Va009FE16C->rva00357E7B(objId, foT->m_name, playerIdx);

	const Overridable *fo2 = ((const Overridable *)m_data->m_template)->friend_getFinalOverride();
	const SpecialPowerTemplate *foT2 = (const SpecialPowerTemplate *)fo2;
	BfmeAudioEventPrefix136 tmp1(foT2->m_34, 0);
	((Rva002D9531 *)&tmp1)->rva002D9531(obj->m_id74);
	TheAudio->v25(&tmp1);

	if (p != 0) {
		const Overridable *fo3 = ((const Overridable *)m_data->m_template)->friend_getFinalOverride();
		const SpecialPowerTemplate *foT3 = (const SpecialPowerTemplate *)fo3;
		BfmeAudioEventPrefix136 tmp2(foT3->m_38, 0);
		((Rva002D9508 *)&tmp2)->rva002D9508(p);
		Player *player2 = obj->getControllingPlayer();
		((Rva0033F15DDwordSlot *)&tmp2)->set(player2->m_playerIndex);
		TheAudio->v25(&tmp2);
	}
}
