// cl: /DNDEBUG /MD /EHsc
// ??1Rva002B5558@@QAE@XZ @0x002B609F 56B.
// List destructor for the Rva002B5558 family: clears via the rowed
// rva002B5558, then the inline head-handle member dtor frees the sentinel
// via the rowed free 0x00030830 with a null guard. Same 56B clear-plus-free
// shape as the rowed ??1Rva001FD42B@@QAE@XZ 0x001FD6BC; the inline member
// dtor needs unwind across the clear, giving the __EH_prolog frame.
// Callers at 0x002B70A1 and jmp at 0x002B64B8; unblocks 0x002B707E.
// C++-linkage free (?free@@YAXPAX@Z, pinned at 0x00030830): the C++
// decoration is what makes the caller emit the unwind state store retail
// carries; same body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Node002B43BA
{
	char m_pad[8];
	Node002B43BA *m_next8;
	Node002B43BA *m_childC;
};

struct Head002B5558
{
	int m_pad0;
	Node002B43BA *m_node4;
	Head002B5558 *m_next8;
	Head002B5558 *m_prevC;
};

struct Rva002B5558HeadHandle
{
	~Rva002B5558HeadHandle()
	{
		if (m_header)
			free(m_header);
	}
	Head002B5558 *m_header;
};

class Rva002B5558
{
public:
	void rva002B5558();
	~Rva002B5558();
private:
	Rva002B5558HeadHandle m_handle;
	int m_count;
};

Rva002B5558::~Rva002B5558()
{
	rva002B5558();
}

// Two more list destructors of the same 56-byte shape, byte-identical to
// ??1Rva002B5558 except for the clear they call: the rowed clears of the
// Rva002B54F9 and Rva002B5522 lists (0x002B54F9 / 0x002B5522, each 41 bytes,
// like 0x002B5558). The owners keep their address tokens.

// ??1Rva002B54F9@@QAE@XZ @0x002B5FF1 56B.
class Rva002B54F9
{
public:
	void rva002B54F9();
	~Rva002B54F9();
private:
	Rva002B5558HeadHandle m_handle;
	int m_count;
};

Rva002B54F9::~Rva002B54F9()
{
	rva002B54F9();
}

// ??1Rva002B5522@@QAE@XZ @0x002B602E 56B.
class Rva002B5522
{
public:
	void rva002B5522();
	~Rva002B5522();
private:
	Rva002B5558HeadHandle m_handle;
	int m_count;
};

Rva002B5522::~Rva002B5522()
{
	rva002B5522();
}

class Rva002B64B8
{
public:
	void rva002B64B8();
};

void Rva002B64B8::rva002B64B8()
{
	((Rva002B5558 *)this)->~Rva002B5558();
}

class Rva002B64BD
{
public:
	void rva002B64BD();
};

void Rva002B64BD::rva002B64BD()
{
	((Rva002B54F9 *)this)->~Rva002B54F9();
}

class Rva002B64C2
{
public:
	void rva002B64C2();
};

void Rva002B64C2::rva002B64C2()
{
	((Rva002B5522 *)this)->~Rva002B5522();
}

