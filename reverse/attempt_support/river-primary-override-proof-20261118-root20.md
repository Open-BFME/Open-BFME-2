# River primary interface: inherited placeholder-name normalization

Inspected2026-11-18 at9dcb0c7478c. Target table8088FC is13slots; the current
Rva0030C1FCOwner constructor view emits four primary slots. Native base table8691EC
is7slots: `[5381B9,47A699,53805D,53806C,53807B,53808A,pure]`.
The river table is `[30C6A2,50B5C6,30C1FC,30C214,30C22C,30C244,30BCBA,
30C25C,30C280,30C28F,30C29E,30C2B6,30C271]`.

The first four notifier implementations override the base's four broadcasts.
Their existing placeholder identifiers differ. To express the C++ overrides,
the derived implementation must use the existing inherited identifier (or the
whole family needs a separately justified naming operation). Inventing a readable
word merely to evade the placeholder check is not a valid repair.

Owning rename of30C1FC to the inherited `rva0053805D` refuses:
`new name rva0053805D is itself a placeholder or weak name`.
A source-restoring native counterexample renames only that derived identifier
and qualifies its base call. After mapping the one intended mangled symbol,
all34runtime sections—including contents, relocation targets, COMDAT policies,
weak bindings and other definitions—are identical. Qualifying the base call
avoids accidental recursion. No naming or virtual transaction was admitted.

A general mechanical-override mode must prove the base/derived native slots,
class relationship, signature and all affected caller bindings, rather than
bypass naming approval or weaken the generic new-placeholder guard. Later
virtual promotion must prepare all existing class views together and keep each
direct base call qualified.

Other mandatory interface facts: base slot1 returns false; the river must
override it with true. The current IsCRC-linked placeholder is not a valid
universal base implementation. Base slot6 is pure and the river's30BCBA row is a
void(int) forwarder under another placeholder class. The no-argument base helper
538099 is not a virtual slot6 provider. The source's seven polygon-interface
methods/thunks on the shared virtual base are separate from these13primary slots.
Root/reference-count/listener/virtual-base layout and lifetime bindings must be
checked across constructors, destructors and notifiers; this one-name proof
establishes no complete class or table repair.

Unchanged controls pass46/46rows across three sources and both lifetime EH
graphs are EXACT. Source, headers, pins, ABI, rows and queue remain unchanged.
[Native tables, exact refusal, symbol-normalization proof and artifact hashes](river-primary-override-proof-20261118-root20.json).
