# The remaining private MiscAudio copies: two names to vote, one contradiction

Measured 2026-11-07, after adopting the canonical header in
`Common/RTS/MoneyRva003B0D7C.cpp` and `GameLogic/Object/Helper/ObjectDefectionHelper.cpp`.

`MiscAudio` is registered in `reverse/canonical_classes.csv` (header
`Code/GameEngine/Include/Common/MiscAudioClass.h`, contract `class_contracts/MiscAudio.json`).
Its members are a flat run of `OpaqueRefElement4`, so an offset maps to exactly one member; the
whole struct is 0xF4 bytes. Three `.cpp` units still declare their own copy.

## Two members the canonical header leaves unnamed, with in-tree evidence to name them

Both adoptions are blocked only by this: taking the canonical header today would replace a
meaningful name with an offset name, which is a readability regression rather than a fix. The
stand-in names are the evidence a member-kind vote needs.

- **+0xBC**, canonically `m_BC`. `GameClient/InGameUIMessages.cpp` calls it
  `m_subtitleTypingSound`, and its use site builds a sound named `click`
  (`static BfmeAudioEventPrefix136 click(TheAudio->getMiscAudio()->m_subtitleTypingSound, 0)`).
- **+0xF0**, canonically `m_F0`. `Common/Rva00428EEBIssueFireWeapon.cpp` calls it `special`,
  which is a stand-in spelling rather than a role, so this one needs its own evidence before a
  vote is worth running.

## One contradiction to settle before that unit can adopt

`GameClient/MessageStream/PlaceEventTranslator.cpp` declares `char m_pad[0xE8];` followed by
`OpaqueRefElement4 m_noCanDoSound;`, putting the no-can-do sound at **+0xE8**. The canonical
header puts `m_noCanDoSound` at **+0x2C** and has an unnamed `m_E8` at +0xE8. Both cannot be
right, and nothing else in the tree names a no-can-do sound, so there is no third witness: the
only two spellings of this member disagree.

Adopting the canonical header in that unit would silently move the sound it plays from +0xE8 to
+0x2C. The bytes would then differ, so the gate would catch it - but the point is that the
question is which offset retail reads, and that needs the body's own relocation, not a
preference between two stand-ins.

## Why the two completed adoptions were safe

They needed no call-site change: every member they used matched the canonical header in both
offset and spelling (`m_moneyDepositSound`/`m_moneyWithdrawSound` at +0x38/+0x3C, and
`m_defectorTimerTickSound`/`m_defectorTimerDingSound` at +0x20/+0x24). That is the test for a
mechanical adoption here; where it fails, the work is a vote or a measurement, not an edit.
