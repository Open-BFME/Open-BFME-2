# ImageCollection consumers, root20, 2026-11-14

Ten of the twelve served sources now include the registered GameClient/Image.h;
owning adopt and accept pass, retiring exactly ten header queue rows. Canonical
headers and providers are unchanged. This replaces private interface/image views,
not native bodies or source ownership; no unique code or game-run gain is claimed.

## Changes and verification

Rva005F0152ImageGet, UpgradeTemplate cache and Shell opt into STLport. Three GUI
files explicitly select their existing Platform SDK provider; StagingRoom selects
its receipt-proven sweep Windows shim instead of replacing it with the SDK.
The initial blanket SDK trial collided with StagingRoom's own hostent/network
prototypes; that trial was corrected before the whole545-row verification.

CommandButton removes the false Image:ModuleData view. A scoped reinterpret_cast
retains its existing non-owning vector<const ModuleData*> provider ABI; it is a
legacy pointer carrier, not a claim that Image inherits ModuleData. MapPreview's
single +8 string access now names the filename, retaining the _art.tga test.
Timeline reads canonical m_imageSize.x/y at+24/+28 directly. The accessor variant
was byte-correct but emitted two extra helper COMDATs, so direct public fields
retain the original object set without new rows or pins.

AptMyHero replaces nine independently audited inert tree-wrapper bodies with
forward declarations and removes their two unused private tree stubs and eight
supporting aliases. No active function uses those types; its active vector
interface and explicit instantiations remain. The complete40-row source passes.
The other pointer-only collection lookups retain their signatures.

Final controls cover all twelve sources: ./build.sh passes545/545 functions,
three data rows,211 literals+18 empty strings,24 float refs and24 named imports.
All1028 runtime COMDATs retain their bytes and relocation identities, including
the generated MappedImageCache initializer. None is added or removed. All71
complete EH graphs checked are EXACT. The adjacent JSON records every source and
object fingerprint. The two blocked source files are restored byte for byte.

## AptMyHero_Unresolved allocator boundary

Including Image.h changes only the native250B AptMyHero destructor to246B:
the EH-state-zero store before vector free disappears (first difference+211).
The object still calls the direct _free symbol; this was not an indirect-call
size increase. Native cleanup uses the game allocator at30830. New standard
header declarations change the visible allocator/exception contract.

Moving the existing free(void*) throw(...) declaration before the header fails
C2375. A source-wide _CRTIMP= trial conflicts on strstr; a header-scoped stdlib
trial conflicts on perror/_wperror/atoi. No variant or alias is retained. The
original source, compiler flags and native250B body are restored. This needs a
coherent game-CRT declaration/exception contract with complete callee/EH proof;
no new pin, wrapper or optimization pragma would be a repair.

## Deleting-destructor satellite placement boundary

ImageCollectionDeletingDtor.cpp's absent-from-retail tag constructor emits its
rowed28B scalar wrapper. Image.h declares no such overload, so substitution fails
C2511. Do not add another constructor/destructor just to force emission.
Current System/Image.cpp already emits the exact same28B wrapper, with identical
relocations to the115B complete destructor and operator delete. Read-only native
analysis also confirms its14-slot table and24B class layout.

A fresh in-memory TU map approves ctor2D932B and complete dtor2D9283 for Image.cpp,
but scalar2D9362 remains unassigned/displaced, only N=System/ImageCollection.cpp.
The supported emit-move refuses unapproved placement and a whole one-row donor;
normal merge discovery only selects approved donors, so it cannot take this
satellite. The prerequisite is placement/donor admission, not missing codegen.
No row, map, source path or provider moved; the original satellite remains queued.

Scratch evidence is under build/root-image-collection/: before controls,
initial/prepared-adoption logs, final-build.log, final-object-proof.json,
accept.log and the preserved allocator diagnostic bytes. The ten passing sources
are the complete independently verified adoption scope.
