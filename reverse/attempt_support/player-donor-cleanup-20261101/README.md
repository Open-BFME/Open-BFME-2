# Player donor-body cleanup

The served Player.cpp owns 12 matched functions (112 bytes, all relocation-free)
and the native TheTeamFactory global at A028BC. The latter has 73 known address
references and stays in place. Player is canonical; no replacement private
class, header or ABI is introduced. Existing header-accessor and ScienceType
copy emissions must remain available throughout this pass.

## Science-points donor body

The unrowed addSciencePurchasePoints body introduces two unresolved invented
helper names. It has no runtime/data incoming relocation in the original object
and no outside incoming edge in published index86db074988. The old ILT comment
is a donor assertion, not BFME2 target evidence. Removing this unverified body
and that comment preserves all 12 native functions and the owned global.

The original-source control has 410 external code definitions, the corrected
object 409. The only removed definition is addSciencePurchasePoints; every
retained complete body and symbolic relocation is identical, and nothing is
added. Normal/frozen verification passes. The unit still does not link: its
other donor methods, two wrong-selected copies and additional STL imports
remain. This is cleanup, with no authored-byte or census gain claimed.
