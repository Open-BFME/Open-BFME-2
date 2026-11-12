# Terrain shader interface adoption

Base: `c40bbd895ae`, MSVC 7.1 with the existing region flags, 2026-11-13.
Scope: the four queued Rva000E19A3Interface consumers. The existing header
declares its four virtual slots with the same four-byte by-value texture
handles; no header, slot order, layout, provider or ledger identity changes.

The owning adoption trial accepts Rva000E19A3Dtor.cpp, FlatHeightMap.cpp and
W3DFloorBuffer.cpp. Each replaces its identical private declaration with the
registered header. Rva000E44BETerrainDraw.cpp is restored and remains queued.

## Remaining terrain draw caller

The private draw view takes TextureArg; the canonical interface takes
RefCountPtr<TextureClass>. Mechanical replacement fails the 169-byte parent
at 0x000E44BE and its 8-byte restore funclet at 0x007632BC. Explicitly using
RefCountPtr<TextureClass>(fallback.Peek()) removes the unnecessary derived-to-
base temporary and produces 169 bytes with every call and all other parent
instructions matching, but the first copy construction still differs:

```
retail E44E7: mov [ebp-10h],esp
retail E44EA: mov ecx,esp
trial  E44E7: mov ecx,esp
trial  E44E9: mov [ebp-10h],esp
both   E44EC: push eax
both   E44ED: call 000424BB
```

The retained direct trial is `terrain-interface-direct-20261113-root20.cpp.txt`.
It is evidence only and does not belong under Code/. The original source
retains its previously verified TextureArg wrapper and private interface.

Tested without closing this residual: explicit copy temporaries, inline
return-by-value and named-return helpers, a const return, copy-constructor
exception visibility, a placement-construction forwarding tag, and compiler
barriers before/after construction. None passes all three rows. These probes
live under ignored build/interface_probe/; no flags, aliases, pins, assembly,
baselines or artificial emitted labels were added. This is a correctly refused
near match, not a false reject. Revisit with a different compiler/source-lifetime
explanation; do not repeat the same copy-forwarding variants.

Acceptance of the other three units is source cleanup and header-queue
retirement. It is not evidence that the executable links or runs, and does not
retire the draw caller's remaining queue entry.

## Verification of the retained cohort

The ordinary build and strict preparation each verify 125/125 function rows,
two data rows, 32 string references, 23 float literals and three named imports
across the four sources, including the restored draw caller. The owning
acceptance tool passes the other three sources and retires their three rows
from header_queue.tsv. All four scoped link previews remain LINKS and retain
10,813 bytes in total (1,446 / 167 / 4,107 / 5,093). The old index at
`aa7acf764d` warns of seven source-path changes since its 2026-11-12 19:19
snapshot. The Dtor preview also reports its unreferenced RefCountPtr::Clear
copy as a diagnostic. These are bounded preservation results, not a new
census, real link, bridge count or runtime receipt.

The commit hook passes 122/122 changed-source rows and all 17 EH graphs.
It also reports two shadow binding findings in W3DFloorBuffer::addFloor for
the existing list push_back/push_front providers at 0x0005548F/0x00392076.
A pre-adoption/current scratch comparison verifies all 51 FloorBuffer rows
and finds all 121 emitted COMDAT byte/relocation fingerprints unchanged,
with no additions or removals. Thus this adoption does not change those
bindings; their underlying identity debt is not cleared. The comparison is
recorded in `terrain-interface-floor-identity-20261113-root20.json`.
