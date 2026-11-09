# FESL base tables: complete native pure slots, 2026-11-09

Recover two native base tables across their constructor and destructor
emitters, following provider repairs e4246d8907 and 5e7ae92736:

| Base table | Native RVA | Complete extent | Slots |
|---|---|---|---|
| Rva00802380Base | 0x008E3CC8 | 20 bytes | G at 0x0066E5A0, four pure calls |
| Rva00802680Base | 0x008E3CDC | 36 bytes | G at 0x0066E690, eight pure calls |

Every remaining slot independently points to retail's _purecall at
0x0003B810. Neutral pure-virtual declarations encode those counts. Their
void signatures are placeholders, not recovered interfaces or names.
The compiler emits the complete tables naturally, with SELECT_ANY policy
and unchanged deleting wrappers. No pin, alias, owner, row, source path,
optimization pragma, emitted instruction or new helper is added.

Constructor-only trials were insufficient: the link preview retained
short copies from Y2FeslBrowserDestructors.cpp, losing 88 linking bytes.
The final change reconciles all four table copies in all three sources.
The two Y2 owner declarations use the same documented flat ABI view as
their constructors and an explicit qualified base teardown. This avoids
inventing inherited pure slots on the concrete owner tables. It does not
recover complete C++ inheritance or lifetime. Native field offsets and
all twenty Y2 bodies remain unchanged.

Normal/strict verification covers 23 rows (770 bytes) across all three
emitters and the actual 62-byte _purecall provider, including its one
literal. Every function/helper byte, relocation position, code flag and
selection policy is unchanged. All retained definitions and non-base data
are unchanged. Only the two base-table data bodies grow from four bytes
to their native 20/36 bytes; all copies agree. The only newly referenced
name is the existing __purecall. No new function identities or definitions.

Frozen-file, new-variant, EH and link checks pass. All four units preserve
LINKS 770 against index 717b70f4ab. In a four-object replay with all four
strict receipts current, two bridges/fourteen slots become zero, with two
already-correct native tables instead. The destructor's standalone base
constructors/destructors and every deleting wrapper still match retail.

This is bounded source-table recovery; the next real image must confirm
selection and aggregate bridge retirement. Both derived owner tables
remain short. Their other slots need actual member/ICF identity work:
shared getters, a four-table folded handle return, proposed TU assignments
and a mangled type-back-reference unsupported by the existing identity
route. Do not add second real names from table membership alone. The
current patch claims no full classes, census gain, image or runtime result.

Published as cb44058863 on attempt one in 30.0 seconds (3.0 rebase, 26.9
hook/push). Normal gates and post-publication object/native proofs pass;
all six scope/table claims are released. The broader outgoing audit is
INCONCLUSIVE: index 717b70f4ab versus base
d87c66609e8194dea2f1f6a10f704eaa7d2b4957, with unchanged allocator
Rva00801B70FeslAlloc.cpp lacking a current receipt. That consumer and actual
image selection remain next-census/image prerequisites. The two owner-table
identity barriers are recorded through re_log.py so the stale wrong-provider
queue does not repeat this already-landed provider work as an untried repair.
