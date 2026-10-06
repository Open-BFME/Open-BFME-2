// cl: /DNDEBUG /MD
//
// Object::findModule, retail 0x0028B6D6, 43 bytes.
// Dedicated TU. Walks the null-terminated module pointer list at +0x244
// and compares virtual name-key slot 0x10.

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module
{
public:
	virtual void _dtor() = 0;
	virtual void _r1() = 0;
	virtual void _r2() = 0;
	virtual void _r3() = 0;
	virtual NameKeyType getModuleNameKey() const = 0;
};

class BodyFwd
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void slot12(int v);
	virtual void slot13(int v);
};

class Drawable
{
public:
	void setSelectable(bool selectable);
};

class Object
{
	char pad00[0x84];
	Drawable *m_drawable; // +0x84
	char pad88[0x244 - 0x88];
	Module **m_modules; // +0x244
	char pad248[0x254 - 0x248];
	BodyFwd *m_body; // +0x254, proven by Object_attemptHealing precedent
	char pad258[0x434 - 0x258];
	bool m_isSelectable; // +0x434

protected:
	Module *findModule(NameKeyType key) const;
public:
	void rva0028B78A(int v);
	void rva0028B79C(int v);
	void setSelectable(bool selectable);
};

Module *Object::findModule(NameKeyType key) const
{
	Module *found = 0;
	for (Module **at = m_modules; *at; ++at)
	{
		if ((*at)->getModuleNameKey() == key)
		{
			found = *at;
			break;
		}
	}
	return found;
}

void Object::setSelectable(bool selectable)
{
	m_isSelectable = selectable;
	if (m_drawable != 0)
		m_drawable->setSelectable(selectable);
}

// ?rva0028B78A@Object@@QAEXH@Z, retail 0x0028B78A, 18 bytes.
// Object body forwarder: if the body at +0x254 is present tail-jumps to its
// slot 0x30 with the caller's int arg, else returns void. Evidence: body at
// +0x254 per Object_attemptHealing, slot 0x30 from retail jmp, callers pass
// 6/9 with Object this at 0x0049930F 0x004AE07B 0x004B0527 0x00499514.
void Object::rva0028B78A(int v)
{
	BodyFwd *b = m_body;
	if (b != 0)
		b->slot12(v);
}

// ?rva0028B79C@Object@@QAEXH@Z, retail 0x0028B79C, 18 bytes.
// Sibling of 0x0028B78A in the same TU: same body at +0x254, same int arg
// shape, tail-jumps to slot 0x34. Callers pass 6/9 at 0x0049927D 0x004ADFD5.
void Object::rva0028B79C(int v)
{
	BodyFwd *b = m_body;
	if (b != 0)
		b->slot13(v);
}
