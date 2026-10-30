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
    void setID(int id);
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

class PSPlayerAllStats;

class GameSpyInfoInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual int getLocalProfileID();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void setCachedStats(PSPlayerAllStats stats);
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual bool slot97();
};
class BfmeOpaqueOwnedRecord1432;

class GameSpyPSMessageQueueInterface {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
    virtual void addRequest(const BfmeOpaqueOwnedRecord1432 &request); virtual void s14(); virtual void s18(); virtual void s1C();
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
