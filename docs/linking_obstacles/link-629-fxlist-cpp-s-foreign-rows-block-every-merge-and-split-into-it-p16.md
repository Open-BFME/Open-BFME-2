### LINK-629: FXList.cpp's foreign rows block every merge and split into it (P16)
Status: Blocked (0x0052BD3A identity; the hashtable question is answered in tooling, below). Updated: 2026-11-07; inspected revision: fbdc0dccd0 (static-defects lane, P16); tooling: harness lane.

Evidence / affected units: Code/GameEngine/Source/GameClient/FXList.cpp, the TU tu_map approves for the
P16 rows (doFXObj@ParticleSystemFXNugget 0x001E24DC, ??0ParticleSystemFXNugget@@QAE@XZ 0x001E0AEF with its
funclets, parse@ParticleSystemFXNugget 0x001E264F). See fxlist-cpp-unit-link-prerequisites-2026-10-31.md for
the P16 cause. `tools/tu_skeleton.py --merge FXList.cpp --dry-run` and every
`--split <donor> --for FXList.cpp --dry-run` refuse with "TU path exists and holds rows of another TU (split it
first)". FXList.cpp holds 7 matched rows: 3 approved for FXList.cpp, and these 4.

- 0x0052BD3A `??0FXList@@QAE@ABV0@@Z` (31 B), tu_map approved for LivingWorldCampaign.cpp (C=0x0052BBF3..0x0052BD59).
  - The row is compiler-generated, with no source body, and its identity is weak. It was placed by a masked
    whole-.text search of the compiled body ("single hit"), and re_attempts.log 0x0052BD3A records it.
  - Its 31 retail bytes install vtable 0x00C61A20 and copy a string at +4. Zero Hour's FXList has no vtable,
    so FXList.cpp's Zero Hour class cannot be what retail compiled here.
  - `--split FXList.cpp --for LivingWorldCampaign.cpp --dry-run` carries no copy-ctor body. It carries the whole
    714-line Zero Hour FXList.cpp (its /FIzh_ascii.h flag line, every nugget class and its inline bodies), and
    fails compiling: `'calcDist': identifier not found`. The tool copies a file-local helper only for carved
    bodies, not for the in-class inline TracerFXNugget::doFX that calls it.
  - Not carved. Moving the Zero Hour port into LivingWorldCampaign.cpp would not be an honest carve. The row
    needs its identity proven (whose 0xC61A20 vtable, what string member) before it has a body to move.
- 0x0060CF5A `?_M_delete_node@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@...` (28 B) and
  0x0060CFB6 `?clear@?$hashtable@...FXList...` (73 B), tu_map approved for XferSave.cpp (C=0x0060CE41..0x0060CFFF).
  - These are STLport template COMDATs FXList.cpp emits through its hash_map<NameKeyType, FXList>.
  - The split refuses both: "no definition spells its name". A template instantiation has no carvable body,
    so a carve cannot move them.
  - Question for a tooling seat: should tu_map treat these instantiations as homeless (follow the file that
    emits them), or should the split tool place them by emitting unit? The consolidation lane does not change
    tu_map.csv (AGENTS.md).
- 0x0023DAA5 `?clear@?$_List_base@PAVFXNugget@@...` (39 B), the row the split listing shows as "(no approved TU)".
  - This is a second ledger row at an address whose tu_map identity is stlport_list_int_o1.cpp's row,
    approved for GameLogic.cpp, so it is an ICF alias.
  - The merge's mixed check already ignores it: the dry run counts FXList.cpp as mixed by 3, not 4. It is not
    a blocker, recorded so it is not chased.

Completed: none by the consolidation lane (dry runs only). Tooling decision for the two hashtable rows
(harness lane, `tools/tu_skeleton.py` `emission_held`):

- Target facts: both rows are implicit instantiations of STLport's hashtable for hash_map<NameKeyType,
  FXList>, and their map rows rest on C alone (`by=C`, `C=0x0060CE41..`), with no F/Z/S/L/W token.
  XferSave.cpp has a matched `?clear@?$hash_map@...FXList...` row (0x0060D02C), so retail's XferSave.obj
  used the same template. Retail kept the copy from XferSave.obj and placed it inside that object's
  contribution.
