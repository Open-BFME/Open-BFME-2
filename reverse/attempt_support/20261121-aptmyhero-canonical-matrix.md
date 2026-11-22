# Matrix3D-only AptMyHero whole-family prerequisite

Private candidate is native 59/59 at parent-confirmed base `55dd91d046f25ce01a961f2582867b2b620dcdcf`.
No production file, shared object, Git/index, claim, ledger or gate was changed by this worker.
Root normal admission/shared-header checks remain mandatory. This is source-contract cleanup:
zero new bodies, exact bytes or completed served items are claimed by the private proof.

## Exact proposed scope

- `Code/Libraries/Source/WWVegas/WWMath/Matrix3DData.h`: forward declare actual `class Vector3`;
  add exactly axis-angle constructor, two axis `Set` overloads, `mul` and `Rotate_Vector`
  declarations. No field, base, vptr, existing inline body, header guard or compilation flag changes.
- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero.cpp` and
  `AptMyHero_Unresolved.cpp`: replace their same private Matrix3D class with the canonical
  include; retain the same axis ctor/angle-Set bodies as honest out-of-class inline definitions.
  All other body definitions remain verbatim. No new helper, copied value, arithmetic
  reassociation, alias, annotation, marker or pin is added.
- Root holds both source scopes and class/header lease `effa44997ebb46b382bb7185a37239a1`;
  see root `bfme2/apt008-matrix-claims.json`. The child made no claim mutation.

## Independent declaration, ABI and layout evidence

The original existing ZH WWMath `matrix3d.h` declares/defines the same API:
axis ctor at451; Set declarations202/204 and bodies571/591; Rotate_Vector302;
lowercase `mul`361/1572. `mul` is an original real method, not an invented name.
Existing B2 native owners independently establish these real COFF identities:

- `??0Matrix3D@@QAE@ABVVector3@@M@Z`, 00102A12,369B;
- `?Set@Matrix3D@@QAEXABVVector3@@M@Z`,001025EB,356B;
- `?Set@Matrix3D@@QAEXABVVector3@@MM@Z`,00102404,318B;
- `?mul@Matrix3D@@QAEXABV1@0@Z`,000B267D,552B;
- `?Rotate_Vector@Matrix3D@@QBE?AVVector3@@ABV2@@Z`,00712030,135B.

The first three live in Matrix3DO1Inlines.cpp; mul in streakRender.cpp;
Rotate_Vector in Matrix3DUnmatchedSSE.cpp. Its actual target, not an alternate alias,
is resolved by the strict Sun caller comparison: no unresolved or masked relocation.
The existing canonical class contract (138 ordinary48B views,57 retail member rows,
no native vtables) and real WWMath declaration agree on `Vector4 Row[3]` at0,
no bases/vptr. Matrix4 is a different64B/four-row class, includes Matrix3DData,
and is neither substituted nor changed. Vector3 is12B. The private old seed's
incorrect const-subscript reference return is NOT corrected by this Matrix-only patch.
No original EA game CodeView/PDB was located. Existing compiler CodeView from
reconstructed sources must not be described as original retail type metadata.

## Native measurements

Fresh native controls: seed43/43 and Unresolved16/16. Proposed header plus both
mechanical source adoptions:43/43+16/16=59/59. All normal real-TU regional flags
were selected by TS.Verifier, then only source/object paths redirected privately.
BFME_OBJSTORE=off, serial compilers, no shared cache outputs. The proposed header
was represented explicitly by a private file containing only the stated changes;
this is a hypothetical normal patch compile, not an assertion that the unchanged
production header already supplies these members.

Full objects:58+13 strong code definitions unchanged in raw bytes and named
relocations; no definitions or undefineds added/removed. Seed has no vtable;
Unresolved retains the exact AptMyHero vtable graph. All31+11 noncode/nondebug
sections retain raw bytes, flags, extents and actual target graphs. Every physical
runtime section also retains its original raw/relocation graph; no code COMDAT
ordering or anonymous target discrepancy is hidden. See both footprint JSONs.
Seed Sun005B0A95 remains the exact971B body and19 original relocations.

One report writer initially failed after successful native compilation because
the source-definition inventory is a set. No source was varied to fix that.
`aptmyhero-matrix3d-recover.py` re-read those exact private outputs, verified
the source/object digests and all original dependency MD5s, and ran normal
compile_function on them without recompiling. The reproducible probe writer is
now fixed to serialize sets. Earlier stale-input guard refusal occurred before
any compiler when Root's window adoptions changed the source; no old seed was
copied over the current tree.

## Separate failed combined hypothesis

The older f22 seed's joint Vector3+canonical-Matrix3D candidate remains42/43;
Sun is971B with the same24 true nonrelocation byte differences in middle-row
floating dot products and all19 original relocations. It is byte/reloc identical
to the prior best Vector3 trial. That result has no acceptance or task credit.
It does NOT refute the separately proved Matrix-only59/59 result, and the latter
does NOT solve Vector3. No further source forms were tried without independent evidence.

## Root integration recipe

Check all three current input SHA256s in NATIVE-RECEIPT-COMPACT.json first;
do not overwrite later source changes. Review/apply `whole-family-matrix-only.patch`
or copy the two exact source banks plus header proposal after that guard.
Root may then run the normal official paths:

```
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero_Unresolved.cpp
./build.sh Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero.cpp Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero_Unresolved.cpp
python3 tools/header_adopt_lane.py accept --class Matrix3D Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero.cpp Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHero_Unresolved.cpp
```

The ordinary staged header-dependent precommit check is still required for the
changed canonical header. This private two-source proof does not replace it or
claim other consumers, full-image linking, actual execution, CRC or performance.
Existing known ctor/Set names remain their original globally rowed identities;
there are no new body rows to admit and no original implementation to delete.
Root owns ordinary source-only commits, records and publication.

Root integration preserves the three existing repository LF line endings; the private banks used CRLF. Only line endings were normalized after the first successful normal header-dependent gate. The ordinary staged-source/header gate was rerun for the final amended commit. This adds no task or byte credit.
