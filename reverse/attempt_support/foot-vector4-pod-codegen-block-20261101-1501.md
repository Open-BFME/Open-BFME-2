# Quadruped foot Vector4 adoption: blocked, not a completed task

The claimed source W3DQuadrupedDrawGetFootLocations.cpp remains unchanged and
its existing 988-byte native row remains matched. This investigation is not one
of the six completed adoptions. Existing higher-quality reconstruction banks
and historical donor uncertainty are preserved.

Replacing the private POD Vector4 with the registered data+constructor view
changes the native parent's SSE schedule and grows the isolated output from
988 to 995 bytes. Nine other external code bodies and relocations remain exact.
Both an explicit force-inline empty Matrix3D constructor and the import-inline
constructor profile retain the same parent mismatch; neither is installed.
The first raw byte difference is +0x14 (a shifted branch destination); the
substantive changes are reordered SSE loads/multiplies in the inlined matrix
multiply, not an unresolved native binding. The import-inline profile removes
the extra standalone constructors but does not restore the parent.

The attached patch reproduces that last isolated profile against the current
matched source. Inputs: source /O1 /G7 /arch:SSE /DNDEBUG /MD and existing
STLport/bfmealloc/ascii include profiles; registered Vector4Data.h unchanged.
No worldSpace predicate, volatile operand, expression grouping, resize binding,
pin, alias, baseline or shared header was changed. A future pass needs evidence
for a source-level lifetime/alias shape preserving the POD-era SSE schedule.
Do not weaken the native gate or replace the better existing bank.

Full compiler commands, object comparisons and variants are retained under
ignored build/six-each-half-resources-20261101-1501/b2-05-* and diagnostics.
