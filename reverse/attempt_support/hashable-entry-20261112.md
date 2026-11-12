# Hashable entry table and shared base

At inspected master eccb92ab037 the picker serves table0x007CEFD4 from
Rva000F1B8FCtor.cpp. Both its constructor and destructor TU emit two slots:
the correct deleting destructor0x000F1B73 followed by a false pure-call slot.
Retail instead holds the complete four-byte getter0x0030F45F (8b4108c3).

Target facts: constructor0x000F1B37 has60 bytes and initializes the key's
StringClass at+8 above the zeroed link at+4. Method0x000F1BC5 allocates12
bytes and calls that constructor at0x000F1BEC, then HashTableClass::Add at
0x000F1BF9. Add0x00613C60 calls virtual slot1 at0x00613C6C, hashes the returned
string and links the entry through+4. The canonical HashableClass header
independently proves the eight-byte base and table0x007CEF94. Thus Get_Key
is supported by target usage and the shared contract. The derived original
application identity and original TU remain unknown.

Both TUs adopt the existing HashableClass header, removing two private base
views and moving the destructor view's duplicated link field into its real
base. Both emit Get_Key returning the owned StringClass buffer. Ordinary
add_match --icf-owner admits the complete four-byte method against the
existing Rva00109C27 key getter; there are no relocations or masks, and no
new pin or class copy. New unique retail bytes are zero.

Exactly one superseded ICF row is retracted with ledger_io's byte-preserving
rewrite: ??_GRva000F1B8FBase@@UAEPAXI@Z at0x000EF9D6/29. Its tombstone records
the canonical replacement. The real ??_GHashableClass@@UAEPAXI@Z owner stays
in InlineDtorDeletingDtorsC01.cpp, and both adopting objects emit its complete
29-byte body with every relocation exact, unmasked and unresolved-free.
The native address remains covered. No removed private-base provider has an
indexed external consumer outside the two edited TUs, or a pin, data_rows,
converged global, debt or header-queue key. The raw data ledger's old base
alias is a derived historical snapshot, not a new owner to preserve in source.
A bounded native reviewer independently checked these facts.

Normal ./build.sh and strict preparation pass all five final rows:60-byte
constructor,4-byte getter,54-byte destructor,28-byte deleting destructor and
10-byte EH handler. Both frozen checks pass. Private trials also verified
every retained body, the getter and canonical29-byte deleting destructor.
Retained constructor code is unchanged; the destructor's dependency identity
changes from the private base to the canonical base while its fully resolved
retail bytes remain exact. The derived table's sole changed slot is Get_Key.

The explicit three-object local planner changes one generated two-slot table
to zero, with no refusals and one already-correct table. Both own link_check
verdicts read LINKS against the supported19:19 index refresh at aa7acf764d.
Own-row totals change89->64 and92->92: the29-byte redundant fold is removed
and the4-byte getter fold added. This accounting decrease is not lost unique
coverage; the canonical29-byte owner and copies remain proven.

No source path changes or active tooling references need repointing. No
canonical header is edited. The indexed hrawanim.obj destructor variant is
outside this repair and remains an existing broader issue; the adopted
canonical deleting-destructor copies match the other nine indexed copies.
The next published real link must confirm that table0x007CEFD4 is neither
bridged nor refused. The queue remains intact, and full consumer/census
confirmation and actual game execution are not claimed. The preceding
strstream push's audit lacked a current StlportStrstreamConstructors.cpp
receipt; its broader confirmation also stays pending.
