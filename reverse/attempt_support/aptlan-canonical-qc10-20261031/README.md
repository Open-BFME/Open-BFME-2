# AptLanLobby canonical-header prerequisite, qc-10

No source edit or adoption is claimed. Current base faba3d8243.

The slot conflict is resolved from retail, not by the private-view majority:
VA C3E0F8 is the primary table, with fifteen code entries. Slot1 is message handler44522D (ret12), slot2 is448826, slot5 is OnUpdateData446443, slot12 is442DB, slot13 is446772, slot14 is MPOwnerValidatGameInfo444208. The next word is string data, not slot15. Thus GameCreate's slots0/1 and MPOwnerValidat's slot0 are both incomplete projections. They cannot be copied into a canonical virtual sequence.

The full matched constructor445EE3 (1187 bytes), destructor44455C (288 bytes) and factory2D1F77 prove size6C4 and interfaces0/218/27C. The existing constructor consumes _bfme_AptGameWindow (27C) and Rva004444D2 (C), with panel288, sorter668, preferences684, string6A0, state6A4, entry6AC. It explicitly warns that those are consumed views, not a complete virtual-interface recovery. Neither base has a canonical header. Its GameWindow declaration has only a destructor; simply adding AptLanLobby's fourteen slots to it would invent the base/override relationship and can emit wrong primary tables and this-adjusting thunks.

Raw primary slots3,6,8,9,10 resolve to existing GameWindow witnesses: draw A12F8, vslot6 313913, vslot8 31393A, vslot9 8FF78 and shared false50B5C6. Slot4 is an ICF ret8 true worker444680; slot7 is a ret0 constant worker44643D; slot11 shares the false worker. Folded bytes and stack widths do not prove base member names or constness. In particular a new named virtual on the derived class does not automatically override a differently named inherited GameWindow virtual. No alias/pin is added to paper over that binding.

The owner/interface table C3E098 has its own callback ordering and secondary deleting thunks. The constructor passes static_cast<Rva004444D2*>(this) as the setup owner. Its slot descriptions must stay separate from the primary table's slots.

The handwritten header must therefore start by reconciling the _bfme_AptGameWindow/GameWindow and Rva004444D2 base interfaces, then override primary slots1/2/5 and introduce/override12..14 at their established places. A flat padding-only class would hide known inheritance and is deliberately not registered. Once that prerequisite exists, the two requested bodies can use the same 6C4 layout and slot1/12/14 declarations; no body behavior changes are presently needed.

header_adopt_lane dest reports no BFME1/ZH header: choose Code/GameEngine/Include/GameClient/GUI/GUICallbacks/Apt/AptLanLobby.h once the bases are resolved. contract-report.txt preserves both explicit inherited-field conflicts (+C and +88), and retail-tables.tsv preserves the table reads. Both listed sources pass find_declared_unmatched before any proposed edit.
