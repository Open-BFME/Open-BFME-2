# MilesAudioManager Snapshot name-slot prerequisite

Served table: `??_7MilesAudioManager@@6BSnapshot@@@`, RVA 0x007C559C,
four entries. Its retail slot 2 is RVA 0x000518B2, whose complete six-byte
body is `B8 00 53 BC 00 C3`, returning the exact MilesAudioManager literal
at RVA 0x007C5300. The old row incorrectly presents this as public nonvirtual
`MilesAudioManager::name() const` in SubsystemNameGetters.cpp. The canonical
header already declares the protected virtual GetSnapshotName override.

Constructor RVA 0x0005CF5F installs primary VA 0x00BC55B0 at +0 and Snapshot
VA 0x00BC559C at +0xC; destructor 0x00060FE2 installs the same pair. The
Snapshot table's four targets are 0x0005D41D, 0x000587C6, 0x000518B2 and
0x0005E3E5. The first is the existing eight-byte `sub ecx,0Ch; jmp` adjustor
to the deleting destructor at 0x00061AA1. AudioManager's original ctor/dtor
independently establish the same base order. Native complete records and cast
witnesses retain SubsystemInterface size12/14 slots, Snapshot size4/four slots,
AudioManager extent16 and MilesAudioManager size0xC08 with Snapshot at +0xC.

The bounded source proposal selects the existing BFME_SNAPSHOT_NAME_SLOT mode
before the first Snapshot include in the existing main TU, adds its real
override declaration, and replaces the getter TU's private one-method class
stub with the existing canonical header and real member definition. No header
or generator contract change is needed. The old unused public name declaration
is not silently rewritten. The regular to-class planner, not this document,
owns the function-row identity change.

Private ordinary compiler controls retain 421/421 main-TU code rows and 43/43
getter rows strictly exact, without unresolved references or new flags. Main
changes only Snapshot table relocation +8 from __purecall to the actual getter;
its 111-slot primary table is unchanged. Getter changes only that six-byte
function's emitted mangling. These are retained existing bytes, not recoveries.

Complete native type-record comparison also identifies the mode's coupled
Drawable, PlayerList and Weapon declarations: only their methods/virtual names
change from crc to GetSnapshotName, with unchanged storage, fields, bases and
slot positions. Their independent retail Snapshot tables at 0x007FB0A4,
0x007FD604 and 0x0080214C have slot2 getters 0x00279669, 0x002A7A23 and
0x002CC2F6, each a six-byte return of its exact class literal. The getter TU
adopts existing canonical audio declarations, including the complete Coord3D;
it emits no other new code/data/provider. Byte equality alone did not establish
these coupled class contracts.

Normal rename initially refused the missing slot-name approval. Two genuine
independent child agents then examined original tables/bodies and the existing
protocol, read their actual native served briefs, and proposed GetSnapshotName.
The native lane validates/submits two votes on header fingerprint
08e68efcad331804afbadeb9c5317985f2363964c72ff809ca3b1af81f964c7b:
w-3aeb163b3df9 (codex-agent-melee), w-4648cf2578f9 (codex-agent-transport).
Each identity is explicitly assigned to that real child; the operator delegated
packet reads through the native foreign-claim snapshot, never its own vote or
write authority. Neither child read the other's private answer. The second saw
an old tracked blocker recommendation and disclosed it; its actual rationale
was independently derived. Exact historical identifier spelling is inferred,
while the physical name-returning role and slot are proved. No external reviewer
CLI, scoped-name votes, synthetic voter or manual approval row is used.

The next native rename must cite the committed approval revision and both
prepared sources, then pass ordinary whole-area builds and loss guards.
Completion of the served bridge task still requires the next published real
link to stop bridging/refusing this table while retaining its data coverage.
No completed queue item, new code coverage, startup or runtime improvement is
claimed from this naming prerequisite or private byte controls.

## Ordinary source integration

After the separate generic compiler-dtor verifier repair, the unchanged
prepared sources pass the normal to-class transaction using committed approval
44358b2dbb. All464 existing code rows,63 literals,33 floats,106 imports and
the existing data row pass. The two compiler deleting-dtor slots are proved
through their complete real local scalar copies; generic weak defaults remain
refused. No shared header, class contract, alias, pin or generated source was
changed.

Fresh per-file linking previews remain identical before/after: the main unit
predicts43,087B and the getter unit257B, both clean. The main's older census
baseline43,068B already differed before this source change, so its19B gap is
not new credit. The old unused public name declaration in the canonical header
remains explicit declaration debt; this is not full main-TU header adoption.
The served task still awaits a published real-link bridge/data-coverage result.

## Authoritative local real-link follow-up

On2026-11-20 the documented native Windows command
`python3 tools/exit_link.py --link --local` measured the unchanged source head
1a59743774fa326e94d0f5fa188e3faa1e0b78e1 at base0x02000000. This is a local
Michael-PC measurement, not a GitHub Actions run. The preceding object plan
found all17,502 expected objects and proved835/835 omitted funclets covered
by exact kept parents. The real link reran the native currency, data, omission
and EH proofs, selected17,486 objects, and exited0 after61.9s in the linker.
There are0 unresolved and0 duplicate names;5 warning/error-log lines remain.
The image receipt is authoritative with omission_proof=passed, no stubs,
no /FORCE, fillers or code aliases. The native export path records24 export
aliases; no custom alias was added. Existing EH debt remains9 baselined byte
differences among11,939 EH rows; no baseline was expanded.

The bridge report places the actual Snapshot table at007C559C in `correct`,
with4 slots, previous_extent16, the real kept Miles object, and no source-slot
mismatches. It occurs in neither bridge entries nor refusals. The related
111-slot/444-byte SubsystemInterface table is likewise correct. Thus the target
table remains measured and covered rather than disappearing from the ledger.
The native `exit_link.py --blockers` writer used this matching unstubbed result
to update both queue files; the Snapshot bridge item is absent from its output.
Publishing this measured queue result satisfies this served bridge item's pass
test. It does not finish other Miles class/header debts or create new code bytes.

Global scaffolding remains:3,013 bridged vtables,44,552 bridged slots,27 refused
tables and431 bridged initializers. This successful link is not a completed
game rebuild and the image was not executed.

ImageSHA256:ded78594be5e9e45d0fd93e6ec2d06fa8fb6654334a247cbd54ce7a7156bb3c0.
MapSHA256:36d6b6cc676f6618757cbcf64904faa0305855957cb60cc2d85b58a84fbf8263.
The complete unmodified result, bridge decisions, native queues, link log and
image receipt are preserved locally under diagnostics/continue-20261120-body-recovery-1656/
bfme2/local-real-link-1a59743774 with an artifact-hash manifest. These native
artifacts belong to the exact source head above, not a later changed code head.
