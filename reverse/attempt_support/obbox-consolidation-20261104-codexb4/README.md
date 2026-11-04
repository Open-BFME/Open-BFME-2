# OBBox consolidation: carried-flag baseline prerequisite

Inspected source revision f4529b5e81. No game source, ledger path, hatch or
protected debt entry changed during this trial.

`tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WWMath/obbox.cpp --dry-run`
rebuilds its TU map in memory and approves two rows for this destination. Its
pure donor is `WW3D2/OBBoxTransformO1.cpp`; `Matrix3DO1Inlines.cpp` remains mixed
(11 other rows). The link guard identifies the destination and pure donor as
census-linked. The merge rejects the donor with `no baseline match`, accepts
nothing and reports no verified merge. This is not a link-regression verdict.

The normal `./build.sh` command on both sources passes 2/2 rows. A targeted
`flag_defaults.py propose` confirms that the donor's regional
`-O1 -arch:SSE -G7` matches without an override, while the destination needs
its registered `-G7 -arch:SSE2` override to retain its one row. The merge's
baseline trial carries that destination override (`tu_skeleton._merge`),
so the ordinary matching donor is not yet a compatible baseline for composition.
Do not remove the override merely to get the donor past this step.

`tu_views.py .../obbox.cpp --dry-run` finds only BfmeVciAnchorElem, already
shared; there is no mechanical private-view reconciliation to apply. Frozen
inventory accepts both sources and reports the destination's existing two
unclaimed definitions. The supported naming planner was run for WWMath and
its snapshot check passed; it grants no new TU approval.

Next useful work is a byte-exact reconciliation of the two compiler contexts,
then the normal merge dry-run and provider/consumer nonloss guard. The dry-run
alone does not prove that the two files' includes or class definitions compose.
No source-file reduction, link gain or debt retirement is claimed.
