// cl: /O1 /DNDEBUG /MD /EHsc
//
// Slots 0 and 1 of the vtable 0x00BEFEA4 that UpgradeSoundSelectorClientBehavior's
// ctor 0x00252CB5 installs at +0x0C (slot 2 is UpgradeSoundSelectorClientBehaviorSlot2.cpp),
// compiled with that subobject this; names by address.
//
// - slot 0, retail 0x004CB3F8 (146 bytes), and slot 1, retail 0x004CB48A
//   (146 bytes): for the drawable's Object (+0xFC), walk the module data's
//   0x384-byte entries (+0x08..+0x0C); each entry whose test 0x004CB333
//   accepts the Object assigns out the 8-byte sound record it returns by
//   value for the key (slot 0: an index, through 0x004CB167; slot 1: a name,
//   through 0x004CB2FB), and the first record whose +0x04 reference is set
//   answers true. The by-value temporary's reference is released inline
//   (OpaqueRefCounted::Release_Ref under an EH state), the record assigned
//   through the rowed Rva002C99FB::operator= 0x002C99FB.
class Object;
class AsciiString;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	~OpaqueRefElement4()
	{
		if (referent)
			referent->Release_Ref();
	}
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

struct Rva004CB51CEntry
{
	bool rva004CB333(Object *obj);
	Rva002C99FB rva004CB167(int index);
	Rva002C99FB rva004CB2FB(const AsciiString &name);
	unsigned char m_pad000[0x384];
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
	virtual bool rva004CB3F8(int index, Rva002C99FB *out) = 0;
	virtual bool rva004CB48A(const AsciiString &name, Rva002C99FB *out) = 0;
};

class UpgradeSoundSelectorClientBehavior : public DrawableModule, public Rva004CB51CInterface
{
public:
	virtual bool rva004CB3F8(int index, Rva002C99FB *out);
	virtual bool rva004CB48A(const AsciiString &name, Rva002C99FB *out);
};

bool UpgradeSoundSelectorClientBehavior::rva004CB3F8(int index, Rva002C99FB *out)
{
	const UpgradeSoundSelectorClientBehaviorModuleData *d = m_moduleData;
	Object *obj = m_drawable->getObject();
	if (obj == 0)
		return false;
	for (Rva004CB51CEntry *e = d->m_begin, *end = d->m_end; e != end; ++e)
	{
		if (e->rva004CB333(obj))
		{
			*out = e->rva004CB167(index);
			if (out->m_second.referent)
				return true;
		}
	}
	return false;
}

bool UpgradeSoundSelectorClientBehavior::rva004CB48A(const AsciiString &name, Rva002C99FB *out)
{
	const UpgradeSoundSelectorClientBehaviorModuleData *d = m_moduleData;
	Object *obj = m_drawable->getObject();
	if (obj == 0)
		return false;
	for (Rva004CB51CEntry *e = d->m_begin, *end = d->m_end; e != end; ++e)
	{
		if (e->rva004CB333(obj))
		{
			*out = e->rva004CB2FB(name);
			if (out->m_second.referent)
				return true;
		}
	}
	return false;
}
