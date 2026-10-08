// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?rva0027675F@Drawable@@QAE?AVRva002390CB@@H@Z, retail 0x0027675F (166B):
// a keyed Drawable lookup returning an Rva002390CB record by value. Key -1
// answers a default record (the folded 8-byte initialiser at 0x004CEE6E:
// -1 then a null reference, pinned as Rva002390CB's default constructor);
// otherwise each listener in the null-terminated +0x154 list (the list
// Drawable::reactToTransformChange also walks) is asked for its slot-13
// interface, whose slot 0 may fill a local record for the key - the first
// that does is returned - and the +0x04 template's rowed rva00239435(key)
// answers the rest. The local's inline destructor releases its reference
// (rowed OpaqueRefCounted::Release_Ref). Twenty-three 25-byte keyed
// wrappers (DrawableKeyedLookups.cpp) and rva00276805 call it.
//
// ?rva00276805@Drawable@@QAE_NH@Z, retail 0x00276805 (42B): whether that
// lookup's record carries a reference; callers 0x004DA80E, 0x004DA81B,
// 0x004DAA13.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);
	int m_0;
	Rva0036CA00Str m_4;
};

class Rva0027675FIface
{
public:
	virtual bool lookup(int key, Rva002390CB *out);
	virtual bool lookupName(const class AsciiString &name, Rva002390CB *out);
};

class Rva0027675FListener
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual Rva0027675FIface *getLookup();
};

class Rva00239435
{
public:
	Rva002390CB rva00239435(int key);
	Rva002390CB rva0033D3E8(const AsciiString &name);
};

class Drawable
{
public:
	Rva002390CB rva0027675F(int key);
	bool rva00276805(int key);
	Rva002390CB rva00274CD8(const AsciiString &name);
private:
	unsigned char m_pad00[4];
	Rva00239435 *m_template; // +0x04
	unsigned char m_pad08[0x154 - 8];
	Rva0027675FListener **m_listeners; // +0x154
};

Rva002390CB Drawable::rva0027675F(int key)
{
	if (key == -1)
		return Rva002390CB();
	Rva002390CB result;
	for (Rva0027675FListener **l = m_listeners; l && *l; ++l)
	{
		Rva0027675FIface *i = (*l)->getLookup();
		if (i && i->lookup(key, &result))
			return result;
	}
	return m_template->rva00239435(key);
}

bool Drawable::rva00276805(int key)
{
	Rva002390CB record = rva0027675F(key);
	return record.m_4.m_ref != 0;
}

// Ghidra [274CD8,274D6F)151B RET8 (hidden result and name reference).
// The matched keyed sibling proves the listener list154 and template04.
// This entry uses interface slot1 and falls back to 33D3E8. The fallback
// calls AsciiString's empty test and finds an AsciiString key in template388;
// its WB twin reports "Unknown Audio name". The original method is unknown.
Rva002390CB Drawable::rva00274CD8(const AsciiString &name)
{
	Rva002390CB result;
	for (Rva0027675FListener **l = m_listeners; l && *l; ++l)
	{
		Rva0027675FIface *i = (*l)->getLookup();
		if (i && i->lookupName(name, &result))
			return result;
	}
	return m_template->rva0033D3E8(name);
}
