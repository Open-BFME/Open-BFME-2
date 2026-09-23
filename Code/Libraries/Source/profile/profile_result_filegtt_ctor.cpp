// cl: /MD /Oi
//
// profile_result.cpp ProfileResultFileGTT's constructor, retail 0x006C74D0
// (171 bytes). The GTT writer ("file_gtt_dot", default file
// "profile_gtt.dot") is BFME2-new: no Zero Hour donor has it. Its head is
// the DOT constructor's shape - optional file name with a default, optional
// frame name defaulting to NULL, integer fold threshold - extended with
// three zeroed trailing members the GTT WriteResults never reads:
//
//   m_reserved10 = m_reserved14 = m_reserved18 = 0;
//   if (!fileName) fileName = "profile_gtt.dot";
//   m_fileName = alloc(strlen+1); strcpy;
//   if (frameName) { m_frameName = alloc(strlen+1); strcpy; }
//   else m_frameName = NULL;
//   m_foldThreshold = foldThreshold;
//
// The vftable installed at +0 is 0x00CE85D8, whose GetName slot returns
// "file_gtt_dot". Both strlen and strcpy are inlined, so the unit needs /Oi
// like its DOT and CSV siblings. ProfileAllocMemory at 0x006C5460 by REL32.
//
// The GTT token itself comes from the retail strings and claims no donor
// provenance; the reserved members' purpose is unknown.

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" char *__cdecl strcpy(char *destination, const char *source);

void *ProfileAllocMemory(unsigned int size);

class ProfileResultInterface
{
public:
	virtual void WriteResults() = 0;
	virtual void Delete() = 0;
};

class ProfileResultFileGTT : public ProfileResultInterface
{
public:
	ProfileResultFileGTT(const char *fileName, const char *frameName,
			int foldThreshold);

	virtual const char *GetName() const;
	virtual void WriteResults();
	virtual void Delete();

private:
	char *m_fileName;
	char *m_frameName;
	int m_foldThreshold;
	int m_reserved10;
	int m_reserved14;
	int m_reserved18;
};

ProfileResultFileGTT::ProfileResultFileGTT(const char *fileName,
		const char *frameName, int foldThreshold)
{
	m_reserved10 = 0;
	m_reserved14 = 0;
	m_reserved18 = 0;
	if (!fileName)
		fileName = "profile_gtt.dot";
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
