// cl: /O1 /MD
// ?rva000554A9@Rva000554A9@@QAEPAXPAX@Z 0x000554A9 61B tail-record shift with copy dispatch
// Evidence: callers at 0x0005FA02 and 0x00060C0B; uses CopyDispatch 0x00054E23 and dtor pin ??1BfmeStringTailRecord144@@QAE@XZ at 0x00050FC4; +0x90 stride matches 144B record.

struct RvaCopyIteratorTag {};
extern "C" void *Rva00054E23CopyDispatch(void *first, void *last, void *result, const RvaCopyIteratorTag &tag);

struct BfmeStringTailRecord144 {
	~BfmeStringTailRecord144();
};

class Rva000554A9 {
public:
	void *rva000554A9(void *arg);
	char m_00[4];
	BfmeStringTailRecord144 *m_04;
};

void *Rva000554A9::rva000554A9(void *arg)
{
	char *base = (char *)arg;
	BfmeStringTailRecord144 *last = m_04;
	if ((void *)(base + 0x90) != (void *)last) {
		RvaCopyIteratorTag tag;
		Rva00054E23CopyDispatch(base + 0x90, last, arg, tag);
	}
	m_04 = (BfmeStringTailRecord144 *)((char *)m_04 - 0x90);
	m_04->~BfmeStringTailRecord144();
	return arg;
}
