// cl: /O1 /DNDEBUG /MD
//
// ??0DieModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045CEBD, 49 bytes.
// DieModule behavior intermediate base ctor over the rowed BehaviorModule base
// (0x253330, thing plus data). Substantial BFME1 reconstruction from the
// GeneralsMD DieModule.h donor: DieModule is multiple inheritance
// (BehaviorModule plus the pure DieModuleInterface), so the compiler emits the
// inline DieModuleInterface base store at +0x10 first and then the derived
// vtable group ([esi], +0x0C, +0x10). The duplicate +0x10 store is structural:
// the interface vtable is unchanged by the derived class, so the base store
// and the derived re-store carry the same table. Hand-written duplicate body
// assignments cannot reproduce it (the toolchain merges them); only the
// faithful MI shape does.
//
// Two documented deviations from the donor, both codegen-neutral for this
// body: the TU-local BehaviorModuleInterface carries only getDie (the real
// one has ~30 getters; slot count lives in .rdata, never in .text), and the
// getDie override is pure here (the donor returns this) so the TU emits no
// unclaimable helper. Vtable immediates are DIR32-masked.
//
// Identity: the BFME1 CrushDie donor calls this base at the matching site;
// the rowed Die behaviors (CreateObjectDie 0x485A96,
// CreateObjectDieIfEldestKindof 0x485B4B, DamageFiltered 0x485F87,
// SpecialPowerCompletionDie 0x486A74 and 9 more 2-arg callers) call it as
// their base; the sole-caller chain runs into RebuildHoleExposeDieUpdate
// 0x486768 via the Update factory 0x24CAE0. Row supersedes the DieModule pin;
// the Rva0045CEBDUpdate pin at the same address stands for its TU users.

class Thing;
class ModuleData;

// Primary base chain of the rowed BehaviorModule: ObjectModule (vptr plus pad
// to 0x0C) with the BehaviorModuleInterface secondary at +0x0C. The ctor call
// below resolves to the rowed BehaviorModule body.
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	unsigned char m_pad08[0x0C - 4];
};

class DieModuleInterface;

class BehaviorModuleInterface
{
public:
	virtual DieModuleInterface *getDie() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class DieModuleInterface
{
public:
	virtual void onDie() = 0;
};

class DieModule : public BehaviorModule, public DieModuleInterface
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);
	virtual DieModuleInterface *getDie() = 0;
};

// ??0DieModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x45CEBD
DieModule::DieModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData), DieModuleInterface()
{
}
