# VideoPlayer element destructor composition prerequisite

Inspected base: `0243cbb3d75b1fbe0549fe9d300c460e87b7e6aa`.

The supported VideoPlayer merge dry-run rejects the element destructor donor
because the seed declares `m_owned` as `void *`, whereas the donor reads it
through a typed pointer. An explicit `static_cast<Rva00688980 *>` accepts
either declaration without changing the donor's current typed member or layout.
This is a composition prerequisite, not evidence of retail's member spelling.

Verification of `Code/Libraries/Source/WWVegas/WWLib/Rva001D28F0ElementDtor.cpp`:

- `./build.sh`: all six rows byte-exact, including three parent-resolved
  funclets; string, float and named-import checks pass.
- `find_declared_unmatched.py`: all defined functions matched.
- `eh_verify.py`: one EH graph EXACT, zero missing objects or exceptions.
- Isolated `tu_skeleton.Verifier` builds of the committed and changed donor
  retain all six rows. Normalized `link_census.object_facts` are identical:
  four COMDAT copies, one exclusive definition, five undefined symbols and
  zero weak aliases. No alias is removed.
- Sequential `link_check.py --prepare-current` accepts the changed provider
  with a strict receipt. Ordinary preview reports LINKS, 138 -> 138 authored
  bytes against census `c95fcfcfcd`, 2026-11-05 05:17 UTC. This is a prediction;
  no real-link or census gain is claimed.

An isolated two-source composition using the supported composer's `first`
and `longest` strategies now compiles. The seed's existing rows and the
destructor/EH rows remain exact. The sole missing ledger symbol is the
9-byte helper at 0x00689740:
`??$_Destroy@VRva001D28F0Element@@@_STL@@YAXPAVRva001D28F0Element@@@Z`.
The seed's `struct Rva001D28F0Element` instead emits the corresponding `U`
class-key spelling. Its other vector helpers already use that spelling.
The declaration-union strategies additionally place the element declaration
after its first vector use and fail compilation. The supported whole-TU
dry-run therefore still accepts no donors; no merge was applied.

Next step: reconcile the element class-key identity, its helper ledger name
and affected provider/consumer bindings before another merge. The Add/Get/Remove
flag overrides and SubsystemInterface/canonical VideoPlayer prerequisites
remain separate. No source path, ledger row, pin, hatch or debt key changes
in this prerequisite commit.
