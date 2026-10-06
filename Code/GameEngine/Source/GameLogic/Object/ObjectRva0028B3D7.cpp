// cl: /DNDEBUG /MD /EHsc
// ?rva0028B3D7@Object@@QBEXXZ @0x0028B3D7 58B
// Object module scan through the +0x244 array: asks each module's +0x0C
// sub-object for slot 10 (+0x28); when non-null asks its slot 4 (+0x10) bool
// and when true calls its slot 5 (+0x14). Evidence: same +0x244 array and
// +0x0C lea as rowed getSpawnBehaviorInterface at 0x0028BCD4 and siblings
// rva0028BD5D (slot 25) rva0028B265 (slot 8); retail lea ecx [eax+0x0C] plus
// call [eax+0x28] plus call [eax+0x10] test al plus call [eax+0x14] prove
// slots and bool; null-terminated scan with plain ret proves 0 args void;
// caller at 0x00374E75; name stays address-derived (Object owner by +0x244).

class Rva0028B3D7Result
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual bool slot04();
	virtual void slot05();
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual Rva0028B3D7Result *slot10();
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

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void rva0028B3D7() const;
};

void Object::rva0028B3D7() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028B3D7Result *r = (*m)->slot10();
		if (r != 0 && r->slot04())
			r->slot05();
	}
}
