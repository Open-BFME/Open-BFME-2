# SiegeDeploy pool-key consolidation

Scope: the approved SiegeDeploySpecialPower.cpp TU and its pool-key donor.
Starting revision: 48f3cd2042; declaration prerequisite handed to the fleet
publisher separately (current rebased commit bab93329e3). The default picker
claimed the seed and eight donor file scopes for codex3.

## Evidence and applied change

The target's existing row at 0x004C577C is the 69-byte virtual const
getModuleNameKey method: it guards a local key initialized from the literal
"SiegeDeploySpecialPower" through NameKeyGenerator::nameToKey. Its compiler
guard-clear funclet and EH handler already own 0x00790124 and 0x00790131.
These are existing matched bodies, not newly recovered coverage. No donor
source path or complete original class layout is inferred from this evidence.

The seed lacked the method declaration. Adding it emits no new vtable in this
partial view. The prerequisite retains 12/12 rows across both objects, the
seed's one data row, all 27 COMDAT fingerprints, strong definitions, undefined
targets and relocation graphs. Strict reusable receipts pass for both units;
the bounded preview retains two clean units and 794 bytes (715 + 79).

`tu_skeleton.py --merge` rebuilds approval in memory because the committed map
is stale, accepts only the seed and pool-key donor, and removes one Code source
file. It repoints three function rows and their TU-map source cells, plus the
two data-ledger ownership records at RVAs 0x00A0427C and 0x00A04280. It does not
regenerate the committed map. TU approval is provisional name/parent evidence,
not a newly established retail __FILE__ path.

After composition:

- The frozen-file check passes; `./build.sh` verifies 12/12 rows, one data row,
  two strings and three compiler float literals. Both parent EH graphs are
  EXACT, including the renamed local funclet labels.
- The merged object equals the precomposition objects' union: 27 normalized
  COMDAT code/relocation digests, seven strong definitions, 35 undefined names,
  one weak binding, 46 relocation roots and 21 reference-edge entries. There
  are no added dependencies or changed external bindings. The weak deleting
  symbol remains listed as both defined and undefined, just as before.
- Strict provider preparation passes. The ordinary preview against index
  12b9e7a7c0 retains 794 bytes in the destination; its apparent 715 -> 794
  change is the absorbed donor, with no linking gain. The merge's census
  LinkGuard accepts the retired-donor composition.
- `check_csv.py` passes with 99,014 function rows unchanged. The planner is
  regenerated after the merge; `--check build/consolidation` passes and the
  selected subsystem's source count falls from 209 to 208.

## Registers, consumers and remaining work

Neither absorbed source has gate, code-identity, data-check baseline, hatch,
flag or canonical-header queue debt to retire. The two data-ledger records
transfer ownership with their existing identities; totals are kept. The seed's
field table stays owned by the seed. Scoped Microsoft-header queue refresh
finds no local Microsoft declarations and changes no queued debt. The Thing
header prerequisite stays on the rejected Update donor.

The data check remains shadow outside converged addresses: the seed's existing
initiateIntent guard differs from the ledger's clearer name at RVA 0x00A04290;
composition additionally renumbers the pool-key guard from $S1 to $S2 at
0x00A04280. The pool key still binds to 0x00A0427C. Reading the current matched
rows' DIR32 operands confirms these exact bindings; the normal byte and EH
checks pass. These compiler guard-name findings are retained explicitly, not
baselined or claimed retired. Enforced converged checking passes for all 11
protected addresses, with no second names or unjudged rows.

The path-consumer audit covers every pending source deletion over fetched
origin/master d67de25390: this pool-key donor, Rva00451EACMethod.cpp into
SpecialAbilityUpdate.cpp, and Coord3DVectorResizeValue.cpp into
W3DQuadrupedDraw.cpp. Combined searches of tools, hooks, workflows, source
includes, build/configuration files, documentation and reverse registers find
no active old-path consumer. Remaining mentions are source provenance comments,
historical attempt/deleted-row evidence and the last census's link_status.csv;
they are retained. Current ledgers and queues resolve to surviving owners.

The staged-tree outgoing link audit is INCONCLUSIVE: index 12b9e7a7c0 predates
base d67de25390, and the broader affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. It proves no loss
and supplies no full-image clearance. Carry all pending source moves and their
broader provider/consumer scope into the next scheduled census; no census or
smoke runner was started.

Remaining donors need separate verified prerequisites: constructor and slot
declarations; computeApproachPoint/setPhase declaration ordering and point
views; Xfer's UpdateModule hierarchy; Update's AICommandInterface hierarchy
and canonical Thing adoption; destructor/base-vtable reconciliation. The
private AIUpdateInterface, UpdateModule, Object and SiegeDeploySpecialPower
views disagree across donors. Two mixed common getter files remain outside
this merge. No rejected donor was edited or left nonmatching.
