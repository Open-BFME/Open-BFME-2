// cl: /MD /Oi
//
// profile_result.cpp ProfileResultFileDOT's constructor, verbatim from the
// Generals reference:
//
//   if (!fileName) fileName = "profile.dot";
//   m_fileName = (char *)ProfileAllocMemory(strlen(fileName)+1);
//   strcpy(m_fileName, fileName);
//   if (frameName) { ...same for m_frameName... } else m_frameName = NULL;
//   m_foldThreshold = foldThreshold;
//
// Both strlen and strcpy are inlined - the byte loops are in the body, not
// calls - so the unit needs /Oi. ProfileAllocMemory is the allocator at
// 0x006C5460, reached by REL32. The vftable stored at +0 is 0x00CE84D0, which
// is what identifies the class: the "profile.dot" default filename anchors
// the file and the reference has exactly one constructor that uses it.

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

void *ProfileAllocMemory(unsigned int size);

class ProfileResultInterface
{
public:
	virtual void WriteResults() = 0;
	virtual void Delete() = 0;
};

class ProfileResultFileDOT : public ProfileResultInterface
{
public:
	ProfileResultFileDOT(const char *fileName, const char *frameName,
			int foldThreshold);

	virtual void WriteResults();
	virtual void Delete();

private:
	char *m_fileName;
	char *m_frameName;
	int m_foldThreshold;
};

ProfileResultFileDOT::ProfileResultFileDOT(const char *fileName,
		const char *frameName, int foldThreshold)
{
	if (!fileName)
		fileName = "profile.dot";
	m_fileName = (char *)ProfileAllocMemory(strlen(fileName) + 1);
	strcpy(m_fileName, fileName);
	if (frameName)
	{
		m_frameName = (char *)ProfileAllocMemory(strlen(frameName) + 1);
		strcpy(m_frameName, frameName);
	}
	else
		m_frameName = 0;
	m_foldThreshold = foldThreshold;
}
