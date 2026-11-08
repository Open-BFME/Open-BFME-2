# Bounding getter alignment refusal, 2026-11-08

The served Rva001684D6 primary table (0x007D41C8) refuses two RenderObjClass
getters. Both are native-exact 22-byte bodies, rowed in hlod.cpp. The scoped
normal build passes all 193 rows across that owner, BaseHeightMapConstructor
and Rva001684D6Copy.cpp, plus five strings, 24 floats and two imports.
No Code, header, ledger owner, pin or verifier change is applied.

The fresh index f4727bbd09 (2026-11-08 12:06, census 6494b4b9d0) uses retail
order: its first copies are animobj.cpp, whose flags, bytes and relocations
strictly equal hlod.cpp. That observation alone does not clear the queue.
exit_link defaults to path order. Replaying Targets.resolve with the same
provider set in path order selects BaseHeightMapConstructor instead, whose
flags are 0x60101020 against the owner's 0x60501020. Bytes and relocations
still agree and both native-byte comparisons pass, but the alignment field
alone triggers target-not-winning-provider. provider-order.json records both
orders and the exact resolution results. The earlier stale-queue diagnosis
was retracted through re_log.py; it did not account for the different order.

LINK-619 proposes ignoring IMAGE_SCN_ALIGN_MASK in the twin rule. A broad
implementation needs more proof: equal raw call/pop code can inspect its own
instruction address and return different low bits at different alignments.
The existing local-relocation/associative-section guards do not exclude that
case. Preserve all non-alignment flags, selection, weak-default, relocation,
byte and EH guards; establish a sound position-observation boundary before
changing the check. No blanket alignment exception or admission is added.

A private /O1 /Ot /G7 /arch:SSE trial for BaseHeightMapConstructor preserves
only 15/30 rows and loses its main constructor and funclets, so a global flag
flip is not a verified repair. No candidate was copied into Code.

The source header is not edited merely to change the verifier's result.
This specific getter refusal is banked as a false-reject investigation;
the whole table, other source-slot diagnostics and the game remain unverified.
The next repair requires a justified identity proof or actual provider recovery,
then the next published real link must clear the queue.
