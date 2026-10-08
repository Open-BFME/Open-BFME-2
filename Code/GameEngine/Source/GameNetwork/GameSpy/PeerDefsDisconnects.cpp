// cl: /EHsc /MD
// Source lead: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo.cpp.
// The donor retains the ZH disconnect-counter semantics. Target WB PeerDefs.cpp
// at 0x00F85E90 independently confirms the helper name, file-count call, and
// sentinel -1. Retail 0x00384A00..0x00384A62 proves the cdecl ABI and virtual
// slots +0x178/+0x17C; donor slots +0x170/+0x174 are not target layout facts.
template<int N> class DisconnectSlots : public DisconnectSlots<N - 1>
{
    virtual void slot(char (*)[N]) = 0;
};
template<> class DisconnectSlots<0> {};

class GameSpyInfoInterface : public DisconnectSlots<94>
{
public:
    virtual int getAdditionalDisconnects() = 0;
    virtual void clearAdditionalDisconnects() = 0;
};

extern GameSpyInfoInterface *TheGameSpyInfo;
int sumOnlineMiscPrefs(int playerID);

int GetAdditionalDisconnectsFromUserFile(int playerID)
{
    int fileCount = sumOnlineMiscPrefs(playerID);
    if (playerID == 0)
        return 0;
    if (TheGameSpyInfo->getAdditionalDisconnects() > 0 && fileCount == 0)
        TheGameSpyInfo->clearAdditionalDisconnects();
    if (TheGameSpyInfo->getAdditionalDisconnects() != -1)
        return TheGameSpyInfo->getAdditionalDisconnects();
    return fileCount;
}
