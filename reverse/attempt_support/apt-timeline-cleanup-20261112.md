# Timeline buffer lifetime and cleanup

The approved timeline merge preserves native parent 0x005BEA22 and its EH
handler. Its remaining generated cleanup at 0x007A0252 is not inferred from
adjacency: eh_verify's verified_funclet_locations binds the parent's exact
FuncInfo graph to the emitted local $L8072. The action adjusts the recovered
receiver by four and jumps to 0x0007FAB3.

The existing Rva005BEA22Buffer destructor is a neutral view of that owned
first pointer, not a recovered original class name or complete container
layout. Its entire 14-byte body is 8b0185c0740750e8710dfbff59c3. The only
relocation within the body is REL32 at offset eight to the existing C++
game-free provider at 0x00030830. Both complete bytes and every relocation
equal the existing integer-vector destructor owner at 0x0007FAB3.

Ordinary add_match --icf-owner admits that existing emitted destructor;
there is no pin, gen-alias mask or object-symbol alias. The consolidation
rules explicitly leave emitted ICF aliases in their consuming TU rather
than imposing the first owner's TU assignment. A bounded native reviewer
independently checked this admission and the parent/lifetime evidence.

Normal ./build.sh passes 79/79 rows, four strings, one float and one import;
strict reusable preparation passes. Own link_check reports LINKS, 4,193
bytes. The increase over the previous 4,179 own-row total is the shared
14-byte fold, not unique coverage or a new linked image. All previously
emitted code remains unchanged. The index is the supported 19:19 refresh
of the older scheduled census; it is not a new census or a game-run result.

The earlier private funclet trial did not pass: it matched 78 of 79 requested
addresses because the buffer callee was unresolved. No trial row was landed.
After the ordinary callee admission, read-only compile_function checks
prove the parent, buffer and cleanup unmasked, with no unresolved symbol
and complete bytes equal to retail. The cleanup's 11 bytes are
8b4df083c104e956f88dff; its sole in-body relocation is REL32 at offset seven
to the now-verified buffer destructor. Relocations after byte eleven belong
to the following EH handler, not this cleanup.

Ordinary add_match --replace-rva replaces the generated cleanup row with
the parent's emitted local in the already-approved timeline TU. Normal
./build.sh passes all 80 destination rows and the same literal/import checks.
Code/gen_small/uw_gen_010.cpp remains untouched, with 202 other rows still
owned there. This removes one generated owner; 946 generated unwind rows
remain in the current ledger. It removes no source file and claims no new
unique retail bytes.

Final strict preparation passes; own link_check still reads LINKS with
4,193 bytes. Normal verification also passes all 202 surviving rows in the
unchanged generated source. Read-only final parent/callee/cleanup proofs
remain unmasked and exact after the source comment update.

The outgoing path audit covers the callee admission and cleanup repoint
together. No physical source is moved or deleted. The generator and exit
link's family patterns still apply to the surviving generated source, and
its other provenance comments and historical references remain accurate.
The new source is tracked; the current TU map already approves this cleanup
for the exact-parent timeline TU. No active include, hook, workflow or build
consumer needs changing. The generated body is left orphaned as required.

The three existing destination header debts and the wider LINK-150 census
scope remain open. The previous merge's outgoing audit was INCONCLUSIVE
on two consumer receipts (first FamilyDeletingDtors12.cpp); this package
does not claim that gap is closed.
