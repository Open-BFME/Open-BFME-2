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

extern Rva0060061AHelper *G00A06E5C;
extern Rva0060061AHelper *G00A06E54;

void operator delete(void *p);

class Rva0060061A
{
public:
	virtual ~Rva0060061A();
};

Rva0060061A::~Rva0060061A()
{
	Rva0060061AHelper *p1 = G00A06E5C;
	void *q1 = p1 ? p1->v0(0) : 0;
	::operator delete(q1);
	G00A06E5C = 0;
	Rva0060061AHelper *p2 = G00A06E54;
	void *q2 = p2 ? p2->v0(0) : 0;
	::operator delete(q2);
	G00A06E54 = 0;
}
// ?G00A06E5C@@3PAVRva0060061AHelper@@A: the global at VA 0xe06e5c is ?TheArchiveFileSystem@@3PAVArchiveFileSystem@@A.
#pragma comment(linker, "/alternatename:?G00A06E5C@@3PAVRva0060061AHelper@@A=?TheArchiveFileSystem@@3PAVArchiveFileSystem@@A")
// ?G00A06E54@@3PAVRva0060061AHelper@@A: the global at VA 0xe06e54 is ?TheLocalFileSystem@@3PAVLocalFileSystem@@A.
#pragma comment(linker, "/alternatename:?G00A06E54@@3PAVRva0060061AHelper@@A=?TheLocalFileSystem@@3PAVLocalFileSystem@@A")
