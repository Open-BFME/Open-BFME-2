// cl: /MD /Oi
//
// profile_result.cpp ProfileResultFileCSV's constructor, retail 0x006C75A0
// (80 bytes). BFME2's CSV writer carries a filename member the Zero Hour
// reference has no trace of (there the CSV class is stateless with a private
// default constructor): here the constructor takes a file name, installs the
// CSV vftable at 0x00CE85E4 (whose GetName slot returns "file_csv") and keeps
// a ProfileAllocMemory-owned copy of the name, or NULL when none is given:
//
//   m_fileName = fileName ? strcpy(alloc(strlen+1)) : NULL;
//
// Both strlen and strcpy are inlined - the byte loops are in the body, not
// calls - so the unit needs /Oi, exactly like the DOT constructor sibling at
// 0x006C6ED0 whose first half this mirrors. ProfileAllocMemory is the
// allocator at 0x006C5460, reached by REL32.

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

void *ProfileAllocMemory(unsigned int size);

class ProfileResultInterface
{
public:
	virtual void WriteResults() = 0;
	virtual void Delete() = 0;
};

class ProfileResultFileCSV : public ProfileResultInterface
{
public:
	ProfileResultFileCSV(const char *fileName);

	virtual const char *GetName() const;
	virtual void WriteResults();
	virtual void Delete();

private:
	char *m_fileName;
};

ProfileResultFileCSV::ProfileResultFileCSV(const char *fileName)
{
	if (fileName)
	{
		m_fileName = (char *)ProfileAllocMemory(strlen(fileName) + 1);
		strcpy(m_fileName, fileName);
	}
	else
		m_fileName = 0;
}
