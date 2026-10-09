// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?init@W3DModuleFactory@@UAEXXZ, retail 0x000652CA..0x0006577F (1205
// bytes, EH). Zero Hour's W3DModuleFactory::init in its BFME 2 form.
//
// Identity: slot 3 of the vftable at 0x007C2638, where the ModuleFactory
// vftable (0x007F3FE4) holds the rowed ModuleFactory::init 0x00257CB8; the
// body runs that base init first and then registers the twenty W3D draw
// modules by name (WorldBuilder twin 0x007F8CC0 pushes the same strings).
// Each registration goes through the rowed six-argument helper 0x002573EE
// with the module's rowed friend_newModuleInstance / friend_newModuleData
// (folded data factories keep the owner names the ledger gives them), the
// optional asset hook (rowed 0x000CED4B; 0x000C32C7, 0x000CA152 and
// 0x000D1112 keep address-derived names like the ModuleFactory::init
// hooks), module type 1 (draw) and interface mask 0x400.

#include "ascii_string.h"

enum ModuleType
{
	MODULETYPE_BEHAVIOR = 0,
	MODULETYPE_DRAW = 1
};

class Module;
class ModuleData;
class Thing;
class INI;
class AssetList;

class Rva002573EE
{
public:
	void rva002573EE(int, int, int, ModuleType, const AsciiString &, int);
};

class ModuleFactory
{
public:
	virtual void init();
};

class W3DModuleFactory : public ModuleFactory
{
public:
	virtual void init();
};

class W3DDefaultDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DDebrisDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DScriptedModelDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DModelDraw { public: static ModuleData *friend_newModuleData(INI *); };
class W3DHordeModelDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DHordeModelDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DLaserDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DQuadrupedDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DRopeDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DSupplyDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DTruckDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DTankDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DTreeDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DFloorDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DFloorDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DPropDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DPropDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DLightDraw
{
public:
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static ModuleData *friend_newModuleData(INI *);
};
class W3DBuffDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DBuffDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DStreakDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DStreakDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DSailModelDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DSailModelDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DBoatWakeModelDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DBoatWakeModelDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DProjectileStreamDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DProjectileStreamDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };
class W3DTornadoDraw { public: static Module *friend_newModuleInstance(Thing *, const ModuleData *); };
class W3DTornadoDrawModuleData { public: static ModuleData *friend_newModuleData(INI *); };

void Rva000CED4BUpdate(void *, AssetList *, int);
void ModuleFactoryHookAt000C32C7(void *, int, void *);
void ModuleFactoryHookAt000CA152(void *, int, void *);
void ModuleFactoryHookAt000D1112(void *, int, void *);

#define ADD_DRAW(instance, data, hook, name) \
	reinterpret_cast<Rva002573EE *>(this)->rva002573EE((int)&instance, (int)&data, hook, MODULETYPE_DRAW, AsciiString(name), 0x400)

void W3DModuleFactory::init()
{
	ModuleFactory::init();

	ADD_DRAW(W3DDefaultDraw::friend_newModuleInstance, W3DDebrisDraw::friend_newModuleData, 0, "W3DDefaultDraw");
	ADD_DRAW(W3DDebrisDraw::friend_newModuleInstance, W3DDebrisDraw::friend_newModuleData, 0, "W3DDebrisDraw");
	ADD_DRAW(W3DScriptedModelDraw::friend_newModuleInstance, W3DModelDraw::friend_newModuleData, (int)&ModuleFactoryHookAt000C32C7, "W3DScriptedModelDraw");
	ADD_DRAW(W3DHordeModelDraw::friend_newModuleInstance, W3DHordeModelDrawModuleData::friend_newModuleData, (int)&ModuleFactoryHookAt000CA152, "W3DHordeModelDraw");
	ADD_DRAW(W3DLaserDraw::friend_newModuleInstance, W3DLaserDraw::friend_newModuleData, 0, "W3DLaserDraw");
	ADD_DRAW(W3DQuadrupedDraw::friend_newModuleInstance, W3DQuadrupedDraw::friend_newModuleData, (int)&ModuleFactoryHookAt000CA152, "W3DQuadrupedDraw");
	ADD_DRAW(W3DRopeDraw::friend_newModuleInstance, W3DDebrisDraw::friend_newModuleData, 0, "W3DRopeDraw");
	ADD_DRAW(W3DSupplyDraw::friend_newModuleInstance, W3DSupplyDraw::friend_newModuleData, (int)&ModuleFactoryHookAt000CA152, "W3DSupplyDraw");
	ADD_DRAW(W3DTruckDraw::friend_newModuleInstance, W3DTruckDraw::friend_newModuleData, (int)&ModuleFactoryHookAt000CA152, "W3DTruckDraw");
	ADD_DRAW(W3DTankDraw::friend_newModuleInstance, W3DTankDraw::friend_newModuleData, (int)&ModuleFactoryHookAt000CA152, "W3DTankDraw");
	ADD_DRAW(W3DTreeDraw::friend_newModuleInstance, W3DTreeDraw::friend_newModuleData, (int)&Rva000CED4BUpdate, "W3DTreeDraw");
	ADD_DRAW(W3DFloorDraw::friend_newModuleInstance, W3DFloorDrawModuleData::friend_newModuleData, (int)&ModuleFactoryHookAt000D1112, "W3DFloorDraw");
	ADD_DRAW(W3DPropDraw::friend_newModuleInstance, W3DPropDrawModuleData::friend_newModuleData, (int)&ModuleFactoryHookAt000D1112, "W3DPropDraw");
	ADD_DRAW(W3DLightDraw::friend_newModuleInstance, W3DLightDraw::friend_newModuleData, 0, "W3DLightDraw");
	ADD_DRAW(W3DBuffDraw::friend_newModuleInstance, W3DBuffDrawModuleData::friend_newModuleData, 0, "W3DBuffDraw");
	ADD_DRAW(W3DStreakDraw::friend_newModuleInstance, W3DStreakDrawModuleData::friend_newModuleData, 0, "W3DStreakDraw");
	ADD_DRAW(W3DSailModelDraw::friend_newModuleInstance, W3DSailModelDrawModuleData::friend_newModuleData, 0, "W3DSailModelDraw");
	ADD_DRAW(W3DBoatWakeModelDraw::friend_newModuleInstance, W3DBoatWakeModelDrawModuleData::friend_newModuleData, 0, "W3DBoatWakeModelDraw");
	ADD_DRAW(W3DProjectileStreamDraw::friend_newModuleInstance, W3DProjectileStreamDrawModuleData::friend_newModuleData, 0, "W3DProjectileStreamDraw");
	ADD_DRAW(W3DTornadoDraw::friend_newModuleInstance, W3DTornadoDrawModuleData::friend_newModuleData, 0, "W3DTornadoDraw");
}
