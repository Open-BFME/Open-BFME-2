/* Target facts (code addresses are RVAs): ManualPhaseEnder has no virtual functions or polymorphic base. Constructor 0x005CD7BD (rowed as Rva005CD7BD) stores its three arguments at +0/+4/+8 at 0x005CD7C3/0x005CD7C9/0x005CD7D0 and clears byte +0x0C at 0x005CD7D3; it calls no base constructor and installs no table. Its receivers are the same embedded objects passed to Translate: PlanningPhaseBehavior constructor 0x005762CA and translator 0x00575C33 use +0x30, ResolveBattlesBehavior 0x00576E71/0x00576689 use +0x20, and PlanRetreatsPhaseBehavior 0x00577708/0x00577212 use +0x18. The following members begin at +0x40/+0x30/+0x28 (0x005762DF/0x00576E86/0x0057771D), bounding this record to 0x10 bytes; three pointer words and the byte flag give that size with four-byte alignment.
   OnEndPhase 0x005CD8A5 loads the pointer at +8 at 0x005CD8BA and the pointer at +0 at 0x005CD8F0; its terminal virtual dispatch is through that pointee, not through this. Update 0x005CD938 tests byte +0x0C at 0x005CD948, passes the +4 pointer to 0x0042D6AE at 0x005CD94E/0x005CD952, and sets the flag at 0x005CD99C. Cleanup 0x005CD7DA (rowed under Rva005CD7DA and Wrap2000576C4B) tests the same flag and dereferences the +4 pointer without a table store. There are no constructor/destructor tables to reconcile. The lifetime rows retain those placeholder owners; the declarations below do not redirect them.
   Translate 0x005CD8F7, Update 0x005CD938 and OnEndPhase 0x005CD8A5 have ordinary thiscall ledger names in StrategicInGameUI. Translate takes const GameMessage * and returns GameMessageDisposition; the other two take no arguments and return void. The class has no named field evidence, so its storage uses neutral offset names. */
#pragma once

#ifndef BFME2_MANUALPHASEENDER_H
#define BFME2_MANUALPHASEENDER_H

class GameMessage;
enum GameMessageDisposition;

namespace StrategicInGameUI
{
class ManualPhaseEnder
{
public:
    ManualPhaseEnder(void *, int, int);
    ~ManualPhaseEnder();

    GameMessageDisposition Translate(const GameMessage *message);
    void Update();
    void OnEndPhase();

private:
    void *m_field00;
    void *m_field04;
    void *m_field08;
    bool m_field0C;
};
}

using StrategicInGameUI::ManualPhaseEnder;

#endif
