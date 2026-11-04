# Supported 0x358E9F ownership correction

Use two separately reviewable commits: **retract the false real claim, then plain-admit the already-proved HotKey Value operation. Publish only the completed verified pair.** This is identity correction, not a hand rename or a new-name vote. The native-copy prerequisite is now published as `b4fe17216d`; root reports current `2be2d0e6d2` did not change this scope.

`add_match.py:462–469` deliberately refuses takeover of a real claim and requires its own retraction commit. `conversion_gate.py` Rule B explicitly permits that retraction. `docs/naming.md:960–961` distinguishes refuted canonical ownership from naming disputes; its manual-signature exception still permits only placeholder-to-canonical hand renames and does not authorize respelling this real AudioEvent specialization. The actual existing Clear/valarray precedents use the APIs below without changing a check.

## Prepared identities and claims

`current-binding-facts.json` holds the exact old row and the actual new full COFF decoration, avoiding shell expansion of its `$` characters. The old row is AudioEvent `_M_insert`, `0x00358E9F`, 148 bytes, ThingTemplate.cpp. The new existing decoration is `_M_insert<Rva00359032Value>`, at the same address/extent in `Code/GameEngine/Source/GameClient/MessageStream/HotKey.cpp`.

Keep active claims for the RVA and both source files through the complete batch; renew normally if needed. Additional edited consumer sources need their own scope claims. Current native proof establishes an eight-byte string/counted-handle operation, not original inheritance, application identity or a new semantic name.

## Commit 1: exact real-claim retraction

Under the existing portable **exclusive `reverse/.add_match.lock`**, revalidate the old exact name/RVA/size/source tuple against the current ledger. Use the repository's existing writer primitives:

```python
# Inputs come from the reviewed snapshot, then are revalidated under the lock.
new_raw, dropped = ledger_io.rewrite(
    raw,
    lambda f: not (len(f) >= 5 and f[0] == old_name
                   and int(f[2], 16) == 0x00358E9F
                   and f[3] == "148" and f[4] == old_source))
assert dropped == 1
# Write new_raw with LF preserved, then while still holding the same lock:
gen_small.write_tombstones([(old_name, 0x00358E9F, reason)])
```

Use `portable_lock.lock(handle, exclusive=True)` as add_match does; keep validation, rewrite and tombstone together while the handle remains open. The tombstone reason should cite the refuted AudioEvent value/lifetime and the proved counted-handle insertion, without claiming an unknown original class. `write_tombstones` does not acquire its own lock. There is no established general real-claim-retract CLI; these are the exact already-used APIs. Do not relabel the old row as generated scaffolding or call the scaffold-only retraction helper.

Preserve both mixed source files and all unrelated rows. This particular old method is a **header-generated template emission**, not an explicit authored definition that can simply be cut from ThingTemplate.cpp. Do not delete its audio parser, add a suppression specialization or invent a marker to remove that incidental emission: the parser still carries other owned rows. The retraction withdraws the false ownership claim; remaining legacy audio emissions stay explicitly outside this repair. Require the normal frozen checks to pass unchanged rather than hiding any refusal.

After staging explicit paths, run `python3 tools/name_dependents.py --staged` and normally verify its affected sources, plus the remaining ThingTemplate rows. Commit the retraction with native evidence/re_log handoff. There is no dump fallback and this intermediate 148-byte ledger gap is **never published alone**.

## Commit 2: plain readmission in the approved TU

The current map already approves **HotKey.cpp** for this RVA (`approved,C,C=0x00358CCD..0x00358F33`). This differs from the same-source-only Clear precedent, where no approved destination existed. Recheck that exact approval before admission.

Invoke plain add_match with the actual decoration from the reviewed current object. An exact argument-vector form avoids shell quoting risks:

```python
subprocess.run([
    sys.executable, "tools/add_match.py", facts["new_name"],
    "0x00358E9F", "148", facts["destination"],
    "--notes", "Native HotKey string and counted-handle insertion; complete 148B and real node/copy closure verified; original application identity unknown"
], check=True)
```

Do not use `--replace-rva`, `--replace-existing`, `--icf-owner`, `--pin`, an object-symbol alias, new wrapper or new pin. Plain admission performs normal verification and rolls back an unsuccessful append. The old-name tombstone does not suppress this different new name/RVA key.

Synchronize the **one observed source cell** separately using the existing narrow internal API used by supported split/shatter code:

```python
map_after, changed = tu_skeleton.repoint_rows(
    map_raw, "reverse/tu_map.csv", "rva", {"0x00358E9F"}, "source",
    "Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp",
    "Code/GameEngine/Source/GameClient/MessageStream/HotKey.cpp")
assert changed == 1
```

Preserve every approval/evidence field and other byte. This helper supplies field-safe writing, **not approval**; the existing approved destination and independent native proof supply that evidence. Plain add_match does not update this cell. Do not regenerate the whole committed map or pretend its in-memory stale-input reader updates it. No `body_owners.csv` entry exists for this exact RVA in the inspected current register. Source-level debt stays with the surviving mixed files unless its owning tool establishes a separate retirement.

## Consumers, pins and final gates

The saved index (`23b85ddde5`, 2026-11-03 18:36) lists the old decorated insertion name only in ThingTemplate.cpp. Its current object both defines it and references it once internally; no indexed outside consumer is found. That is scoped evidence, not exemption from `name_dependents --staged` and `--range <batch-base> HEAD` or the actual outgoing provider audit.

The Value pin at current line 4251 and Record pin at 7024 already map this address; no old AudioEvent insertion pin exists and no relevant tombstone predates this correction. **Add no pins.** Keep existing bindings unless the normal pin checks require a justified retirement. Once the Value row is admitted, its redundant existing pin can be retired as a separate reviewed shrink if desired; preserve the Record binding while its real callers still need it. No new fold assertion is granted by this procedure.

Normally verify both mixed sources, the admitted 148-byte body, full native callee closure, applicable EH graphs, strict frozen checks, CSV/TU ownership and actual dependents. Run normal pin consistency; use each register's owning retirement path for any genuinely cleared key. Confirm one final matched owner at the address, final coverage restored and no changed/removed-provider loss. The prerequisite's existing guard proof does not replace these final checks.

Because the ledger home changes, record the outgoing row/path/register/provider audit across the whole final batch. Both file paths survive; do not globally replace old path references or move all file-level debts. Stage exact paths. Source/functions/deleted_rows/map/evidence changes alone do not inherently require `Verifier-Change`; gate/baseline/whitelist edits, including an owning hatch-baseline shrink if performed, follow their actual trailer rules. No `Debt-Retired` exception is needed merely because a row moved out of a file that still exists.

Push the completed normally checked batch with `tools/push.py` and its shared clock/lease. This maintains final native coverage without bypassing the real-claim guard. This reviewer made no tracked edits, ran no builds or claims, and performed no network/publication operation. All tracked reads are stopped.
