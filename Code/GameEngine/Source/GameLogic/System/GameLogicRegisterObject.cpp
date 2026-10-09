// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// GameLogic::registerObject (retail 0x00242AE9, 203B), Zero Hour
// GameEngine/Source/GameLogic/System/GameLogic.cpp.
// Target facts: links the object with BFME's head/tail Object::appendToList
// (0x0028B49B, &GameLogic+0xAC/+0xB0), then the rowed addObjectToLookupTable
// (0x00242AC2). Each behavior module's update interface (slot 0x24) is
// converted to its UpdateModule (-0x10); a zero next-call frame becomes
// min(now, UPDATE_SLEEP_FOREVER), with frame 0 treated as 1 as in ZH. BFME
// replaces ZH's pushSleepyUpdate heap: a sleeping-forever module gets phase
// -1 and goes on the vector at +0xF8, any other on the per-phase vector
// +0xC8 + 12 * phase (phase from UpdateModule slot 0x30); +0x18 keeps its
// index in that vector and +0x1C its phase.
// The vector push_back is the ICF-folded STLport body at 0x004DFCB0, rowed
// as vector<const ModuleData*>::push_back; that spelling is the only one the
// REL32 resolver knows for it, so the lists are viewed with that element type.

typedef int Int;
typedef unsigned int UnsignedInt;

class ModuleData;
class Object;

namespace _STL {
template <class T> class allocator {};

template <class T, class Alloc = allocator<T> >
class vector
{
public:
	typedef unsigned int size_type;
	size_type size() const { return size_type(m_finish - m_start); }
	void push_back(const T &value);

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ObjectModule
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual Int getUpdatePhase();

private:
	unsigned char m_unmodelled04[0x0C - 0x04];
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20();
	virtual UpdateModuleInterface *getUpdate();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UnsignedInt friend_getNextCallFrame() const { return m_nextCallFrame; }
	void friend_setNextCallFrame(UnsignedInt frame)
	{
		m_nextCallFrame = frame > UPDATE_SLEEP_FOREVER ? UPDATE_SLEEP_FOREVER : frame;
	}

	UnsignedInt m_nextCallFrame; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_phase; // +0x1C
};
typedef UpdateModule *UpdateModulePtr;

class Object
{
public:
	void appendToList(Object **pListHead, Object **pListTail);
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

private:
	unsigned char m_unmodelled000[0x244];
	BehaviorModule **m_behaviors; // +0x244
};

typedef _STL::vector<const ModuleData *> UpdateModuleVector;

// class-gate: allow GameLogic the shared GameLogicObjectLookupView.h pads over the object-list tail (+0xB0) and BFME's per-phase/sleeping update vectors (+0xC8/+0xF8) this body writes; same frame (+0x40) and list head (+0xAC) offsets
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	void addObjectToLookupTable(Object *obj);
	void registerObject(Object *obj);

private:
	unsigned char m_unmodelled00[0x40];
	UnsignedInt m_frame; // +0x40
	unsigned char m_unmodelled44[0xAC - 0x44];
	Object *m_objList; // +0xAC
	Object *m_objListTail; // +0xB0
	unsigned char m_unmodelledB4[0xC8 - 0xB4];
	UpdateModuleVector m_phaseUpdates[4]; // +0xC8
	UpdateModuleVector m_sleepingUpdates; // +0xF8
};
extern GameLogic *TheGameLogic;

// ------------------------------------------------------------------------------------------------
/** Add an object to the world: the master list, the lookup table and the update lists */
// ------------------------------------------------------------------------------------------------
void GameLogic::registerObject( Object *obj )
{

	// add to the master list
	obj->appendToList( &m_objList, &m_objListTail );

	// add object to lookup table
	addObjectToLookupTable( obj );

	UnsignedInt now = TheGameLogic->getFrame();
	if( now == 0 )
		now = 1;

	for( BehaviorModule **b = obj->getBehaviorModules(); *b; ++b )
	{
		UpdateModulePtr u = static_cast<UpdateModulePtr>( (*b)->getUpdate() );
		const ModuleData *entry = reinterpret_cast<const ModuleData *>( u );
		if( !u )
			continue;

		// it's important to set it to "now" so that it will update this frame
		if( u->friend_getNextCallFrame() == 0 )
			u->friend_setNextCallFrame( now );

		UpdateModuleVector *list;
		if( u->friend_getNextCallFrame() == UPDATE_SLEEP_FOREVER )
		{
			list = &m_sleepingUpdates;
			Int index = list->size();
			u->m_phase = -1;
			u->m_indexInLogic = index;
		}
		else
		{
			Int phase = u->getUpdatePhase();
			list = &m_phaseUpdates[ phase ];
			Int index = list->size();
			u->m_indexInLogic = index;
			u->m_phase = phase;
		}
		list->push_back( entry );
	}

}
