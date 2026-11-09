# FESL constructor deleting-destructor provider, 2026-11-09

The served table is `??_7Rva00802380Owner@@6B@`, RVA 0x008E3D14.
Rva00802330FeslCtor.cpp emitted its first deleting-destructor copy as a
call to the external destructor. Retail's 56-byte wrapper at 0x0066E750
instead contains the complete cleanup and final base-vptr teardown, as
already verified in Y2FeslBrowserDestructors.cpp. LINK-619 records this
provider mismatch; it is not missing byte coverage.

The constructor view now contains the same cleanup: zero fields +4/+24/+28,
clear the existing twelve-byte member view at +18, then explicitly tear down
the existing base view. The final qualified destructor call is a partial
ABI view of the retail base subobject, not recovered C++ inheritance. The
flat constructor view and its +8 initialization order remain unchanged.
No original class names, field ownership, complete lifetime model or retail
class size are claimed. The separate destructor source is byte-for-byte
unchanged. No function row, source path, pin, alias, pragma or owner moves.

Native and object evidence:

- Normal build verifies all 21 rows across the two files (657 bytes), with
  no string, float, import or EH obligations in this scope.
- The constructor's 37 bytes and its retained V2ZeroInt helper, relocations,
  code flags and selection policies are unchanged.
- The changed wrapper is identical to the existing verified provider in
  body, relocations, flags and SELECT_ANY policy; independent retail-byte
  verification passes at 0x0066E750, 56 bytes.
- The only additional emitted definitions are the existing base's 4-byte
  compiler table and 31-byte deleting wrapper. Both equal the old provider;
  the wrapper independently matches retail at 0x0066E5A0. No new standalone
  base constructor or destructor is emitted. All original destructor-file
  code/data/reference/definition facts are unchanged.
- Normal frozen-file and new-variant checks pass. Paired link previews
  preserve LINKS at 657 bytes against index c885072a48; no census update.
- In a bounded eight-source cached replay, the target-not-winning-provider
  refusal goes from one to zero. Temporary bridges go from one/five slots
  to two/ten slots. Both native tables are still twenty bytes; the compiler
  tables are only four. This clears provider eligibility, not table debt.
  Four supporting objects lack strict receipts, listed in the replay JSON.

Rejected trials are kept under build/fesl-owner-reconcile-20261109 rather
than Code/. A full Base12/placement view introduces a non-retail null test
and a 41-byte constructor; typed temporary initialization gives 63 bytes.
The donor-suggested Base8/derived +8 view matches the constructor and wrapper
but emits two SELECT_ANY base methods against existing strong definitions,
which the measured link rule correctly refuses. Inlining the unused old
base constructor loses its standalone nine-byte row. Those methods have
only a proposed TU; no unsupported row rehome or emission anchor is used.
BFME1's different field ownership is donor evidence only, never BFME2 source
or layout proof. Native review accepted the final limited teardown view.

Remaining work: recover the full class and both five-slot tables, resolve
the proposed-TU/emission prerequisite for a complete inheritance view,
and remeasure the newest real image. No bridge retirement, headline link
gain, game-start or runtime clearance is claimed by this package.

Published as e4246d8907 on the first attempt in 29.9 seconds (3.6 seconds
rebase, 26.3 hook/push). Normal publication gates and post-publication native
and object proofs pass; all three claims are released. The broader batch
audit remains INCONCLUSIVE: index c885072a48 versus outgoing base
aaf7727eee2bdbfbd2b686e07d1f6f34bab13cd1, with unchanged consumer
Rva00801B70FeslAlloc.cpp lacking a current receipt. Carry that consumer into
the next census/image pass; the bounded repair does not prove global closure.
