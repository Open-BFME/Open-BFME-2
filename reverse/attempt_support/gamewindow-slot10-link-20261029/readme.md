# GameWindow slot 10: native constant-return fold

Control: e584f589295. Target facts: the constructor and destructor install
the 44-byte GameWindow table at RVA 0080BBCC. Its last slot selects RVA
0050B5C6, whose entire body is `b0 01 c3`, with no relocations. Slot 7
selects the genuine purecall. The original slot-10 method name and const
qualification remain unknown; vslot10 is an explicit placeholder.

Both emitting views previously declared slot 10 pure. They now declare
`virtual bool vslot10()`. Its clean C++ body is admitted through
`add_match.py --icf-owner` alongside the existing opaque constant owner in
VtableConstantPredicates.cpp, with fold-proof pointing to that same source.
The new GameWindow view lists all eleven observed slots. This is a real
virtual-member ICF twin: native installed-table evidence establishes its
GameWindow use independently of the identical body. The opaque owner and
its unrelated consumers retain their existing identities. No new pin,
alternatename, generated alias, shared header or source path is introduced.

Normal builds pass 11/11 provider rows and 62/62 constructor/destructor-unit
rows. The proof script independently reads game.dat and the compiled COFF
objects: both real symbols have exactly the three native bytes and no
relocations; both tables remain 44 bytes, preserve every relocation at slots
0 through 9, and replace only offset 40 with GameWindow::vslot10.

Ordinary preview before and after: 3/3 LINKS, 3,082 authored bytes retained,
against census index 85f6b7f40c (2026-10-29 15:08). The census predates this
source repair. Unique matched coverage gain is zero; the extra row describes
the existing folded range, not three new game bytes. No measured linking,
image-ownership or runtime gain is claimed. Full consumer closure and the
next scheduled census remain necessary. Slot 10's false purecall is repaired
in these two emitters; original method names and complete object layout are
still open.

Model GPT-6; t=5 minutes; lane=R; budget=30m. The later mandatory BFME-1
reference freshness verification is a separate maintenance step.

## Reference freshness boundary

The official Open-BFME/Open-BFME-1 master was fetched on 2026-10-29:
337e4b48e8f295f74bdd1155ad2b6dd848b63c32, compared with the maintained
f64f0f32d56adf72bee366d42cbb2a72cf192ae3. No header or inputs/reference
file differs, but the required complete byte verification did not finish.
It found 4,874 stale units out of 20,756; 2,389 were restored from the
object store, leaving 2,485 compiler jobs. After about nine minutes the
single-pool run was deliberately interrupted (real exit 130). The captured
log is evidence of an incomplete verification, not a successful full gate
or proof that the new reference is faulty. An initial unstaged-pin attempt
had correctly refused with exit 1; staging the intended pin resolved that
precondition without changing any check.

The reference checkout and index were restored to f64f0f32, its scope claim
released, and the freshness success stamp was not updated. The source repair
is reverified under that last verified pin. No reference pointer update is
published. A future reference-maintenance pass must finish the complete
comparison before advancing the pointer or recording freshness success.
