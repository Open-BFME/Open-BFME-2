# XferSave fragments: use the CRT free declaration before STLport

Base `da2c4d00c25f`. The consolidation picker claimed XferSave.cpp and eight
clean donor candidates. The current planner and supported dry run were read;
the map is rebuilt in memory, not committed. All nine sources pass 44/44 rows
and frozen-file checks before editing. Mixed and refused donors are untouched.

The dry run refuses Rva0060D269.cpp, rva0060D2E9Rva0060D2E9Farm.cpp and
XferSaveBlocks.cpp with C2883: their manual `_STL::free` declaration conflicts
with an earlier header's `using ::free` in the composed unit. Replace that
declaration with `<stdlib.h>` before STLport. The existing `/D_CRTIMP=` and
allocator options stay unchanged. This removes a fragment include-context
conflict; it does not establish a completed merge or a new application name.

Normal and strict builds pass all seven edited rows. EH is EXACT 2; frozen
checks pass. The three ordinary previews retain LINKS and 138 + 341 + 148 =
627 authored bytes against index `0d24c60eef` (2026-11-01 09:19). No census
gain, new matched body, source reduction or registered debt retirement is claimed.

Normal-build before/after object controls show:

- All 39 external section bodies and relocation offsets/types are unchanged
  after masking relocation slots. Relocation names are identical after the
  sole normalization `?free@_STL@@YAXPAX@Z` -> `_free`.
- Strong and weak symbol sets are unchanged, with no added/removed COMDATs.
  Only the expected undefined free spelling changes in the finder and name
  writer; the block writer's complete object facts are identical.
- Every affected 14-byte destructor twin compares to native `0x0007FAB3`.
  Each native REL32 free call targets the engine allocator `0x00030830`,
  before and after the declaration change. This is not the CRT import thunk
  at `0x00628F98`; the existing GameMemory.cpp row owns the engine wrapper.

Adjacent receipts record both the raw fact differences and the qualified
normalization/native call proof. Saved control objects remain under ignored
`build/resume-eh-local/turn95/`; neither they nor the proof code compile by hand.

The second supported dry run clears C2883 but accepts no merge yet. Remaining
stops include finder node/iterator declaration order and spelling, XferSave
base/member views, duplicate template specializations, the open writer's Xfer
adoption, byte differences in the deleting destructor and bucket-number helper,
and deque-provider losses. Continue those as separately verified prerequisite
changes. No source path, ledger, pin, baseline, shared header or build option
changes in this commit.
