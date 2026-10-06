// cl: /O1 /DNDEBUG /MD
//
// ?rva004B2F7B@Rva004B2F7B@@QAE_NPBVSpecialPowerTemplate@@@Z @0x004B2F7B 82B.
// Object at +0x8 must lack status 0x5A. TheSpecialPowerStore then accepts the
// template, and the module from Object::getSpecialPowerModule must answer
// virtual slot 1. A missing module clears the byte at +0x20 and returns false.

enum ObjectStatusTypes
{
	OBJECT_STATUS_5A = 0x5A
};

class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
	virtual void s0();
	virtual bool s1();
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *tmpl) const;
};

class SpecialPowerStore
{
public:
	bool rva003B1244(Object *obj, const SpecialPowerTemplate *tmpl);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class Rva004B2F7B
{
public:
	bool rva004B2F7B(const SpecialPowerTemplate *tmpl);

private:
	char m_pad[0x08];
	Object *m_obj;
	char m_mid[0x14];
	volatile unsigned char m_flag;
};

bool Rva004B2F7B::rva004B2F7B(const SpecialPowerTemplate *tmpl)
{
	Object *obj = m_obj;
	if (obj->testStatus(OBJECT_STATUS_5A))
		goto fail;
	if (!TheSpecialPowerStore->rva003B1244(obj, tmpl))
		goto fail;
	SpecialPowerModuleInterface *mod = m_obj->getSpecialPowerModule(tmpl);
	if (mod != 0)
	{
		if (mod->s1())
			return true;
	}
	else
		m_flag = 0;
fail:
	return false;
}
