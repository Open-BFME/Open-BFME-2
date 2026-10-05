// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
//
// ?rva0048C7BF@Rva0048C7BF@@QAEXXZ @0x0048C7BF 96B.
// Builds an audio event from the ref at [this+4]+0x18 and the id at
// [this+8]+0x74, hands it to TheAudio slot 0x64, and stores the result at +0x34.

#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva0048C7BFAudio
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
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *evt);
};

struct Rva0048C7BFRef
{
	char m_pad[0x18];
	OpaqueRefElement4 m_ref;
};

struct Rva0048C7BFId
{
	char m_pad[0x74];
	ObjectID m_id;
};

class Rva0048C7BF
{
public:
	void rva0048C7BF();

private:
	char m_pad[4];
	Rva0048C7BFRef *m_ref;
	Rva0048C7BFId *m_id;
	char m_padC[0x34 - 0x0C];
	int m_result;
};

void Rva0048C7BF::rva0048C7BF()
{
	Rva0048C7BFRef *ref = m_ref;
	Rva0048C7BFId *id = m_id;
	BfmeAudioEventPrefix136 evt(ref->m_ref, id->m_id);
	m_result = reinterpret_cast<Rva0048C7BFAudio *>(TheAudio)->addAudioEvent(&evt);
}
