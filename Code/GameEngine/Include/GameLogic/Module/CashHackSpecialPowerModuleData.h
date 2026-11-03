// Target facts (code addresses are RVAs, table addresses are VAs): factory 0x00251957 allocates 0x8C at 0x00251963 and calls constructor 0x004C2889 at 0x0025197B. The constructor calls SpecialPowerModuleData's 0x004930A0 at 0x004C288E, installs 0x00C5C688 at +0 at 0x004C289D, constructs the vector at +0x7C through 0x00211E58, clears it through 0x003FA4DB, and zeros the int at +0x88 at 0x004C28B4. The parent's factory 0x0024DC8C allocates 0x7C at 0x0024DC98; its final float store at 0x0049318E is +0x78. Derived storage therefore starts at +0x7C; its vector occupies twelve bytes and retains opaque storage.
// The live table 0x00C5C688 has 31 slots and ends at string data 0x00C5C704. Slot 0 is deleting destructor 0x004C28C1, which calls destructor 0x004C28DD; slots 1..30 equal the parent's 0x00C4E318 table. The class adds no virtual slots. Destructor 0x004C28DD frees the vector's +0x7C buffer through 0x00030830 and calls parent destructor 0x0049334F at 0x004C2906 without a derived vptr store. The parent stores Snapshot's four-slot 0x00BBB554 at 0x004933B2; that teardown table is not the live derived table. Both derived special members remain out of line.
// buildFieldParse 0x004C2955 registers 0x00C5C724: UpgradeMoneyAmount at +0x7C uses parser 0x004C2918, which builds an eight-byte science/int pair and calls vector push_back 0x00539A2E; MoneyAmount at +0x88 uses parseInt 0x0002EF56. Zero Hour's GameLogic/Module/CashHackSpecialPower.h supplies Upgrades, m_science, m_amountToSteal, m_upgrades and m_defaultAmountToSteal. Ledger rows declare Upgrades() (0x004CEE6E, -1/0 dwords), Upgrades(int, const int &) (0x003FA38C) and its copy constructor (0x003FA3AF); the latter two initialize +0, call a four-byte zeroing constructor at +4, then OR the supplied amount. Their member's type identity is unproven; its four-byte value remains int storage. Ledger rows also prove buildFieldParse and friend_newModuleData (0x00251957).
#pragma once

#ifndef BFME2_CASHHACKSPECIALPOWERMODULEDATA_H
#define BFME2_CASHHACKSPECIALPOWERMODULEDATA_H

#include "SpecialPowerModuleData.h"

class CashHackSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
    struct Upgrades
    {
        int m_science;
        int m_amountToSteal;

        Upgrades();
        Upgrades(int science, const int &amount);
        Upgrades(const Upgrades &source);
    };

    CashHackSpecialPowerModuleData();
    virtual ~CashHackSpecialPowerModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    unsigned char m_upgrades[0x0C];
    int m_defaultAmountToSteal;
};

#endif
