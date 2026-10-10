// cl: /O1 /Ireference/shims/bfmevector /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?rva004ECECD@AITactic@@QAEPAVTeam@@H@Z retail 0x004ECECD 56B
// Evidence: unlock lane; array stride 0x14 matches ModelNodeClass (RenderObj Model + BoneIndex + Vector3 Offset) in HLodModelNodeAssign.cpp; callees rowed/pinned TheTeamFactory 0x00A028BC plus findTeamByID 0x0039F761; callers 0x005ACDA9 (push 0) 0x005AD0E6 (push eax null Object then Team iterate) plus 11 more; prev 0x004ECEA8 ModelNodeClass::operator= ends at this start.
//
// ?rva004ECF05@AITactic@@QAEPAURva004ECECDNode@@H@Z retail 0x004ECF05 60B
// Evidence: chain via 0x004ECECD same TU flags and pins; same ModelNode loop but returns the node on id match; callers 0x004ED138 0x004ED1A6 0x004ED202 0x004ED27F 0x004ED2F2.
//
// ?anyTeamMembersInCombat@AITactic@@QAE_NXZ retail 0x004ECF41 91B
// Evidence: same AITactic class m_begin 0x14 m_end 0x18 stride 0x14 as siblings; callees rowed iterate_TeamMemberList 0x00263864 plus pin DLINK advance 0x00263526 plus rowed getCurrentVictim 0x00268D71 plus pinned findTeamByID 0x0039F761 via TheTeamFactory 0x00A028BC; caller 0x004EDDAD.
class Team;
class TeamFactory;
extern TeamFactory *TheTeamFactory;

class TeamFactory
{
public:
    Team *findTeamByID(unsigned int id);
};

struct Rva004ECECDNode
{
    void *m_model;
    char m_pad[0x10];
};

class AITactic
{
public:
    Team *rva004ECECD(int id);
    Rva004ECECDNode *rva004ECF05(int id);
    bool anyTeamMembersInCombat();
    void cohereTeams();

private:
    char m_pad00[0x14];
    Rva004ECECDNode *m_begin;
    Rva004ECECDNode *m_end;
};

class AIUpdateInterface;

class Object
{
public:
    unsigned char m_pad0[0x258];
    AIUpdateInterface *m_ai;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];

public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
    void getTeamAsAIGroup(class AIGroup *grp);
};

class AIGroup
{
public:
    void rva00372C05();
};

class AI
{
public:
    AIGroup *createGroup();
    void destroyGroup(AIGroup *grp);
};
extern AI *g_Va009FF0F8;

class AIUpdateInterface
{
public:
    Object *getCurrentVictim() const;
};

Team *AITactic::rva004ECECD(int id)
{
    Rva004ECECDNode *begin = m_begin;
    Rva004ECECDNode *end = m_end;
    for (Rva004ECECDNode *it = begin; it != end; ++it)
    {
        Team *t = TheTeamFactory->findTeamByID((unsigned int)it->m_model);
        if (t != 0)
        {
            void *mid = *(void **)((char *)t + 0x30);
            if (*(int *)((char *)mid + 0x2dc) == id)
                return t;
        }
    }
    return 0;
}

Rva004ECECDNode *AITactic::rva004ECF05(int id)
{
    Rva004ECECDNode *begin = m_begin;
    Rva004ECECDNode *end = m_end;
    for (Rva004ECECDNode *it = begin; it != end; ++it)
    {
        Team *t = TheTeamFactory->findTeamByID((unsigned int)it->m_model);
        if (t != 0)
        {
            void *mid = *(void **)((char *)t + 0x30);
            if (*(int *)((char *)mid + 0x2dc) == id)
                return it;
        }
    }
    return 0;
}

bool AITactic::anyTeamMembersInCombat()
{
    Rva004ECECDNode *begin = m_begin;
    Rva004ECECDNode *end = m_end;
    for (Rva004ECECDNode *it = begin; it != end; ++it)
    {
        Team *team = TheTeamFactory->findTeamByID((unsigned int)it->m_model);
        for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
        {
            if (iter.cur()->m_ai->getCurrentVictim() != 0)
                return true;
        }
    }
    return false;
}

// ?createGroup@AI@@QAEPAVAIGroup@@XZ present-unmatched
// ?getTeamAsAIGroup@Team@@QAEXPAVAIGroup@@@Z present-unmatched
// ?rva00372C05@AIGroup@@QAEXXZ present-unmatched
// ?destroyGroup@AI@@QAEXPAVAIGroup@@@Z present-unmatched
void AITactic::cohereTeams()
{
    Rva004ECECDNode *begin = m_begin;
    Rva004ECECDNode *end = m_end;
    for (Rva004ECECDNode *it = begin; it != end; ++it) {
        AIGroup *grp = g_Va009FF0F8->createGroup();
        Team *t = TheTeamFactory->findTeamByID((unsigned int)it->m_model);
        t->getTeamAsAIGroup(grp);
        grp->rva00372C05();
        g_Va009FF0F8->destroyGroup(grp);
    }
}
