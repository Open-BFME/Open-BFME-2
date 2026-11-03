# ObjectCreationUpgradeModuleData tail representation reconciliation

Scratch-only private prerequisite,2026-11-03. Control source SHA256:fd3eb1d5fbe9c16aa7a10ccd256ef2c3d9bfc5c18f1cf4d6d35c7f5eba2dd712. Candidate replaces seed's opaque m_tail[0x154-0x12C] with the EXACT existing Update vocabulary and representation: Coord3D m_offset, float m_angleOffset, unsigned char m_pad13C[0x14C-0x13C], unsigned int m_fadeInTime and bool m_useSpecialContext. It includes the existing Lib/Coord3D.h at the data-class declaration. No fresh field name is invented or merely used to hide padding; these are the existing typed fields that a later mechanical pair-view tool must reconcile.

The data class remains __declspec(novtable), privately stores its fields and three real AsciiString members, and derives the SAME existing four-byte Snapshot. Its actual destructor and lifetime behavior are unchanged; no canonical eight-byte ModuleData base is substituted. Candidate contains no scratch assertions or /Z7 flag.

Sanctioned private Verifier passes ALL20 source rows for control and candidate. The three actual parent EH graphs (pool key, removal, data destructor) are EXACT in both. All31 ordinary external code/data definitions and symbolic relocation contexts compare IDENTICALLY, with no additions, removals or changed definitions. No new vtable/provider or source-path move is made.

A separate sanctioned private /Z7 observation, with all20 rows still exact, supplies compiler CodeView layout read by tools/class_layouts.py. It confirms class key, Snapshot base at0, sizeof0x154; opaque prior-state storage at+4 length0x11C; AsciiString members at0x120/0x124/0x128; Coord3D at0x12C size12; angle at0x138 size4; padding at0x13C size16; fade-in uint at0x14C size4 and special-context bool at0x150 size1. layout-proof.json preserves the raw compiler-derived result. This diagnostic does not change the clean candidate's compiler profile or assert complete retail class/table recovery.

Root should reject application if the captured control hash has changed, then perform normal/strict/EH/link checks and later supported class-view/merge tools. No tracked source, ledger, claim, network, shared match-cache or check mutation occurred. No sourcefile or census credit is claimed by this representation prerequisite alone. Artifacts are candidate.cpp/control.cpp, proof.json, layout-proof.json and private objects.

Tracked application matches captured control before adopting these exact existing
field names/types. It additionally grants the owning ObjectCreationUpgrade
friend access to the private data view for the forthcoming shared declaration;
private data access and Snapshot/novtable/string/destructor representation stay
otherwise unchanged. Normal20/20 and strict receipts pass, and the actual normal
object including that friend declaration retains all31 external definitions and
ordinary relocations exactly. This is a real typed storage reconciliation, not
renaming an overlapping field to bypass the class-view layout check. Complete
ModuleData base lifetime/table work and actual source composition remain separate.
