// cl: /MD
// ?rva006006D9@Rva0060061A@@QAEXPAX@Z @0x006006D9 158B
// Leaf between Rva0060061A dtor and Rva00600777Set: news Rva00604A5F and Win32BIGFileSystem
// into TheArchiveFileSystem and TheLocalFileSystem then virtual A1 plus Helper v1 plus
// Archive doesFileExist shaders.big gate to BFME2PreferLocalFiles.
// Evidence: same globals and flags as Rva0060061A dtor TU, same Archive layout
// as FileSystemDoesFileExist, rowed ctors, string literal, caller 0x0022E3B7.

#include <new>

class Rva00604A5F
{
public:
	Rva00604A5F();
	virtual ~Rva00604A5F();
};

class Win32BIGFileSystem
{
public:
	Win32BIGFileSystem();
	virtual ~Win32BIGFileSystem();
private:
	unsigned char m_pad[0x10 - 4];
};

class Rva0060061AHelper
{
public:
	virtual void *v0(int a1);
	virtual void v1(void *a1);
};

extern class LocalFileSystem *TheLocalFileSystem;

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

#include "../../Include/Common/Rva0060061A.h"

void Rva0060061A::rva006006D9(void *a1)
{
	Rva00604A5F *p1 = new Rva00604A5F();
	TheArchiveFileSystem = (ArchiveFileSystem *)p1;
	Win32BIGFileSystem *win32BIGFileSystem = new Win32BIGFileSystem();
	(*(Rva0060061AHelper **)&TheLocalFileSystem) = (Rva0060061AHelper *)win32BIGFileSystem;
	TheArchiveFileSystem->A1();
	(*(Rva0060061AHelper **)&TheLocalFileSystem)->v1(a1);
	if (!TheArchiveFileSystem->doesFileExist("shaders.big"))
		BFME2PreferLocalFiles = true;
}
