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
