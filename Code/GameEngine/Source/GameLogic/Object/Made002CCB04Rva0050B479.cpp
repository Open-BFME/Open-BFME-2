// cl: /DNDEBUG /MD
// ?rva0050B479@Made002CCB04@@QAEXPAXPAVObject@@@Z @0x0050B479 105B
// Emotion tracker forward: Made virtual slot 1 check, then GameLogic findObjectByID via global plus arg+8 fallback, then Object::rva0028ECA8 with m_128 plus (float)m_130 plus found as int. Evidence: members 0x128/0x130 in Made002CCB04Ctor, TheGameLogic plus g_Va00DFEFD8 plus findObjectByID rowed, float 0xBC26EC for unsigned conversion, callees rowed, callers in 0x0050B519.
class GameLogic;
extern GameLogic *TheGameLogic;
extern int g_Va00DFEFD8;
enum ObjectID { INVALID_ID = 0 };
class Object;
struct MadeArg
{
	char m_pad[8];
	ObjectID m_id08;
};

class Object
{
public:
	void rva0028ECA8(int index, float value, int arg);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class Made002CCB04
{
public:
	virtual ~Made002CCB04();
	virtual bool check(void *a, void *b);
	void rva0050B479(void *a, Object *b);
private:
	char m_pad[0x128 - 4];
	int m_128;
	float m_12C;
	unsigned int m_130;
};

void Made002CCB04::rva0050B479(void *a, Object *b)
{
	MadeArg *arg = (MadeArg *)a;
	if (!check(a, b))
		return;
	GameLogic *logic = TheGameLogic;
	Object *found = logic->findObjectByID((ObjectID)g_Va00DFEFD8);
	if (!found)
		found = logic->findObjectByID(arg->m_id08);
	float f = (float)m_130;
	b->rva0028ECA8(m_128, f, (int)found);
}
