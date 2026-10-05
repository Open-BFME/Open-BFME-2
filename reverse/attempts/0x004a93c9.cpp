// ?rva004A93C9@Rva004A93C9@@QAEPAVAIStateMachine@@XZ
// partial score=0.9 date=2026-10-05
// cl: /O1 /EHsc /DNDEBUG /MD
//
// ?rva004A93C9@Rva004A93C9@@QAEPAVAIStateMachine@@XZ @0x004A93C9 63B.
// Allocates an AIStateMachine for the object at +8 with id 0x11224BB7.

class Object;

class AIStateMachine
{
public:
	AIStateMachine(Object *obj, unsigned int id);

private:
	char m_bytes[0x68];
};

class Rva004A93C9
{
public:
	AIStateMachine *rva004A93C9();

private:
	char m_pad[8];
	Object *m_obj;
};

AIStateMachine *Rva004A93C9::rva004A93C9()
{
	return new AIStateMachine(m_obj, 0x11224BB7u);
}
