# FireWeaponUpdate StringBase donor prerequisite (2026-11-04)

Base: `c685a827a7`. Preview index: `a62ac1c10b`, census 2026-11-04 07:28.
Scope: `Code/Libraries/Source/WWVegas/WWLib/string_base_clear.cpp`.

The current FireWeaponUpdate merge dry run accepts no donor. The cleanup
wrapper donor redeclares StringBase after the destination has included the
shared header, producing C2953/C2955. Replace that private template and its
already-header-defined bodies with the existing frozen shared header. Keep
all ten explicit instantiations and the leak-hook body. No shared header,
ledger row, pin, alias or register changes.

Verification:

- `./build.sh Code/Libraries/Source/WWVegas/WWLib/string_base_clear.cpp`:
  10/10 matched; string, float and import references pass.
- `find_declared_unmatched.py` before/after: all defined functions matched.
- `class_gate.py` passes.
- Ordinary `link_check.py` before/after: LINKS, 18 -> 18 unique authored bytes.
  This is a preview against the named index, not a new census measurement.

The module-data constructor's explicit vtable declaration still conflicts
with the destination's virtual class. The replacement method donor has a
flat FireWeaponUpdate view with the owner under the real UpdateModule bases;
its method is absent from the destination declaration. Weapon-header work
is held by a peer, so no Weapon definition or provider is changed here.
The mixed donors remain out of scope. Retry the guarded merge after this
prerequisite, retaining only its independently verified composition.

## Supported composition and claim outcome

After cleanup, `tu_skeleton.py --merge .../FireWeaponUpdate.cpp --dry-run`
accepts the destination plus `string_base_clear.cpp`, preserving 27 rows under
the destination flags. It rejects the other two donors with C2039/C2065 and
C2373, respectively. The merger's census link guard accepts this trial.

The actual `--merge` at `a0fd3c01c9` refuses before writing because peers hold
`0x000B3FD0` and `0x0048BA39`. It reports no accepted or rejected donors and
releases its acquired scope. Thus no file is removed, no ledger path changes,
and no source-reduction gain is claimed. Retry only when those claims are free;
the verified shared-header prerequisite is independently published.

A path-consumer survey found no active tool, hook, workflow or include that
hard-codes this donor. Remaining mentions are comments, historical evidence,
the census status, and STLport trial records. Because no path move was applied,
no consumer repointing or protected-register transfer is needed. Code identity
reports 10 rows and zero new findings; data identity reports zero findings.
Ledger validation remains clean (99,440 function rows). Header queues and
existing hatch/register ownership are unchanged.
