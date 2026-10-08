// cl: /O1 /G7 /MD /EHsc
// WB AptOnlineShell::RefreshCachedStats (0x0145CE70; assert645) provides
// the name lead. Retail 0x00517F31 independently proves the singleton
// guards, virtual slots, two by-value 0x548-byte stats transfers, preference
// lookup and stats lifetimes. Retain the existing call-site ABI spelling
// Rva005B8EBB::rva00517F31; its receiver identity is not reconciled yet.
// Stats size/id and preferences prefix agree with their matched providers.
class PSPlayerAllStats {
public:
    PSPlayerAllStats(const PSPlayerAllStats &);
    ~PSPlayerAllStats();
    void rva00552E9E(int locale);
    int id;
private:
    unsigned int unknown[0x544 / 4];
};
typedef char StatsExtent[sizeof(PSPlayerAllStats) == 0x548 ? 1 : -1];

class GameSpyMiscPreferences {
public:
    GameSpyMiscPreferences();
    virtual ~GameSpyMiscPreferences();
    int rva00559782();
private:
    unsigned int unknown[4];
};

class GameSpyInfoInterface {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
    virtual void s70(); virtual void s74(); virtual void s78();
    virtual int getLocalProfileID();
    virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8C();
    virtual void s90(); virtual void s94();
    virtual void setCachedStats(PSPlayerAllStats stats);
};
class GameSpyPSMessageQueueInterface {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
    virtual void setCachedStats(PSPlayerAllStats stats);
    virtual void s24(); virtual void s28(); virtual void s2C();
    virtual PSPlayerAllStats findPlayerStatsByID(int id);
};
extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;
struct Gen_uw_00385371;
void Rva00556FB8(const Gen_uw_00385371 &);

class Rva005B8EBB {
public: void rva00517F31();
};

void Rva005B8EBB::rva00517F31()
{
    if (!TheGameSpyInfo) return;
    int id = TheGameSpyInfo->getLocalProfileID();
    if (!id) return;
    PSPlayerAllStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(id);
    GameSpyMiscPreferences preferences;
    if (!stats.id) return;
    stats.rva00552E9E(preferences.rva00559782());
    TheGameSpyPSMessageQueue->setCachedStats(stats);
    PSPlayerAllStats cached = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
    if (cached.id) {
        Rva00556FB8(*(const Gen_uw_00385371 *)&cached);
        TheGameSpyInfo->setCachedStats(cached);
    }
}
