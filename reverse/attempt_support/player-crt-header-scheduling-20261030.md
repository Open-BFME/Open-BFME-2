# Player CRT declarations: fresh scheduling control

Control: 7906295d3f8e99862e1b7b005566c1fd7a6b4984, reference pin
85ff94681faf00d093304e48f8e3069b88252399.
The current audit confirms that the local free and memset declarations in
PlayerInitFromDict.cpp have the same contracts as the shipped CRT headers.
That static classification does not establish a byte-preserving substitution.

Replacing both declarations with stdlib.h/string.h changes initFromDict's
2762-byte body to 2764 bytes; its other 30 rows stay exact. Repeating once
through the normal build with BFME_OBJSTORE=off and an invalidated exact
source object/sidecar pair reproduces the difference. The prior cache problem
logged for this TU is therefore not the explanation for this trial.
An isolated stdlib.h/free replacement also fails, as does removing only the
local memset declaration (which is used by two mask clears, and is also
declared through existing includes). No flags or headers are altered to force
the desired scheduling. The adjacent patch preserves the combined trial.

The unchanged original source is then compiled freshly, again with object-store
reuse disabled: all 31 functions, one data row, six strings plus one empty
string pass. The original parent EH graphs were all four EXACT, and ordinary
preview retains LINKS for 4,707 authored bytes against ccafe54d1d.
No source or queue change from these replacement trials is retained.
Do not infer an exception-contract mismatch from this result: the audit proves
contract equality here, whereas the compiler still changes body scheduling.
