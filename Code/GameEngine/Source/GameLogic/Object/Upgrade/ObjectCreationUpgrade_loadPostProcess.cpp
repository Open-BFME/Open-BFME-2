// cl: /DNDEBUG /MD
// ?loadPostProcess@ObjectCreationUpgrade@@MAEXXZ @0x004B3FCB 17B evidence vtable 0x0085762C slot 1 plus callers none plus base loadPostProcess plus StringBase validate
// ObjectCreationUpgrade::loadPostProcess: slot 1 of its UpdateModule vtable at
// +8, the loadPostProcess slot (198 of 223 named sibling tables). It is
// compiled with that subobject this: it calls
// UpdateModule::loadPostProcess on this, then tail-jmps to StringBase validate
// on this-8 (the UpgradeMux head). Layout from ObjectCreationUpgradeDtor.cpp:
// UpgradeMux at +0, UpdateModule at +8. Shape follows Rva005FED59Validate.cpp
// (friend-private validate via cast) with a preceding base call, giving
// push esi / mov esi,ecx / call / lea ecx,[esi-8] / pop esi / jmp at /O1.
class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"




template <typename T> class StringBase
{
	friend class ObjectCreationUpgrade;
	void validate() const;
};

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~ObjectCreationUpgrade();
	virtual void loadPostProcess();
};

void ObjectCreationUpgrade::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	return ((StringBase<unsigned short> *)(UpgradeMux *)this)->validate();
}
