# BitFlags clear provider prerequisites, 2026-10-30

Base: `c647a75e55`. Published provider index: `12b9e7a7c0`,
2026-10-30 10:11. Scope: LINK-030; no census gain is claimed.

## Target facts and change

The existing 14-byte `BitFlags<116>::clear` owner at `0x00666E80` is
`Common/System/BitFlagsClear.cpp`. Its raw bytes are
`33c0890189410489410889410cc3`: clear four dwords and return.
The prior ownership evidence is in `bitflags-clear-owner-20261023/readme.md`.
The current index still selects a wrong clear copy and rejects the owner's
18-byte bitset reset against the earlier 20-byte reset copies.

DumbProjectileBehavior and WeaponSet now declare the existing clear
specialization before PreRTS includes KindOf's inline helpers. The early
BitFlags include uses the same array-placement-new guard as PreRTS. This
resolves both previously recorded trial failures: C2908 after instantiation,
and C2084 from including the CRT array placement operators before GameMemory.
No header, layout, ledger identity, pin or source path changes.

The `#line` directives preserve each original PreRTS line number. Without
that preservation, three GetGameLogicRandomValueReal diagnostic line-number
arguments in the unrowed projectile-fire body change by eight. That trial
was corrected; the final body is identical to the input object.

## Object comparison

Comparison uses strict-current pre-edit objects copied under
`build/bitflags-clear-link/`, `link_census.comdat_bodies` fingerprints and
`allowed_symbols.Obj` raw bodies/relocations.

| Unit | External COMDATs before/after | Identical retained fingerprints |
| --- | --- | --- |
| DumbProjectileBehavior | 786 / 784 | 783 |
| WeaponSet | 663 / 661 | 659 |

Each object removes exactly `BitFlags<116>::clear` (5 B) and
`bitset<116>::reset` (20 B), adding no definition. All retained raw bodies
are identical. The only retained fingerprint changes are four REL32 calls
from bitset reset to the declared clear:

- BitFlags parse: offsets 192 and 261 in DumbProjectileBehavior.
- CLEAR_KINDOFMASK: offset 5 in WeaponSet.
- WeaponTemplateSet clear: offset 34 in WeaponSet.

Each object's undefined-name set gains only the existing clear symbol and
loses nothing. These calls clear the same leading bitset through its existing
owner. This establishes the local binding change, not recovery of the other
unrowed donor bodies or their original source placement.

## Verification and remaining boundary

- `find_declared_unmatched.py` passes both edited units before and after.
- `./build.sh` passes 4/4 rows in the two edited units.
- `link_check.py --prepare-current` passes 5/5 rows across both edited units
  and the unchanged clear provider, with reusable strict receipts.
- Ordinary three-source preview retains 0/3 LINKS, 0 -> 0 authored linked
  bytes against the index above. The unchanged Player copy still prevents
  selection of the retail clear. Its reset copy also remains. The two edited
  units retain their independent unresolved/class/COMDAT obstacles.
- The staged-tree batch audit is INCONCLUSIVE: the index predates the base,
  and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Full consumer selection/loss verification remains open. Carry the
  two repaired provider objects, clear owner, Player and affected consumers
  into the next scheduled census.

`Common/RTS/Player.cpp` is held by another worker, so it was not edited.
Next: when that scope is available, apply the early declaration there,
preserve its existing kindmask test specialization, verify its twelve rows
and all four providers together, then repeat the consumer audit. The owner
must lose both its clear-selected and reset-COMDAT blockers before LINK-030
can be cleared. No debt key or headline figure is retired here.
