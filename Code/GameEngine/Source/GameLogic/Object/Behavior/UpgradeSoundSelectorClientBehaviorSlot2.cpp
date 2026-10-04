// cl: /O1 /DNDEBUG /MD
//
// ?rva004CB51C@UpgradeSoundSelectorClientBehavior@@UAE_NPAH@Z, retail
// 0x004CB51C, 86 bytes: slot 2 of the vtable 0x00BEFEA4 that
// UpgradeSoundSelectorClientBehavior's ctor 0x00252CB5 installs at +0x0C.
// For the drawable's Object (+0xFC), walks the module data's 0x384-byte
// entries (+0x08..+0x0C); each entry whose test 0x004CB333 (pinned) accepts
// the Object writes its +0x37C value out, and the first such entry with its
// +0x380 flag set answers true. Compiled with the +0x0C subobject this. Names
// by address.
class Object;

struct Rva004CB51CEntry
{
	bool rva004CB333(Object *obj);
	unsigned char m_pad000[0x37C];
	int m_37C; // +0x37C
	bool m_380; // +0x380
	unsigned char m_pad381[0x384 - 0x381];
};

struct UpgradeSoundSelectorClientBehaviorModuleData
{
	unsigned char m_pad00[0x08];
	Rva004CB51CEntry *m_begin; // +0x08
	Rva004CB51CEntry *m_end; // +0x0C
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad000[0xFC];
	Object *m_object; // +0xFC
};

class DrawableModule
{
public:
	virtual ~DrawableModule();
protected:
	const UpgradeSoundSelectorClientBehaviorModuleData *m_moduleData; // +0x04
	Drawable *m_drawable; // +0x08
};

class Rva004CB51CInterface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual bool rva004CB51C(int *out) = 0;
};

class UpgradeSoundSelectorClientBehavior : public DrawableModule, public Rva004CB51CInterface
{
public:
	virtual bool rva004CB51C(int *out);
};

bool UpgradeSoundSelectorClientBehavior::rva004CB51C(int *out)
{
	const UpgradeSoundSelectorClientBehaviorModuleData *d = m_moduleData;
	Object *obj = m_drawable->getObject();
	if (obj == 0)
		return false;
	Rva004CB51CEntry *end = d->m_end;
	for (Rva004CB51CEntry *e = d->m_begin; e != end; ++e)
	{
		if (e->rva004CB333(obj))
		{
			*out = e->m_37C;
			if (e->m_380)
				return true;
		}
	}
	return false;
}
