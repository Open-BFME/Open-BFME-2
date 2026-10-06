// cl: /O1 /DNDEBUG /MD /EHs
// ??1BfmeNarrowRecord00427F75@@QAE@XZ retail 0x0022CCEF 59B
// Implicit-shape dtor: the member at +0x0C runs the rowed clear-then-free
// dtor 0x0022C5DA (rowed as ??1Rva00226856@@QAE@XZ), then the inline CRT
// buffer member at +0 frees its block.
extern "C" void __cdecl free(void *);

class Rva00226856
{
public:
	~Rva00226856();
private:
	void *m_header;
	int m_count;
};

struct BfmeNarrowRecord00427F75Buffer
{
	void *m_block;
	~BfmeNarrowRecord00427F75Buffer()
	{
		if (m_block)
			free(m_block);
	}
};

class BfmeNarrowRecord00427F75
{
public:
	~BfmeNarrowRecord00427F75();
private:
	BfmeNarrowRecord00427F75Buffer m_buffer; // +0x00
	char m_pad04[0x0C - 0x04];
	Rva00226856 m_tree; // +0x0C
};

BfmeNarrowRecord00427F75::~BfmeNarrowRecord00427F75()
{
}
