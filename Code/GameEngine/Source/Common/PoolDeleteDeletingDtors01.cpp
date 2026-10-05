// cl: /O2 /MD
// Scalar deleting destructors with a sized release through the chain-block
// pool at 0x00E176E8 (Rva006DB270::freeBlock 0x006DB270), same 35B shape and
// recipe as Rva006CBF40Siblings.cpp: call the complete dtor, test the delete
// flag, then push sizeof(class) and this into the pool's freeBlock. None has a
// direct data or call reference in retail except 0x006DE320, which fills slot
// 14 of the vftables 0x00CEB19C and 0x00CEB1D8 (two classes ICF folded into
// one body), so its name is a view name.
// Target facts: the wrapper bytes, the REL32 dtor callee at +4 and the pushed
// size. The complete dtors are already rowed under the names declared here
// (ModuleInfoNuggetDestructor.cpp, Rva006DE350Dtor.cpp, Rva006FBDB0Dtor.cpp);
// this unit declares them without defining them. Layouts are opaque padding to
// the pushed size, not recovered members.
//  0x006CFA80 via dtor 0x006CFA30, size 0x18
//  0x006DE320 via base dtor 0x006DE350 (empty inline derived dtor), size 0x08
//  0x006FE330 via dtor 0x006FBDB0, size 0x0C

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator;   // 0x00E176E8

class Rva006CFA30
{
public:
	class Members
	{
	public:
		~Members();
		static void operator delete(void *p, unsigned int size)
		{
			g_pChainBlockAllocator->freeBlock(p, size);
		}
	private:
		char m_unknown[0x18];
	};
};

class Rva006DE350
{
public:
	virtual ~Rva006DE350();
};

class Rva006DE320 : public Rva006DE350
{
public:
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
private:
	char m_unknown[4];
};

class Rva006FBDB0
{
public:
	~Rva006FBDB0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocator->freeBlock(p, size);
	}
private:
	char m_unknown[0x0C];
};

void Rva006CFA30Members_DeleteAnchor(Rva006CFA30::Members *p) { delete p; }
void Rva006DE320_CtorAnchor(Rva006DE320 *p) { p->Rva006DE320::Rva006DE320(); }
void Rva006FBDB0_DeleteAnchor(Rva006FBDB0 *p) { delete p; }
