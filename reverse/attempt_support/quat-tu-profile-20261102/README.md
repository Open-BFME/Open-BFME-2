# Quaternion consolidation boundary, 2026-11-02

Current approved map (rebuilt in memory): 17 rows, two files, no mixed or refused donors. The existing seed also carries four compiler/inline rows outside this placement set; no rows or source changed.

`tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WWMath/quat.cpp --dry-run` rejects the Build_Matrix4 donor with `no baseline match`. Both units are census-linked, so the merge guard is active. The seed override is `-G7 -arch:SSE2`; `_merge` carries it when constructing donor baselines. The donor's own normal build passes 1/1 (375 bytes at 0x00717FA0), including four compiler-float references. The existing donor comment records its SSE versus SSE2 code-generation boundary; this repeat confirms the tool rejection and separate-build success, rather than proving a new workaround.

Prior record: the log's earlier quat.cpp consolidation attempt also accepted zero donors at this boundary. Matrix4 default-constructor interference was separately repaired in earlier history and is not this merge rejection. No source rewrite, pragma, compiler override, map regeneration or provider deletion was applied. Next step requires a byte-preserving common-profile reconstruction before the owning merge tool can absorb this donor. This is consolidation cleanup, not lost byte coverage or a demonstrated link regression.
