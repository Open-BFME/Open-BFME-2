### LINK-016: folded bodies whose consumers declare them decl-only, with no provider

**2026-10-30 native list append (base `505b71888c`):** the 0x001B4D0E wrapper
declares its already-rowed push_back at 0x001B4CEF instead of instantiating
11 local helper copies, including the selected non-retail POD72 construction.
Its eight bytes and native target remain exact. Normal strict three-source
verification passes 71 rows and four EXACT EH graphs; paired bounded previews
improve 2/3 to 3/3 LINKS, 2,361 -> 2,369 bytes, with both providers preserved.
No census gain, element identity or provisional-TU clearance is claimed.
The staged audit is INCONCLUSIVE on the older index and affected consumer
Common/0CreateAHeroManager21FE49.cpp without a strict receipt. Carry the removed
instantiation chain and affected consumers into the next scheduled census.
[Evidence](../../reverse/attempt_support/native-list-append-1b4d0e-20261030/readme.md).

**2026-10-30 native range cleanup (base `8e99791e22`):** SidesList provides the
existing pinned `_Destroy<RvaPair00257544 *>` operation at 0x0032C0CA directly;
the last Deferred alias and its one counter key are retired. The actual kept
25-byte definition certifies as retail and is a complete byte/relocation twin
of the existing owner. No new row or pin is added. All 269 cohort rows and
17 EH graphs pass; bounded paired previews preserve three native units and
2,330 authored bytes. This is hatch retirement, not new census linking.
The generated unwind unit's existing unresolved names are unchanged. A larger
current-ledger preview lacks strict receipts for 11,957 other objects, so full
closure is unmeasured; the scheduled census and outgoing batch audit retain
that scope. The outgoing audit is INCONCLUSIVE on the older index and affected
consumer Common/0CreateAHeroManager21FE49.cpp without a strict receipt. Carry
the new provider, retired alias and affected consumers into the next scheduled
census. Four shadow identity findings in unchanged definitions remain separate.
[Evidence](../../reverse/attempt_support/pair-range-provider-20261030/readme.md).

**Status: Repair landed / awaiting verification. Updated: 2026-10-26; inspected revision: 856b8bc032.**

- **Evidence / scope:** in the census at 763dc8759f, several units were
  unresolved only on an STL member or a global that they declare (decl-only, to
  avoid a non-retail COMDAT) but that no object defines under that name: retail
  ICF-folded the body under another instantiation's row. Found with
  `tools/link_rank.py --near 1 --json` (units whose only blockers are `U`) and
  each name's `reverse/symbols.csv` address.
- **Completed** (each `./build.sh`-exact; previewed with `tools/link_check.py`
  against the 763dc8759f index, passing the provider and its consumers together):

  | Unresolved name | Retail body | Provider (its flags already emit that shape) | Preview |
  |---|---|---|---|
  | `g_lgaKeyRecords` (0x00A02E50; it also carried two address names) | 16 B tree, ctor 0x007AF8CD | `Rva007B6880Thunks.cpp`: one zero-filled definition through an opaque tree view; Count, Merge and the initializer bind it (25f107697e) | unresolved gone from both LargeGroupAudio units |
  | key-tree `erase(iterator)` (`LargeGroupAudioKeyList.cpp`'s /O1 /Oy- copy was selected) | 0x00056BC3 | `stlport_asciistring_set_base.cpp` (3a828f7bea) | KeyList 0 -> 191 B |
  | `hashtable<pair<const int, Rva0060CF76Element>>::_M_initialize_buckets` | 0x00148DDF | `SelectionIDMap.cpp` (e80fae26b7) | XferSave.cpp 0 -> 1,060 B |
  | `_String_base<char>::_M_throw_out_of_range` | 0x00023A40 (empty /Od body) | `stlport_vector_voidptr_alloc.cpp` (357c8c8a3e) | four narrow-string units 0 -> 904 B |
  | `_Destroy<Rva002BBB96Element *>` | 0x002BB6A5 (BfmeAssignRecord52 loop) | `stlport_asciistring_record_bodies.cpp` (57b0571b72) | the two Deferred units 0 -> 2,925 B |
  | `/alternatename` onto an undefined `__copy<BfmeAssignRecord28 *>` | 0x003F6477 | the rowed `__copy<Rva003F6477Element *>` called directly; two hatches removed (856b8bc032) | VectorRangeEraseRva003F6975.cpp 0 -> 80 B |

- **2026-10-26:** `LargeGroupAudioKeyMapBfmeAddKey.cpp` needed
  `vector<void*>::resize` (0x000E6D39). Its `_M_fill_insert` callee is
  0x00233A5A while `vector<void*>::_M_fill_insert` is rowed at 0x00029CA0, so a
  plain instantiation would bind the wrong callee; the unit now calls the rowed
  owner `vector<Drawable*>::resize` (`DrawableVectorResize.cpp`) through a cast.
  `link_check.py` with `Rva007B6880Thunks.cpp` and `DrawableVectorResize.cpp`:
  0 -> 314 B.
- **Audio overlap reconciled (2026-10-26, base `e12e2545d9`):** the table above
  records the earlier independent repair. The retained audio implementation
  uses the verified 12-byte array owner in KeyList; sixteen native zero bytes
  did not establish a 16-byte tree layout. AddKey's native resize and insert
  calls are already repaired, as recorded in
  [the storage follow-up](../../reverse/attempt_support/largegroup-keylist-storage-link-20261026.md).
  [Removing the now-unused pair-tree erase instantiation](../../reverse/attempt_support/largegroup-unused-erase-provider-20261026.md)
  prevents its divergent pair destructor from overriding AddKey's cleanup.
  All 20 affected function rows, two data rows and two EH graphs pass; current
  consumer objects contain no reference to that alternative erase. The bounded
  seven-object preview restores AddKey's 314 bytes and passes 7/7 at
  10,874 -> 11,379 against index `763dc8759f`. No new census gain is claimed.
  These preview results overlap the independent resize repair above;
  they are not additive linked-byte gains.
- **Remaining / next check:** Many `U` entries in the 763dc8759f index are stale: check
  with the defining unit's current object before working one (e.g.
  `~SpecialPowerModule` already resolves).
