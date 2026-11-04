# ObjectCreationUpgrade load-post-process prerequisite (2026-11-04)

Inspected revision: 178df977b6. Scope: the approved ObjectCreationUpgrade.cpp
and ObjectCreationUpgrade_loadPostProcess.cpp fragment, under existing file claims.

Target facts: row 0x004B3FCB is the 17-byte +8 UpdateModule-subobject override.
It calls UpdateModule::loadPostProcess, adjusts this by -8, and tail-jumps to
0x000B3FD0. The current UpgradeMux header declares its protected hook; the
UpgradeModule.cpp owner rows upgradeMuxLoadPostProcess at that folded empty body.
The earlier StringBase<unsigned short>::validate binding named the same empty
body, but introduced an unrelated private template that collides with the TU's
real string header. No new name, pin, table or fold row is needed.

Donor facts: the committed ZH GeneralsMD ObjectCreationUpgrade.cpp:133 calls its
UpgradeModule base; UpgradeModule.cpp:77 calls BehaviorModule::loadPostProcess
then UpgradeMux::upgradeMuxLoadPostProcess. This corroborates semantics; the
BFME2 subobject layout and call addresses above come from the target.

Change: call the protected canonical UpgradeMux hook directly. Reconcile only
the seed/fragment ObjectCreationUpgrade declarations using tu_views.Tool.run
(only ObjectCreationUpgrade, explicit files and seed). The supported tool keeps
layout, frozen-file, byte and external-symbol checks enabled. Keep meaningful
parameter spellings; no local/parameter rename is needed in this complete body.
Remove duplicated offset comments produced by repeated view reconciliation.

Verification:
- Normal build.sh: 25/25 matched across the two sources, one data row verified;
  string, float and import references pass. Declared-unmatched: no findings.
- eh_verify.py: all four EH graphs EXACT, no baseline findings or missing objects.
- Fresh ordinary seed build before/after: all 47 definitions, body bytes and
  relocation tuples identical; no added or removed external symbol.
- Fragment: identical bytes 568bf1e8000000008d4ef85ee900000000. Relocation +4
  remains UpdateModule::loadPostProcess; +13 changes from StringBase wide
  validate to UpgradeMux::upgradeMuxLoadPostProcess, both rowed at 0x000B3FD0.
  One definition preserved, no extra definitions. See object-comparison.json.
- Bounded link_check preview on the 2026-11-04 17:56 index (8c757ea0db):
  both LINKS, own current bytes 1521+17. This is no new census/headline credit.

Initial supported merge dry-run rejected all four candidates: this fragment's
StringBase redefinition, ctor missing declaration/opaque bases, ModuleData ctor
base/layout mismatch, destructor bytes. This prerequisite clears the string and
leaf declaration conflicts only; actual composition still requires a fresh
supported merge and provider/consumer/path audit. Ctor/dtor/ModuleData issues
remain separate and are not claimed resolved.
