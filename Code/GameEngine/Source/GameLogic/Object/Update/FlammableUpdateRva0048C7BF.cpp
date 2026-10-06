// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva0048C7BF@FlammableUpdate@@QAEXXZ @0x0048C7BF 96B
// Evidence: rowed ??0BfmeAudioEventPrefix136 ObjectID overload 0x002DA461 plus rowed ??1BfmeStringTailRecord144 0x002D9A43 plus TheAudio 0x009FE6E8 slot 0x64 addAudioEvent storing handle to +0x34; neighbours FlammableUpdate rva0048C771 and FlammableUpdate layout with m_34 audio handle.
#include "Common/BfmeAudioEventPrefix136.h"

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad00[0x74];
	ObjectID m_id74;
};

struct FlammableUpdateModuleData
{
	char m_pad00[0x18];
	OpaqueRefElement4 m_ref18;
};

class AudioManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
};

extern AudioManager *TheAudio;

class FlammableUpdate
{
public:
	void rva0048C7BF();
private:
	const void *m_vtable;
	const FlammableUpdateModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x34 - 0x0C];
	int m_handle34;
};

void FlammableUpdate::rva0048C7BF()
{
	const FlammableUpdateModuleData *md = m_moduleData;
	Object *obj = m_object;
	BfmeAudioEventPrefix136 evt(md->m_ref18, obj->m_id74);
	m_handle34 = TheAudio->addAudioEvent(&evt);
}
