# Weather reset: exact native owner candidate, missing admission operation

2026-11-01, basee7e003d74b876a972cf77f0a23e5991020778f06; GPT-6;
lane R; budget30m; t=6min. Production Code and rows remain unchanged.

The native primary GlobalWeatherSystem table C0C734 slot9 holds3186A5. The
named constructor318588 installs that table at offset0; the complete owner
and both tables are proven in ../globalweather-owner-native-20261101/.
The existing declaration already calls this virtual operation reset(). Its
73-byte matched implementation is currently the sole member of the placeholder
Rva003186A5Owner in Common/Rva003186A5Reset.cpp.

The private candidate joins that member to the existing GlobalWeatherSystem
spelling and makes reset virtual. Reducing its existing leading padding from
10 to C accounts for the newly explicit vptr and keeps every accessed field
at its native offset (10,14,18,20,24,28,2C,58). Official permute.Scorer with the
unchanged actual source flags returns exact1.0/unresolved=false for all73 bytes.
Object inspection finds no emitted GlobalWeatherSystem vtable. This candidate
therefore does not introduce the incomplete table banked in the previous pass.
It recovers one callback; it is not complete class or original-TU recovery.

The existing native-owner admission operation is missing: rename.py class
--native-owner-rva3186A5 is refused as an unknown argument. Generic class naming
is intentionally not used to bypass agreement or an existing-name collision.
A dedicated mechanical identity operation is needed, preserving normal naming
approval for new spellings and all normal claims/body/consumer/rollback checks.
It must refuse ambiguous/folded members, secondary/base-only table evidence,
multiple old members, registered classes, protected names, frozen keys and
signature/name collisions. The target class must already exist and declare the
same operation; no new original spelling or canonical tier may be granted.

Normal unchanged control passes1/1 plus its empty-string reference. The exact
candidate is evidence under attempt_support, not an ordinary near-match stash
for an already matched address. No pin, hatch, header edit or source move.
Once the operation is independently tested and published, apply the owner join
and normal --virtual respell together through the default transaction, with
the padding preparation included. Then replace only the constructor view's
pure reset declaration with the correctly bound declaration, retaining the
other five unresolved native callback prerequisites and auditing all providers.
