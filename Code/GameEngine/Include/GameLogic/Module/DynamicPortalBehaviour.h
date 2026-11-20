// DynamicPortalBehaviour: canonical declarations for the members its units call or read through private views of it;
// each call resolves to the unit's ledger row or pin. The virtual prefix keeps the first three Snapshot slots.
// sizeof is 0x40 (operator new in the rowed 0x0024B47B); +0x04/+0x08 are the reads of the rowed 0x00460CBA.
#ifndef CANONICAL_DYNAMICPORTALBEHAVIOUR_H
#define CANONICAL_DYNAMICPORTALBEHAVIOUR_H

struct Coord3D;
class DynamicPortalBehaviourModuleData;
class Module;
class ModuleData;
class Object;
class Thing;

class DynamicPortalBehaviour
{
public:
	DynamicPortalBehaviour(Thing *thing, const ModuleData *moduleData);
	bool IsEndPortalAboveWall(Coord3D *pos);
	void createWaypoints();
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);
	static Module *rva004608E0(Object *obj);
	void rva0046094C();
	void rva00460CBA(Coord3D *out);

protected:
	virtual ~DynamicPortalBehaviour();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;

private:
	const DynamicPortalBehaviourModuleData *m_04;	// +0x04
	Object *m_08;	// +0x08
	char m_pad0C[0x40 - 0x0C];
};

#endif // CANONICAL_DYNAMICPORTALBEHAVIOUR_H
