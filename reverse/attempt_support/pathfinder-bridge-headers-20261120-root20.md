# Remaining header dependencies in the bridge classifier

The shared Rva00366500 declaration and the canonical Bridge layout both passed
queue acceptance in PathfinderBridgeUpdateRva0052ED74.cpp. The bridge layout
adoption retains the local scalar snapshots of its Region2D bounds. The final
restored source builds both functions and both data rows byte for byte.

## PathfindCell

The shared class exposes the packed flags at +0x0C but leaves PathfindCellInfo
opaque. The trial reused the existing null-checked obstacle-ID read at info
+0x28. The 1,312-byte updater at RVA 0x0052ED74 and its two neighbor arrays
passed throughout.

With the shared class at the original declaration site, the 1,120-byte
classifier at RVA 0x0052E914 emits 1,110 bytes. A dword mask, a byte mask, and a
one-bit field for clearing packed bit 16 all produce identical code. VC71
merges parts of two setter sequences. Explicitly sequencing the off-bridge
setters restores the length and changes the accumulator and branch layout.

Moving the shared include immediately after Rva00366500 is the closest trial.
The result has the retail length and differs only at offsets 0x163-0x165 and
0x16E-0x170. Those bytes swap the calls to rva0036652D at RVA 0x0036652D and
SetType_Dirty at RVA 0x0052DA1C in the first four-call group. Parenthesizing
the two pairs preserves the same six-byte difference. Splitting three calls
from the fourth emits 1,122 bytes. Fully sequencing the calls changes the
frame and branch layout. The tracked source was restored and the queue entry
remains open. The local trial logs are in build/root-resume-20261120/field-header.

## Rva002E713FOwner

The canonical receiver header declares methods only. The bridge updater needs
the map, extent, bridge list, layers, zone manager, and dirty byte at +0x1BEB4.
The corresponding Pathfinder storage is private, and the dirty byte is part of
its opaque tail. The Pathfinder class scope was held by another worker, so
the existing updater owner and callers were left in place.
