#ifndef BFME_GETTING_BUILT_BEHAVIOR_VIEW_H
#define BFME_GETTING_BUILT_BEHAVIOR_VIEW_H

struct BfmePod20 { int a[5]; };

class Rva004530ED;

class GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehaviorInterface();
	// Retail vtable 0x00C40020 holds _purecall in all 27 slots. Eighteen take the
	// signature of the rowed GettingBuiltBehavior override in table 0x00C403C8.
	// Slot 0 adjusts to the BehaviorModuleInterface receiver and returns this interface.
	virtual void *slot32() = 0;
	virtual void slot1() = 0;
	virtual void rva00454430() = 0;
	virtual void rva00453905(Object *other) = 0;
	virtual void rva00453652(bool) = 0;
	virtual void rva004535B7() = 0;
	virtual void slot6() = 0;
	virtual bool rva0045314E(Object *obj) = 0;
	virtual bool rva004533B2() = 0;
	virtual bool rva004533A7() = 0;
	virtual void rva004543D5(bool value) = 0;
	virtual void slot11() = 0;
	virtual float rva0045342F(Object *obj) = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void rva00453B20(Object *obj) = 0;
	virtual bool rva004540F5() = 0;
	virtual float rva00453FE7(Object *obj) = 0;
	virtual void rva00453F31(int a1) = 0;
	virtual bool rva004531E4(Object *obj) = 0;
	virtual bool rva0045362B(int id) = 0;
	virtual int rva00453B7B(int, Rva004530ED *) = 0;
	virtual bool rva00453E5C() = 0;
	virtual void rva00453BF1() = 0;
};
class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GettingBuiltBehavior();
	virtual UpdateSleepTime update();
	void rva0045427E();
private:
	const Object *getObject(void) const { return m_object; }
	unsigned int m_audio24;
	float m_f28;
	int m_x2C;
	unsigned char m_b30;
	unsigned char m_b31;
	unsigned char m_b32;
	unsigned char m_b33;
	unsigned char m_b34;
	unsigned char m_b35;
	unsigned char m_b36;
	int m_x38;
	unsigned char m_b3C;
	unsigned char m_b3D;
	unsigned char m_b3E;
	_STL::list<BfmePod20, _STL::allocator<BfmePod20> > m_workList;
public:
	// retail slot 4: the rowed ?getModuleNameKey@GettingBuiltBehavior@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
	// Primary table 0x00C404FC, slots 5 and 8: the rowed onObjectCreated 0x004534F5
	// and onDelete 0x00454501.
	virtual void onObjectCreated();
	virtual void onDelete();
	virtual void *slot32();
	virtual void slot45(int);
	// Interface table 0x00C403C8: the eighteen rowed overrides.
	virtual void rva00454430();
	virtual void rva00453905(Object *other);
	virtual void rva00453652(bool);
	virtual void rva004535B7();
	virtual bool rva0045314E(Object *obj);
	virtual bool rva004533B2();
	virtual bool rva004533A7();
	virtual void rva004543D5(bool value);
	virtual float rva0045342F(Object *obj);
	virtual void rva00453B20(Object *obj);
	virtual bool rva004540F5();
	virtual float rva00453FE7(Object *obj);
	virtual void rva00453F31(int a1);
	virtual bool rva004531E4(Object *obj);
	virtual bool rva0045362B(int id);
	virtual int rva00453B7B(int, Rva004530ED *);
	virtual bool rva00453E5C();
	virtual void rva00453BF1();
protected:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
	// Primary table 0x00C404FC, slot 1: the rowed loadPostProcess 0x004542AD.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
};

#endif