- **Clearance:** preview scope only (the units listed).
- **Census confirmation:** awaiting the next census.

**2026-10-27 package c140 follow-up, inspected `a0b82f68445de8ab0254437ef7e97332ce48cfb0`, ordinary-preview index `bf3dd31211` (2026-10-27 00:39):** `BannerUI.cpp` still lacks `??1?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAE@XZ`. Native constructor cleanup 0x0076E38E adds 0x28 to the BannerUI receiver and jumps to 0x0007FAB3, the existing 14-byte `vector<int>` destructor row in `GameClient/InGameUICtor.cpp` (load start, null test, game free 0x00030830, return). No new body, pin, container cast or element rename was attempted. All 28 BannerUI rows remain exact, and the current-object preview retains U1. Next: establish the emitted whole-body and relocation twin for the actual banner vector, then admit its folded name against that existing owner; the native folded target alone is not a completed fold-proof admission. No clearance or census gain is claimed.

**2026-10-27 BannerUI vector-destructor fold completed (claude4, base `65abb0c7f0`):** `BannerUI.cpp`'s vector view now defines `~vector()` out of line (empty body over the inline base teardown), so the object emits `??1?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAE@XZ` as the whole 14-byte null-checked start-pointer free with REL32 `_free` 0x00030830. `tools/pin_admission.py --add` admitted it onto 0x0007FAB3 with `fold-proof=` naming this unit (`pin_consistency.py --check` OK). The constructor unwind funclet 0x0076E38E (`$L3015`, parent `??0BannerUI@@QAE@XZ` 0x00217211, eh_verify EXACT) was repointed off `Code/gen_small/uw_gen_010.cpp` with `add_match.py --replace-rva`, clearing the `uw_0076e38e` LINK-095 refusal. `./build.sh`: 29/29 rows exact. `link_check.py BannerUI.cpp`: LINKS, LINKED 0 -> 1,885 bytes against census `bf3dd31211`. Clearance: preview scope (this unit); census confirmation pending.

**2026-10-28 current-battle forwarder alias cleanup (Codex, base `a3adcc8d10`):** BannerUI's prior fold already previews LINKS. Its remaining alias for 0x0020E6B7 was still used by declarations in LivingWorldLogic.cpp and PlayerInitFromDict.cpp. Those callers now declare the existing owner's `Rva003F468D *` return and cast locally; the unused alias and redundant pin are removed (one of each hatch retired). [Evidence and scope](../../reverse/attempt_support/battle-forwarder-alias-cleanup-20261028-codex.md): 238/238 function rows, four data rows and 47 EH graphs exact; all 574 COMDAT bodies unchanged, with only the two external callee referents corrected. Joint ordinary previews retain all four units' 26,934 authored bytes against index `14dc3d2467`. No new census gain or global clearance is claimed; published-index batch-audit coverage and the prior fold's census confirmation remain prerequisites for broader clearance.

**2026-10-28 BannerUI declaration prerequisites (codex3, base `666892446c`):** The supported consolidation dry run initially accepted no donors: MessageStream's local slot macro was undefined before the composed class, and a later complete Apt target declaration could displace its earlier forward declaration. Expanding the existing virtual declarations and placing the existing Apt interface at its first use preserves all 29 seed rows, seven EH graphs, all 71 COMDAT copies and external bindings. Strict preparation passes; the current-object preview retains LINKS for 1,885 authored bytes against index `d92e7e6635` (2026-10-28 15:58). [Evidence and remaining view conflicts](../../reverse/attempt_support/banner-ui-composition-20261028-codex3.md). This clears the two declaration prerequisites only; donor composition, affected-consumer verification and census confirmation remain pending. No path or census gain is claimed.

**2026-10-28 BannerUI bounded composition (codex3, prerequisite `5304c4c17f`):** The supported merge now absorbs five whole-file fragments into the approved BannerUI.cpp, reducing SOURCE FILES by five. All 36 merged rows and nine EH graphs remain exact; all 77 original unique COMDAT bodies, exclusive definitions and weak bindings survive, with four references resolved internally. Strict preparation verifies all 79 group rows across the fifteen remaining files; those files preview LINKS against `d92e7e6635` (the merged unit has 2,093 authored bytes, including moved rows). The path audit covers all eleven removals in the pending BannerUI/INIWater/CallHelpOnDamage batch and finds no active path consumer to change. The staged batch audit remains INCONCLUSIVE: after preparing DestroyInstances.cpp's 58 rows, it reaches a missing affected-consumer receipt for `Common/0CreateAHeroManager21FE49.cpp`, and the index is older than the outgoing base. [Composition audit and register details](../../reverse/attempt_support/banner-ui-composition-20261028-codex3.md#verified-composition-after-the-prerequisite). Fourteen whole-file donors and eleven mixed files remain; broader consumer verification and census confirmation are pending. No census gain is claimed.
