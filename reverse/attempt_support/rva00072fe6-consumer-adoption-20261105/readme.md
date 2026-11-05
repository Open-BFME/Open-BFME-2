# Rva00072FE6 consumer header adoption

Inspected base: `10b5d79f4820`; 2026-11-05; seat
`yasinschroeder-codexb4`, model `gpt-6.1-sol`.

Three consumers now include the existing canonical header:

- `Code/GameEngine/Source/Common/System/Rva003EF14ADtor.cpp`
- `Code/GameEngine/Source/GameNetwork/NetworkGetCommandsFromCommandList.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/SpawnArmy.cpp`

The canonical header records target constructor/destructor/clear evidence for a
12-byte tree. The two record consumers previously included the trailing 12 opaque
bytes of their 32-byte record in the tree view. Those bytes now belong to
`Rva004E2199Record::unknown14`; the record stride and existing accesses are
unchanged. This does not identify the original tree or record type. The network
consumer uses only the destructor declaration; its private field declarations
were unused. No function body, inline provider, alias, pin, or data definition
was removed. The shared header and destructor provider are unchanged.

Checks on the final source:

- `find_declared_unmatched.py` on all three: no unrowed defined functions.
- `./build.sh` on all three: 95/95 function checks, eight data rows, seven string
  references and 24 funclet pins pass. Renumbered compiler labels resolve through
  the verified parent EH data.
- `eh_verify.py` on all three: 17/17 EH graphs EXACT, no baseline exceptions.
- Ordinary `link_check.py`, census index `c95fcfcfcd` (2026-11-05 05:17): all
  three LINKS, preserving 580 + 539 + 2,808 = 3,927 authored bytes. These are
  previews, not a new census or a real-link measurement.
- One `header_adopt_lane.py accept --class Rva00072FE6` over the full five-unit
  cohort passes these three and retires exactly their three header-queue rows.
  It returns 1 because the two unchanged private-view units below remain queued.

## Remaining cohort

The supported automatic adoption trial restored all rejected files. In
`Common/RTS/PlayerTemplate.cpp`, the view derives from `_STL::set<int>`: begin,
end and insert are used, and the rowed store constructor at 0x001FDB55 also
relies on the inherited set constructor. Replacing only the view cannot preserve
those operations and lifetime calls. Preserve that constructor/destructor
profile while expressing the existing set operations through the canonical
storage before retrying.

`Common/RvaTreeDtorFamily.cpp` defines destructor 0x000730DE with a
`RvaTreeFamilyHolder` member whose destructor frees the header on normal and EH
paths. The canonical header has a raw pointer at +0; direct replacement loses
that member cleanup. Reconstruct the same cleanup/EH shape before adoption.
This provider and its wrapper remain untouched. No retirement is claimed for
either remaining unit, and no failed reconstruction remains in Code/.

The initial default pick, `WWMath/coord3d.cpp`, was already healthy: 67/67 byte
checks and LINKS 2,265 -> 2,265 against the same census. Its stale real-link
blocker was not treated as a new source defect; its claim was released.
