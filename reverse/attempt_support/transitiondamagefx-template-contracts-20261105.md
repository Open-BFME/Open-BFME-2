# TransitionDamageFX consolidation prerequisites

Inspected `bdbf2ed06c`, 2026-11-05; INI adoption is separately recorded in
`13e3e98e1a`. The picker claimed the approved seed and four unmixed donors.
The supported consolidation planner rebuilt the stale TU assignments in
memory: 75 approved rows, five files, seven excluded mixed donors. No map,
source path, pin, alias, generated source or debt baseline is changed here.

## Retained repairs

The map-load donor now calls the existing `vector<Rva004BA1D0>::push_back`
through an explicit vector view, as the seed's neighbor parser already does.
This permits the seed's `TensileFormationUpdateMember` member declaration to
compile with the donor body without asserting that Rva004BA1C8 and
Rva004BA1D0 are the same native type. The retail append provider is the
existing 55-byte row at 0x004BA7E0.

The seed formerly requested that provider through explicit instantiation.
The donor's declaration of an explicit specialization suppressed its emission
in the composed object. The seed now defines the equivalent STLport 4.5.3
member body explicitly. An `extern template` declaration was tested and
reverted: VC7.1 refuses simultaneous instantiation suppression and forcing
with C2929.

`./build.sh` verifies all 63 rows across the two sources, 15 unwind pins,
28 literals plus two empty-string references, one float and five named imports.
Both frozen-file checks pass. `link_check.py` preserves both units' LINKS
preview, 3,871 + 339 = 4,210 authored bytes, against the 2026-11-05 05:17
census at `c95fcfcfcd`. This is no census or real-link coverage gain.

## Remaining boundaries

Supported merge dry-runs still accept zero donors. Instrumenting the same
Verifier (no gate changes or byte-check bypass) isolates a compiled seed/map
candidate: the seed's rows, including 0x004BA7E0, match; 0x004BA9E4 is
321/321 bytes with 11 differing register bytes, and its 0x0078F51E funclet
cannot verify against a nonexact parent. Retail uses EBX for the receiver and
EDI for module data; this candidate reverses them. Other composition orders
fail declaration ordering, such as the missing DamageModuleinterface base.
The report's final `compile:` alone does not describe every attempted order.

The map donor's `/Oa` restores its standalone register allocation. Applying
that flag to the seed breaks seven bodies and an unwind row. The erase
donor needs `/Oy-`: its retail 51-byte body has an EBP frame; the composed
51-byte body omits it. Applying `/Oy-` to the seed also breaks existing rows.
Adding noinline to the two erase callees does not resolve this; both calls
are already out of line. Zero-size alloca trials also fail and are reverted.
No flag experiment or nonmatching reconstruction remains in Code/.

The other donors remain blocked by ModuleData declaration/layout composition
and the Behavior destructor selecting `??1DamageModule@@UAE@XZ` instead of
its existing native base provider (the link guard refuses it). Next: preserve
the map-load register allocation without changing other rows, then reconcile
those destructor contracts. The equal record sizes and folded destructor do
not establish record identity. ParticleSystem adoption also includes the
canonical handle, whose destructor contract needs reconciliation before that
remaining header debt can be retired.
