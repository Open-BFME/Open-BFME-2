# BoneFXDamage canonical exception adoption and current providers

Inspected revision: `dd65af9110`, including the upstream canonical module
rewrite. The real-link blocker list and local provider index predate that work.

Change: replace the TU-local eight-byte INIException declaration with
`Common/INI/FieldParse.h`. The canonical declaration retains the same
constructor, copy constructor, destructor and field layout. No body, vtable
contract or binding is changed. `header_adopt_lane.py accept --class
INIException Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`
passes and retires exactly its one header-queue row through the owning tool.

Verification:

- Before and after: `./build.sh BoneFXDamage.cpp` verifies 9/9 function rows,
  both renumbered funclets through parent EH data, and three string literals.
  Float and import checks pass; declared-unmatched checks pass.
- The consumer-only preview still sees missing destructor and DamageModule
  snapshot providers because its index is `112a456a2c`, 2026-11-05 15:52.
- Before and after adoption, overlaying **all three current objects** using
  `link_check.py BoneFXDamage.cpp DamageModule.cpp Rva004B96CCDerived.cpp`
  reports 3/3 LINKS, 165 -> 519 scoped linked bytes: BoneFXDamage 322,
  DamageModule 38, destructor-provider unit 159. This is a preview, not a
  census or real-link measurement. The obsolete crc reference is gone.

Consolidation was investigated through the supported `name_lane.py
consolidate --under Code/GameEngine/Source/GameLogic/Object/Damage/` planner
and `tu_skeleton.py --plan` / `--merge ... --dry-run`. The fresh in-memory map
approves BoneFXDamagePoolKey.cpp's three rows (69-byte getter, 13-byte
funclet and 10-byte EH handler). The merge compiles, but the guard refuses it
because the index lacks the same three providers proven current above.
No merge was applied, no donor was deleted and no gate was changed. The
false reject is recorded in re_attempts.log. Retry after the published index
includes the provider repairs. Two other donors are mixed files; the static
pool-key placeholder's eventual virtual identity remains a separate task.

Outgoing path audit: checked `origin/master..dd65af9110` against upstream
`ea2d384db7` plus this adoption. The only removed source in the existing five
commits is ActiveBodySetMaxHealth.cpp, absorbed into ActiveBody.cpp. A combined
basename/path search of tools, hooks, workflows, Code, shims, docs and reverse
finds only the retained historical census row, merged origin comment and
historical attempt evidence. No active path consumer needs updating; its
function/TU/header records already point to ActiveBody.cpp. This adoption
changes no source paths. Existing per-commit verification remains applicable.

No measurement, smoke runner, runtime or headline linking gain is claimed.
