// cl: /DNDEBUG /MD /EHsc
// ?rva0028B265@Object@@QBEXXZ @0x0028B265 45B
// Object module scan through the +0x244 array: asks each module's +0x0C
// sub-object for slot 8 (+0x20); when non-null calls its slot 15 (+0x3C)
// with 1.0f. Evidence: same +0x244 array and +0x0C lea as rowed
// getSpawnBehaviorInterface at 0x0028BCD4 and siblings rva0028C4ED (slot 26)
// rva0028BA85 (slot 46); retail lea ecx [eax+0x0C] plus call [eax+0x20] plus
// fld1/push/fstp plus call [edx+0x3C] prove slots and float arg;
// null-terminated scan with plain ret proves 0 args void; caller at
// 0x0037F1D4; name stays address-derived (Object owner proven by +0x244).

class Rva0028B265Result
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(int v); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(float v);
};

class Rva0028B1D4Result
{
public:
	virtual void slot00(int a, int b);
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual Rva0028B1D4Result *slot05(); virtual void slot06(); virtual void slot07();
	virtual Rva0028B265Result *slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42();
	virtual void slot43(float v);
};

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class PartitionData
{
public:
	void maybePrepend();
};

class Rva009A2350
{
public:
	void init();
};

class Rva00625840
{
public:
	void rva00625840();
};

class Rva0028B193Provider
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03();
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;
	char m_pad248[0x250 - 0x248];
	Rva0028B193Provider *m_provider250;
	char m_pad254[0x4C4 - 0x254];
	PartitionData *m_partitionData4C4;
	Rva00625840 *m_4C8;
	Rva009A2350 *m_4CC;

public:
	void rva0028B265() const;
	void rva0028B292(int v) const;
	void rva0028B1D4(int a, int b) const;
	void rva0028B193();
	void rva0028B701(float v);
};

void Object::rva0028B265() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028B265Result *r = (*m)->slot08();
		if (r != 0)
			r->slot15(1.0f);
	}
}

void Object::rva0028B292(int v) const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028B265Result *r = (*m)->slot08();
		if (r != 0)
			r->slot09(v);
	}
}

void Object::rva0028B1D4(int a, int b) const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028B1D4Result *r = (*m)->slot05();
		if (r != 0)
			r->slot00(a, b);
	}
}

// ?rva0028B193@Object@@QAEXXZ @0x0028B193 65B: refreshes the Object's
// helpers in turn - the +0x4C4 partition data through the rowed
// PartitionData::maybePrepend 0x0073A0E0, the +0x4CC and +0x4C8 objects
// through the rowed twin initialisers 0x007584C0 and 0x00625840 - then
// tail-calls slot 3 of the +0x250 provider (the interface rowed
// 0x0028C197 reaches). Directly before rva0028B1D4; no direct callers.
void Object::rva0028B193()
{
	if (m_partitionData4C4)
		m_partitionData4C4->maybePrepend();
	if (m_4CC)
		m_4CC->init();
	if (m_4C8)
		m_4C8->rva00625840();
	Rva0028B193Provider *provider = m_provider250;
	if (provider)
		provider->slot03();
}

// ?rva0028B701@Object@@QAEXM@Z @0x0028B701 41B: the same +0x244 module scan
// handing a float to slot 43 (+0xAC) of each module's +0x0C interface,
// unconditionally. Caller 0x004CCED3.
void Object::rva0028B701(float v)
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
		(*m)->slot43(v);
}
