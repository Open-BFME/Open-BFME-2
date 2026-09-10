// ?Vendor_Specific_Hacks@DX8Caps@@AAEXABU_D3DADAPTER_IDENTIFIER8@@@Z
// partial score=0.989 date=2026-09-09
// cl: (compiled as part of Code/Libraries/Source/WWVegas/WW3D2/dx8caps.cpp)
//
// ?Vendor_Specific_Hacks@DX8Caps@@AAEXABU_D3DADAPTER_IDENTIFIER8@@@Z
// 0x0012B9B0, 1065 bytes. The body is ALREADY IN THE TREE at dx8caps.cpp
// behind a present-unmatched marker; this stash is the analysis, not a second
// copy of the source. Two corrections landed here took it from 1120 bytes with
// 625 non-relocation differences to 1053 bytes with TWELVE, in ONE region.
// Everything else -- 250 instructions, every string literal site, every vendor
// and device comparison, every resolution clamp, the whole switch -- agrees.
//
// ================= CORRECTION 1: deviceId is at 0x2C0, not 0x2C8 ============
// dx8caps.cpp carried TWO overlay structs for one class and they disagreed.
// BFME_DX8Caps_All put deviceId at 0x2c8 and driverBuildVersion at 0x2c4;
// BFME_DX8Caps_ComputeFields, which Compute_Caps uses to WRITE the same
// fields, put mappedDevice at 0x2c0 and driverBuildVersion at 0x2c8.
// Retail settles it: every deviceId comparison in this body is
// `mov eax,[esi+0x2c0]`, at ten independent sites. The value compared against
// the DEVICE_* constants is the MAPPED index Get_NVidia_Device/Get_ATI_Device
// return, not the raw PCI id -- which is why the field is spelled
// `mappedDevice` in the other overlay.
//
// The lesson generalises and this file has been bitten by it before: two
// overlays of one class that disagree are a DEFECT, and the tiebreaker is
// retail's own displacement bytes, never the more plausible-looking struct.
//
// ================= CORRECTION 2: no GeForce2 MX clamp in BFME2 =============
// The reference tree limits GeForce2 MX / MX400 to 1024x768. BFME2 does not.
// Retail's NVidia arm ends immediately after the DXTC fold, with `xor bl,bl`
// and then the Matrox vendor test at `cmp [esi+0x2d0],VENDOR_MATROX`. Proven
// two ways: there is no load of the device id anywhere between the store to
// supportDXTC (0x139) and that compare, and the body contains no 1024x768
// store at all. Its only resolution clamps are three 1280x1024
// (0x500 x 0x400) and one 800x600 (0x320 x 0x258), all in the ATI/Intel arms.
//
// ================= WHAT IS LEFT: 12 bytes, one scheduling region ===========
// retail 0x67..0x99                        ours
//   mov al,[esi+0x1b8]   ; fmt[122]          mov al,[esi+0x1b8]
//   mov dl,[esi+0x1b6]   ; fmt[120]          or  al,[esi+0x1b7]
//   mov cl,[esi+0x1b5]   ; fmt[119]          mov [esi+0x13b],bl
//   mov [esi+0x13b],bl   ; NPatches=false    or  al,[esi+0x1b6]
//   mov [esi+0x1b4],bl   ; fmt[118]=false    mov [esi+0x1b4],bl
//   mov bl,[esi+0x1b7]   ; fmt[121]          or  al,[esi+0x1b5]
//   or  al,bl                                mov [esi+0x139],al
//   or  al,dl
//   or  al,cl
//   mov [esi+0x139],al
//   xor bl,bl            ; bl was clobbered
//
// Same four operands, same result, same elision of fmt[118]. Retail holds
// three of them in registers ACROSS the two stores; we fold from memory.
//
// REFUTED HERE -- do not re-run these:
//   * /Oa. It is the documented lever for "retail keeps a value in a register
//     where we reload from memory", and on this unit it is destructive: 11 of
//     dx8caps.cpp's 19 matched rows fail with it. Measured, not guessed.
//   * const bool temporaries naming the three loads in retail's exact order.
//     Changes NOTHING -- MSVC folds a single-use temporary straight back into
//     the memory operand. Emitted length identical to the version without.
//
//   * /G6 instead of /G7 -- and this one is the interesting refutation.
//     Under /G6 this body comes out at EXACTLY 1065 bytes, the scheduling
//     region included. But /G6 breaks the rest of the unit: Compute_Caps and
//     Check_Driver_Version_Status both fail, and the tell is decisive --
//     retail increments the DX8 call counter with `83 05 <mem> 01`
//     (add mem,1) where /G6 emits `ff 05 <mem>` (inc mem). Retail compiled
//     this TU with /G7, so the fold's shape must have another cause and the
//     matching length under /G6 is a coincidence of scheduling, not evidence.
//     Do not switch the unit's flag to chase this body.
//
// NOT YET TRIED:
//   * Making the fold's operand set literally exclude fmt[118] in the source.
//     Retail elides it, so the source may never have named it, and dropping it
//     removes the only reason the fold must be ordered after the store.
//
// place_bodies over the unit after both corrections: 0 new bodies, 0 new pins.
// The layout fix did not unblock siblings here the way the RenderObjClass and
// CameraClass ones did -- worth knowing before hoping for a cascade.
