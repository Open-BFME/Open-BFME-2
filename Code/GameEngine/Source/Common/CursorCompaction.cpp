// cl: /MD
//
// Wave-3 F47 shape family: cursor-compaction wrappers. Each body loads the
// +0x4 cursor, and when (char*)p + K differs calls a pinned cdecl helper
// with (dst, cursor, p, tag) (observed `lea edx,[ebp+0xB]` is the empty tag
// address), then subtracts K from the cursor and returns p. Recipe is the
// rowed tail-record shift 0x000554A9: `char *base` first, member-loaded
// cursor, empty tag struct, plain /O1 /MD. Identities beyond these shapes
// are not recovered.
//

struct Rva004ED3A2Tag {};
void rva005B09D8(char *dst, char *cur, void *p, const Rva004ED3A2Tag &tag);

class Rva004ED3A2
{
public:
	void *rva004ED3A2(void *p);
private:
	char m_00[4];
	char *m_cursor;
};

void *Rva004ED3A2::rva004ED3A2(void *p)
{
	char *base = (char *)p;
	char *last = m_cursor;
	if ((void *)(base + 0x14) != (void *)last) {
		Rva004ED3A2Tag tag;
		rva005B09D8(base + 0x14, last, p, tag);
	}
	m_cursor -= 0x14;
	return p;
}

struct Rva005412E2Tag {};
void rva00541214(char *dst, char *cur, void *p, const Rva005412E2Tag &tag);

class Rva005412E2
{
public:
	void *rva005412E2(void *p);
private:
	char m_00[4];
	char *m_cursor;
};


struct Rva00541311Tag {};
void rva00541231(char *dst, char *cur, void *p, const Rva00541311Tag &tag);

class Rva00541311
{
public:
	void *rva00541311(void *p);
private:
	char m_00[4];
	char *m_cursor;
};

void *Rva00541311::rva00541311(void *p)
{
	char *base = (char *)p;
	char *last = m_cursor;
	if ((void *)(base + 0x14) != (void *)last) {
		Rva00541311Tag tag;
		rva00541231(base + 0x14, last, p, tag);
	}
	m_cursor -= 0x14;
	return p;
}
