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

class Object
{
public:
	void rva00298979(Object *source, bool wasSelected);
};

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
public:
	virtual void onContaining(Object *rider, bool wasSelected);

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

// Target evidence: SiegeEngineContain's constructor installs vtable 0x00C46F80
// at full-object +0x20; entry 66 at 0x00C47088 is 0x0047BEF8. The same body is
// present at entry 83 of vtable 0x00C47834 installed at +0xFC. In the +0x20
// view, the list head at +0xFC is the constructor's list<int> at full-object
// +0x11C. Retail walks it backwards, calls Object::rva00298979 on each stored
// receiver with the incoming Object and selection flag, then calls the base
// routine at 0x00463191 with both arguments.
//
// Identity evidence: the vtable entries and the BFME1 donor signature support
// SiegeEngineContain::onContaining(Object *, Bool), whose donor implementation
// forwards to TransportContain::onContaining. The target body remains
// address-labelled because its entry uses the +0x20 subobject this-view. The
// partial class below starts at that view; its +0xFC field is the proven full
// object +0x11C list. The node word is used as an Object receiver by the target
// call, while its semantic type remains inferred from the existing list<int>
// declaration.
struct Rva0047BEF8Node
{
	Rva0047BEF8Node *m_next;
	Rva0047BEF8Node *m_previous;
	int m_value;
};

class __declspec(novtable) Rva0047BEF8
{
public:
	virtual void rva0047BEF8(Object *rider, bool wasSelected);

private:
	unsigned char m_pad04[0xFC - 4];
	Rva0047BEF8Node *m_headFC;
};

void Rva0047BEF8::rva0047BEF8(Object *rider, bool wasSelected)
{
	Rva0047BEF8Node *current = m_headFC;
	if (current != current->m_next) {
		do {
		Rva0047BEF8Node *previous = current->m_previous;
			Object *receiver = (Object *)previous->m_value;
			if (wasSelected) {
				receiver->rva00298979(rider, true);
			} else {
				receiver->rva00298979(rider, false);
			}
			current = current->m_previous;
		} while (current != m_headFC->m_next);
	}

	((TransportContain *)this)->TransportContain::onContaining(rider, wasSelected);
}
