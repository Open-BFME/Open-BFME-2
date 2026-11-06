# Projected-shadow owner/table identity, 2026-11-06

Bounded read-only review. No Code/ledger changes, claims, builds, network,
publication or child workers. Scope: existing Rva007AFF00Owner/Base and
Rva0010BA2COwner views. Current HEAD during review: `d379ce9f77`.

## Proven receiver identity

Retail disassembly independently ties the two owner names together:

* Constructor **10BA2C/25**, rowed as Rva0010BA2COwner, calls base constructor
  F0F2B, installs **BCF9E0** at this+0, then calls 108895 on the same this.
* Destructor **1092B9/86**, rowed as Rva007AFF00Owner, first installs that
  same BCF9E0 at this+0, releases this+68 and this+70, then restores BCEFA0.
* Deleting destructor **10BA45/28** calls 1092B9 and conditionally deletes this.
* BCF9E0 contains exactly three code pointers:
  **[50BA45, 4B3FD0, 509DA6]**, followed by non-code floats -3.2 and +3.2.
  Slot 0 is therefore the rowed deleting destructor of the same owner.
* A narrow native .text scan finds the BCF9E0 immediate at exactly two
  operands: 1092CC (the destructor) and 10BA38 (the constructor). Both are
  covered by the rows above; no third direct immediate installer was found.
  The normal fold tool must still make its complete third-owner/slot checks.

This is stronger than merely sharing a same-sized or ICF-folded table. It
supports folding **Rva0010BA2COwner into Rva007AFF00Owner**, the existing
vtable's class token. It does not recover an original semantic class name.
The reverse direction lacks the required existing vtable name. Neither owner
is currently canonical/registered, and no old-owner frozen key or naming
record was found in the checked registers.

## Current source/table defect

The seed has both complete class declarations. Rva0010BA2COwner derives from
the measured 0x68-byte F0F2B view and carries the observed fields through
next114/sizeof118. Rva007AFF00Owner instead derives from a padding-only
0x68-byte Rva007AFF00Base and carries only the two retained resource fields
at +68/+70. Both views have relevant target facts, but they are not currently
a single C++ type.

The current normal seed COFF defines `??_7Rva007AFF00Owner@@6B@` as **4 bytes**,
one relocation to its deleting destructor. Its Rva007AFF00Base table is also
one slot. The manual constructor reference therefore reaches a **short
compiler table**, not a separately complete three-slot table. The ledger's
20-byte upper bound includes the two floats and does not validate that emitted
table. A class-name fold alone cannot fix its two missing slots.

Do not fold Rva007AFF00Base into F0F2B just because both restore BCEFA0:
BCEFA0 is independently known to be ICF-shared by distinct classes. Retail's
base table has [EFAD2, B3FD0, __purecall]; the canonical
BfmeShadowBufferOwnerBase currently models only its first observed slot.
The explicit constructor call to F0F2B supports the owner's actual base path;
the folded base table alone is not class-name evidence. LINK-095/5a3ef66578
also requires preserving the existing implicit inline-reset F0F2B destructor,
not recreating its earlier conflicting call-form copy.

## Smallest supported identity transaction

Direct `class --fold` is the appropriate no-new-name operation, but plain
token rewriting would declare Rva007AFF00Owner twice in the seed. Direct
`plan_fold(..., prepared=...)` permits prepared source only for a nested or
registered destination. **A new canonical header is not mandatory merely to
solve this collision:** the documented batch source-preparation API is narrower.

`docs/naming.md:494`, `tools/rename.py:8054,8100` and
`tools/tests/test_rename_run_batch.py` support:

    rename.run_batch(ctx,
        [("class", {"name": "Rva0010BA2COwner",
                    "new": "Rva007AFF00Owner", "fold": True})],
        source_edits={seed_path: prepared_seed_bytes,
                      ctor_path: prepared_ctor_bytes})

