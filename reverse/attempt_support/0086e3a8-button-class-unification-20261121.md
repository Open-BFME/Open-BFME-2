# 0x0086E3A8 `??_7Rva007B401CButton@@6B@`: a class unification, not a slot fix

Target facts (retail bytes and the ledger):
- Table 0x0086E3A8 has 2 slots: 0x00574B4C `??_GRva00574499@@QAEPAXI@Z`
  (FamilyDeletingDtors_Rva00574499.cpp) and 0x005742A1
  `?rva005742A1@Rva005742A1@@UAEXPAVINI@@@Z` (GapBodiesS3E.cpp, INI parse with
  Title +0x08 and Help +0x0C).
- Its base table 0x007E6BA8 has 2 slots: 0x0022168A `??_GRva0022167C@@QAEPAXI@Z` and
  `__purecall`. 0x0022167C `??1Rva0022167C` stores it, and 0x00221635
  `??0Rva00221635` builds the same 8-byte base.
- The initializers 0x007B401C and 0x007B4081 construct 16-byte objects at 0x00E062FC
  and 0x00E0630C and register atexit thunks running `??1Rva00574499` (0x00574499).

Inference: one class, which the ledger spells four ways.
- Base: `Rva00221635`, the same class as `Rva0022167C`. It has a virtual dtor and a
  pure slot 1.
- Derived: `Rva00574499`, the same class as `Rva005742A1` and `Rva007B401CButton`. Its
  members are AsciiString at +0x08 and +0x0C, and slot 1 is `rva005742A1(INI*)`.

Steps needed. Each is a separate verified rename and contract change.
1. Merge `Rva0022167C` into `Rva00221635`:
   - Make `??1`/`??_G` `--virtual` and move them `--to-class`.
   - The canonical header's inline `virtual ~Rva00221635() {}` must become the
     out-of-line 0x0022167C.
2. Edit the `Rva00574499` contract: base `Rva00221635`, polymorphic, with an inline
   ctor `(const AsciiString&)` that zeroes +8 and +C. Then regenerate the header and
   re-verify its 9 consumer units.
3. Run `rename.py function --virtual` on 0x00574B4C, and `--to-class Rva00574499` on
   0x005742A1.
4. Drop `Rva007B401CButton`, its `/alternatename` hatch and its private class.

Not attempted: the size and the contract churn are beyond a single bridge item.
