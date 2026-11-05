// Target facts: constructor RVA 0x00431F61 stores VA 0x00C3C9B8 at +0, clears bytes +4/+5 and stores its owned state pointer at +8; allocation RVA 0x0023A52C requests 0x0C bytes before calling it at 0x0023A541. Table 0x00C3C9B8 has translateGameMessage (RVA 0x00431FF2) in slot 0 and deleting destructor 0x00432151 in slot 1; the next independently stored table starts at 0x00C3C9C0.
// Target facts: deleting destructor RVA 0x00432151 calls destructor 0x00431FB5, which restores 0x00C3C9B8 at 0x00431FC6, clears singleton VA 0x00E0322C, releases +8 at 0x00431FDA and restores the base table 0x00BDBA74 at 0x00431FE2. That base table contains __purecall and deleting destructor 0x001DB080; unwind RVA 0x00787A8A calls the folded base destructor 0x00429191. The named base interface and enum signature are supplied by the matched constructor caller GameClient::init (RVA 0x0023A1BB); no registered header defines that interface.
// Target facts: translateGameMessage RVA 0x00431FF2 reads and clears the two flag bytes, reads the state pointer at +8 and dispatches its slot 2. Constructor RVA 0x00431920, allocated as 0x1C bytes at 0x00431B36, creates the separate WaitForSecondButtonDownStateHandler with table VA 0x00C3C994 and fields +4/+8/+0C/+14/+18; its ledger methods at 0x00431955, 0x00431B76, 0x00431BDD, 0x00431C35, 0x00431C9D and 0x00432038 belong to that nested class, whose definition is separate from the 0x0C-byte translator.
// Target facts: base deleting destructor 0x001DB080 (29 bytes) stores 0x00BDBA74 inline before operator delete, so ~GameMessageTranslator is an inline empty body (ZH MessageStream.h agrees); an out-of-line declaration emitted a 28-byte non-retail ??_G that beat WindowXlat.cpp's retail copy.
#pragma once
#ifndef BFME2_FORMATIONTRANSLATOR_H
#define BFME2_FORMATIONTRANSLATOR_H

class GameMessage;
enum GameMessageDisposition;

class GameMessageTranslator
{
public:
    virtual GameMessageDisposition translateGameMessage(const GameMessage *message) = 0;
    virtual ~GameMessageTranslator() {}
};

class FormationTranslator : public GameMessageTranslator
{
public:
    class WaitForSecondButtonDownStateHandler;

    FormationTranslator();
    virtual GameMessageDisposition translateGameMessage(const GameMessage *message);
    virtual ~FormationTranslator();

private:
    unsigned char m_04;
    unsigned char m_05;
    void *m_08;
};

#endif
