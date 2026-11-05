# W3DShadow consolidation prerequisite (2026-11-05)

Inspected revision: `5edd7860d9`. Scope: `W3DShadow.cpp`,
`AudioEventRTSAssign.cpp` and `W3DShadowManagerAddShadow.cpp`.

The supported planner surveyed the Shadow directory. Its committed map is
stale; `tu_skeleton.py` rebuilt current approvals in memory. The initial
merge dry run accepted no donor: both hit the seed's private StringBase
template when their shared ASCII header was included.

Target fact: the second guarded dispatch in the complete 61-byte
`Rva0009A2CDRun` calls the folded empty body at RVA `0x000B3FD0` with the
shadow-manager pointer as receiver. The StringBase spelling did not establish
the receiver's type or the original method name. Replace that private template
and its friend exception with the existing opaque `Rva000B3FD0` member
declaration. Its out-of-line owner is already rowed in `EmptyFoldTwins.cpp`;
no new name, pin, alias or code row was added. No donor name is asserted.

Verification of the prerequisite:

- `./build.sh .../Shadow/W3DShadow.cpp`: all 17 rows match; four unwind labels
  verified through the existing parent EH data; literal/import checks pass.
- `find_declared_unmatched.py` before/after: all definitions matched.
- `class_gate.py`: pass. `hatch_counters.py --update`: class exceptions 31 -> 30.
- `link_check.py`: LINKS, 1,237 -> 1,237 authored bytes against the
  2026-11-05 05:17 census index at `c95fcfcfcd`. This is a preview, not a census.
- A fresh supported merge dry run accepts the seed plus the assignment donor.
  The addShadow donor still fails declaration ordering (`Shadow::ShadowTypeInfo`)
  and requires reconciliation of its manager views and canonical headers.

The existing GlobalData and W3DShadowManager header-queue debts remain owned
by their sources. No protected debt is retired except the removed class hatch.
