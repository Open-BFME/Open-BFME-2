# Four-slot holder recovery: native lifetime and tooling prerequisites

Inspected on 2026-11-17 at `e8e34c0e8f6`; independent adoption banked as
`2fa6c426794`. The target is `??_7Rva00575383@@6B@`, RVA `0x0086E5B4`.
Retail has four slots/16 bytes: deleting destructor `5753B4`, then existing
8-byte forwarders `57539C`, `5753A4`, `5753AC`. The compiled table still has
one slot/four bytes. No new row, alias or pin is needed to supply the three bodies.

The planning update now uses the canonical eight-byte holder header. Its three
runtime sections remain identical, all ten relevant units pass 102/102 rows with
strict reusable receipts, and the owning tool retired one header-debt row. See
[the source-coupled proof](holder-update-canonical-20261117-root20.md).
This does not retire the four-slot bridge.

The two lifetime hypotheses were rejected and restored:

- A declaration-only canonical destructor and a strong complete-destructor
  definition in its existing owner preserve that owner's 7-byte complete dtor
  and 29-byte deleting dtor. They also permit the member-destructor unit to adopt
  the shared header without changing its 82 runtime sections. But the complete
  eight-consumer native trial shows `V3PolyCopyCtors.cpp` emitting a 28-byte ANY
  deleting-destructor copy, adding a call to the complete destructor. The other
  constructor consumers stop emitting their former base lifetime packets.
  The owner-only success therefore cannot establish safe shared lifetime semantics.
- Keeping the inline canonical destructor and adding `/Ob0` to the member unit
  emits a new 28-byte deleting-destructor copy and table there, growing 82 to 85
  runtime sections. That unit precedes the correct owner in the real path order.
  The trial was rejected rather than accepting the three derived bodies alone.

The verified private-base layout preparation (base 4 to 8 bytes, each of three
children stays 12 bytes/member at +8; 82 runtime sections identical, 51/51 rows)
was restored as well. No additional private view or compile-flag change was banked.

The obsolete pin `?rva0057539C@Rva0057539C@@QAEXXZ` at `57539C` must be retired
before the owning virtual promotion accepts that row as one class member. Fresh
claims show both `reverse/symbols.csv` and `reverse/hatch_counts.json` held by
`Krzysztof Włoch@DESKTOP-D6QURIN/807d632b`; neither was edited. All 17,517 expected
kept objects existed after the ordinary full gate. The first independent scan
stopped before the COFF reference scan because its scratch audit guard wrongly
refused an authorized read-cache timestamp touch. That result is incomplete;
the later exact owning-API scan **completed cleanly** at source commit2fa6c426794:
all17,517unique kept objects were parsed, with zero pin references, all three exact
mention-closure objects current before/after, and unchanged inventory, source/object
metadata, source hashes, symbols hash and HEAD. The complete result and artifact
hashes are preserved in the companion JSON. This is a point-in-time consumer proof,
not authorization to edit another worker's ledgers; refresh it when those claims
are free before retiring the pin.

A separate generator prerequisite was found by source inspection: the normal
private-source census omits declarations found only in the established canonical
header, including this constructor, and its tournament does not require all
existing canonical consumers to pass. Merely updating contract slots or supplying
fake header-emitter facts is unsafe. A separate tooling seat is repairing the
declaration/native-witness boundary and mandatory consumer coverage with regression
controls. The earlier sole-destructor method-order fix `e8e34c0e8f6` is already
landed; it solves ordering only.

After these prerequisites clear, use owning `rename.py --virtual` for slot 1 and
`--to-class Rva00575383 --also` for slots 2/3, retaining current placeholder names
and signatures. The A4 forwarder needs its existing `noinline` effect. Prepare all
actual direct callers to qualified base calls: the update, common update and
mouse-click caller for slot 1; `rva00576B99`, `rva00575D88`, `rva00577324` in the
member unit for slots 2/3. Check every installer and derived table, every destructor
copy and weak binding, all existing rows and EH, not just the target table.
Stage only legitimately generated interface/contract facts before the owning
transaction; protected canonical headers are not valid `--prepared` inputs.
Prepared CPP paths must be clean against HEAD.

Authoritative real-link run [319](https://github.com/Open-BFME/Open-BFME-2/actions/runs/44166176629),
commit `50737acf866b73727a21dc0bc8ef45d6c07f8b4f`, still has **3 unresolved,
0 duplicates, no real image**, with **468 initializer bridges and 3,110 vtable
bridges / 45,896 slots**. Its target entry still reports all three source slots
missing. Artifact `14368572756` was downloaded and verified against SHA-256
`dc43b55c33c94ce37501fb6aea9bd6adce8a6536d0473cb1d22caf405fc1832d`.
Run 320 was already in progress when read; no result is inferred for it.
There is no matching real-image menu/skirmish/save-load or image-ISO clearance.

[Native packets, trial verdicts and artifact target entry](holder-four-slots-20261117-root20.json)
keep the positive owner-only result separate from the rejecting cohort result.
No lifetime, header, contract, pin or slot adoption from these rejected trials remains.
