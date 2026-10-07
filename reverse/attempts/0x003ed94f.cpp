// ??1Rva003ED94FDtor@@QAE@XZ
// partial score=0.95 date=2026-10-07
// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// ??1Rva003ED94FDtor@@QAE@XZ @0x003ED94F 58B
// Dtor: bfmeClearMembers(this) then inline vector release free(m_start).
// Evidence: callers ??1Rva0020DXXX@@UAE@XZ and ??1Rva004ABFD9@@UAE@XZ name
// this member dtor Rva003ED94FDtor; next TU LargeGroupAudioKeyMapAssignment
// shows bfmeClearMembers((LGA_MemberObj*)this) plus 3-dword storage; donor
// reference/open-bfme-1/game/GameEngine/Source/Common/LGA_MemberObjDestructor.cpp
// shows LGA_MemberObj::~LGA_MemberObj calling bfmeClearMembers then inlined
// BfmeMemberVector release with EH state 0 across cleanup and -1 for release.

class LGA_MemberObj;
void bfmeClearMembers(LGA_MemberObj *map);

void __cdecl free(void *block);

struct BfmeMemberVector
{
	~BfmeMemberVector()
	{
		if (m_start != 0)
			free(m_start);
	}
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva003ED94FDtor
{
public:
	~Rva003ED94FDtor();
private:
	BfmeMemberVector m_vec;
};

// ??1Rva003ED94FDtor@@QAE@XZ
Rva003ED94FDtor::~Rva003ED94FDtor()
{
	bfmeClearMembers((LGA_MemberObj *)this);
}
