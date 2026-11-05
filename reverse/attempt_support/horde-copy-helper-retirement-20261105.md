# Horde erase copy-helper identity cleanup

Inspected revision: `f87dd00ce4`; census index: `c95fcfcfcd`,
2026-11-05 05:17. Scope: `HordeMeleeSwarm.cpp` in WWLib and
`GameClient/GUI/InGame/Tactical/BannerUI.cpp`.

The swarm range erase at 0x005842F7 called a separate
`__copy_ptrs<BfmePod28*, BfmePod28*>` specialization, marked
`present-unmatched` and pinned to 0x002161A5. That address already has a
29-byte matched `__copy_ptrs<Rva00215FEFElement*, ...>` owner in BannerUI.
Its rowed 50-byte forward-copy worker is 0x00215FEF. This cleanup reuses
those existing identities; it does not recover the retail element name or
change either element layout.

Both erase callers now cast their existing element pointers to the rowed
helper's view. BannerUI's single erase at 0x00216267 is specialized with
the same STLport control flow. Both TUs emit the dispatcher as an identical
inline, noinline specialization so it remains a selectable COMDAT without
inlining into either caller. A declaration-only trial added empty-tag stack
initialization and failed the 38-byte range erase; a strong specialization
duplicated BannerUI's provider. Neither failed variant remains.

Consumer checks: a source search and the census index's per-object touches
both identify only these two units as defining or referring to the old
decorated helper name. Updating only the swarm leaves BannerUI unresolved;
the committed change updates both. The unused pin and the swarm's unmatched
marker are removed. `hatch_counters.py --update` lowers pins 9,322 -> 9,321
and present-unmatched 2,322 -> 2,321. No other debt register, source path,
function row or linker alternate is changed.

Verification after pin removal:

- `./build.sh` both sources: 97/97 function rows and 3 data rows pass;
  27 nonempty/3 empty strings, 9 floats and 1 import verify.
- Both `find_declared_unmatched.py` checks pass. BannerUI retains its
  unrelated pre-existing deleting-helper marker.
- `link_check.py --prepare-current` prepares and byte-verifies strict reusable
  receipts for exactly these two sources; no census/index/status is updated.
- The paired ordinary preview preserves LINKS 1,947 + 4,901 = 6,848 bytes.
  The paired `--new-variants` check reports no new COMDAT variant. The swarm's
  emitted dispatcher was also read from its object and byte-compared against
  the existing 29-byte owner.
- `check_csv.py`, `pin_consistency.py --check` and `git diff --check` pass.

Wider batch audit against HEAD and the staged tree remains **inconclusive**:
the index predates HEAD, and the first unchanged affected consumer lacking a
current receipt is `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`.
The initial audit also lacked strict receipts for the two edited sources;
the explicit preparation above remedied that prerequisite before the final
audit. No full consumer clearance or census improvement is claimed. Next:
refresh the affected consumer receipts in their owned lane and repeat the
batch audit, or confirm the cohort in the next scheduled census. LINK-442
tracks that verification requirement. The setter/vtable consolidation
prerequisite in LINK-436 is unchanged.