- Structural inference: C records retail's link order (the object the linker took the COMDAT from), not
  where a body is written. Every TU that uses the template emits these bytes. tu_map stays as it is: it
  is right about the placement, and the map's C remains what the rows are approved by.
- Handling: a row that is a template instantiation by its own symbol (`?m@?$T@`, `??0?$T@`, `??$f@`),
  is placed by C alone, and is spelled by no definition in its file (no explicit specialization, no
  body of the class itself; an unreadable file counts as spelled) is held by emission. Only the TU
  file whose code emits it keeps it, as the merge seed or as a split or shatter destination. A donor
  still never carries it into another TU. A split moves it only as a rider: when the carved bodies
  were its only emitters and the map places it in the destination. `--split FXList.cpp --for
  XferSave.cpp` now says why it moves nothing, instead of "no definition spells its name".
- Effect at 61cf52f345: FXList.cpp's foreign rows fall from 3 to 1 (0x0052BD3A). Across the tree, 32
  merge decisions change, each only a TU file's own mixed count (2,102 rows qualify, in 755 files,
  after explicit operators and explicit instantiations count as spelled). 11 TUs become mergeable
  (DamageFX, ProductionPrerequisite, ScoreKeeper, ThingFactory, GameClient, SpawnBehavior,
  AITargetHeuristicEnemyStructure, MilesAudioManager, W3DModelDraw, static_sort_list, pk). No donor is gained or lost, other than a TU file seeding
  its own merge.
- Not done: XferSave.cpp cannot take the rows today. Its private FXList view (a virtual dtor) does not
  compile these bytes, so it declares `hashtable<...FXList...>::clear` as an explicit specialization to
  suppress its own copy. Once FXList is one shared class, XferSave.cpp emits them too, and the rows can
  be repointed there by emission (verified by ./build.sh).

Remaining / next check:
- (Answered in tooling above; lands with the tu_skeleton change.) The two hashtable rows block nothing.
- An identity proof for 0x0052BD3A.
- Then `--split FXList.cpp --for XferSave.cpp` and `--for LivingWorldCampaign.cpp` (or the rows' new homes),
  after which FXList.cpp is no longer mixed.

Measured separately for P16 (static-defects lane, 2026-11-07, scratch only):
- FXList.cpp's flags are not the wall. Its `// cl:` line builds all 34 FXListNuggetParse.cpp rows exact.
- The wall is its Zero Hour seed. Composed with the byte-proven BFME 2 donors, the seed's Zero Hour
  definitions of FieldParse/MultiIniFieldParse, Coord3D, GameClientRandomVariable, AsciiString (/FIzh_ascii.h)
  and the seven nugget classes conflict with the donors' canonical headers and views.
  - ParticleSystemFXNugget lacks nine BFME 2 members (m_nuggetType, m_systemLife, m_targetOffset,
    m_useTargetOffset, m_targetCoeff, m_setTargetMatrix, m_createBoneAtTarget, m_onlyIfOnLand, m_onlyIfOnWater).

Clearance: pending.
Census confirmation: not claimed.

Update (2026-11-07, static-defects lane, base 61cf52f345): the copy ctor 0x0052BD3A is not FXList's.
- **Retail bytes (31 B):** `mov esi,ecx; mov [esi],0x00C61A20; lea ecx,[esi+4]; push src+4; call 0x000365F0
  (StringBase<char> copy ctor); mov eax,esi; ret 4`. That is the implicit copy ctor of an 8-byte
  `{vptr, AsciiString}` class: an implicit copy ctor copies every member, and this one copies only the string.
- **Vtable 0x00C61A20:** one slot, `??_GRva004E156B` 0x004E1BC4, wrapping the ICF-shared 14-byte
  `{vptr, AsciiString}` dtor 0x004E156B. The string "ParseEnableRegion::Invalid data passed in." follows it at
  0x00861A24.
- **Identity:** the class is the EnableRegion record SpawnArmy.cpp views as `Rva003B7BA0Record` (virtual dtor
  plus `AsciiString m_name`; FieldParse `Region` at +4). SpawnArmy.cpp already notes that its FXList spelling of
  the push-back thunk 0x00566527 "is a callable view, not this record's identity".
- **Why it cannot be FXList:** BFME 2's FXList holds `list<FXNugget*>` at +4 (`FXList::clear` 0x001E11A6 walks
  it, `addFXNugget` 0x0037D097 appends to it), not a string.
