// Zero Hour internal_result.h with BFME2's writers:
// - CSV (vtable 0x00CE85E4) gained an optional file name (+4); with one it
//   writes only the busiest thread.
// - DOT (vtable 0x00CE84D0) is Zero Hour's; Create's default fold
//   threshold became 999.
// - GTT (vtable 0x00CE85D8, "file_gtt_dot") is new: a DOT graph by global
//   time with a visited-edge array at +0x10, count +0x14, capacity +0x18.
// GetName is each vtable's slot 2 (0x006C7580 DOT, 0x006C7590 GTT,
// 0x006C75F0 CSV); Delete is one ICF-folded body (0x006C74C0).

#ifndef INTERNAL_RESULT_H
#define INTERNAL_RESULT_H

#include <stdio.h>

class ProfileResultFileCSV : public ProfileResultInterface
{
	void WriteThread(ProfileFuncLevel::Thread &thread);

public:
	ProfileResultFileCSV(const char *fileName);

	static ProfileResultInterface *Create(int argn, const char *const *argv);

	virtual const char *GetName(void) const { return "file_csv"; }
	virtual void WriteResults(void);
	virtual void Delete(void);

private:
	char *m_fileName;
};

class ProfileResultFileDOT : public ProfileResultInterface
{
public:
	enum
	{
		MAX_FUNCTIONS_PER_FILE = 200
	};

	static ProfileResultInterface *Create(int argn, const char *const *argv);

	virtual const char *GetName(void) const { return "file_dot"; }
	virtual void WriteResults(void);
	virtual void Delete(void);

	ProfileResultFileDOT(const char *fileName, const char *frameName, int foldThreshold);

private:

	struct FoldHelper
	{
		FoldHelper *next;
		const char *source;
		ProfileFuncLevel::Id id[MAX_FUNCTIONS_PER_FILE];
		unsigned numId;
		bool mark;
	};

	char *m_fileName;
	char *m_frameName;
	int m_foldThreshold;
};

class ProfileResultFileGTT : public ProfileResultInterface
{
public:
	ProfileResultFileGTT(const char *fileName, const char *frameName, int percentThreshold);

	static ProfileResultInterface *Create(int argn, const char *const *argv);

	virtual const char *GetName(void) const { return "file_gtt_dot"; }
	virtual void WriteResults(void);
	virtual void Delete(void);

	bool MarkVisited(unsigned from, unsigned to);

private:
	// Original name unknown; address-derived (0x006C7DD0).
	void rva006C7DD0WriteGraph(ProfileFuncLevel::Thread &thread, FILE *f,
		unsigned rootIndex, unsigned __int64 maxTime, unsigned frame);

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

#endif // INTERNAL_RESULT_H
