# MultiplayerSettings obsolete optimization debt

The old artificial two-element array anchor forced a local compiler vector
constructor iterator copy, with its own optimization overrides. The real class
now emits its verified implicit lifetimes in the approved TU and needs no such
array construction. Its integer credit array is trivial; the color values and
map use their separately verified constructors.

Remove the unused anchor, its declaration-only invented element type and all
four optimization pragmas in this file. The getColor size overrides are also
redundant under the current source/compiler profile: the complete native body
and every other retained external code body are identical without them. Keep
the actual common-return behavior documented, removing the stale override claim.

[The private before/after comparison](private-comparison.json) reproduces all
22 source rows, with all five owned EH parents EXACT. Every one of 30 retained
external code bodies and its symbolic relocations is unchanged. No definition
is added. The only removed external code is the unneeded local iterator copy.
Compiler-local cleanup labels are verified through their current parent graphs.

Normal strict preparation passes 23 rows and the existing data row across this
TU and the actual ATL iterator owner. Both preview LINKS against `e1f7c1dd18`,
retaining 857 + 34 authored bytes; all five EH graphs are EXACT. The source's
historical printed 450 -> 857 difference belongs to previous repairs and is
not a gain here. [Actual strict-object evidence](actual-proof.json) proves that
the removed copy is absent and the rowed ATL provider remains fully native exact
at `00001423/34`. No source path, ledger row, pin, name or manual alias changes.

The owning counter tool removes exactly four pragma keys from
`reverse/hatch_baseline.tsv` (1,942 -> 1,938 pragma occurrences in this checkout).
No unrelated key changes. This retires four hatches with matching coverage and
the existing native provider kept. Broader consumer selection and the next
scheduled census remain separate; the inherited color-constructor binding
warning is unchanged and its previous control evidence remains applicable.