- **The same misnaming covers two more rows:** `_Construct<FXList>` 0x0052C2F3, the copy ctor's only caller
  (0x0052C30F), and `vector<FXList>::_M_insert_overflow` 0x00565ACB. re_attempts.log records all three as
  `identity-suspect`.
- **Next:** respell the three-row chain onto the record class (the class's name goes through the naming lane)
  and let the unit that copies the record emit it. tu_map approves 0x0052BD3A for LivingWorldCampaign.cpp. The
  respelled copy ctor then leaves FXList.cpp, which removes one of its three blocking foreign rows. The two
  hashtable rows are routed to the Harness lane as a tooling question.

Update (2026-11-07, merge lane 2 / seat5, base 2e872048cd): who emits the EnableRegion record chain.
- The record chain's C approval for LivingWorldCampaign.cpp (0x0052BD3A, 0x0052C2F3, 0x0052C8EF, 0x0052CAC9)
  is right. LivingWorldCampaign.obj emits it through the Act copy ctor 0x0052D555. That copy ctor is reached
  only through the LivingWorldCampaign member at 0x0052D83B (`add ecx,0x0C; jmp vector<Act>::push_back`),
  which the parser 0x00566D83 calls with the campaign as `this`.
- The 0x0052D3F1..0x0052D83B Act run is LivingWorldCampaign.cpp's. The parser and the Act ctor 0x00566BF6
  belong to the Act's own unit (the provisional Glo012F1024Item.cpp group), not LivingWorldCampaign.cpp.
- Approving the run needs only a naming fix: respell 0x0052D83B onto LivingWorldCampaign. Measured in memory,
  that approves 14 code rows; the cost is in the handoff.
- So the record copy ctor's home is LivingWorldCampaign.cpp, and that unit must see the complete Act (with its
  vector<EnableRegionRecord>) and define the act forwarder out of line.
- Evidence: reverse/attempt_support/livingworld-act-tu-evidence-20261107/readme.md.

