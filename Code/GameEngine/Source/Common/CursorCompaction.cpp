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

struct FalseType {};
void rva005B09D8(char *dst, char *cur, void *p, const FalseType &tag);

class Rva004ED3A2
{
public:
	void *rva004ED3A2(void *position);
private:
	char m_00[4];
	char *m_cursor;
};

void *Rva004ED3A2::rva004ED3A2(void *position)
{
	char *base = (char *)position;
	char *last = m_cursor;
	if ((void *)(base + 0x14) != (void *)last) {
		FalseType tag;
		rva005B09D8(base + 0x14, last, position, tag);
	}
	m_cursor -= 0x14;
	return position;
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
	void *erase(void *position);
private:
	char m_00[4];
	char *m_cursor;
};

void *Rva00541311::erase(void *position)
{
	char *base = (char *)position;
	char *last = m_cursor;
	if ((void *)(base + 0x14) != (void *)last) {
		Rva00541311Tag tag;
		rva00541231(base + 0x14, last, position, tag);
	}
	m_cursor -= 0x14;
	return position;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x005B09D8 reads ??$__copy_ptrs@PAURva005B09D8Record@@PAU1@@_STL@@YAPAURva005B09D8Record@@PAU1@00ABU__false_type@0@@Z
#pragma comment(linker, "/alternatename:?rva005B09D8@@YAXPAD0PAXABUFalseType@@@Z=??$__copy_ptrs@PAURva005B09D8Record@@PAU1@@_STL@@YAPAURva005B09D8Record@@PAU1@00ABU__false_type@0@@Z")
//   0x00541231 reads ??$__copy_ptrs@PAVRva0054103E@@PAV1@@_STL@@YAPAVRva0054103E@@PAV1@00ABU__false_type@0@@Z
#pragma comment(linker, "/alternatename:?rva00541231@@YAXPAD0PAXABURva00541311Tag@@@Z=??$__copy_ptrs@PAVRva0054103E@@PAV1@@_STL@@YAPAVRva0054103E@@PAV1@00ABU__false_type@0@@Z")
