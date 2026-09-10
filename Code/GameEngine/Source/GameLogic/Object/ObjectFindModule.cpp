// cl: /O1 /DNDEBUG /MD
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

class Object
{
	char pad[0x244];
	Module **m_modules;

protected:
	Module *findModule(NameKeyType key) const;
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
