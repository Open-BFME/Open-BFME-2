# FESL key-vector and cleanup header adoption

Base `88d748a7da4`, 2026-11-12. Picker serves Rva007F76F0Vector in
Common/BfmeSlot1173.cpp and GameNetwork/BfmeThingZI.cpp. The whole-file pass
also finds the latter's remaining Gen_007e86c0 header entry.

## Opaque cleanup receiver

BfmeThingZI.cpp uses Gen_007e86c0 only in two casts of its existing message
object before calling `m()`. No object, base, field, sizeof or array depends
on the private declaration's 16 padding bytes. Replace that declaration with
the existing canonical header, preserving both calls and their signatures.
This does not establish a complete class size or recover an original name.

Normal `./build.sh` passes all 22 source rows and string/float/import checks.
All 28 COMDAT bodies retain their fingerprints, with no addition or removal.
The frozen-file check is clear. `header_adopt_lane.py accept --class
Gen_007e86c0` passes and retires this source's one queue entry through its
own verdict. The shared cleanup header is unchanged.

## Key-vector prerequisite

The automatic adoption cannot drop operator[]: its complete 22-byte body at
target `0x006633C0` is already rowed in BfmeThingZI.cpp. The shared vector
header has only the established eight-byte `{void *begin, int count}` layout.
Keep the existing accessor declaration and definition during adoption rather
than replacing its caller with a different expression and losing the row.
The target key-index helper is `0x00663DE0`, 105 bytes; `0x007F76F0` is the
BFME I source lead, not the BFME II target address.

Private preparation adds the existing accessor declaration to the shared
header and retains an inline definition in the owning source, viewing the
void pointer as the existing eight-byte slot type. All 22 rows and all 28
COMDAT fingerprints remain unchanged in that trial.

Completed adoption retains the accessor's original inline linkage and row
in BfmeThingZI.cpp, declares it in the shared header, and forward-declares
its existing return type. The layout contract and its eight-byte void-pointer/
count representation are unchanged. The method views the existing pointer as
the existing slot type; no private copy of the registered vector remains.
The two calls in the key-index helper retain their original expression.

Normal `./build.sh` passes all 29 rows across all five direct consumers:
BfmeSlot1173, BfmeThingZI, FeslHost_get_rva00801900,
FeslHost_get_rva00802470 and Rva00802240FeslLookup. BfmeThingZI's final object
still has all 28 original COMDAT fingerprints, with no addition or removal.
Both frozen-file checks pass. The owning acceptance tool passes both queued
vector units and retires exactly two rows; BfmeSlot1173 already used the
header, so its queue entry was stale. Together with the cleanup receiver,
this drains all three header entries in these two source files.

Strict preparation also verifies all five consumers. Their own previews
preserve LINKS for 523, 1,664, 59, 59 and 44 authored bytes (2,349 total)
against index `aa7acf764d` of 2026-11-12 19:19. Its four-unrelated-path-change
warning remains; these are scoped previews, not a new census or image result.
There are no new pins, aliases, ledger rows, source moves or layout decisions.

## Publication follow-up

The preceding PolygonTrigger repairs landed as `4afe4ca881d` and
`88d748a7da4`; 259 rows and 11 EH graphs passed their push. Its broader audit
remained INCONCLUSIVE against index `aa7acf764d`, with
Common/0CreateAHeroManager21FE49.cpp lacking a current consumer receipt.
Carry that cohort into the next normal census. The separate PolygonTrigger
callback refusal and its unapplied patch remain banked, not resolved here.
