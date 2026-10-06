// cl: /DNDEBUG /MD /EHsc
// ??1Rva001FD42B@@QAE@XZ @0x001FD6BC 56B.
// Tree destructor for the Rva001FD42B node family: clears via the rowed
// rva001FD630, then the inline header-handle member dtor frees the sentinel
// via the rowed free 0x00030830 with a null guard. Same 56B clear-plus-free
// shape as the rowed ??1AnimationSoundTree@@QAE@XZ 0x004CA653; the inline
// member dtor needs unwind across the clear, giving the __EH_prolog frame.
// Callers at 0x001FE27D 0x002B13AE and jmp at 0x001FD85E; unblocks 0x002B11A7.
// C++-linkage free (?free@@YAXPAX@Z, pinned at 0x00030830): the C++
// decoration is what makes the caller emit the unwind state store retail
// carries (pin note); same body as the extern C _free at that address.
extern "C" void __cdecl free(void *block) throw(...);

struct Rva001FD42BNode
{
	unsigned char m_color;
	unsigned char m_pad01[3];
	Rva001FD42BNode *m_parent;
	Rva001FD42BNode *m_left;
	Rva001FD42BNode *m_right;
	unsigned char m_value[8];
};

struct Rva001FD42BHeaderHandle
{
	~Rva001FD42BHeaderHandle()
	{
		if (m_header)
			free(m_header);
	}
	Rva001FD42BNode *m_header;
};

struct Rva001FD42B
{
	void rva001FD630();
	~Rva001FD42B();
	Rva001FD42BHeaderHandle m_handle;
	unsigned int m_count;
};

Rva001FD42B::~Rva001FD42B()
{
	rva001FD630();
}
