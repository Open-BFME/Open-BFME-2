# Record vector push-back identity correction

LINK-092's native 6BF950/59-byte body copies a nonpolymorphic 36-byte record.
Its calls at +15 and +33 reach the existing record copy 63BE4/79 and vector
overflow 6BF5E0/268. The current Money-labelled whole-vector instantiation
instead emits incompatible Money constructors, overflow and three unresolved
Money virtuals. Its preview is nonlinking; the two real providers already link.
No original application type or source path is inferred from matching bytes.

The private replacement uses the existing BfmeVecBE/BfmeElemBE ABI views and
existing BfmeStringRecord00063BE4 copy owner. It performs ordinary placement
copy when capacity remains, otherwise calls the existing overflow with a
default-initialized empty trait object. Both complete 59-byte bodies are raw
identical; new symbolic relocations bind directly to the two real providers.
Private verification resolves every byte and call target to retail. There is
no new pin, alias, manual storage reuse or generated body.

The record copy declaration exposes its no-C++-throw contract to the caller.
This is supported by the complete owned call chain, independently of EH shape:
the 79-byte copy writes seven words, calls StringBase<char>'s 66-byte copy,
then writes two bytes. StringBase shares the buffer and increments its count
under Enter/LeaveCriticalSection; it allocates no string and invokes no callback.
Its getter 35C90 constructs a static lock, with argument one to 411C1, and
registers cleanup with atexit. The current constructor owner is
MilesMutexGuard.cpp; that argument skips its optional virtual-lock call.
Critical-section imports are declared C and nonthrowing. AtexitThunk.cpp
registers the callback through CRT onexit functions and returns success/failure,
without invoking it. This establishes the C++ exception contract under /EHsc;
it does not claim that Windows structured exceptions cannot occur.

The empty trait must be default-initialized. Value-initializing the POD trait
adds a byte store and a different frame (67 bytes). A default-initialized local
keeps the native 59-byte body; the compiler chooses its storage. No source
assumption about the original local variable or application record is made.

## Required publication sequence

The existing Money row is a real claim, so add_match's scaffold replacement
path is inapplicable. First retract exactly that row, record its tombstone and
remove its now-rowless source in a separate normal commit. Then readmit the
verified neutral body at the same source path. The current TU map does not
approve a source move; the misleading legacy filename is retained pending TU
approval. Audit the old row and removed COMDAT providers' consumers, retire
unused false pins only after their real bindings verify, and retire registered
identity/header debt solely through each register's owning tool.

The source retraction is not completion or byte progress. Final publication
must preserve the body and its verified providers. Current scoped strict
preparation passes 97/97 rows across the old source and two real providers.

## Readmission and retained boundaries

The normal retraction commit passed the required dependent verification:
182 potentially affected units, 4,633 function rows, 58 data rows and 633
EXACT EH graphs. This includes conservative name-based candidates; it does
not assert that all 182 actually called the withdrawn Money-labelled row.

`add_match.py` readmitted the complete 59-byte neutral method at the same
source path and normal verification passed. The three-unit current preview
now predicts LINKS for the source (0 -> 59), retaining the copy provider's
3,129 and overflow provider's 268 bytes: 3,397 -> 3,456 in this bounded cohort.
The owning identity retirement command initially passed with zero remaining
findings, but the outgoing-range guard refused its proposed key removal:
it treats the withdrawn Money symbol name as lost coverage despite the
separate retraction and exact same-RVA replacement. The old register key is
therefore retained in the source publication, and the refusal evidence is
banked. These are scoped predictions, not a new census result,
additional byte coverage or a completed identity-debt retirement.

The Snapshot acceptance command refuses because the replacement does not
include the Snapshot header. It now needs no Snapshot type; this repair does
not add an unused include merely to retire the queue row. The queue entry is
retained for the register's supported identity-change retirement path. No
false claim of header adoption is made. The old Money-copy/overflow pins were
reserved for the separate consumer audit below.

The second served source, FXParticleSystem.cpp, is unchanged and still predicts
LINKS for 5,650 bytes. It already includes global canonical Snapshot, but its
namespaced one-destructor compatibility view still models real unresolved
base-view debt. Namespace ambiguity in the acceptance check is not evidence
that this view is canonical, and no discovery-error retirement is claimed.

Publication retains the earlier broader AIBaseBuilder receipt/index boundary
until the normal outgoing audit establishes its current scope. No new source
path move, shared-header change, pin or escape hatch is introduced here.

## Superseded pin retirement

A separate audit scanned 18,650 object paths belonging to the current matched
Code ledger, with no missing source/object or parse error and an unchanged
functions-ledger hash. Neither old pin name had an observed undefined consumer.
The overflow name appeared nowhere. The constructor name appears only as a
defined 27-byte COMDAT in SkirmishGameOptionsMenu.cpp, with a current source
hash and full compile receipt. That definition copies the real 12-byte Money
view and references its vtable; it is not the 79-byte record copy at 63BE4.
No same-object code relocation calls it. Its definition and source are kept.

Only the two false address bindings are removed. The owning hatch update
reduces pin counts at 63BE4 and 6BF5E0 by one each (two total). This audit does
not assert full receipt currency for every unhit object: the normal dependency
gate widens stale-object cases and lists 29 units for verification.

The corrected source and its two real providers retain their 3,456-byte
prediction. The legitimate Money-defining menu unit retains the census's
zero linking bytes and existing unresolved prerequisites; its preview is
not clean, and no menu-unit repair is claimed. The outgoing consumer audit
still supplies the broader publication verdict. The retained identity key and
header queue row are unchanged by this pin retirement.

## Debt retirement after the source publication

After 0a5c6b4a4d landed the verified replacement, the ordinary owning identity
retirement command passes again. This time the register-only change compares
against an upstream state that already holds the new symbol, so it removes
no function identity from its outgoing range. The source and 59-byte row are
unchanged. This resolves the earlier range-guard sequencing prerequisite
without a checker change or bypass. The earlier false-reject label is voided:
the safe path is source publication followed by register retirement.

Only this follow-up retires the old Money-copy key. The Snapshot header queue
entry and the menu unit's unrelated link prerequisites remain open.
