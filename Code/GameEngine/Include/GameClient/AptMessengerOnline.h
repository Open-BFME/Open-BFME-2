// Target facts (code addresses are RVAs; table addresses are VAs): ctor 0x005AEF6B calls AptMessenger at 0x005AEF83, stores 0x00C72760 at +0 (0x005AEF8A) and 0x00C7275C at +0x218 (0x005AEF90), and clears byte +0x2A0 (0x005AEF9A). Dtor 0x005AE66B restores that same pair and jumps to AptMessenger::~AptMessenger at 0x005AE68A. Factory 0x005114C6 pushes 0x2A4 at 0x005114DA and calls the ctor at 0x005114F5. The secondary table's sole entry is the -0x218 deleting-dtor thunk 0x005AE763 to 0x005AE76E. This class is polymorphic.
// The 17 primary entries at 0x00C72760 target 0x005AE76E/0x005117B7/0x00511990/0x000A12F8/0x00444680/0x00511E6D/0x00313913/0x00510D87/0x0031393A/0x0008FF78/0x0050B5C6/0x0050B5C6/0x00511826/0x005118B2/0x005AF117/0x0050B5C6/0x005AE68F; string data starts at 0x00C727A4. CreateChatWindow's name and signature come from its 0x005AE68F ledger row.
// Online methods are rowed at 0x005AE7C6/0x005AED3C/0x005AF12F; lifetime methods remain out of line.
#ifndef BFME2_GAMECLIENT_APTMESSENGERONLINE_H
#define BFME2_GAMECLIENT_APTMESSENGERONLINE_H

#include "AptMessenger.h"

class AptMessengerOnline : public AptMessenger
{
public:
    AptMessengerOnline(void *context);
    virtual ~AptMessengerOnline();
    virtual void vslot14();
    virtual bool vslot15();
    virtual void *CreateChatWindow(int selector);

    void OnBttnInvite();
    void UpdatePlayerTabButtons();
    static bool ProcessGameSpyResponse(void *response);

    bool m_2A0;
};

typedef char Bfme2AptMessengerOnlineExtent[(sizeof(AptMessengerOnline) == 0x2A4) ? 1 : -1];

#endif
