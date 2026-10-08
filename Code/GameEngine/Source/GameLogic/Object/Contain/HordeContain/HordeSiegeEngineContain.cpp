// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// Target evidence: HordeSiegeEngineContain ctor 0x0047D247 installs primary
// vtable 0x00C474A0; slot 8 at 0x00C474C0 points to 0x0047CB4D. That slot in
// the OpenContain and TransportContain primary tables points to 0x00464120.
// The target calls that base body, walks the list at +0x128, clears dword
// +0x274 for each stored object pointer, calls rowed GameLogic::destroyObject,
// and tail-calls the rowed int-list clear at 0x0023DAA5.
//
// Identity: BFME1 OpenContain declares primary slot 8 as onDelete(void), and
// the target vtable slot and base call support HordeSiegeEngineContain::onDelete.
// The list<int> and +0x128 offset are target constructor evidence; its values
// are object pointers stored as ints. Object+0x274 remains unnamed.
#include <list>
// stlport

class Object;
class Thing;
class ModuleData;

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

class OpenContain
{
public:
	virtual void onDelete();

private:
	unsigned char m_padding[0xFC];
};

class TransportContain : public OpenContain
{
private:
	unsigned char m_padding100[0x11C - 0x100];
};

class HordeTransportContain : public TransportContain
{
private:
	unsigned char m_padding11C[0x128 - 0x11C];
};

class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	virtual void onDelete();

private:
	_STL::list<int> m_riderObjects;
};

void HordeSiegeEngineContain::onDelete()
{
	OpenContain::onDelete();

	_STL::list<int>::iterator rider = m_riderObjects.begin();
	while (rider != m_riderObjects.end()) {
		int riderAddress = *rider;
		++rider;
		Object *object = (Object *)riderAddress;
		*(int *)((char *)object + 0x274) &= 0;
		TheGameLogic->destroyObject(object);
	}
	m_riderObjects.clear();
}

// Retail 0x0047CE0C..0x0047CEBB uses the +0x20 containment interface.
// WB 0x011AF7D0 establishes the loop, removal slot and random-force behavior;
// its class file and line 824 string agree with this unit. The slot's name
// and ignored argument remain unknown. Retail supplies the offsets below.
struct Rva0047CE0CVector
{
	float x, y, z;
	Rva0047CE0CVector(float first, float second, float third) : x(first), y(second), z(third) {}
	Rva0047CE0CVector(const Rva0047CE0CVector &other) : x(other.x), y(other.y), z(other.z) {}
};

class Rva003909FAObj
{
public:
	void consume(void *vector, int first, int second);
};

struct Rva0047CE0COwner
{
	unsigned char m_pad00[8];
	float m_directionX;
	unsigned char m_pad0C[0x18 - 0x0C];
	float m_directionY;
	unsigned char m_pad1C[0x25C - 0x1C];
	Rva003909FAObj *m_physics;
};

int GetGameLogicRandomValue(int low, int high, char *file, int line);

template <int N> class Rva0047CE0CSlots : public Rva0047CE0CSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0047CE0CSlots<0> {};

class Rva0047CE0CInterface : public Rva0047CE0CSlots<41>
{
public:
	virtual void removeRider(Object *object, bool flag) = 0;
	void removeAndApplyForce(int unused);
private:
	unsigned char m_pad04[0x108 - 4];
	_STL::list<int> m_riders;
};

void Rva0047CE0CInterface::removeAndApplyForce(int)
{
	_STL::list<int>::iterator first = m_riders.begin();
	while (first != m_riders.end()) {
		Object *rider = (Object *)*first;
		if (rider != 0) {
			removeRider(rider, false);
			Rva0047CE0COwner *owner = *(Rva0047CE0COwner **)((char *)this - 0x18);
			Rva003909FAObj *physics = owner->m_physics;
			if (physics != 0) {
				Rva0047CE0CVector direction(owner->m_directionX, owner->m_directionY, 1.0f);
				float magnitude = (float)GetGameLogicRandomValue(3, 8,
					"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeSiegeEngineContain.cpp", 824);
				direction.x *= magnitude;
				direction.y *= magnitude;
				direction.z *= magnitude;
				Rva0047CE0CVector force = direction;
				physics->consume(&force, 0, 0);
			}
		}
		first = m_riders.begin();
	}
}