Preparations are in-memory starting text before ordinary fold planning. They
can combine the two existing views into one compatible declaration/emitter
before the fold's token rewrite, while the normal tool owns row, notes,
body-owner, tombstone and symbol changes. The intermediate prepared spelling
must leave the fold a single declaration to rewrite; the final compiler must
still emit all existing rowed definitions under their final ledger names.
Do not pre-edit the files or hand-edit their rows. Every coupled request must
plan successfully; one refusal applies nothing. Normal claims, byte checks,
ledger checks, journals and rollback remain active. Source paths must be
tracked, clean, matched, non-generated/non-vendored Code/*.cpp (maximum 32),
so bank current source edits before using this path.

### Bounded one-slot fold prerequisite

The smallest truthful candidate keeps the existing one-slot Owner table
semantics while reconciling the source views. Use the already target-backed
`Rva000F0F2B : BfmeShadowBufferOwnerBase` as the owner's 0x68-byte base; remove
the padding-only Rva007AFF00Base declaration/body after its last use is gone.
Do not rename that fake base via BCEFA0 or introduce a replacement body/alias.
Keep Owner's existing virtual destructor and ordinary reset method, with no
new virtual methods in this prerequisite. Its constructor must still call
F0F2B and install the existing Owner table. This preserves the current table
token and scope of the identity change; it does not claim the table complete.

There is enough target evidence for one 0x118-byte declaration with these
field types, without inventing concrete retained-object classes:

| Offset | Existing measured representation |
| --- | --- |
| 00..67 | F0F2B base; prefix58, float58/5C/60 and byte64 are independently written by its constructor |
| 68 | Rva007AFF00Ref* m_first (dtor reads refcount+4 and dispatches slot0) |
| 6C | opaque four-byte word; do not infer ownership from its zeroing |
| 70 | Rva007AFF00Ref* m_second (same independently observed release protocol) |
| 74 /75..77 | byte flag / padding |
| 78 /7C /80 | float / float / unsigned four-byte word |
| 84 /85 /86..87 | byte flag / byte flag / padding |
| 88..93 | full existing three-float Rva00108895Triplet |
| 94..D3 /D4..113 | existing unsigned int arrays[16], reset in lockstep |
| 114..117 | pointer to the same owner type, established by factory free-list use |

Reconcile the old `retained68[2]` initializer with the two distinct +68/+6C
words, preserving its observed eight-byte bulk zero; reset +70 through the
typed second pointer. The old destructor can then keep its actual m_first/
m_second accesses. Do not replace the proven release protocol with a
TextureClass/RenderObjClass destructor based on a donor role. Native ctor,
reset and factory accesses establish the full extent/offsets, while the dtor
establishes the two retained-pointer protocols. The role/type of +6C remains
opaque; this does not prevent a faithful four-byte field representation.

Before folding, prepare a single combined class declaration under the OLD
token in the seed, with both existing ctor/reset and destructor definitions
represented by that declaration; fold then yields the existing NEW token and
the existing destructor ledger spellings. Supply the other constructor unit's
matching view in the same source_edits transaction. Normal tool planning must
still prove the fold and final declarations. This is a source preparation,
not a request to rewrite destructor rows by hand.

**Unproved codegen boundary:** replacing the fake padding-base destructor by
the existing F0F2B inline reset may change EH cleanup symbols/selected COMDATs;
giving the constructor its real polymorphic base may add an automatic vptr
store or helper emission. The typed two-word zero can also change the 97-byte
initializer's STOS scheduling. These are concrete private-probe requirements,
not missing receiver-identity evidence. Retain the candidate only if all
existing rows, parent EH, and the selected one-slot table/destructor/provider
behavior remain exact. No such candidate was compiled in this review.

## Additional prerequisites for the actual three-slot repair

1. **Slot 2 already has a real body.** 109DA6/13 is rowed as
   `?rva00109DA6@Rva00109DA6Host@@QAEXXZ` in Common/VslotMiscForwarders.cpp.
   Retail pushes this as the manager argument, loads DEC2D8, calls 1091A8 and
   returns. The supported transfer, retaining its existing address-derived
   identifier, is `rename.py function --rva 0x00109DA6 --to-class
   Rva007AFF00Owner --new rva00109DA6` with owned prepared source. It changes
   the declaration to virtual and moves the existing row/provider; it does
   not need another copy, forwarding wrapper, pin or alias. Prepared installer
   units are exempt from the early current-object table check, but the rebuilt
   objects must name the correct symbol at slot 2 and preserve every other
   resolvable slot. Include the real forwarder source in claims/verification.
2. **Slot 1 is an unresolved identity prerequisite.** B3FD0 is the genuine
   shared one-byte RET. No existing Shadow/AFF00/F0F2B member row or pin at
   that address was found. `--virtual` and `--to-class` explicitly refuse
   stealing an unrelated shared/ICF body: the table proves an empty function
   is there, not which unrelated member owns it. Establish the slot's actual
   signature/inheritance from target callsites or existing class evidence,
   then use its truthful owning/admission path. Copying an unrowed empty
   body merely to fill a table, or binding an unrelated empty virtual, is
   not a demonstrated repair. No such shortcut is proposed here.
3. Reconcile the complete owner view's dependencies and lifetime before
   application: canonical BfmeShadowPrefix.h, full by-value
   Rva00108895Triplet, retained-field types, exact constructor/destructor,
   EH and selected helper COMDATs. A correct 25-byte constructor is
   insufficient proof of the three-slot provider or the rest of the 0x118
   allocation. Check the final emitted table's complete 12-byte relocation
   sequence against all three retail slots, with the two following floats
   excluded from the table.

A genuine canonical shared header plus header_adopt_lane/class_contract and
registered-destination prepared fold is another supported route if this owner
will be shared across more units. It should freeze measured facts, not be
registered solely to unlock `--prepared`; no such header currently exists.

**Next concrete action:** finish and bank the current supported mechanical
work, then prepare one unified owner view in build/ and privately prove its
existing ctor/reset/destructor/EH/provider behavior. Resolve slot 1 before
claiming a full short-table fix; couple the proven fold/preparations through
run_batch and migrate the existing slot-2 row through --to-class. No direct
fold/application or short-table verification was run in this read-only review.
