# One static-field Vector3 reconciliation probe: blocked42/43

**Do not land this source.** Parent-authorized base
`b146a56624e02d3329378d808e624bf2f18bb233`; actual source input
`33b56b9184f0ddb762bca0bb63180b42e1518b4430b74e5bd1ffffea9344ec5d`.
Exactly one candidate form plus one unchanged baseline control was compiled.
Production source and all five real headers remained unchanged. No new identity,
header, flag, row, pin, shim, claim, Git, gate or shared-cache change. Zero credit.

## Why this single hypothesis was justified

Current canonical Vector3 declares public nonvolatile float X/Y/Z, size12 with
field offsets0/4/8. Its source const subscript is pure `return (&X)[index]` by
value. Original ZH source and the seed private view use the same pure expression
returning const float&. At the actual constant indices0/1/2 in Set(axis,s,c),
these source definitions name exactly X/Y/Z without other effects. Direct public
fields preserve the original lvalue expression category using the current shared
API, without a false reference-return declaration or new reference/value locals.
The source generator mechanically checked equal formula text after normalizing
only those component-access spellings. All casts, terms, arithmetic grouping and
statement order were preserved; no numeric/operand/register/name permutation.

The rest is the same mechanical canonical adoption: unchanged WWMathClass,
Vector3Data and Vector3InlineMath headers replace the private Vector3 class;
the existing free unary call is explicitly qualified. Existing canonical Matrix3D
is retained. This source-equivalence argument does not independently identify the
original tiny retail leaf004047D9; the prior identity correction remains in force.

## Actual native result

Fresh control43/43. Candidate42/43, sole missing row005B0A95:
**976B instead of971B**,19 relocation sites, no masking or unresolved symbols.
The names/kinds sequence of those19 relocations is unchanged, but their offsets
are not all equal. Do not describe them as19 identical complete relocations.
The source is worse than the preserved earlier971B/24-byte best; it replaces no bank.

Three unrowed matrix bodies, read from actual complete COFF definitions:

| Body | Control | Candidate | Raw comparison |
|---|---:|---:|---|
| Set(axis,s,c) |318B|318B|Different bytes; same named relocations|
| Set(axis,angle)|356B|356B|Identical bytes and named relocations|
| Axis-angle constructor|369B|373B|Different bytes; same named relocations|

Complete current-base footprint is60 strong code definitions before,59 after
(not the older base's58). Removed is only the seed reference-returning const-index
COMDAT; no value-index COMDAT was emitted because this source no longer uses it.
Its only incoming relocation in the control object is a debug$F entry; this is
not a whole-image outside-consumer/unreachability proof. No new code definition.
Besides the removed helper, actual changed code is the two matrix bodies above
and Sun. Source definition inventory remains equal. Undefined sets, linker
directives and empty VTable sets are unchanged.

All31 noncode/nondebug sections have equal semantic actual-target graphs.
The16B SafeSEH .sxdata raw symbol-index array changes because the removed COMDAT
renumbers COFF symbols. The actual same four handler names/bound identities were
explicitly decoded and compared; original raw arrays remain in FOOTPRINT.json.
They were not ignored or falsely described as raw-identical. Other data bytes,
flags, extents, edges and actual target offsets remain unchanged.

## Compiler, evidence and limits

Native TS.Verifier retained the real TU's managed flags:
`/O1 /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc`.
Only source/object paths and relative includes were relocated to the private build
directory. BFME_OBJSTORE=off; serial control/candidate compilers. Existing funclets
were read through the normal located_funclet/read_funclet path, not guessed labels.

NATIVE-PROOF.json contains every43-row result and input/header hashes;
FOOTPRINT.json contains all definition/data/undefined and SafeSEH observations;
SUN-NATIVE-DIFF.txt contains the full instruction residual. Source banks and
SOURCE-TRIAL-DIFF.txt are private failed-experiment evidence, not a landing patch.
No further compiler/source form was tried. No acceptance, merge, full link,
runtime, CRC, performance, crash or memory improvement is claimed. No production
change or landing patch remains. Root owns the ordinary no-change record.
