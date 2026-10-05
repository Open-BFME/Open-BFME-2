// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0051C139@Rva0051CBC6@@QAEHXZ @0x0051C139 69B
// evidence: chain from 0x0051BF47 you landed, vtable slot 5 of 0x00866FAC class Rva0051CBC6, caller none, callees rowed showCampaignReview plus enable target plus vslots
class MessageStream
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18(int v);
};
extern MessageStream *MessageStreamSubsystem;

class AudioManager
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
};
extern AudioManager *TheAudio;

bool _bfme_showCampaignReview();
void Rva0051BF47Run();

class Rva0051CBC6
{
public:
    int rva0051C139();
private:
    char _pad[0x27c];
    int m_27c;
};

int Rva0051CBC6::rva0051C139()
{
    int m = m_27c - 1;
    if (m != 0)
    {
        m -= 2;
        if (m != 0)
        {
            m--;
            if (m != 0)
                return 1;
            MessageStreamSubsystem->v18(0x1d);
            _bfme_showCampaignReview();
        }
        else
        {
            Rva0051BF47Run();
        }
    }
    else
    {
        TheAudio->v09();
    }
    m_27c = 0;
    return 1;
}
