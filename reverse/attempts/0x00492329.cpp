// ?rva00492329@Rva00492179@@UAEXXZ
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// ?rva00492329@Rva00492179@@UAEXXZ at retail 0x00492329 (185B). Slot 17 (offset
// 0x44) override of SpecialAbilityUpdate for the class of Rva00492179 ctor
// (vtable 0x0084DEF8). Evidence: calls pinned SpecialAbilityUpdate::rva0045108D
// 0x0045108D plus rowed AICommandInterface::aiIdle 0x001E8A38 plus rowed
// StringBase<char>::isEmpty 0x00001E2F plus rowed StringBase ctor 0x00037BA0
// plus pinned Object::rva0028EA91 0x0028EA91 plus rowed releaseBuffer 0x00036410
// plus rowed Object::isKindOf 0x0006F039 plus rowed
// Object::setSpecialModelConditionState 0x0028AEB2; ModuleData AsciiString at
// +0xC8 plus int at +0xCC plus bools at +0xD0/+0xD1; Object holder at +0x258
// with AICommandInterface at +0x20.
#include "ascii_string.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum KindOfType
{
	KIND_BA = 0xBA,
	KIND_DC = 0xDC
};

enum ModelConditionFlagType
{
	MODELCOND_BA = 0xBA,
	MODELCOND_DC = 0xDC
};

class Object;
class AsciiString;

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr492329(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType src);
};

class Object
{
public:
	bool isKindOf(KindOfType kind) const;
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	bool rva0028EA91(const AsciiString &name, int v);

	unsigned char m_pad00[0x258];
	void *m_258;
};

class Rva00492179ModuleData
{
public:
	unsigned char m_pad[0xC8];
	AsciiString m_C8;
	int m_CC;
	bool m_D0;
	bool m_D1;
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();

protected:
	const Rva00492179ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x88 - 0x0C];
};

class Rva00492179 : public SpecialAbilityUpdate
{
public:
	virtual void rva00492329();
};

// ?rva00492329@Rva00492179@@UAEXXZ present-unmatched
void Rva00492179::rva00492329()
{
	SpecialAbilityUpdate::rva0045108D();
	const Rva00492179ModuleData *data = m_moduleData;
	Object *object = m_object;
	if (data->m_D1 != 0)
	{
		char *holder = *(char **)((char *)object + 0x258);
		if (holder != 0)
			((AICommandInterface *)(holder + 0x20))->aiIdle(CMD_FROM_AI);
	}
	if (!((const StringBase<char> &)data->m_C8).isEmpty())
	{
		AsciiString tmp(GetStr492329(data->m_C8));
		object->rva0028EA91(tmp, -1);
	}
	int kind = 0xBA;
	if (!data->m_D0)
		kind += 0x22;
	if (!object->isKindOf((KindOfType)kind))
		object->setSpecialModelConditionState((ModelConditionFlagType)kind, (unsigned int)data->m_CC);
}
