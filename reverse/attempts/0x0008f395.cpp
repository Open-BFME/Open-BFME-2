// ?rva0008F395@Rva0008F395@@UAEXXZ
// partial score=0.95 date=2026-10-07
// ?rva0008F395@Rva0008F395@@UAEXXZ
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc

class Mouse
{
public:
	char m_padToPosition[0x4F0C];
	int m_x;
	int m_y;
};

class Display
{
public:
	void rva0008EE9E(float, float, float, float, float, int, int);
	void rva0008EEF0(float, float, float, float, float, int);
};

extern Mouse *TheMouse;
extern Display *TheDisplay;

struct Rva0008F395Node
{
	Rva0008F395Node *next;
	int unused;
	int x;
	int y;
};

// ?rva0008F395@Rva0008F395@@UAEXXZ @0x0008F395 249B
// Target evidence: central table slot 120 at 0x007C7A88; rowed display
// drawing methods and TheMouse/TheDisplay globals. Class and linked-list
// semantics are address-derived structural inference from target offsets.
class Rva0008F395
{
public:
	virtual void rva0008F395();

private:
	char m_padToRect[0x2C - 4];
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
	char m_padToList[0x910 - 0x3C];
	Rva0008F395Node *m_list;
	char m_padToEnabled[0x924 - 0x914];
	unsigned char m_enabled;
};

void Rva0008F395::rva0008F395()
{
	if (m_enabled != 0)
	{
		Rva0008F395Node *node = m_list->next;
		while (node != m_list)
		{
			int startY = node->y;
			int startX = node->x;
			node = node->next;
			int endX;
			int endY;
			if (node == m_list)
			{
				endX = TheMouse->m_x;
				endY = TheMouse->m_y;
			}
			else
			{
				endX = node->x;
				endY = node->y;
			}
			TheDisplay->rva0008EE9E((float)startX, (float)startY,
				(float)endX, (float)endY, 2.0f, 0xBBFFBB33, 0xBBFFBB33);
		}
	}
	else
	{
		float left = (float)m_left;
		float top = (float)m_top;
		float width = (float)(m_right - m_left);
		float height = (float)(m_bottom - m_top);
		TheDisplay->rva0008EEF0(left, top, width, height, 2.0f, 0xBBFFBB33);
	}
}
