// cl: /Ireference/shims/bfme2_ascii /GX- /O1 /arch:SSE
// ?rva003802DF@Rva00380200@@QAEHXZ @0x003802DF 157B. Unlock min selector plus rank store tail.
// evidence: abuts prev 0x0038028B same page same class Rva00380200; vcall +0x14 plus g_009FEF10 plus TheRankInfoStore get 0x003B0FC6 plus rva002B2AFD plus TheGameLogic mode +0x110 plus isInMultiplayerGame; unblocks 4.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva003B0FC6SarAvgField
{
public:
    int get() const;
};
class Rva002B2AFD
{
public:
    int rva002B2AFD();
};
class RankInfoStore;
extern RankInfoStore *TheRankInfoStore;
class Rva002BA8F1Logic;

class GameLogic
{
public:
    char m_pad[0x110];
    int m_gameMode;
    bool isInMultiplayerGame();
};
extern GameLogic *TheGameLogic;
class Rva00380200Base
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual bool isReady();
};
struct Rva003802DFPayload
{
    char m_pad[8];
    int m_08;
    int m_0C;
};
class Rva00380200 : public Rva00380200Base
{
public:
    int rva003802DF();
private:
    Rva003802DFPayload *m_04;
};
int Rva00380200::rva003802DF()
{
    if (isReady() && (*(Rva002BA8F1Logic **)&TheLivingWorldLogic))
    {
        int a = ((Rva003B0FC6SarAvgField *)TheRankInfoStore)->get();
        int b = ((Rva002B2AFD *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B2AFD();
        const int &r = b < a ? b : a;
        return r;
    }
    else if (m_04)
    {
        GameLogic *logic = TheGameLogic;
        if (logic->m_gameMode == 2 || logic->isInMultiplayerGame())
        {
            int a = ((Rva003B0FC6SarAvgField *)TheRankInfoStore)->get();
            int b = m_04->m_08;
            const int &r = b < a ? b : a;
            return r;
        }
        else
        {
            int a = ((Rva003B0FC6SarAvgField *)TheRankInfoStore)->get();
            int b = m_04->m_0C;
            const int &r = b < a ? b : a;
            return r;
        }
    }
    else
    {
        return ((Rva003B0FC6SarAvgField *)TheRankInfoStore)->get();
    }
}
