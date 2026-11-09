# Wind transfer overrides and the two compiler table slots

Native 003A5896 forwards a transfer through the WindModuleInfo subobject at
+1C; 003A589E first adjusts the receiver by -1C. Both are eight-byte bodies.
The exported callee is FXParticleSystem::WindModuleInfo::DoXfer(Xfer&), at
003A547E. Constructor 003A5856 independently places the primary table at
0081B5A8 through operand 003A5870, and the secondary table at 0081B598
through operand 003A5886. Each table spans sixteen bytes and requires the
corresponding override in its last slot.

The original rows guessed rva003A5896(int) on Rva003A5896Forwarder. Genuine
independent blind proposals agreed on DoXfer for both current sources in
session review-52f2d5c352594720. The normal prepared ordinary-respell batch
applied both names, their reference parameter and existing namespaced owner
in one verified transaction. Its manifest and original candidates remain
unchanged in build/wind-prepared-respell-20261109/.

A follow-up link preview caught two real duplicates: the constructor view's
inline primary definition collided with the out-of-line owner, and the
thunk-emission constructor collided with OpaqueScalarDeletingDtorsB02.cpp's
existing destructor-emission constructor. The constructor view now declares
the primary override; its compiler-generated adjusting wrapper remains
native exact. The thunk emitter uses a distinct WindTransferEmitTag type.
All unrelated macro expansions and helper bodies retain bytes, relocation
positions, flags and selection policies. No helper count increases.

Normal compilation verifies all 117 existing code rows and seventeen data
rows. Both owned eight-byte methods and the constructor-generated adjustor
match native bytes. All retained object facts agree with the independently
compiled private candidates. Frozen checks pass; no row has EH obligations.
The link preview reports LINKS for all three sources, conserving 1,273 bytes
against index 717b70f4ab. The final object proof records strict currency and
the bounded provider selections separately.

Both compiler tables now contain all four native relocated slot values.
The Common forwarder remains a partial ABI view with its WindModuleInfo
member at +1C. The thunk source retains its emission-only constructor and
two existing base helpers. Neither proves retail's complete class layout
or original class identifier. The addresses lack approved TU assignments;
their row paths are unchanged. No donor, pin, alias or identity exception
is used. The two one-byte explicit owners are a separate cleanup.

The three-object provider proof covers only the renamed methods and their
constructor copy. It does not establish unchanged outside providers, a
complete image or game behaviour. Carry broader audit gaps into the next
maintained census and real image run. Local reproducible evidence: trial.py,
selection.py, link-trial.py, verify.py and the corresponding logs/proofs in
build/wind-prepared-respell-20261109/.

Published as b7d3808f37 on push attempt two (46.9 seconds after a 52.0-second
lost race). Normal hooks and post-publication strict/object proof pass. The
authentic vote records precede the source repair in their own commit, so
their append-only fingerprints remain bound to the original reviewed text.
The broad audit is INCONCLUSIVE at index 717b70f4ab/base 9012dfde9b because
unchanged AIBuildable.cpp lacks a current receipt. The three owned sources'
own link verdicts remain clean; next-image confirmation is still required.
