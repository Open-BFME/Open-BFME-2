// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// Target evidence: SiegeEngineContain ctor 0x0047C21E installs primary vtable
// 0x00C470F8, whose slot 8 is this body. The same primary slot in OpenContain
// vtable 0x00C435E8 and TransportContain vtable 0x00C45EB8 points to
// 0x00464120. The body calls that base implementation, walks the +0x11C list,
// clears dword +0x274 on each referenced object, calls rowed
// GameLogic::destroyObject, then tail-calls the rowed int-list clear at
// 0x0023DAA5.
//
// Identity: the BFME1 OpenContain declaration names primary slot 8
// onDelete(void); the matching BFME2 slot and direct base call support
// SiegeEngineContain::onDelete. The list<int> layout is from the BFME2 ctor
// and the matched removeFromContainList sibling; payloads are pointer values
// stored as ints. Object+0x274 remains an unnamed target field.
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

class SiegeEngineContain : public TransportContain
{
public:
	virtual void onDelete();

private:
	_STL::list<int> m_riderObjects;
};

void SiegeEngineContain::onDelete()
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
