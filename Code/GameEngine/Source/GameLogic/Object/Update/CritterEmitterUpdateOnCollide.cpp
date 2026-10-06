// cl: /DNDEBUG /MD
//
// ?onCollide@CritterEmitterUpdate@@UAEXPAVObject@@PBVCoord3D@@1@Z, retail
// 0x004C8E83, 124 bytes: slot 0 of the vtable 0x00C5E8C4 that the matched
// CritterEmitterUpdate ctor 0x004C8D86 installs at +0x20, compiled with that
// subobject this (the candidate list had filed it as HordeDispatchSpecialPower
// slot 14, whose primary vtable 0x00C5E88C directly precedes it). The ctor
// first stores the all-purecall 6-slot vtable 0x00C40818 there; the slots
// after this one are a one-argument bool returning false (0x005CB9FF) and
// four argless false bools, the shape of ZH CollideModuleInterface with
// CollideModule's defaults, so the slot is onCollide.
// Once only (flag +0x24, which the matched xfer saves and the ctor clears):
// plays a random FXList from the module data's vector at +0x08 on the owner
// and creates a random ObjectCreationList from the vector at +0x14 from the
// owner. Retail's random calls carry the source path literal of
// CritterEmitter.cpp with lines 127 and 138.

class Object;
class Coord3D;
class ModuleData;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class ObjectCreationList
{
public:
	void rva001F08D3(void *primary, void *secondary, void *a3);
	static void create(const ObjectCreationList *ocl, const Object *primary, const Object *secondary)
	{
		if (!ocl)
			return;
		const_cast<ObjectCreationList *>(ocl)->rva001F08D3((void *)primary, (void *)secondary, 0);
	}
};

template <class T> class PtrVector
{
public:
	int size() const { return m_end - m_begin; }
	T operator[](int i) const { return m_begin[i]; }
private:
	T *m_begin;
	T *m_end;
	T *m_cap;
};

struct CritterEmitterUpdateModuleData
{
	unsigned char m_pad00[0x08];
	PtrVector<const FXList *> m_fxLists; // +0x08
	PtrVector<const ObjectCreationList *> m_oclLists; // +0x14
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface { public: virtual void behaviorModuleInterfaceAnchor(); };
class UpdateModuleInterface { public: virtual void updateModuleInterfaceAnchor(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_updateState; // +0x1C
};

class CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CritterEmitterUpdate : public UpdateModule, public CollideModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
private:
	bool m_emitted; // +0x24
	bool m_25;
};

// ?onCollide@CritterEmitterUpdate@@UAEXPAVObject@@PBVCoord3D@@1@Z @0x004C8E83
void CritterEmitterUpdate::onCollide(Object *, const Coord3D *, const Coord3D *)
{
	if (m_emitted)
		return;

	const CritterEmitterUpdateModuleData *data = (const CritterEmitterUpdateModuleData *)m_moduleData;

	int count = data->m_fxLists.size();
	if (count > 0)
	{
		int which = GetGameLogicRandomValue(0, count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\CritterEmitter.cpp", 127);
		FXList::doFXObj(data->m_fxLists[which], m_object, 0);
	}

	count = data->m_oclLists.size();
	if (count > 0)
	{
		int which = GetGameLogicRandomValue(0, count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\CritterEmitter.cpp", 138);
		ObjectCreationList::create(data->m_oclLists[which], m_object, 0);
	}

	m_emitted = true;
}
