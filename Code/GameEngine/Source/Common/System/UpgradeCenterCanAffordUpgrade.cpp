// cl: /O1 /Oy- /DNDEBUG /MD /EHsc
// UpgradeCenter::canAffordUpgrade from the Upgrade.cpp reference, isolated
// so its BFME 2 money and UI layouts can be checked against retail.

class Player {
public:
    char m_pad[0x94];
    unsigned m_money;
};

class UpgradeTemplate {
public:
    unsigned calcCostToBuild(Player *, unsigned) const;
};

template <class T> class StringBase {
public:
    StringBase(const T *);
    StringBase(const StringBase &);
    ~StringBase();
    T *m_text;
};

class AsciiString : public StringBase<char> {
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &);
    ~AsciiString();
};

class InGameUI {
public:
    virtual void __stdcall slot0();
    virtual void __stdcall slot1();
    virtual void __stdcall slot2();
    virtual void __stdcall slot3();
    virtual void __stdcall slot4();
    virtual void __stdcall slot5();
    virtual void __stdcall slot6();
    virtual void __stdcall slot7();
    virtual void __stdcall slot8();
    virtual void __stdcall slot9();
    virtual void __stdcall slot10();
    virtual void __stdcall slot11();
    virtual void __stdcall slot12();
    virtual void __stdcall slot13();
    virtual void __stdcall slot14();
    virtual void __cdecl message(AsciiString);
};

extern InGameUI *TheInGameUI;

bool __stdcall bfmeCanAffordUpgrade(Player *player,
                                   const UpgradeTemplate *upgrade,
                                   unsigned context,
                                   bool displayReason)
{
    if (!player || !upgrade)
        return false;
    unsigned money = player->m_money;
    if (money < upgrade->calcCostToBuild(player, context)) {
        if (displayReason)
            TheInGameUI->message(AsciiString("GUI:NotEnoughMoneyToUpgrade"));
        return false;
    }
    return true;
}
