// cl: /O1 /MD
// ?rva006006D9@Rva0060061A@@QAEXPAX@Z @0x006006D9 158B
// Leaf between Rva0060061A dtor and Rva00600777Set: news Rva00604A5F and Rva0060453B
// into TheArchiveFileSystem and G00A06E54 then virtual A1 plus Helper v1 plus
// Archive doesFileExist shaders.big gate to BFME2PreferLocalFiles.
// Evidence: same globals and flags as Rva0060061A dtor TU, same Archive layout
// as FileSystemDoesFileExist, rowed ctors, string literal, caller 0x0022E3B7.

void *__cdecl operator new(unsigned int s);

class Rva00604A5F
{
public:
	Rva00604A5F();
	virtual ~Rva00604A5F();
};

class Rva0060453B
{
public:
	Rva0060453B();
	virtual ~Rva0060453B();
private:
	unsigned char m_pad[0x10 - 4];
};

class Rva0060061AHelper
{
public:
	virtual void *v0(int a1);
	virtual void v1(void *a1);
};

extern Rva0060061AHelper *G00A06E54;

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual void A3();
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
};

extern ArchiveFileSystem *TheArchiveFileSystem;
extern bool BFME2PreferLocalFiles;

class Rva0060061A
{
public:
	virtual ~Rva0060061A();
	void rva006006D9(void *a1);
};

void Rva0060061A::rva006006D9(void *a1)
{
	Rva00604A5F *p1 = new Rva00604A5F();
	TheArchiveFileSystem = (ArchiveFileSystem *)p1;
	Rva0060453B *p2 = new Rva0060453B();
	G00A06E54 = (Rva0060061AHelper *)p2;
	TheArchiveFileSystem->A1();
	G00A06E54->v1(a1);
	if (!TheArchiveFileSystem->doesFileExist("shaders.big"))
		BFME2PreferLocalFiles = true;
}
