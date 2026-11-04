# Real-name insertion ownership correction: policy and tooling boundary

Read-only audit, 2026-11-04. No compilation, claims, network, tracked edits, ledger writes, or tool execution that mutates repository state. The root owns the native/type/provider proof and dependency review. This note does not approve a new application type name or assert full link closure.

## Supported identity-correction route

The current row is a real-named AudioEvent tree insertion at `0x00358E9F`, extent 148, in `Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp`. A different real/opaque operation identity is not eligible for `add_match --replace-rva`'s scaffold takeover. `--replace-existing` is for an unchanged full decorated name, not replacement of this identity.

`docs/naming.md:949-961` distinguishes refuted canonical identities from ordinary inferred-name disputes and points identity correction toward `add_match`. Its flag example is broader than the current scaffold-only guard. The documented hand-signature/scope exception (`docs/naming.md:981-999`) remains a **placeholder-to-canonical** route with evidence requirements. It is not a blanket permission to hand-rename this existing real AudioEvent specialization into a different opaque operation type.

The established real-claim precedent is `reverse/attempt_support/clear-member-identity-20261103/policy.md`, consistent with `reverse/attempt_support/valarray-record-identity-20261101/README.md`:

1. Independently establish the replacement identity, source, ABI, and native operation evidence. Exact bytes or an existing caller/pin spelling alone do not establish the original application type.
2. Retract the incorrect real claim in its **own normally checked commit**; remove/bank its superseded source body while preserving the other rows of a mixed TU. `tools/conversion_gate.py` explicitly allows retraction of a wrong clean claim, in its own commit, rather than repointing a still-live clean claim back to a dump.
3. In the next commit, admit the actual proved decorated symbol with plain `tools/add_match.py`, the verified RVA/extent, and approved source. Do not use a takeover/alias/ICF switch to conceal the real-identity replacement.
4. Publish the completed, fully verified replacement batch, rather than a temporary coverage gap. Normal name-dependency, frozen-source, row, byte, pin, provider/consumer and outgoing-batch checks remain applicable.

The Clear precedent's SAME-source condition was specific to its lack of an approved destination. It is not a universal prohibition on source changes during identity correction, and it does not authorize this move by itself. This case has an explicit approved HotKey destination in the currently inspected committed map.

## Exact retraction primitives and tombstones

There is no generic real-row retraction CLI established by this audit. The existing precedent uses the same `reverse/.add_match.lock` ledger lock as add_match, then the existing APIs:

- `ledger_io.rewrite(raw, keep)` (`tools/ledger_io.py:123`): remove only the exact old full decorated-name/integer-RVA row; require exactly one removal. All retained record payloads and original terminators are preserved byte for byte. This primitive supplies no identity approval or coverage proof.
- `gen_small.write_tombstones(entries)` (`tools/gen_small.py:4927`), with entries shaped as `(old_name, integer_rva, reason)`: append the removed old-name/RVA tombstone to `reverse/deleted_rows.csv` using the writer's LF validation and CSV quoting. It does not acquire the lock itself. The reason should identify the refuted AudioEvent identity and cite the actual native copy/insertion evidence without claiming an unknown original application type.

The tombstone suppresses resurrection of the **old name/RVA key** during union merging. It does not forbid a different, justified full decoration at the same address, transfer metadata, waive naming rules, or supply TU approval. `gen_small.retract_dump_rows` and `gen_dump --retract` are generated-dump mechanisms, not generic real-claim withdrawal commands.

A later plain admission has the shape:

```text
python3 tools/add_match.py "<actual proved COFF decoration>" 0x00358E9F 148 Code/GameEngine/Source/GameClient/MessageStream/HotKey.cpp --notes "<evidence; original application identity remains unknown>"
```

The placeholder above is intentional: selecting Value versus Record or a precise full decoration belongs to the root's current type/COFF proof. Retraction/readmission cannot bypass canonical-name evidence. No new pin or alias is authorized by this procedure; the root must reconcile existing consumers and pins on their actual evidence.

Source/functions/deleted_rows/evidence changes alone do not require `Verifier-Change`. Editing gate code, hooks, a baseline/whitelist or another protected register invokes that register's actual rules. Retraction is not debt retirement. There is no basis here for adding a baseline or a `Verifier-Change` trailer merely to excuse the correction. Existing debt/path keys must follow their owning transfer/retirement paths.

## The separate TU-map source-cell issue

The inspected row at `reverse/tu_map.csv:27124` is:

```text
0x00358E9F,148,code,Code/GameEngine/Source/GameClient/MessageStream/HotKey.cpp,approved,C,C=0x00358CCD..0x00358F33,Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
```

Thus the destination `tu` is already approved HotKey, whereas the observed `source` is still ThingTemplate. Plain add_match writes functions.csv; neither it nor retraction/tombstoning should be described as updating this source cell. The parent also inspected rehome_rows and found no map update there.

There **is** an existing narrow internal byte-preserving primitive in `tools/tu_skeleton.py:3769`:

```text
repoint_rows(raw, label, keycol, keys, column, old, new) -> (new_raw, count)
```

For this exact record its mechanical arguments would be `label="reverse/tu_map.csv"`, `keycol="rva"`, `keys={"0x00358E9F"}`, `column="source"`, and the two exact source paths above; the caller must require count 1. The helper requires the requested header fields, matches the given key and old field, and preserves other bytes. The existing `shatter_repoint` caller (`tools/tu_skeleton.py:3463-3473`) uses this helper for per-RVA path-keyed source transfers. It is not a TU-approval checker, identity checker, lock owner or replacement transaction.

No standalone source-cell refresh CLI or independently documented real-retraction/map-sync transaction was established in this bounded audit. The helper is an existing internal API mechanically suitable for a scoped source update; its existence alone must not be represented as policy approval for arbitrary map editing. A full regenerated committed map is not the proposed remedy and is forbidden in the consolidation lane.

`tu_map.current_rows` (`tools/tu_map.py:1545-1575`) explicitly returns the committed map when the fingerprint is fresh, otherwise rebuilds current inputs **in memory/cache**, refusing an absent ZH reference tree. That supplies fresh reader input; it does not rewrite the committed source cell, and this audit does not establish a universal hook exemption for stale source cells. The safe reporting boundary is to record source synchronization separately, preserve the existing approved destination/evidence, and use normal ownership checks rather than pretend the withdrawal/admission performs it.

## Scope and remaining proof

The root is responsible for existing claims over the address, both mixed source files and any changed consumers; full source retention; exact candidate bytes/relocations; the copy/insertion contract; current pin/name dependents; and final normal verification. This review supplies the supported withdrawal/readmission precedent and exact implementation limits, not approval of the opaque identity or of an unchecked metadata move. Reads stopped after this report; no tests were run.
