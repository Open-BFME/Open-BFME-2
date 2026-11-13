# LINK-665: Rva0056AE4A's `ac26Slot1` override was declared but never defined (P149)

Status: Repaired locally, awaiting landing and the regression monitor's RECOVERED. Updated: 2026-11-13 (seat6,
placeholder lane); base `9c8be4d702f`, repair commit "P149: row 0x0056A9A3 as Rva0056AE4A::ac26Slot1, the slot
the link left unresolved" (branch `p149`; reviewed as `3c92b20bcc5`, the same tree).

**Symptom.** The real link of master has failed since `5968bf97836` with `LNK2001
?ac26Slot1@Rva0056AE4A@@UAE_NXZ`. Only `Rva0056AC26Derived.obj` references it: it defines the destructor and so
emits the vtable. The regression monitor found it at `abefa434563` (integration results 20261113-0313); the last
green link was at `c40bbd895a`. The packet is `~/bfme2-ops/swarm/global_packets/0056A9A3_P149_*` on srv1.

**Cause.** `5968bf97836` moved Rva0056AE4A onto the canonical `Rva0056AC26.h` base, whose slot 1 is
`virtual bool ac26Slot1() = 0`, and declared the override. No unit defined it. The same commit removed the
`/alternatename` that had bound `?ac26Slot1@Rva0056AC26@@UAE_NXZ`.

**Retail.** The constructor 0x0056ADF1 and destructor 0x0056AE4A install table 0x0086D23C at +0. Its slot 1 is
0x0056A9A3 (18 bytes): the logic singleton's +0x100 >= this+0x14, unsigned, with sbb/inc writing 0 or 1 to all of
eax. No other retail table, and no rel32 call or jump, reaches the body. The body was rowed as
`?rva0056A9A3@Rva0056A9B5@@QAEHXZ`, a non-virtual int member of a view class.

**Repair (`3c92b20bcc5`).**
- `Rva0056A9B5GuardedOneSetter.cpp` defines `bool Rva0056AE4A::ac26Slot1()`. `bool` compiles to retail's 18 bytes,
  so the base contract and the ACFF and AC82 overrides do not change.
- `Rva0056ADF1Ctor.cpp`'s `_vtbl_00C6D23C` names it in slot 1.
- The old row is tombstoned, and the new row added by `add_match.py`.
- Verified:
  - 4/4 and 36/36 rows, plus both data rows;
  - objects: the setter defines the symbol, and the vtable and constructor units reference it;
  - `link_check`: 3 of 3 link cleanly (LINKED 404 -> 404 bytes).

**Process note.** The retraction and the new row are one commit. A retraction-only commit fails the pre-commit hook:
`_vtbl_00C6D23C`, a matched data row, then names a symbol with no ledger address ("Data rows: FAIL 1 of 2"). The
coordinator granted an exception to docs/naming.md's separate-retraction rule for this commit (the owner can
override it), as the smallest change that passes the hooks while master's link is broken.

**Next check.** A real link of master after landing: no `?ac26Slot1@Rva0056AE4A@@UAE_NXZ` unresolved (the monitor
logs RECOVERED), and slot 1 of Rva0056AE4A's primary table in the image is the 0x0056A9A3 body.

**Related.** [LINK-663](link-663-a-rebased-scaffold-view-emits-a-short-copy-of-the-real-class-s-table.md) (the
Rva0056AD19 scaffold's table and its `ac26Slot1` override); [LINK-660](link-660-canonical-header-adoption-drops-unit-novtable.md)
(the Rva0056AC26A/B adoption).
