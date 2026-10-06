// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0043B0EA@Rva0043B8C0@@QAE_NPAX0@Z @0x0043B0EA 90B
// Evidence: caller 0x0043B8C0 passes this plus 2 pushes ret8; TheGameLogic+0x40 frame delta unsigned fild+fadd scaled by +0x20 float compare.
class GameLogic
{
public:
	char m_pad[0x40];
	int m_frame;
};
extern GameLogic *TheGameLogic;

struct Rva0043B0EAEntry
{
	char m_pad0[0x20];
	float m_scale;
	char m_pad1[0x80 - 0x20 - 4];
	int m_frame;
};

class Rva0043B8C0
{
public:
	bool rva0043B0EA(void *a, void *b);
};

bool Rva0043B8C0::rva0043B0EA(void *a, void *b)
{
	Rva0043B0EAEntry *ea = (Rva0043B0EAEntry *)a;
	Rva0043B0EAEntry *eb = (Rva0043B0EAEntry *)b;
	int cur = TheGameLogic->m_frame;
	return (float)(unsigned)(eb->m_frame - cur) * eb->m_scale > (float)(unsigned)(ea->m_frame - cur) * ea->m_scale;
}
