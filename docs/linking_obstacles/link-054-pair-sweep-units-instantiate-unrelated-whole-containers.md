### LINK-054: pair sweep units instantiate unrelated whole containers

Status: Open (partial emission repair verified). Updated: 2026-10-26; inspected revision: `896af216804e`.
Evidence / affected units: `StlSweepW4Rva004157BB.cpp`, `StlSweepW4Rva00540053.cpp` and `StlSweepW5Rva002CEFAA.cpp`, each with one rowed pair constructor, instantiate an entire hash_map or map. Raw before/after source-object inventories and the 40-unit preview are in `build/link-worker-w5/`; the full local handoff is `build/link-report.md`.
Completed: explicitly instantiate only each rowed pair constructor from the unchanged STLport `_pair.h`. All three rows remain exact; unused unresolved names fall from U4/U4/U3 to U1/U1/U1. The object inventories remove 373 distinct unrelated function names. The index reference graph has no retained node referencing the 362 names without alternate providers. The other 11 have alternate providers; two first-provider changes retain the identical retail-proven digests in current TeamFactory providers. The paired 40-unit previews keep the same 26 LINKS units and introduce no blocker. Frozen-file, EH, data, CSV and pin checks pass; all 53 assigned rows pass the ordinary byte gate.
Remaining / next check: each pair still calls an undefined placeholder element copy name. Retail destinations already have rows: 0x0041573F is `Rva0041573F` copy construction (67 B, `Rva0041573FCopy.cpp`); 0x0053FFCE is `Render2DSentenceClass::SentenceDataStruct::operator=` (61 B, `render2dsentence.cpp`); 0x000366F0 is `StringBase<char>::set` (132 B, `StringBaseNarrowCopySet.cpp`). Reconcile the pair/element operation identities and existing owners through the naming lane. In particular, assignment callees must not be renamed as constructors merely to satisfy the current sweep labels. The row names and pins are unchanged here.
Clearance: only the unused-emission subset is cleared in ordinary-preview scope; the three units remain blocked. Census confirmation pending.
Census confirmation: not claimed.

**`StlSweepW5Rva002CEFAA.cpp` cleared (2026-10-29, index `85f6b7f40c`):** 0x002CEFAA was never a pair
constructor. Its body copies two words, calls `StringBase<char>::set` on +8 and returns `this`. Its sole
caller is the 12-byte record copy loop 0x004F4DC0, which `vector<PrereqUnitRec>::erase` 0x004F50E2 reaches
through 0x002CF594. So it is `ProductionPrerequisite::PrereqUnitRec`'s implicit `operator=`. The row and
its two callers' placeholder rows (`__copy`/`__copy_ptrs<Rva004F4DC0Element *>`) now carry the real
`PrereqUnitRec` names that symbols.csv had already pinned at 0x004F4DC0/0x002CF594. The
`/alternatename` in `StlSweepW5Rva004F4DC0.cpp` and four pins (including the bogus
`??0Rva002CEFAAElement` at 0x000366F0) are gone. All three rows are exact; link_check reports 3/3 LINKS
(0 -> 35 B for this unit). Census confirmation pending. The two sibling units
(`StlSweepW4Rva004157BB.cpp`, `StlSweepW4Rva00540053.cpp`) already preview LINKS at the same index
(29 B each), so they are no longer link-blocked. 0x0053FFCE is an `operator=`, so 0x00540053's
pair-constructor identity may still be wrong. That is naming-lane work, not a link blocker.

#### Additional constructor-only sweep cleanup, 2026-10-26

**2026-10-30 0x004DA329 storage/representation repair (base `b4c2cc394c`):**
the opaque construction view now reserves a 56-byte node and copies the
native comparator representation byte. Its 25-byte wrapper stays identical;
both emitted 51/36-byte helpers are wholly exact, uniquely kept and certified
retail. The native storage fold is tool-admitted; no row or signature rename
is made. Four-source strict verification passes 84 rows, one data row and
four EXACT EH graphs. The bounded preview improves the wrapper 0 -> 25 bytes,
retaining both owners and the 8,150-byte voice caller (4/4 LINKS). Original
element/comparator identities and unapproved TU routes remain unresolved.
The staged audit is INCONCLUSIVE on the older index and affected consumer
Common/0CreateAHeroManager21FE49.cpp without a strict receipt; carry this
construction chain, fold binding and consumers into the next scheduled census.
No census gain is claimed.
[Evidence](../../reverse/attempt_support/tree-header-4da329-20261030/readme.md).

Status: Open; unused-emission subset cleared in ordinary-preview scope; census confirmation pending. Inspected revision: `58598f540fd3c84610304b3659ed382a4c05acca`; index `d1f046749a`, rules `retail-truth-4`.

