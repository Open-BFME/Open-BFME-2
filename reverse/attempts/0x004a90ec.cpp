// ?rva004A90EC@Rva004A90EC@@QAEPAVAIStateMachine@@XZ
// partial score=0.9 date=2026-10-05
// cl: /O1 /EHsc /DNDEBUG /MD
//
// ?rva004A90EC@Rva004A90EC@@QAEPAVAIStateMachine@@XZ @0x004A90EC 63B.
// Allocates an AIStateMachine for the object at +8 with id 0x2FD27857.

class Object;

class AIStateMachine
{
public:
	AIStateMachine(Object *obj, unsigned int id);

private:
	char m_bytes[0x68];
};

class Rva004A90EC
{
public:
	AIStateMachine *rva004A90EC();

private:
	char m_pad[8];
	Object *m_obj;
};

AIStateMachine *Rva004A90EC::rva004A90EC()
{
	return new AIStateMachine(m_obj, 0x2FD27857u);
}
