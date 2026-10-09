// cl: /DNDEBUG /MD /EHsc
// ?swap@ModuleTagString@@QAEXAAV1@@Z
// Retail 0x006D0F50..0x006D1082 (306 bytes).
// Swaps two small-buffer containers of counted handles: count +0 and
// capacity +4 trade places; the data pointer +8 is exchanged except that a
// container using its own two-slot inline buffer (+0xC) is pointed back at
// the other side's inline buffer; when either side was inline the two
// inline buffers are exchanged through a two-handle temporary with the rowed
// range copy 0x006D0460.
// Evidence (target): same shape as the matched Rva00895050 inline-container
// swap at 0x006D0040 (Rva00895050InlineContainerSwap.cpp) with 4-byte
// handle elements: the EH vector constructor iterator builds the temporary
// with the shared zeroing element constructor at 0x00013260 and the rowed
// element destructor 0x000A9DF3 (as in the rowed ModuleTagString destructor
// 0x006CE7F0 which destroys the same +0xC two-element array); the second
// temporary slot is reset by assigning an empty handle whose release path
// is inlined (pinned teardown 0x006D0280 then g_pChainBlockAllocator
// freeBlock 0x006DB270 of 0x1C bytes as in Rva006D0460Copy). The only
// caller (0x006D1C4D) swaps the object with a freshly built empty
// container and then destroys that container through 0x006CE7F0
// (clear-by-swap), which is why the method is called swap here.
class BfmeRefVGO;
BfmeRefVGO *__cdecl Rva006D0460Copy(BfmeRefVGO *first, BfmeRefVGO *last, BfmeRefVGO *result);

class Rva006D0280
{
public:
	~Rva006D0280();
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int size);
};
extern Rva006DB270 *g_pChainBlockAllocator;

class Rva006D0F50Handle
{
public:
	Rva006D0F50Handle() : m_count(0) {}
	~Rva006D0F50Handle() { release(); }
	Rva006D0F50Handle &operator=(const Rva006D0F50Handle &other)
	{
		release();
		m_count = other.m_count;
		if (m_count)
			++*m_count;
		return *this;
	}
private:
	void release()
	{
		if (m_count)
		{
			unsigned int *p = m_count;
			--*p;
			if (*p == 0)
			{
				Rva006D0280 *owner = (Rva006D0280 *)m_count;
				owner->~Rva006D0280();
				g_pChainBlockAllocator->freeBlock(owner, 0x1C);
			}
		}
	}
	unsigned int *m_count;
};

struct Rva004A9DF3Element : public Rva006D0F50Handle
{
	Rva004A9DF3Element();
	~Rva004A9DF3Element();
};

class ModuleTagString
{
public:
	void swap(ModuleTagString &other);
private:
	unsigned int m_count;              // +0x00
	unsigned int m_capacity;           // +0x04
	Rva004A9DF3Element *m_data;        // +0x08
	Rva004A9DF3Element m_inline[2];    // +0x0C
};

void ModuleTagString::swap(ModuleTagString &other)
{
	unsigned int count = other.m_count;
	other.m_count = m_count;
	m_count = count;
	unsigned int capacity = other.m_capacity;
	other.m_capacity = m_capacity;
	Rva004A9DF3Element *data = m_data;
	bool thisInline = data == m_inline;
	m_capacity = capacity;
	bool otherInline = other.m_data == other.m_inline;
	if (otherInline)
		m_data = m_inline;
	else
		m_data = other.m_data;
	if (thisInline)
		other.m_data = other.m_inline;
	else
		other.m_data = data;
	if (!otherInline && !thisInline)
		return;
	Rva004A9DF3Element temporary[2];
	static_cast<Rva006D0F50Handle &>(temporary[1]) = Rva006D0F50Handle();
	Rva006D0460Copy((BfmeRefVGO *)m_inline, (BfmeRefVGO *)(m_inline + 2), (BfmeRefVGO *)temporary);
	Rva006D0460Copy((BfmeRefVGO *)other.m_inline, (BfmeRefVGO *)(other.m_inline + 2), (BfmeRefVGO *)m_inline);
	Rva006D0460Copy((BfmeRefVGO *)temporary, (BfmeRefVGO *)(temporary + 2), (BfmeRefVGO *)other.m_inline);
}