Evidence / affected units: `StlSweepW4Rva0033A7DC.cpp`, `StlSweepW4Rva0056DDF5.cpp`, `StlSweepW4Rva004DA329.cpp` and `StlSweepW4Rva00501B33.cpp`. Completed: instantiate only the two rowed `pair` constructors and the default/copy `set` constructors from the unchanged STLport headers. All five rows remain exact. The paired preview changes the four units from U5/U5/U3-L1-S1/U3-L1-S1 to U1/U1/U1-L1-S1/U2-L1-S1 respectively. Object inventories remove 389 distinct emitted names without adding any definition. The index reference-edge audit finds no retained external referrer for the 383 names without alternate providers; the other six have alternatives, and no selected first provider changes. The same 70 of 91 current units preview LINKS before and after, including `StlportElementCopyCtorsW3G15.cpp` and `PickAndPlayUnitVoiceResponse.cpp`; no compared unit gains a named blocker. Raw inventories, reference audit, comparisons and all passing byte/declaration/EH/shadow-data/CSV/pin checks are under `build/c136-w4sweep/`, mapped by `build/link-report.md`.

Remaining / next check: the pair constructors call 0x002CF0F0 (`BfmeFixedStorage002CF0F0`, 24 bytes, FixedStorageCopyBFME2.cpp) and 0x00037050 (the private `StringBase<unsigned short>` copy, 66 bytes, StringBaseWideCopyCtor.cpp). Reconcile each key's actual identity and pair row with those existing owners; the earlier 0x0033A7DC wrapper failure was not repeated. The default set calls the rowed 51-byte `Rva004D9B18` constructor at 0x004D9B18, whose allocator/type contract still differs. The copy set's tree calls the 36-byte proxy constructor at 0x004FF55E and 115-byte tree-copy worker at 0x0050146E, which operates on 92-byte values rather than its eight-byte placeholder. The residual element destructors/comparators are emitted dependencies, not independently established missing native bodies. All four units remain blocked; naming/receiver/allocator reconciliation precedes another emission trial. No row, pin, alias, code-generation flag or shared header was changed.

Clearance: only the removed unrelated emissions are cleared in ordinary-preview scope; census confirmation pending. No whole-unit link or census gain is claimed.

**`StlSweepW4Rva0056DDF5.cpp` key identity (2026-10-27, seat halilkkaya-lk3, inspected `d16a31e4dc`, index `73061d9452`):** Repair landed / awaiting census. The key copy is one direct call to 0x00037050, the private `StringBase<unsigned short>` copy constructor, which is exactly what the canonical `UnicodeString`'s `__forceinline` copy constructor expands to (`reference/shims/bfme2_ascii/unicode_string.h`); the dword value lands at +4. The row is respelled `pair<const UnicodeString, int>::pair(const UnicodeString &, const int &)`, the unit includes the canonical header and instantiates only that constructor, and the `Rva0056DDF5Element` copy pin is dropped. Target fact: retail's `map<UnicodeString, int>` (online country list, `stlport_online_country_tree.cpp`) inlines the same constructor at 0x0056FE2C; the value type `int` follows that family and is not distinguishable from another dword by bytes. The two existing emitted copies of this name (AptOnlineLogin.cpp, stlport_online_country_tree.cpp, one digest) are now judged against 0x0056DDF5 and both units still LINKS. `./build.sh` 1/1 exact; link_check 0 -> 27 B. Not done: `StlSweepW4Rva0033A7DC.cpp` still needs a real name for the four-byte `BfmeFixedStorage002CF0F0` key (its earlier blocked verdict stands; respelling one placeholder into another was not attempted).

**Tree-copy worker binding (2026-10-28, base `9daf20b530`, index `14dc3d2467`):**
The `StlSweepW4Rva00501B33.cpp` subset is cleared in ordinary-preview scope.
Its constructor now calls the existing proxy and 92-byte-value tree-copy
owners directly, and suppresses the unrelated element-destruction emission.
Both edited rows and the EH graph remain exact; five current sources pass
97/97 rows and one data row. All five preview LINKS, with this unit 0 -> 183
authored bytes and its four providers/callers unchanged. Two obsolete pins
and their hatch keys retire. [Evidence and limits](../../reverse/attempt_support/tree-copy-00501b33-link-20261028-codexb.md).
The batch audit remains INCONCLUSIVE: the index predates the base and lacks
per-object consumer names. Carry removed-helper consumers into the next normal
census; no headline or runtime gain is claimed. The other LINK-054 identity
prerequisites remain open.
