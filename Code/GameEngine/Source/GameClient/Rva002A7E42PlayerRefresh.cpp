// ?rva002A7E42@Rva002A7E42@@QAEXPAVPlayer@@@Z
// cl: /O1 /DNDEBUG /MD /EHsc
// Native2A7E42..2A7EA0 RET4. Non-null player gates shroud notification,
// two rowed ControlBar workers and a traversal from client virtual slot8C.
// Each traversed entry receives slot34 then follows next104; finally the
// rowed ShowControlBar receives false. Original receiver identity unknown.
// The no-stack-argument virtual call views use ECX, as their native slots do.
class Player;
class PartitionManager;
extern PartitionManager *TheShroudManager;
class Rva007397D0 { public: void rva007397D0(); };
class ControlBar
{
public:
    void rva0031BAC3(Player *);
    void setControlBarSchemeByPlayer(Player *);
};
extern ControlBar *TheControlBar;
class ClientFrameSubsystem;
extern ClientFrameSubsystem *TheGameClient;
void ShowControlBar(bool);
struct Rva002A7E42Entry;
struct Rva002A7E42EntryVTable
{
    void *unknown00[13];
    void (__fastcall *refresh)(Rva002A7E42Entry *);
};
struct Rva002A7E42Entry
{
    Rva002A7E42EntryVTable *vtable;
    char unknown04[0x100];
    Rva002A7E42Entry *next;
};
struct Rva002A7E42Client;
struct Rva002A7E42ClientVTable
{
    void *unknown00[35];
    Rva002A7E42Entry *(__fastcall *first)(Rva002A7E42Client *);
};
struct Rva002A7E42Client { Rva002A7E42ClientVTable *vtable; };
class Rva002A7E42 { public: void rva002A7E42(Player *player); };
void Rva002A7E42::rva002A7E42(Player *player)
{
    if (player)
    {
        if (TheShroudManager)
            reinterpret_cast<Rva007397D0 *>(TheShroudManager)->rva007397D0();
        TheControlBar->rva0031BAC3(player);
        TheControlBar->setControlBarSchemeByPlayer(player);
        Rva002A7E42Client *client = reinterpret_cast<Rva002A7E42Client *>(TheGameClient);
        Rva002A7E42Entry *entry = client->vtable->first(client);
        while (entry)
        {
            entry->vtable->refresh(entry);
            entry = entry->next;
        }
        ShowControlBar(false);
    }
}
