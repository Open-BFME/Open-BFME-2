// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??1Rva00328CF8@@QAE@XZ, retail 0x00328CF8, 82 bytes.
// Non-virtual MI dtor over two holder bases with inlined base dtors: each base
// stores global plus rowed handle call. Secondary at +0x0c via null-safe.
// Chain from deleting dtor 0x00328CDC plus rowed handle 0x00306D7B plus
// global 0x00BC9574.
// Evidence: EH prolog plus neg sbb and plus two handle calls plus ret.
class Q1Forwardee0000871A
{
public:
	void handle(int node);
};

extern int g_00BC9574;

struct Base00328CF8A
{
	void *m_head;
	Q1Forwardee0000871A *m_fw;
	int m_node;
	~Base00328CF8A()
	{
		m_head = &g_00BC9574;
		m_fw->handle(m_node);
	}
};

struct Base00328CF8B
{
	void *m_head;
	Q1Forwardee0000871A *m_fw;
	int m_node;
	~Base00328CF8B()
	{
		m_head = &g_00BC9574;
		m_fw->handle(m_node);
	}
};

class Rva00328CF8 : public Base00328CF8A, public Base00328CF8B
{
public:
	~Rva00328CF8();
};

Rva00328CF8::~Rva00328CF8()
{
}