Update (2026-11-07, static-defects lane): the two "hashtable<pair<const NameKeyType,FXList>>" rows are XferSave's
string table, not FXList's.
- Retail bytes:
  - `_M_delete_node` 0x0060CF5A destroys the pair at node+4 through 0x0007FAB3 (`mov eax,[ecx]; free if set`,
    the STLport string key's buffer, ICF-folded with vector dtors) and frees the node with `_free` 0x00030830.
  - `clear` 0x0060CFB6 walks the buckets at +4/+8 and zeroes the count at +0x10.
  - The same table's `_M_new_node` 0x0060D089 allocates 0x14-byte nodes: next, a 12-byte STLport string and an
    unsigned int.
- Identity: XferSave.cpp's `XferNameTable`, `hashtable<pair<const string, unsigned int>, string, hash<string>, ...>`.
  Its `_M_new_node`, `_M_bkt_num` and `_M_insert` rows sit beside these two.
  - The only callers of `clear` are `??1Rva0060D031Member` 0x0060D031 and `XferSave::Open` 0x0060D10A, both
    approved for XferSave.cpp.
  - A third misnamed row belongs to the same table: `hash_map<NameKeyType,FXList>::clear` 0x0060D02C
    (XferSave.cpp) is `jmp 0x0060CFB6`.
- Where the FXList spelling came from: FXList.cpp's Zero Hour port instantiates a by-value
  `hash_map<NameKeyType, FXList>` whose `clear`/`_M_delete_node` are masked byte twins of these. XferSave.cpp even
  types `Rva0060D031Map` as that hash_map and declares `clear` only, because "the copy the link keeps is retail's
  (FXList.cpp)".
- BFME 2's own FXListStore stores pointers (`hash_map<NameKeyType, Rva001E2747*>`). No BFME 2 FXList code
  instantiates a by-value FXList map, so these rows can never come back from FXList TU code.
- re_attempts.log records all three as `identity-suspect`.
- Next: respell the three rows onto the string table and its hash_map in XferSave.cpp (their approved TU),
  which then emits them, and retype `Rva0060D031Member` as that map. FXList.cpp then emits none of them, and
  the held-by-emission rule no longer applies to them.

Update (2026-11-07, static-defects lane): scratch measurements for P4 (the record chain into LivingWorldCampaign.cpp)
and for A3 (`Rva001DFEAABase` -> `FXNugget`). Scratch texts only, judged with `tu_skeleton.Verifier`; nothing in
`Code/` changed. Scripts: srv1 `~/bfme2-ops/seat3/build/scratch_defects/`.
- P2 folds into P4. `_Construct<EnableRegionRecord>` 0x0052C2F3 calls the record's implicit copy ctor out of line,
  by name, even under `/Ob2`. So the 8 respelled rows (with `vector::~vector` 0x0052CB26) and the move of the
  copy ctor 0x0052BD3A into LivingWorldCampaign.cpp form one change, and it waits on the emission mover.
- The Act copy ctor 0x0052D555, left implicit, is retail's 333 bytes; all 59 rows of Glo012F1024Item.cpp stay exact.
- Act members, each as its real class with an implicit copy ctor in LivingWorldCampaign.cpp:

  | Member | Real element type | Copy ctor | Result |
  |---|---|---|---|
  | +0x08 | EnableRegionRecord | 0x0052BD3A | exact |
  | +0x2C | Rva004E1B00 (Snapshot) | 0x0052BDE6 | exact |
  | +0x38 | Rva004E179A (Snapshot) | 0x0052BE33 | exact |
  | +0xA8 | Rva004E1B72 (Snapshot) | 0x0052BEF0 | exact |
  | +0x54 | Rva003A6F70 | 0x0052BB34 | exact |
  | +0x6C element | Rva004E194E | 0x0052BE96 | exact |
  | +0x78 element | Rva004E18A2 | 0x0052BB6D | exact |
  | +0x84 element | Rva004E14E1FlashRecord | 0x0052BB9A | exact |
  | +0x60 | Rva004E32F2 (`map<int, AsciiString>` member) | 0x0052D477 | exact |

  - Caveat: three Unwind funclets of the Snapshot records (0x0079713A, 0x00797157, 0x00797162) are unjudged.
    Their `$L` labels renumber; `./build.sh` rebinds them through the EH graph, the scratch verifier cannot.
  - P4 can retire two hatches: the hand-declared `??_7Rva004E1B00/179A/1B72@@6B@` externs and the
    `/alternatename` for `R2Data010EC760`. The real classes install their own vftables.
  - The vector-shaped members (+0x6C, +0x78, +0x84) are not yet real vectors. A real `vector<Rva004E194E>` copy ctor
    is 0x0052CD81's bytes except two callees:
    - `get_allocator` (ICF 0x0021983A): one more `fold-proof=` pin through `pin_admission.py`, like the ~70
      existing ones.
    - `__uninitialized_copy<const T*>` (`PBV`): 0x0052C987 is rowed as the placeholder `Rva0052C987Get` and
      pinned `<T*>`. Respell it to the `PBV` spelling rather than pin.
- The remaining Act members (same scratch method):
  - +0x14 is `vector<Rva004E16D9Record>`, not `vector<BfmePod40>`. `_Construct` 0x0052C320 calls copy 0x0052BD59,
    which installs the ForceBattle record's vftable 0xC61A70. As SpawnArmy.cpp's real record with an implicit
    copy, 0x0052BD59, 0x0052C320 and `__uninitialized_copy` 0x0052C915 are exact. +0x1E is padding, not a member.
    The vector copy 0x0052CB65 then gets retail's EH frame. Its two callees fold: `get_allocator` and
    `_Vector_base` 0x0053FF92, which is rowed for `BfmePod40`.
  - +0x20 is `vector<SpawnArmy>`: `_Construct` 0x004E3706 calls `SpawnArmy`'s copy 0x004E2F9F (`BfmePod88`'s
    copy is pinned as its twin). The vector copy 0x005008EB is outside LivingWorldCampaign.cpp's range, so P4
    only respells it.
  - +0x9C is `vector<vector<BfmeE8>>`: `_Construct` 0x0052D355 calls `vector<BfmeE8>`'s copy 0x004334D7.
    Instantiated for real, 0x0052D355 is exact; 0x0052D417 and 0x0052D3F1 differ only in calls to each other's
    placeholder names (`Rva005668E9Element`), so their respell resolves them.
  - +0x44 `vector<AsciiString>`: its copy 0x000BC07E is kept from another unit; nothing moves.
  - +0x90 `Rva004E1A04` stays open. It is 16 bytes and copies as AsciiString then three dwords, through the ICF'd
    0x0052BEC9 (rowed as two pair copies). Its dtor 0x004E1A04 is a user body that clears the string (the
    first 0x00036410 call), then the member's own dtor. Rva004E1A04Dtor.cpp now spells that as real code
    (exact, 3/3), replacing an explicit `~StringBase()` call. The dwords' types and the class's identity stay
    open.
