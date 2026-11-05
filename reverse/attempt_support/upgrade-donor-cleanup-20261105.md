# Upgrade donor-only method cleanup — 2026-11-05

Inspected base: `8ccf129796`. Scope: `Code/GameEngine/Source/Common/System/Upgrade.cpp`.
No code/data rows, pins, aliases, approved TU paths or source paths move.

Removed five unledgered Zero Hour definitions and their existing
`present-unmatched` markers: `UpgradeTemplate::calcTimeToBuild`, its one-argument
`calcCostToBuild`, `UpgradeCenter::findNonConstUpgradeByKey`,
`firstUpgradeTemplate`, and the three-argument `canAffordUpgrade`.
These are existing donor placeholders, not lost retail rows. The named retail
cost worker already has a different signature at 0x0026EF50, and the affordable
upgrade worker is owned at 0x0026F11A. No new retail identity is inferred here.

## Provider check

Compared external definitions in the ordinary before/after objects, then
scanned all 24,827 `build/match/*.obj` COFF symbol tables (including harvest
objects) for undefined/weak references to removed names. None of the five
removed methods has an outside reference. The automatically removed inlines,
float constant and message literal also have no outside references except
`AsciiString(const char *)`, which ThingFactory references and 1,042 other
compiled objects still define. Detailed final scan: [JSON](upgrade-donor-cleanup-provider-scan-20261105.json).
This is a local compiled-object inventory, not a claim that every object has a
current receipt or that the game links.

An initial broader trial also removed the three snapshot methods. That scan
found UpgradeCtor.obj references `Upgrade::crc`, `xfer` and `loadPostProcess`.
All three definitions and markers were restored before final verification.
The link-wide BfmeVector push_back alias is retained unchanged.

## Verification

- `./build.sh Code/GameEngine/Source/Common/System/Upgrade.cpp`: 27/27 exact;
  string, float and import references pass. Fifteen compiler-label rows resolve
  through their parents' EH data, including labels renumbered by the deletion.
- `find_declared_unmatched.py`: passes; remaining marked definitions: three.
- `hatch_counters.py --update`: `present_unmatched` 2,260 -> 2,255; only the
  five source keys above leave the register. No gate, data, identity or header
  debt is retired.
- Ordinary `link_check.py`: LINKS, 754 -> 754 bytes, index `c95fcfcfcd`,
  2026-11-05 05:17. This is a preview, not a census gain.
- The normal `tu_skeleton.LinkGuard` prepared the destination's current rows
  and judged its ordinary rebuilt object: `prepare=None`, `judge=[]`;
  the destination is census-linked. This checks this one changed object
  against the published index; the outgoing hook still owns the batch audit.
- `git diff --check`: passes.

## Lifecycle donor prerequisite narrowed

Used `tu_skeleton.compose` and its ordinary scratch `Verifier` on only the
seed plus UpgradeCtor.cpp, allowing header-owned Upgrade and UpgradeStatusType
redefinitions to be dropped as the merge search does. The original composition
matches the seed's 27 rows and misses all three lifecycle rows. Selecting the
canonical moduledata Snapshot explicitly before the seed's includes also
matches only 27/30. No nonmatching candidate was left under Code/.

Target facts: the independently byte-verified constructor is 29 bytes, with
template/status/next/prev at +4/+8/+0xC/+0x10. Its destructor and deleting
destructor have public `UAE` manglings. Donor facts: the seed includes Zero
Hour's Upgrade, inheriting MemoryPoolObject and Snapshot and declaring its
destructor protected through pool glue. The composed constructor is 86 bytes,
uses EH, and stores those fields at +8/+0xC/+0x10/+0x14; its destructor symbols
are `??1Upgrade@@MAE@XZ` and `??_GUpgrade@@MAEPAXI@Z`, so the ledger's public
names are absent. Snapshot inclusion alone cannot reconcile that derived view.

Next: reconcile the seed's Upgrade declaration with the already verified
single-Snapshot lifecycle view before retrying the lifecycle merge. Preserve
its three existing snapshot providers until their vtable identities are
reconciled. Other canonical subsystem, parser, specialization-order and
Rva0026F684 donor obstacles remain unchanged. No full donor search was repeated
and no merge/source-file reduction or new linking coverage is claimed.
