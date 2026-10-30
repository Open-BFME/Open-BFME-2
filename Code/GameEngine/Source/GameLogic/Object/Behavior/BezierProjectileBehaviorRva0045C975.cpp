// cl: /O1 /G7 /arch:SSE /GX /DNDEBUG /MD
//
// (281 B, RET4, the int argument unused): the projectile's landing. Between the
// rowed deleting destructor 0x0045C959 and xfer 0x0045CA8E, on the module's
// layout (module data +4, object +8, path vector +0x44, counters +0x28/+0x70/
// +0x78, list +0x7C as xfer and the BFME 1 Bezier bodies establish).
// Target facts: the layer for the position 10 above the object
// (getLayerForDestination) is set on the object (0x0028B4CE), the object is
// put on that layer's height (TheTerrainLogic slot 7), the path and counters
// are cleared, model-condition bits 0x9A/0x9B are applied (0x001E4912 ->
// 0x001E42F2), a data flag at +0x19 marks status bit 0x4000000 (0x0028AE6D)
// and kills the object (DamageType 8), status 5 is cleared, and the AI gets
// command 0x0045003E with the data's +0x38 value, or idles, from source 2.
// Method and field names are address- or role-derived.
// WB 0x1183230 (inlined into its BitFlags<591>::SetBit slot) gives the statement
// shape: Object::setModelConditionState(122) as an early-return test/set on the
// model-condition words at +0x10C followed by the notifier, and the AI command
// block re-reading getAI() and the data command in each arm; that shape gives
// retail's register assignment and the [esi+0x118] memory operands.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
enum PathfindLayerEnum { LAYER_INVALID = -1 };
enum DamageType { DAMAGE_TYPE_8 = 8 };
enum DeathType { DEATH_TYPE_0 = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_5 = 5 };
enum CommandSourceType { COMMAND_SOURCE_2 = 2 };

class Object;

class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual float getGroundHeight(float x, float y, Coord3D *normal);
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, Coord3D *normal, bool clip);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *coord);
};
extern TerrainLogic *TheTerrainLogic;

#include "../../../Common/Thing/thing.h"

class AICommandInterface
{
public:
	void rva0045003E(int v, CommandSourceType src);
	void aiIdle(CommandSourceType src);
};
struct ObjectAI
{
	char m_pad[0x20];
	AICommandInterface m_ai; // +0x20
};

class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int a, unsigned int b, unsigned int c);
	unsigned m_bits[19];
};
class Rva001E42F2
{
public:
	void rva001E42F2(const int *p);
};

struct CondBits { unsigned words[4];
 unsigned test(int bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 void set(int bit) { words[bit>>5] |= 1U<<(bit&31); } };
class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos38; }
	ObjectAI *getAI() const { return m_ai258; }
	// Model condition 122 (+0x118 bit 26), notifying through 0x0028AE6D.
	__forceinline void setModelConditionState122()
	{
		if (m_cond.test(122))
			return;
		m_cond.set(122);
		rva0028AE6D();
	}
	void setLayer(PathfindLayerEnum layer);
	void rva0028AE6D();
	void kill(DamageType damage, DeathType death);
	void setStatus(ObjectStatusTypes status, bool flag);

	char m_pad0[0x38];
	Coord3D m_pos38; // +0x38
	char m_pad44[0x10c - 0x44];
	CondBits m_cond;
	char m_pad11C[0x258 - 0x11C];
	ObjectAI *m_ai258; // +0x258
};

struct Gen_p12pod
{
	int a[3];
};
namespace _STL
{
template <class T> class allocator {};
template <class T, class A = allocator<T> >
class vector
{
public:
	T *erase(T *first, T *last);
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
private:
	void *m_head; // +0x00
};

struct BezierModuleData
{
	char m_pad[0x19];
	bool m_flag19; // +0x19
	char m_pad1A[0x38 - 0x1A];
	unsigned int m_finalStuckTime; // +0x38
};

class BezierProjectileBehavior
{
public:
	void rva0045C975(int unused);
private:
	void *m_vtbl;
	const BezierModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x28 - 0x0C];
	int m_id28; // +0x28
	char m_pad2C[0x44 - 0x2C];
	_STL::vector<Gen_p12pod> m_path; // +0x44
	char m_pad50[0x70 - 0x50];
	int m_int70; // +0x70
	int m_pad74;
	int m_int78; // +0x78
	Rva0029FB3BMember m_list7C; // +0x7C
};

void BezierProjectileBehavior::rva0045C975(int)
{
	Object *obj = m_object;
	Coord3D pos;
	pos.x = obj->getPosition()->x;
	pos.y = obj->getPosition()->y;
	pos.z = obj->getPosition()->z + 10.0f;
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &pos);
	obj->setLayer(layer);
	pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
	((Thing *)obj)->setPosition(&pos);

	_STL::vector<Gen_p12pod> &path = m_path;
	path.erase(path.begin(), path.end());
	m_int70 = 0;
	m_int78 = 0;
	m_id28 = 0;
	m_list7C.reset();

	Rva001E4912 bits;
	((Rva001E42F2 *)obj)->rva001E42F2((const int *)bits.rva001E4912(0, 0x9a, 0x9b));

	const BezierModuleData *bezierModuleData = m_moduleData;
	if (bezierModuleData->m_flag19)
	{
		obj->setModelConditionState122();
		obj->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
	}
	obj->setStatus(OBJECT_STATUS_5, false);

	if (bezierModuleData->m_finalStuckTime > 0)
	{
		if (obj->getAI())
			obj->getAI()->m_ai.rva0045003E(bezierModuleData->m_finalStuckTime, COMMAND_SOURCE_2);
	}
	else if (obj->getAI())
	{
		obj->getAI()->m_ai.aiIdle(COMMAND_SOURCE_2);
	}
}
