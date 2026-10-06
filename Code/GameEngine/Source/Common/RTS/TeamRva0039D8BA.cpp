// cl: /DNDEBUG /MD

// ?rva0039D8BA@Team@@QAEXPAVObject@@@Z @0x0039D8BA (18B).
// Team::rva0039D8BA(Object*): sets Team+0x5c entered flag then refreshes the
// ScriptEngine frame cache via rowed Rva002039C5Host::rva002039C5 on the
// 0xDFE16C global. Callers at 0x2920D6 and 0x2921EB pass Team from Object+0x304
// with the Object as arg. Neighbours share /O1.
extern class ScriptEngine *TheScriptEngine;

class Object;

class Rva002039C5Host
{
public:
	void rva002039C5();
};

#define TheRvaHostPtr (*(Rva002039C5Host **)&TheScriptEngine)

class Team
{
public:
	void rva0039D8BA(Object *obj);

private:
	unsigned char m_pad[0x5c];
	bool m_enteredOrExited;
};

void Team::rva0039D8BA(Object *obj)
{
	(void)obj;
	m_enteredOrExited = true;
	TheRvaHostPtr->rva002039C5();
}
