// cl: /MD
// ?rva0031F89E@Rva0031F89E@@QAEXMMHH@Z @0x0031F89E 209B unlock: draw three lists via TheDisplay float draw
// Evidence: triple list at +0x158 plus entry ints at +4 plus Image at +0x14 via rowed W3DDisplay draw 0x4D6B3 plus TheDisplay 0xDFE9D8; caller 0x31FABC; prev deleting dtor /O1 /MD next Rva0031FA40Create.
class Image;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

struct Entry
{
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	Image *m_14;
};

struct Node
{
	Node *m_next;
	Node *m_prev;
	Entry *m_data;
};

class Rva0031F89E
{
public:
	void rva0031F89E(float a, float b, int c, int d);
private:
	char m_pad[0x158];
	Node *m_lists[3];
};

void Rva0031F89E::rva0031F89E(float a, float b, int c, int d)
{
	Node **p = &m_lists[2];
	int n = 3;
	do
	{
		Node *cur = (*p)->m_next;
		while (cur != *p)
		{
			Entry *e = cur->m_data;
			if (e && e->m_14)
				((W3DDisplay *)TheDisplay)->rva0004D6B3(e->m_14,
					(float)e->m_4 * a + (float)c,
					(float)e->m_8 * b + (float)d,
					(float)(e->m_c + e->m_4) * a + (float)c,
					(float)(e->m_10 + e->m_8) * b + (float)d, -1, 2);
			cur = cur->m_next;
		}
		--p;
		--n;
	} while (n != 0);
}
