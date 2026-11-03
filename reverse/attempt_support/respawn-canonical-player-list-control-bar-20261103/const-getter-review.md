# Old const PlayerList getter: focused consumer review

**The seed's old const-getter removal does not remove its provider in this audited cohort.** Both named outside copies remain, with identical freshly read four-byte bodies. No full-image closure is claimed.

Old decoration: `?getLocalPlayer@PlayerList@@QBEPAVPlayer@@XZ`. The supplied both-operations proof records22 matched rows, no missing/errors, removes this one definition, adds the distinct non-const QAE getter and ControlBar::markUIDirty, and reports no changed retained definitions. This audit does not repeat byte verification or the owning reviewer's two new-helper witness checks.

## Actual named objects

| Normal cached object | Old QBE definition | Incoming references | Receipt binding |
|---|---|---|---|
| Object.cpp |4B `8b4110c3`, no outgoing relocations | Only its own `.debug$F` metadata relocation, type7; no runtime code/data edge | Object/source/all97 recorded dependencies match |
| GameLogicInit.cpp |4B `8b4110c3`, no outgoing relocations | Only its own `.debug$F` metadata relocation, type7; no runtime code/data edge | Object/source/all126 recorded dependencies match |
| RespawnUpdate.cpp seed |Absent in current normal object | None | Object/source/all86 recorded dependencies match |

None of the three has an undefined old QBE name, a weak/default, `/INCLUDE`, or `/alternatename` involving it. The outside symbol-table appearances are definitions, not evidence of an external call. The two debug relocations describe each retained getter itself; they are not game-code or table consumers. All three object files remained stable through the read.

## Selection/cohort property

The saved index is2026-11-03 18:36 at23b85ddde5. It records three copies in order: Object rank935, GameLogicInit rank1376, seed rank12921. All have the same symbol digest0ebf5f24c0ac, native verdict `null`, and no recorded selection exception/native owner. Under that saved order, Object's first copy survives the seed replacement; removing the later seed copy therefore does not change the old getter's first available body. Fresh reads establish the same4B body in both surviving outside objects even though their whole-object index digests have changed.

This is a supported cohort property, not proof of the old const name's native identity. QBE and QAE are distinct symbols. No aliasing or identity substitution is inferred from their similar machine-code shape, and no old-QBE native binding is newly certified.

## Limits

Only the three touches in const-getter-consumer-audit.json were inspected through `link_census.object_symbols`, `eh_verify.Obj`, and direct receipt hashes. There was no broader object sweep, build, network, claim, source body inspection or tracked edit. Recorded dependency/source/object hashes agree, but compile-command fingerprints and strict include search inventories were not regenerated; these are bounded current-byte receipts, not a full strict preparation result.

Current normal seed bytes already contain no old QBE definition/reference. Its private candidate and whole-image/provider graph remain the owning reviewer's responsibility. Additional outside consumers, current global link order and runtime reachability were not exhaustively established. The result supports removal of this one later duplicate within the observed cohort; it does not approve unrelated helper losses. Tracked reads stopped after this focused review.
