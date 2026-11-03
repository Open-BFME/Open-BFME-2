# Respawn seed + tree composition boundary

The frozen sources compile independently and their declarations compose, but neither complete existing profile preserves every body. The blocker is shared preprocessor/CRT call context, rather than a further class-view disagreement. No supported merge or link approval is claimed.

The inputs were obtained with `git show 9a47cdf7b0:<path>`, not from mutable main Source. The ledger was streamed and retained only the exact seed/tree source filters: 24 seed rows and eight tree rows. Two private controls and two private compositions ran through sanctioned `tu_skeleton.Verifier.matched` in the existing supported private worktree. Both controls pass fully. Four spelling strategies reduce to one distinct `union-first` text for each profile, so repeating the other three would repeat the same input. No source, ledger, normal-cache or tool change was made.

| Existing profile | Exact rows | Misses |
| --- | --- | --- |
| Seed | 28/32 | tree base destructor `0x7FAB3`, erase `0x4AF28F`, tree destructor `0x4AF46E`, unique insert `0x4AF4A6` |
| Tree donor | 30/32 | only parsers `0x4AFC5F` and `0x4AFE6C` |

Both composition objects retain all four owning EH graphs exactly. The fresh controls provide a conflict-free union of 117 ordinary external definitions. Neither composition adds/removes a definition or changes its ordinary binding properties. Seed-profile composition changes six existing tree/allocator providers; tree-profile composition changes only the two parsers. Full bytes, symbolic relocations, route sets, flags and first-mismatch disassembly are in `proof.json`.

## Seed profile: two concrete missing contexts

The command retains `/DNDEBUG /MD /D_STLP_USE_STATIC_LIB` and the existing shim include list, with region-managed `/O1 /arch:SSE /G7`. It omits the donor's command-line `_CRTIMP=` and `_BFME_RETAIL_TREE_INSERT_LAYOUT` definitions.

Three failed native tree bodies use direct `_free` calls to native `0x30830`. The composition instead emits indirect `__imp__free` calls, growing base destructor 14 to 15 bytes, erase 45 to 46 bytes, and tree destructor 56 to 57 bytes. The proxy/allocator deallocation spare providers change in the same way. This accounts for five of the six changed tree/allocator definitions.

The unique-insert provider is 132 bytes instead of retail's 134. At the leftmost-insertion branch, the candidate lacks the native two `push edi` instructions and uses the stock `_M_insert(x,y,value)` path. The donor's source `#define` appears after the seed's `<map>` has already included guarded `_tree.h` and `_tree.c`; it cannot retroactively change the parsed template. The existing donor command-line definition activates the proven branch before all includes. The macro changes this insertion algorithm branch, not storage layout. See `header-read.md` for exact vendor locations.

## Tree profile: precise parser conflict

The donor profile carries `/EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT`, followed by the supported seed-first include union. It restores all eight donor rows and preserves the other 22 seed rows.

Its only failed providers are the parsers. Their CRT calls change from native/imported `__imp___strcmpi` DIR32 references to direct `__strcmpi` REL32 references. The default parser's first ordinary divergence is offset 22, including an additional saved register caused by the changed call shape; its emitted section is 503 bytes against the 524-byte retail row. The level parser has a changed branch displacement at offset 78 and its first changed call route later; its section is 741 bytes against the 742-byte retail row. Full disassembly and relocation lists distinguish these from relocation-only metadata substitutions.

This is a comparison of the two complete existing profiles, not isolated attribution of every scheduling change to a single flag. The actual conflicting call shapes are established: direct native tree `_free`, imported native parser `_strcmpi`. Merely retaining the donor profile globally repairs the former and breaks the latter. The late tree source macro is also insufficient under seed flags.

## Boundary and next work

There is no byte-exact composition to submit to LinkGuard in these trials, so no guard run was needed and none was waived. The current standalone profile prerequisite remains valid: the C2766 fix compiles eight rows unchanged. Composition still needs a clean, sanctioned way to preserve the two native CRT declaration contexts and the known insertion template branch together, followed by all-row/EH/provider checks. No new flag, import spelling, pragma, pin, header edit or check workaround is proposed here. Root's newer canonical parser/INI work is outside this frozen9a47 input and has not been assumed to solve this boundary.

The four-trial cap was honored. All tracked/native reads stopped after the bounded investigation; scratch report generation only followed.

Artifacts are copied into this directory; originals and the harness are under `build/sole-private-proof-20261103/build/respawn-tree-composition-boundary-20261103` and `build/sole-private-proof-20261103/build/respawn-tree-composition-probe-20261103.py`.
