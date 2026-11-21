# AptInGameChat 0x00862630 and its base _bfme_AptGameWindow 0x008659E8

Landed: AptInGameChat.cpp (20bbdb213b) and parseSpellIndex_Thunk.cpp (c18db7c5d0)
adopt the canonical `_bfme_AptGameWindow.h`. A dry run over the other 12 private
copies failed (header_adopt_lane adopt): STL include conflicts (AptStrategicPlayerStatus,
AptScoreScreen, AptSkirmishDestructor, AptLanLobbyDestructor, AptTimeLine -- its
class-layout compile also hung under wine for 40 min, Rva0043D1C9Destructor),
AptExternHandlerAdder field00 vs m_names (AptQuitMenuCallbacks, AptCreateAHero,
AptPlayerStatus, AptSpellStore), GameWindow m_pad004 (AptScoreScreenCallbacks),
missing default ctor (OpaqueScalarDeletingDtorsB12) and a BfmeAptScreenBase
initializer (BfmeAptGameWindowConstructor).

## Retail tables (target facts)

GameWindow 0x0080BBCC has 11 slots. _bfme_AptGameWindow 0x008659E8 has 14:

| slot | base 0x8659E8 | AptInGameChat 0x862630 | GameWindow name | current row |
|---|---|---|---|---|
| 0 | 0x5127D7 | 0x4E84E3 | dtor | matched |
| 1 | 0x5748AD | 0x4E846A | input | Rva005748AD placeholder (ICF, 2 rows) / `?rva004E846A@Rva004E8220@@` |
| 2 | 0x51274F | 0x4E8D3E | bfmeGoEHCb | `?rva0051274F@_bfme_AptGameWindow@@QAE` non-virtual (unique 136B) / `?rva004E8D3E@Rva004E8D3E@@` |
| 3 | 0xA12F8 | same | draw | ICF return-1 (AptTimeLine landed twin `?draw@Rva005202C8`) |
| 4 | 0x444680 | same | tooltip | ICF (AptTimeLine twin) |
| 5 | 0x910FB | 0x4E8620 | rva0009FD78 | ICF 140 slots / AptInGameChat::rva004E8620 |
| 6 | 0x313913 | same | vslot6 | inherited OK |
| 7 | 0x510D87 | 0x4E8D86 | fetchCreateInstance | free `?Rva00510D87Get@@YAHXZ` / `?Rva004E8D86Get@@YAHXZ` (mov eax,factory; ret) |
| 8-10 | inherited | inherited | vslot8-10 | OK |
| 11 | 0x50B5C6 | same | (new) | ICF twin of GameWindow::vslot10 |
| 12,13 | 0xB3FD0 | same | (new) | 1-byte ret ICF |

Blocked: slots 1, 2 and 7 move unique or placeholder rows onto a GameWindow
slot name; rename.py --to-class needs a name_lane approval (two workers' blind
votes) for each. Slots 3-5 and 11-13 could land as add_match ICF twins
(AptTimeLine precedent), but adding slots 11-13 to the canonical base shifts
every derived screen's own new virtuals, so do them together with the derived
tables, not alone.
