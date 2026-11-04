# Rva007401F6 view reconciliation and row rehome (2026-11-04, claudec)

Scope: `Code/GameEngine/Source/Common/W3DAptComponentView3D.cpp` (approved TU,
provisional name) and the split units that held Rva007401F6's ctor, dtor and
deleting dtor.

## Target facts

- `??0Rva007401F6` 0x007401E5 (17 B) stores vtable 0x00CF15E8 (file 0x008F15E8),
  -1 at +4 (inlined base ctor 0x00410297), clears +8.
- `??1Rva007401F6` 0x007401F6 (48 B, EH handler 0x007AB44B): releases the
  string handle at +8 and restores base vtable 0x0083962C. It does **not**
  store its own vptr at entry.
- `??_GRva007401F6` 0x00740226 (28 B): calls 0x007401F6, then delete.
- Vtable 0x008F15E8: slot 0 = ??_G, slots 1-3 = `__purecall`; the
  W3DAptComponentView3D vtable 0x008F1600 fills slots 1 and 3.

## Compiler finding (MSVC 7.1, /O1 /G7 /arch:SSE)

A user-written virtual destructor (`virtual ~Rva007401F6() {}` or defined
out of line) emits `mov [esi], ??_7Rva007401F6@@6B@` at entry, which retail
lacks (1/3 matched in a scratch build). `__declspec(novtable)` removes it but
also drops the vtable store the ctor needs (re_attempts 57554). Declaring
**no** destructor gives the compiler-generated one, which skips the derived
vptr store and matches 0x007401F6 together with the ctor and ??_G.

## Changes (four commits handed to publish)

1. Shared view in seed and ctor donor: `Rva007401F6 : Rva0045EF90Base`
   (same base view as Rva004103E7Finish.cpp), `AsciiString` from
   `reference/shims/bfme2_ascii` instead of a private StringBase copy, three
   pure virtuals, no user dtor. Both units 19/19.
2. `??1Rva007401F6` and its `__ehhandler` repointed to the seed (add_match
   --replace-existing); `Rva007401F6Dtor.cpp` removed with its
   present_unmatched line (2377 -> 2376). Needed at once: the seed's implicit
   dtor COMDAT would otherwise duplicate the split unit's definition
   (tu_skeleton link guard: "duplicate ??1Rva007401F6@@UAE@XZ").
3. `tu_skeleton --merge` accepted `Rva007401E5Ctor.cpp` (21 rows).
4. `??_GRva007401F6` repointed to the seed (22/22); the famgen unit
   `FamilyDeletingDtors_muse-e282.cpp` removed (last row).

Source files: -3. No census-linked coverage claimed; carry the seed into the
next census.

## Still rejected

- `GUI/W3DAptComponentView3D.cpp`: StringBase redefinition vs the seed's
  remaining StringBase users (0x00740A60), CameraClass/LightClass views.
- `GUI/W3DAptComponentView3DSetup.cpp`: SimpleSceneClass base undefined in
  merged order, CameraClass/Matrix3D views.
- `GUI/W3DAptComponentView3DAnimInfo.cpp`: StringBase redefinition, own
  AssetList / Rva007401A3 views.
- `uw_007ab443` (dtor unwind funclet, Code/gen_small/uw_gen_012.cpp) is still
  a gen row; its parent now lives in the seed.
