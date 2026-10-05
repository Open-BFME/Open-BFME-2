// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG
//
// ?rva004891DE@Rva004891DE@@QAEXPAURva004891DEArg@@H@Z @0x004891DE 120B ret 8.
// When the ref at arg+4 is live, slot 0x60 runs, an event is built with
// integer 0, the second argument is applied, and TheAudio slot 0x64 stores +0x24.

#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;

class Rva004891DEAudio
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

class Rva002D9531
{
public:
	void rva002D9531(int value);
};

struct Rva004891DEArg
{
	char m_pad[4];
	OpaqueRefElement4 m_ref;
};

class Rva004891DE
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	void rva004891DE(Rva004891DEArg *arg, int value);
	char m_pad[0x20];
	int m_24;
};

void Rva004891DE::rva004891DE(Rva004891DEArg *arg, int value)
{
	if (arg->m_ref.referent == 0)
		return;
	s24();
	BfmeAudioEventPrefix136 evt(arg->m_ref, 0);
	((Rva002D9531 *)&evt)->rva002D9531(value);
	m_24 = reinterpret_cast<Rva004891DEAudio *>(TheAudio)->addAudioEvent(&evt);
}
