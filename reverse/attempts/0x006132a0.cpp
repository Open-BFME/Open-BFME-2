// ?Return_File@RawFileFactoryClass@@QAEXPAVFileClass@@@Z
// partial score=0.7 date=2026-09-09
// cl: /O2 /DNDEBUG /MD
//
// RawFileFactoryClass::Return_File, retail 0x006132A0, 36 bytes.
// delete the FileClass; the null path still calls operator delete(0).

void __cdecl operator delete(void *);

class FileClass
{
public:
	virtual ~FileClass();
};

class RawFileFactoryClass
{
public:
	void Return_File(FileClass *file);
};

void RawFileFactoryClass::Return_File(FileClass *file)
{
	if (file)
	{
		file->~FileClass();
		operator delete(file);
	}
	else
		operator delete(0);
}
