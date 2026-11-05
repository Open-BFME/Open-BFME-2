# AttributeModifierStore range-destroy merge prerequisite

Inspected revision: `7dc4b67c8e`; 2026-11-05; worker codexb5.
Scope: `Code/GameEngine/Source/Common/AttributeModifierStore.cpp` and the
three clean donors selected by the consolidation picker. Prior handoff:
[2026-11-04 reconciliation](attribute-modifier-store-tu-20261104-codex4.md).

## Change and verification

The seed explicitly instantiated `_Destroy<Rva00214ADC *>`, while
`StlSweepR3Rva00214B22.cpp` declared an explicit specialization. Combining
those declarations produced C2908 (specialization after instantiation).
Define the specialization before the seed's explicit instantiation, forwarding
to STLport's existing `__destroy` helper. This preserves the native loop and
helper emission while agreeing with the donor's specialization declaration.
It establishes no application element name or additional layout claim.

- `./build.sh` seed: 36/36 code rows and both data rows exact. The unchanged
  STL donor also passed its four rows in this pass.
- `find_declared_unmatched.py` seed: all definitions matched; existing
  `famgenDelete00214ADC` marker unchanged.
- `eh_verify.py` seed + STL donor: EXACT 7/7, including renumbered funclets.
- Before/after seed objects were built only through `./build.sh`.
  `link_census.object_facts` with a null retail verdict returns identical
  ordered facts: 90 COMDAT name/digest/size tuples, 21 strong definitions,
  33 undefined externals and one weak external. Serialized facts SHA-256:
  `50031d6b5bd104b7daa8064dcaec0accebaebfbc4fcede08e3643ea1e5941a7b`.
  No provider or alias disappears.
- `link_check.py` seed + STL donor + Rva0022CA95Dtor: 3/3 LINKS using the
  published index at `c95fcfcfcd`, census 2026-11-05 05:17. Current own-byte
  previews: 1,455 / 87 / 220. The seed's +16 relative to that older census
  already existed before this change; no linked-byte gain is claimed.

## Remaining composition work

A fresh `tu_skeleton.py --merge .../AttributeModifierStore.cpp --dry-run`
accepts the seed and Rva0022CA95Dtor. The STL donor now passes C2908 and stops
at C2910: its explicitly specialized vector destructor conflicts with the
seed's full `vector<Rva00214B22Record>` class specialization. Reconcile the
class and member declarations next, keeping the native base destructor's
symbol and EH target. Rva00214ACCPush still fails bytes; the three mixed
donors remain outside the batch.

Rejected trials were restored: `extern template` matched standalone bytes but
failed combined compilation (C2929); making the specialized vector inherit
`_Vector_base<BfmeE16>` preserved the main destructor but changed the unwind
funclet's required `_Vector_base<Rva00214B22Record>` target. A direct range
loop was byte-exact but stopped emitting two helpers; forwarding to `__destroy`
keeps the entire original object-fact set instead.

An earlier actual merge attempt wrote nothing after claim acquisition failed;
the shared 0x0007FAB3 row was held by another worker. Do not bypass that claim.
This commit moves no path or ledger row, retires no debt and changes no hatch.
The NameKeyGenerator header-queue item remains. No source-file reduction,
real-link measurement or census improvement is claimed.
