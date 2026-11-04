# XferSave block writer consolidation

Base: `3a95b274a2`. Scope: `Code/GameEngine/Source/Common/System/XferSave.cpp`
and `Code/Libraries/Source/xfer/XferSaveBlocks.cpp` (0x0060D435, 148 bytes).

## Declaration prerequisite

The supported planner ran under `Code/GameEngine/Source/Common/System/`.
The current in-memory TU map approves the block writer for System/XferSave;
the initial supported dry run accepted no donor. Its block-writer composition
failed because the seed's XferSave view lacked the two existing helper methods
and the body used donor-only field spellings.

Declare both existing nonvirtual helpers in the seed; align the donor's
stream, flag and position-vector field references with the seed. Taking the
position-vector field's address permits either view's existing representation.
This preserves offsets 4, 8 and 12 and changes no virtual slot or function name.
The donor's unused tail is not claimed as recovered layout.

Verification of the prerequisite:

- Normal builds before/after: 23/23 matched rows; string, float and import
  reference checks pass. Frozen-file checks pass both sources.
- All 162 seed and five donor COMDAT fingerprints are identical before/after.
  `link_census.object_symbols` returns identical definitions, references,
  weak externals, alternate names and includes for each object.
- Ordinary paired previews before/after both retain LINKS, 1,442 bytes total
  (seed 1,294; block writer 148), index `f12552d0a7`, 2026-11-04 20:47.
- Supported dry run now accepts the seed and block writer, 23 rows, with the
  current link guard passing. No other donor is accepted. The hash helper's
  private/public spelling, other donors' declarations and remaining byte
  failures are separate prerequisites; this change does not clear them.

Raw local checks: `build/xfersave-blocks-{before,after}.log`,
`build/xfersave-blocks-{before,after}-link.log`,
`build/xfersave-blocks-dry.log`; before objects under `build/xfersave-blocks/`.
No census or full-image gain is claimed.

## Application boundary

Prerequisite commit: `d02fb7da09` (handed to the fleet publisher).
The normal application command refused before writing: another worker holds
`0x0007FAB3`, the shared string destructor fold in the candidate scope.
No claim bypass, source move or ledger repoint was attempted. The application
released its scope claims. When that claim is free, rerun the supported merge;
the verified seed/block-writer composition is the new positive prerequisite.
EH verification passes all three graphs; data checks report zero findings.
No source-file reduction is claimed for this pass. This is the existing shared
fold claim boundary documented in the earlier XferSave handoffs, not a newly
discovered linking obstacle.
