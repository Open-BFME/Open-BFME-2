// cl: /DNDEBUG /MD /EHsc
// ??1Rva001FD458@@QAE@XZ @0x001FD6F4 56B.
// Tree destructor for the Rva001FD458 node family: clears via the rowed
// rva001FD659, then the inline header-handle member dtor frees the sentinel
// via free 0x00030830 with a null guard. Same 56B clear-plus-free shape as
// the rowed ??1Rva001FD42B@@QAE@XZ 0x001FD6BC (Rva001FD42BDtor.cpp precedent:
// C++-linkage free emits retail's unwind state store; /EHsc for the stores).
// Callers at 0x001FE25F 0x002B1372 and jmp at 0x001FD863; unblocks 0x002B11A7.
// C++-linkage free (?free@@YAXPAX@Z, pinned at 0x00030830): the C++
// decoration is what makes the caller emit the unwind state store retail
// carries; same body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva001FD458Node
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD458Node *m_parent;
	Rva001FD458Node *m_left;
	Rva001FD458Node *m_right;
	unsigned char m_value[8];
};

struct Rva001FD458HeaderHandle
{
	~Rva001FD458HeaderHandle()
	{
		if (m_header)
			free(m_header);
	}
	Rva001FD458Node *m_header;
};

struct Rva001FD458
{
	void rva001FD659();
	~Rva001FD458();
	Rva001FD458HeaderHandle m_handle;
	unsigned int m_count;
};

Rva001FD458::~Rva001FD458()
{
	rva001FD659();
}