- A3 group A (seat6's scope, `build/bridge_lane/fxnugget_scope.md`): `merge_definitions` refuses all six private
  `FXNugget` views, which have pads, no vptr or own method names. On the canonical class they byte-match with
  these reshapes:

  | Unit | Rows | Reshape |
  |---|---|---|
  | FXNuggetSlotBodies, LightPulseFXNuggetEffects, SoundFXNuggetSlots | 4/4, 1/1, 4/4 | view -> header |
  | RayEffectFXNuggetDoFXPos | 1/1 | drop the derived `m_pad04` |
  | FXListNuggetParse | 34/34 | 15 derived pads shrink by 0x148; declare their `doFXPos`/`slot03` overrides |
  | FXListDoFXPos | 2/2 | calls spell `rva001DFF5D`/`doFXPos`/`m_144`; slot 4 takes `const Object *` |

  - The slot-4 body 0x001DFF5D is rowed with non-const `Object *` parameters, but its only real caller
    `FXList::doFXObj` passes its own `const Object *`. Respelling it (`function --respell`, with the vtable
    declarations in AttachedModel, LightPulse and DynamicDecal) comes just before A3.
  - Plan: the six reshaped units go as `--prepared` texts in A3's plan, so they verify with the rename.

Update (2026-11-07, static-defects lane): the slot-4 const respell's prerequisite, `Rva2225E0Filter::accepts`
0x00362437 taking `const Object *`.
- `rename.py function --respell` (signature-only, db021bcc67) needs 52 prepared units in one transaction:
  51 private `Rva2225E0Filter` views that declare `accepts`, plus its definition. `_batch_source_edits`
  caps a run at 32, so it is refused (false reject in re_attempts.log). It cannot be split: a unit left on
  the non-const view calls a symbol no row names. Waiting on seat6's `--max-prepared N` override; then
  `accepts`, then 0x001DFF5D.
- The 52 prepared texts scratch-verify: 49 exact, 3 miss only renumbered funclets of exact parents.
- Follow-up cleanup: give `Rva2225E0Filter` one shared header and adopt it in the 51 view units
  (`header_adopt_lane.py`). That removes 51 private class copies, and a later signature change would
  touch only the header, the definition and the units that spell the mangled name.

Update (2026-11-07, static-defects lane): P16 route chosen: minimal B.
- FXList.cpp keeps its Zero Hour FXList/FXListStore machinery (so 0x0052BD3A and the two hashtable rows keep
  their emitter) and replaces only the Zero Hour `ParticleSystemFXNugget` view with BFME 2's on canonical
  `Rva001DFEAABase`, with the rowed ctor 0x001E0AEF defined in the unit. FXList.obj then emits retail's ctor
  and `??_G`, and no Zero Hour `parse`, pool glue or `addFXNugget`. In scratch: 15/15 exact (FXList.cpp's 7
  rows plus the ctor family).
- Landing it needs three Harness rules, queued with `tu_skeleton --emit-move`: (a) held-by-emission covers
  an implicit copy ctor placed by contiguity alone (0x0052BD3A); (b) a displaced compiler-generated
  special member (`??_G` 0x001E10CE) rides with the body that emits its vtable; (c) `--split` takes a
  prepared target-TU text in the same transaction.
- Pass test: a boot-queue run on an image with minimal B gets past P16 (FXList.ini loads).
- Handoff, with the text, the refusing commands and their output: `reverse/attempt_support/p16_minimal_b/`.
- The record chain respell, the shared Act header and the LivingWorldCampaign.cpp move (P2-P4, stage 0)
  are later cleanup, no longer on P16's path; their stage-0 tool needs are in the same handoff.
