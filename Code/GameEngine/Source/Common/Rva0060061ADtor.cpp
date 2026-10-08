// cl: /MD
// ??1Rva0060061A@@UAE@XZ @0x0060061A 75B. Virtual dtor: stores vtable 0x0087A660
// then frees globals 0x00A06E5C and 0x00A06E54 via virtual slot0 with arg 0
// plus operator delete and nulls them. Evidence: same vtable as prev
// Rva00600611VTableInstall init; same globals as sibling Rva00600676Get;
// caller 0x006006BD is the ??_G deleting dtor calling this.
class Rva0060061AHelper
{
public:
	virtual void *v0(int a1);
};

extern class ArchiveFileSystem *TheArchiveFileSystem;
extern class LocalFileSystem *TheLocalFileSystem;

void operator delete(void *p);

class Rva0060061A
{
public:
	Rva0060061A();
	virtual ~Rva0060061A();
};

// ??0Rva0060061A@@QAE@XZ @0x00600611 9B, just ahead of the dtor: installs the
// same one-slot vtable 0x0087A660 and returns this (the empty ctor).
Rva0060061A::Rva0060061A()
{
}

Rva0060061A::~Rva0060061A()
{
	Rva0060061AHelper *p1 = (*(Rva0060061AHelper **)&TheArchiveFileSystem);
	void *q1 = p1 ? p1->v0(0) : 0;
	::operator delete(q1);
	(*(Rva0060061AHelper **)&TheArchiveFileSystem) = 0;
	Rva0060061AHelper *p2 = (*(Rva0060061AHelper **)&TheLocalFileSystem);
	void *q2 = p2 ? p2->v0(0) : 0;
	::operator delete(q2);
	(*(Rva0060061AHelper **)&TheLocalFileSystem) = 0;
}
// ?G00A06E54@@3PAVRva0060061AHelper@@A: the global at VA 0xe06e54 is ?TheLocalFileSystem@@3PAVLocalFileSystem@@A.
#pragma comment(linker, "/alternatename:?G00A06E54@@3PAVRva0060061AHelper@@A=?TheLocalFileSystem@@3PAVLocalFileSystem@@A")
