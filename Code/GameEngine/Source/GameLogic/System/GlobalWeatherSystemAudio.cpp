// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /DNDEBUG
// ?rva003184B8@Rva003184B8@@QAEXXZ @ 0x003184B8 (119B). Unlock: TheAudio removeAudioEvent on +0x14 then array +0x30 stride 8 indexed by +0x10 then handle=1 then BfmeAudioEventPrefix136 from entry with 0 then addAudioEvent slot 0x64 storing handle. Evidence: callees BfmeAudioEventPrefix136 ctor 0x002D97D6 and BfmeStringTailRecord144 dtor 0x002D9A43 rowed plus TheAudio 0x009FE6E8 plus AudioManager slots 0x64/0x6c matching Rva00358A53Audio and Rva0030D606; callers 0x00318711 0x003187A3; neighbours GlobalWeatherSystem parseWeatherData and Rva0028C6FB.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva003184B8AudioView
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
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *);
	virtual void slot26();
	virtual void removeAudioEvent(int handle);
};

struct Rva003184B8Entry
{
	OpaqueRefElement4 ref;
	int pad04;
};

class Rva003184B8
{
public:
	void rva003184B8();
private:
	char m_pad00[0x10];
	int m_index10;
	int m_handle14;
	char m_pad18[0x10];
	int m_28;
	int m_2C;
	Rva003184B8Entry m_entries30[5];
};

void Rva003184B8::rva003184B8()
{
	reinterpret_cast<Rva003184B8AudioView *>(TheAudio)->removeAudioEvent(m_handle14);
	Rva003184B8Entry *entry = &m_entries30[m_index10];
	m_handle14 = 1;
	if (entry->ref.referent != 0) {
		BfmeAudioEventPrefix136 evt(entry->ref, 0);
		m_handle14 = reinterpret_cast<Rva003184B8AudioView *>(TheAudio)->addAudioEvent(&evt);
	}
}
