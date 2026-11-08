# Remove Camera's redundant vector-constructor anchor

camera.cpp no longer declares the fake BfmeVciAnchorElem class or the unused
bfmeVciAnchor function that instantiated two of them. The historical comment
claimed this anchor was required to choose the native vector constructor
iterator. Under the current compiler inputs it is redundant: all 60 code rows
and the one data row remain byte-exact, and both parent EH graphs are EXACT.

Private before/after objects contain the same 212 external COMDAT names,
extents and normalized body/relocation fingerprints. The private LinkGuard
has no findings, and the ordinary current-object preview stays LINKS with
10,151 authored bytes. No flags, pragmas, ledger paths, rows, pins, headers or
verifier rules change. This removes one fake class declaration and one
unnecessary anchor without claiming a new native implementation.

Broader anchor/pragma removal was investigated in the same file and rejected.
Removing all anchors still preserves the 60 owned rows, but changes selected
FrustumClass constructor/assignment providers and breaks indexed consumers.
Removing all optimization pragmas loses CameraClass::Apply and several
unrowed provider identities. Those mechanisms remain; their private reports
are retained so the next cleanup does not repeat the unsafe broader trial.

The served Camera primary-table refusal still names the shared RenderObjClass
bounding getters at slots 65/66. The real-link queue selects the path-ordered
BaseHeightMapConstructor provider rather than the hlod owner. This is the
same alignment/order boundary recorded in the earlier
renderobj-bounding-order-20261108 packet (LINK-619), not repaired by removing
the anchor. No blanket alignment exception is made. A future real link must
confirm native binding and clear that queue; runtime remains unverified.

Published as eb6c24b55e after preserving both sides of a LINK-619 append
conflict and rechecking Camera on the rebased tree. Required gates pass all
60 code rows, the data row, scoped DIR32 for seven symbols and both EH graphs.
The broader audit remains INCONCLUSIVE: index f4727bbd09 versus base
8be98f3efe60da401d09c05038aeac98afe27011, one missing current source receipt
(camera.cpp). The three Matrix definition findings in the code-identity
shadow report remain outside this cleanup; provider fingerprints are unchanged.
