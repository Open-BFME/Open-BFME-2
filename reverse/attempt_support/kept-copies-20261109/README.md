# Rowed names whose linked copy differs from retail (hole 1)

`kept_copies_687433edd9.tsv` lists the rowed names whose copy in a real link differs from retail, measured on 2026-11-09 at
`687433edd9` with path object order, the order real links use. A row is byte-verified in its owner's object, but link.exe keeps the
first COMDAT definition on the command line, so the image can run another unit's copy under the row's name.

How it was measured: the map names the kept object; that object's copy, with its own relocation fields masked and trailing padding
stripped, was compared with retail's bytes at the row's address. Over 25,551 multi-copy names, the first definer on the command line
was the map's kept object every time. 258 rows differ; 256 of them are kept from a non-owner unit.

Columns: `retail_rva`, `size` and `name` are the row's. `owner_source` is its source, `kept_source` the unit whose copy the image runs.
`class_from_p75` is crash prevention's reading from the same pass (P75), blank where it had none. `allocator_side_by_name` is only a name
match, for sorting. `fixed_by_trial_order` says whether the scratch object order put a retail copy first; it does not mean that order works.

Limits: masked bytes equal is not proof the callees are right. Line numbers and sources are as of that commit: check the current row first.

The rule is unit fixes, wrong-field and allocator cases first. Don't use object order to get these. The trial order fixed 250 of the 258 in
the kept-copy count and stopped a boot about 194 s earlier on `swarm/triage/route-boot`, cause not found. All these copies have retail's
bytes, so a unit fix on this list may meet the same dependency: boot each batch and compare with the commit before it.
