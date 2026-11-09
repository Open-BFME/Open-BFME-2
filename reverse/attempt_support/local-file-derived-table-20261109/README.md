# LocalFile-derived native table, 2026-11-09

The served Rva00605C58Ctor.cpp defined the 72-byte strong array
g_00C7AAE0 at native RVA 0x0087AAE0. Its constructor is 18 bytes.
The independent 11-byte destructor at 0x00605C6A binds that address to
the existing compiler name `??_7Rva00605C6A@@6B@` through its zero-addend
DIR32 operand at 0x00605C6C. Its tail call reaches LocalFile's rowed
destructor at 0x00605CA7; the old opaque base spelling already aliased it.

The constructor view now uses the existing LocalFile interface and declares
its destructor out of line. Its compiler emits the native vptr store,
the complete 18-slot table and the existing 28-byte deleting wrapper.
The strong array, eighteen void function declarations and manual vptr store
are removed. The destructor view in OpaqueSingleInheritanceDtors.cpp now
uses LocalFile directly instead of a destructor-only private base. That
emitter's compiler table grows from four to 72 bytes. Both table copies
resolve all eighteen slots to the native words, including the derived
deleting destructor 0x00605C75, rather than LocalFile's own 0x00605F38.

Every retained row's bytes, relocation positions, flags and COMDAT policies
are preserved after exactly the constructor's table referent and derived
destructor's base-callee substitutions. The constructor's additional
28-byte deleting wrapper equals the existing destructor-TU copy. An unused
five-byte Rva00605C91 destructor helper, previously a File tail jump, is no
longer emitted. The before-index finds that helper only in the constructor
object; no current source/ledger/pin user was found. Other code and data
facts are unchanged. LocalFile.cpp loses only the unused base alias; its
whole object code/data facts remain equal. The obsolete base pin is removed.

The existing explicit 72-byte data owner transfers from the strong array
to the compiler table in the destructor TU, preserving the native range.
No function row, pin, alias, compiler flag, shared header or source path
is added. These remain partial class views: the original derived name,
the Rva00605C91 constructor's identity and complete common hierarchy are
not recovered by this repair. No donor name or layout is inferred here.

Normal verification passes all 77 code rows and the one data row across
the constructor, OpaqueSingleInheritanceDtors, LocalFile and File sources:
three literals plus two empty-string references, 22 imports, and seven
EXACT EH graphs. The four-source link_check verdict is LINKS throughout,
preserving 3,235 bytes against index 717b70f4ab. Four strict reusable
receipts, new-variant checks and normal publication hooks are required
before publication; their logs are in build/local-file-derived-table-20261109.

The bounded four-provider bridge replay changes from one generated
18-slot compiler-table bridge plus one strong-definition refusal to zero
bridges/refusals and one already-correct table. This is a source-object
selection proof, not an actual image or runtime measurement. The next
census and real image still decide global selection and bridge counts.

An attempted full raw data-index refresh is NOT published. The normal
commit gate correctly caught its resurrection of the retired
`?g_validityEnd@@3PAEA` from an unrelated stale object. Per that gate's
guidance, reverse/data_ledger.csv is restored to HEAD. Explicit data_rows
ownership supplies the repaired compiler table and its verified 72-byte
range; all 2,357 explicit owners remain with only this owner/name transfer.
index-audit.json retains the rejected refresh's thirteen removed cache
observations, one added observation, 74 changed records and seven changed
raw extents. Those foreign metadata changes, including W3DGlowOutline,
are unverified and are not in this source commit. The retired-global
observation is recorded for cache/tooling follow-up without modifying
another worker's source or treating a correct rejection as a false reject.

The mandated hatch_counters --update retires the alias and pin and also
removes eleven previously stale entries. A bounded rescan of each affected
HEAD source using the tool's scan function proves the latter already had
count zero before this repair; only the alias and pin had count one.
hatch-audit.json records every key. A read-only independent review found
no source blocker and confirmed those counts and the partial-view limit.
