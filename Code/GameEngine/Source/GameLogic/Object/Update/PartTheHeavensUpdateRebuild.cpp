// cl: /I. /Oy- /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// PartTheHeavensUpdate shadow rebuild, native 004ACADA..004ACBB3 (217B).
// Called by the matched update and loadPostProcess. Retail proves module data
// +4, owning Object +8, shadow +24, descriptor name+8/color+C/curve+10,
// manager vslot4 and child position+8. Shadow::ShadowTypeInfo is the owned
// 79514/793FA descriptor pair; its former AudioEventRTS label is retired.
// The manager uses the existing provisional data-ledger owner declaration;
// its historical C++ type name is not asserted as the retail class identity.
// Keeping Object* as a local preserves retail's ECX load then ESI LEA for
// the 12B coordinate copy. Flags precede the two zero-float stores.
#include "ascii_string.h"



#include "../../../../Include/Common/FCurve.h"

#include "Code/Libraries/Include/Lib/Coord3D.h"

class Shadow
{
public:
struct ShadowTypeInfo
{
public:
	ShadowTypeInfo();
	~ShadowTypeInfo();
	AsciiString m_first;
	AsciiString m_second;
	int m_unknown8;
	float m_floatC;
	float m_float10;
	float m_float14;
	float m_float18;
	float m_float1C;
	float m_float20;
	unsigned char m_byte24;
	unsigned char m_byte25;
	unsigned char m_byte26;
};

	void setColor(int v);
	unsigned char m_pad00[8];
	Coord3D m_pos08;
};

#include "../object.h"

class PartTheHeavensUpdateModuleData
{
public:
	void *m_vtable;
	int m_unused04;
	AsciiString m_str08;
	int m_color0C;
	FCurve m_curve10;
};

class AudioManager0029E159
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual Shadow *createEmitter(int a, Shadow::ShadowTypeInfo *b, Shadow::ShadowTypeInfo *c);
};

class ProjectedShadowManager;
extern ProjectedShadowManager *TheProjectedShadowManager;

class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);
private:
	void rva004ACADA();
	unsigned int m_startFrame;
	Shadow *m_shadow;
};

void PartTheHeavensUpdate::rva004ACADA()
{
	if (m_shadow != 0)
		return;
	PartTheHeavensUpdateModuleData *data = (PartTheHeavensUpdateModuleData *)m_moduleData;
	if (((const StringBase<char> &)data->m_str08).isEmpty())
		return;
	Shadow::ShadowTypeInfo ev;
	float v = data->m_curve10.operator()(0.0f);
	((StringBase<char> &)ev.m_first).set((const StringBase<char> &)data->m_str08);
	float v2 = v * 2.0f;
	int type = 0x40;
	ev.m_unknown8 = type;
	ev.m_floatC = v2;
	ev.m_float10 = v2;
	ev.m_byte25 = 0;
	ev.m_byte26 = 1;
	ev.m_float14 = 0.0f;
	ev.m_float18 = 0.0f;
	AudioManager0029E159 *mgr = (AudioManager0029E159 *)TheProjectedShadowManager;
	m_shadow = mgr->createEmitter(type, &ev, &ev);
	if (m_shadow != 0)
	{
		Object *obj=m_object;const Coord3D *pos = &obj->m_cachedPos;
		Coord3D *dest = &m_shadow->m_pos08;
		*dest = *pos;
		m_shadow->setColor(data->m_color0C);
	}
}
