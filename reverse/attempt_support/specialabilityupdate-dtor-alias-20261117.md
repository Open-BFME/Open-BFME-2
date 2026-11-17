# SpecialAbilityUpdate opaque base dtor: a retired alias, 11 units

Recorded 2026-11-17 against `master` at `13f1393a2a`.

## Symptom

`reverse/exit_link_blockers.tsv` (real link at `abb031ee`) lists
`??1Rva0044EF5E@@UAE@XZ` for 11 units:

- `DominateEnemySpecialPower.cpp`
- `ArrowStormUpdateBehaviorCtor.cpp`
- `GloriousChargeUpdate.cpp`
- `MissileLauncherBuildingUpdate.cpp`
- `ModuleUpdateDtors.cpp`
- `OCLUpdateCtor.cpp`
- `RousingSpeechUpdate.cpp`
- `Rva00492C59Ctor.cpp`
- `ScaleWallSpecialAbilityUpdate.cpp`
- `SpecialAbilityUpdate.cpp`
- `WeaponFireSpecialAbilityUpdate.cpp`

## Cause

The 93-byte body at `0x00451F45` is rowed only as
`??1SpecialAbilityUpdate@@UAE@XZ` (`SpecialAbilityUpdateDtor.cpp`, matched,
EH graph exact). The 11 units declare their base locally as the opaque
`Rva0044EF5E`, so their derived destructors reference the opaque spelling.

Commit `f1b347e091` had bound the two spellings with

```
#pragma comment(linker, "/alternatename:??1Rva0044EF5E@@UAE@XZ=??1SpecialAbilityUpdate@@UAE@XZ")
```

Commit `8eab05132d` ("Retire 4 COMDAT-redundant alternatename pragmas",
2026-11-15) removed that one line. The two names are not COMDAT twins: the
provider row carries the real class name, while the callers carry the
address-derived one. `SpecialAbilityUpdateDtor.cpp` still ends with the two
comment lines that describe this binding, which is why the loss is easy to
spot.

## Why this attempt did not land

- Restoring the directive grows the `alternatename` hatch register by 1.
  `python3 tools/hatch_counters.py --update` refuses it
  ("1 occurrence key(s) grew; remove them, or admit them with --allow").
  `--allow` / `--admit` are the hand-add path this lane must not take, and no
  tool here re-admits a *restored* alias automatically.
- A hatch-free twin body is not practical: `SpecialAbilityUpdateDtor.cpp`
  compiles the dtor from the canonical class with four complete-class vptrs
  (+0, +0x0C, +0x10, +0x20), `onExit(true, true)` through 0x004502CE, the
  `list<int>` at +0x64 and `UpdateModule`'s dtor 0x0024A797. A local
  `Rva0044EF5E` view cannot reproduce that layout without becoming the
  canonical class.
- Repointing the row to the opaque spelling would break every unit that
  reaches the dtor under the real `SpecialAbilityUpdate` spelling (the row's
  own `??_GSpecialAbilityUpdate` at 0x004522F0 calls it in that unit).
- Adding the definition to a caller's TU is unsafe for the same reason
  `APT`/`AptCIH` needed a sibling TU: the derived dtors tail-jump the base
  dtor, and an in-TU definition inlines it and breaks those matched rows.

## Routes left

1. A maintainer admits the restored `alternatename` line (the same line
   `8eab05132d` removed) with a Verifier-Change reason. This is the smallest
   change and restores the state between `f1b347e091` and `8eab05132d`.
2. Adopt the canonical `SpecialAbilityUpdate` header in the 11 units. That
   also moves their base-constructor calls from the opaque
   `??0Rva0044EF5E@@QAE@...` row (`SpecialAbilityUpdate.cpp`) to the real
   `??0SpecialAbilityUpdate@@QAE@...`, which is currently a pin only, so the
   ctor would need its own provider as well. Larger, class-adoption lane.

## Related false retirements from the same sweep

- `Player_Radar.cpp`: the alias for `?okToPlayRadarEdgeSound@Player@@QAE_NXZ`
  was retired by `1cc99cc230` and is being repaired by another worker.
- `AptValueDonorBitsBFME2.cpp`: the alias for
  `?rva006dbd80@AptCIH@@QAEXXZ` was retired by `1e79469632`; fixed on master in
  `0265144a76` by giving the opaque spelling its own fold-proof body in
  `AptCIHJumpToFrame.cpp` (no hatch).
- `StringBaseNarrowCopySet.cpp`: `1e79469632` also removed

  ```
  ?bfmeSetBSF@BfmeSubBSF@@QAEXPAX@Z=??0?$StringBase@D@@AAE@ABV0@@Z
  ?bfmeCopyUVKE@BfmeUniVKE@@QAEXABV1@@Z=??0?$StringBase@D@@AAE@ABV0@@Z
  ```

  leaving `BfmeConv526.cpp` and `BfmeConv1399.cpp` unresolved at the rowed
  `StringBase<char>` copy constructor 0x000365F0. They are exact siblings of
  the six bindings still in that file (`copyFrom@BfmeTail50`,
  `?bfmeSetBPD@BfmeSubBPD`, …), so the same restore applies.

  A hatch-free twin was tried on 2026-11-17 and is impossible: both callers
  declare a void-returning method, while the 66-byte copy constructor ends
  `mov eax, edi` (it returns `this`). Compiling the same narrow-lock source as
  a void method gives 64 bytes, missing exactly that `8b c7`. Changing the
  caller's declaration would change the mangled name the link asks for, so
  only the alias (or the caller-side declaration, held by another worker) can
  bind these.

## Why a "trade a dead alias for a needed one" does not work

`register_growth` in `tools/hatch_counters.py` explains an added occurrence
only by an old occurrence with the *same (hatch, token)* in another file, or
(rule 8) the same file once the code-identity register is enforced. A restored
token has no old occurrence left, so removing an unrelated dead alias does not
pay for it. `--update` therefore refuses all three restores, and `--allow` is
the hand-add path this lane must not take.

Only 17 of the 2,177 aliases in the tree look dead by the census index
(no object references the left-hand name): most of them in
`FXParticleSystem.cpp` (purecall slots) and `OpaqueSingleInheritanceDtors.cpp`.
They are still dead candidates for a tooling seat, not a currency here.

A tool that retires `alternatename` directives should resolve the *undefined*
name across the whole tree, not only the file that carries the pragma.
