// cl: /MD /Oi /EHsc
//
// Result-writer factories from profile_result.cpp (the constructors live in
// profile_result_filecsv_ctor.cpp / profile_result_filegtt_ctor.cpp):
//   0x006C80B0 ProfileResultFileCSV::Create
//   0x006C7C50 ProfileResultFileDOT::Create
//   0x006C7D10 ProfileResultFileGTT::Create
// Zero Hour's CSV writer takes no arguments; BFME2's takes an optional file
// name. The DOT writer's default fold threshold became 999. The GTT-DOT
// writer is BFME2's (a DOT graph by global time, default file
// "profile_gtt.dot", default threshold 100 = 1%).

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" char *__cdecl strcpy(char *dest, const char *src);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

void *ProfileAllocMemory(unsigned int size);
void *ProfileReAllocMemory(void *oldPtr, unsigned int newSize);

#include <new>

class ProfileResultInterface
{
public:
	virtual void WriteResults() = 0;
	virtual void Delete() = 0;
};

class ProfileResultFileCSV : public ProfileResultInterface
{
public:
	static ProfileResultInterface *Create(int argn, const char *const *argv);
	ProfileResultFileCSV(const char *fileName);

	virtual void WriteResults();
	virtual void Delete();

private:
	char *m_fileName;
};

class ProfileResultFileDOT : public ProfileResultInterface
{
public:
	static ProfileResultInterface *Create(int argn, const char *const *argv);
	ProfileResultFileDOT(const char *fileName, const char *frameName, int foldThreshold);

	virtual void WriteResults();
	virtual void Delete();

private:
	char *m_fileName;
	char *m_frameName;
	int m_foldThreshold;
};

class ProfileResultFileGTT : public ProfileResultInterface
{
public:
	static ProfileResultInterface *Create(int argn, const char *const *argv);
	ProfileResultFileGTT(const char *fileName, const char *frameName, int percentThreshold);

	virtual void WriteResults();
	virtual void Delete();

	bool MarkVisited(unsigned from, unsigned to);

private:
	struct Edge
	{
		unsigned from;
		unsigned to;
	};

	char *m_fileName;
	char *m_frameName;
	int m_percentThreshold;
	Edge *m_visited;
	unsigned m_numVisited;
	unsigned m_visitedAlloc;
};

// ?Create@ProfileResultFileCSV@@SAPAVProfileResultInterface@@HPBQBD@Z
ProfileResultInterface *ProfileResultFileCSV::Create(int argn, const char *const *argv)
{
	return new (ProfileAllocMemory(sizeof(ProfileResultFileCSV)))
		ProfileResultFileCSV(argn > 0 ? argv[0] : 0);
}

// ?Create@ProfileResultFileDOT@@SAPAVProfileResultInterface@@HPBQBD@Z
ProfileResultInterface *ProfileResultFileDOT::Create(int argn, const char *const *argv)
{
	return new (ProfileAllocMemory(sizeof(ProfileResultFileDOT)))
		ProfileResultFileDOT(argn > 0 ? argv[0] : 0,
			argn > 1 ? argv[1] : 0,
			argn > 2 ? atoi(argv[2]) : 999);
}

// ?Create@ProfileResultFileGTT@@SAPAVProfileResultInterface@@HPBQBD@Z
ProfileResultInterface *ProfileResultFileGTT::Create(int argn, const char *const *argv)
{
	return new (ProfileAllocMemory(sizeof(ProfileResultFileGTT)))
		ProfileResultFileGTT(argn > 0 ? argv[0] : 0,
			argn > 1 ? argv[1] : 0,
			argn > 2 ? atoi(argv[2]) : 100);
}

