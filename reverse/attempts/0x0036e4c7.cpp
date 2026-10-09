// ??0AIGroup@@QAE@XZ
// partial score=0.95 date=2026-10-09
// ??0AIGroup@@QAE@XZ
// partial score=0.95 date=2026-09-30
// ??0AIGroup@@QAE@XZ
// partial score=0.95 date=2026-09-30
// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /arch:SSE /G7 /I.
// stlport
//
// ??0AIGroup@@QAE@XZ, retail 0x0036E4C7, 151 bytes.
// AIGroup ctor: vtable 0x00817D00, list<int> at +0x04, ID from AI global
// 0x009FF0F8 (+0x1C), floats including global 0x007C2428 at +0x24,
// vector<BfmeE16> at +0x30, list clear. Caller AI::createGroup at
// 0x002FEC4B news 0x3C then calls here. BFME1 donor AIGroupConstructor.cpp.
#include <list>
#include <vector>

typedef unsigned int UnsignedInt;

class AI
{
public:
	UnsignedInt getNextGroupID() { return ++m_nextGroupID; }

private:
	unsigned char m_unmodelled[0x1C];
	UnsignedInt m_nextGroupID;
};

extern AI *TheAI;



struct BfmeE16
{
	float x, y, z, w;
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"

class AIGroup : public Snapshot
{
public:
	AIGroup();
 virtual ~AIGroup();
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void xfer(Xfer *);

private:
	
	_STL::list<int> m_memberList;
	float m_08;
	bool m_0C;
	UnsignedInt m_id;
	void *m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
	_STL::vector<BfmeE16> m_vec;
};

// ??0AIGroup@@QAE@XZ present-unmatched
AIGroup::AIGroup()
{
	m_14 = 0;
	float tmp24 = 140.0f;
	m_18 = 0.0f;
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = tmp24;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_08 = 0.0f;
	m_0C = false;
	m_id = TheAI->getNextGroupID();
	m_memberList.clear();
}
