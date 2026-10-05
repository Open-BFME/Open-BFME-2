// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva004C9A51@EvaAnnounceClientCreate@@UAEXXZ, retail 0x004C9A51, 49 bytes:
// slot 1 of the vtable EvaAnnounceClientCreate's ctor 0x004C99D4 installs at
// +0x0C (0x00C5ED48; slot 0 is the shared no-op). Once (the +0x14 flag), sets
// the frame at +0x10 to TheGameLogic's frame (+0x40) plus the module data's
// +0x14 delay, at least 2, and never earlier than frame 7 (the at-least-2
// written as a running maximum is what gives retail's cmova under
// /arch:SSE). Compiled with the +0x0C subobject this. Names by address.
typedef unsigned int UnsignedInt;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

struct EvaAnnounceClientCreateModuleData
{
	unsigned char m_pad00[0x14];
	UnsignedInt m_delay; // +0x14
};

class ClientCreateModule
{
public:
	virtual ~ClientCreateModule();
protected:
	const EvaAnnounceClientCreateModuleData *m_moduleData; // +0x04
	void *m_drawable; // +0x08
};

class CreateModuleInterface
{
public:
	virtual void slot0();
	virtual void rva004C9A51() = 0;
};

class EvaAnnounceClientCreate : public ClientCreateModule, public CreateModuleInterface
{
public:
	virtual void rva004C9A51();
private:
	UnsignedInt m_10; // +0x10
	bool m_14; // +0x14
};

void EvaAnnounceClientCreate::rva004C9A51()
{
	if (m_14)
		return;
	m_14 = true;
	UnsignedInt delay = 2;
	if (m_moduleData->m_delay > delay)
		delay = m_moduleData->m_delay;
	m_10 = delay + TheGameLogic->getFrame();
	if (m_10 < 7)
		m_10 = 7;
}
