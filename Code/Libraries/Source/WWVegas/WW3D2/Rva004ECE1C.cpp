// cl: /MD /EHs /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// stlport
// ?rva004ECE1C@AITactic@@QAEXXZ @ 0x004ECE1C, 69 bytes.
// An AITactic member: AITacticsGenerator.cpp's 0x00505924 pass calls it on
// each AITactic, in the AITactic.cpp range.
// Early-return checks on +0x51 +0x28 +0x10 then GameLogic m_40 vs +0x54 with
// threshold g_00E044B0 then tail-jmps to vtable slots 0x18 and 0x1c.
// Evidence: xor-edx byte compares; TheGameLogic rowed name; g_ stopgap;
// 4 callers in 0x00505924 looping over object arrays; /O1 per xor-first.
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A
extern unsigned int g_00E044B0;
// g_00E044B0: matched references place it at VA 0xe044b0 (zero-filled .bss).
unsigned int g_00E044B0;

#include <vector>
#include "ascii_string.h"
#include "Coord3DBase.h"
class Player;
class Team;
class TeamPrototype;
class Xfer;
class Rva002C589B;
class Rva004ECDC8;
struct Rva00506909Request;
struct Rva004ECECDNode;
struct AITacticPoint : Coord3D
{
    __forceinline AITacticPoint(float a, float b, float c) { x=a; y=b; z=c; }
};

class AITactic
{
public:
	AITactic(const AsciiString &name, bool flags);
public:
	void rva004ECE1C();
	unsigned char rva004ED169();
	bool anyTeamMembersInCombat();
public:
	void rva004EDA60();
public:
	void rva004EDDAA();
public:
	virtual void slot00() = 0;
public:
	virtual void slot01() = 0;
public:
	virtual void slot02() = 0;
public:
	virtual bool initializeTeamTemplate(void *p, int dummy);
public:
	virtual unsigned int getNumberOfTeamsNeeded() = 0;
public:
	virtual void xfer(Xfer *xfer);
public:
	virtual void slot06() = 0;
public:
	virtual void slot07() = 0;
public:
	virtual void slot08() = 0;
public:
	Player *playerForAssist() const { return (Player *)m_24; }
public:
	void end(bool a, bool b);
public:
	void preUpdate();
public:
	bool start(Rva00506909Request *request, void *owner);
public:
	bool start(void *owner);
public:
	void NotifyTeamCreated(Team *team);
public:
	void updateTeamInfos();
public:
	void calcLastTeamPos();
public:
	void cohereTeams();
public:
	bool sendTeamToAssistAnotherHorde(Team *team);
private:
	std::vector<TeamPrototype *> m_protos;
private:
	bool m_10;
private:
	std::vector<Rva004ECDC8> m_teams;
private:
	Rva002C589B *m_20;
private:
	void *m_24;
private:
	bool m_ended;
private:
	unsigned char m_pad29[3];
private:
	AsciiString m_name;
private:
	unsigned int m_30;
private:
	bool m_34;
private:
	unsigned char m_pad35[3];
private:
	AITacticPoint m_38;
private:
	AITacticPoint m_44;
private:
	bool m_50;
private:
	bool m_51;
private:
	unsigned int m_54;
public:
	Rva004ECECDNode *rva004ECF05(int id);
public:
	bool isTeamIdle(int id);
public:
	void rva004ED372(const struct Coord3D *p);
private:
	struct Sub
	{
		int m_00;
		int m_04;
	};
};

void AITactic::rva004ECE1C()
{
	if (m_51 == 0)
		return;
	if (m_ended != 0)
		return;
	if (m_10 == 0) {
		if (m_54 == 0) {
			m_54 = TheGameLogic->getFrame();
			return;
		}
		if (TheGameLogic->getFrame() - m_54 < g_00E044B0)
			return;
		m_10 = 1;
		slot06();
		return;
	}
	slot07();
}
