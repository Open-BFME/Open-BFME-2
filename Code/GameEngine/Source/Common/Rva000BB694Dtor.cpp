// cl: /MD /EHs
//
// ??1Rva000BB694@@QAE@XZ, retail 0x000BB694, 56 bytes.
// Non-virtual dtor of a list container holding Rva000B6498 at +0: user code
// calls rowed ?rva000B9324@Rva000B6498@@QAEXXZ on same this (no ecx reload),
// then the holder member at +0 frees the head via inlined test plus rowed
// _free 0x00030830. EH from the holder (state 0 during the call, or -1 before
// the free needs /EHs); twin 0x000BB65C calls unclaimed 0x000B92FB the same
// way. Evidence: chain from 0x000B9324 plus callers 0x000C7B56 and jmp
// 0x000BBF50 plus DisplayString dtor precedent for call plus disarm plus free.
extern "C" void __cdecl free(void *block);

class Rva000B6498
{
public:
	void rva000B9324();
private:
	void *m_head;
	int m_count;
};

struct Rva000BB694Holder
{
	char *m_p;
	~Rva000BB694Holder() { if (m_p) free(m_p); }
};

class Rva000BB694
{
public:
	~Rva000BB694();
private:
	Rva000BB694Holder m_holder;
	int m_count;
};

Rva000BB694::~Rva000BB694()
{
	((Rva000B6498 *)this)->rva000B9324();
}

class Rva000B646B
{
public:
	~Rva000B646B();
};

class Rva000BBF4B
{
public:
	void rva000BBF4B();
};

void Rva000BBF4B::rva000BBF4B()
{
	((Rva000B646B *)this)->~Rva000B646B();
}

class Rva000BBF50
{
public:
	void rva000BBF50();
};

void Rva000BBF50::rva000BBF50()
{
	((Rva000BB694 *)this)->~Rva000BB694();
}

