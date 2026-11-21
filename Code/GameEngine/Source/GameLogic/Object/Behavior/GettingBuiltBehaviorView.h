#ifndef BFME_GETTING_BUILT_BEHAVIOR_VIEW_H
#define BFME_GETTING_BUILT_BEHAVIOR_VIEW_H

#include "GettingBuiltBehaviorInterface.h"

struct BfmePod20 { int a[5]; };

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
	bool m_b32;
	bool m_b33;
	unsigned char m_b34;
	bool m_b35;
	bool m_b36;
	int m_x38;
	unsigned char m_b3C;
	unsigned char m_b3D;
	bool m_b3E;
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
	virtual void resumeBuildingConstruction(bool instant);
	// Interface table 0x00C403C8: the eighteen rowed overrides.
	virtual void rva00454430();
	virtual bool rva004543B6();
	virtual bool checkCompletion();
	virtual double rva004543BA();
	virtual bool rva004543BE();
	virtual bool rva004543C2();
	virtual bool rva004543C6();
	virtual void rva00454472(int frame);
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
