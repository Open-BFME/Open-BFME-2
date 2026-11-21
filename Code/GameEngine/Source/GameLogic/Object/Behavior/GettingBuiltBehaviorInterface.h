#ifndef BFME_GETTING_BUILT_BEHAVIOR_INTERFACE_H
#define BFME_GETTING_BUILT_BEHAVIOR_INTERFACE_H

class Object;
class Rva004530ED;

class GettingBuiltBehaviorInterface
{
public:
	GettingBuiltBehaviorInterface();
	// The retail base table at 0x00C40020 has 27 _purecall entries.
	// The derived slot 0 adjusts through BehaviorModuleInterface to return this interface.
	virtual void *slot32() = 0;
	virtual void resumeBuildingConstruction(bool instant) = 0;
	virtual void rva00454430() = 0;
	virtual void rva00453905(Object *other) = 0;
	virtual void rva00453652(bool) = 0;
	virtual void rva004535B7() = 0;
	virtual bool rva004543B6() = 0;
	virtual bool rva0045314E(Object *obj) = 0;
	virtual bool rva004533B2() = 0;
	virtual bool rva004533A7() = 0;
	virtual void rva004543D5(bool value) = 0;
	virtual bool checkCompletion() = 0;
	virtual float rva0045342F(Object *obj) = 0;
	virtual double rva004543BA() = 0;
	virtual bool rva004543BE() = 0;
	virtual bool rva004543C2() = 0;
	virtual bool rva004543C6() = 0;
	virtual void rva00454472(int) = 0;
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
#endif
