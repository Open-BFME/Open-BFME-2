# WorldHeightMap canonical-header boundary (qc-11)

Target: vanilla-1.06 game.dat SHA256 f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640.

## Target facts

Native W3DTerrainVisual::load pushes 0x120F0 at RVA 0x00092193, calls operator new at 0x0002FDA0, and calls WorldHeightMap's one-argument stream constructor at 0x000921AB (target 0x000B0ACD). This is an explicit retail allocation, not a size vote. The three matched constructors at 0x000B098A/0x000B0ACD/0x000B0C38 write through +0x120D0 and construct members at +0x120D8. Their existing source view includes final words through +0x120EC, consistent with the allocation. The vptr is 0x00BC967C. At that address are DeleteThis 0x0006CE57 and the rowed deleting destructor 0x000B0238; the following code-valued word is parseBlendTileData 0x000B1173, then non-code words 0x41800000 and 0xC7C34FF3. This pass did not establish whether that third word extends the vtable or is separate adjacent data. It must not be silently added or omitted as a slot.

## Tool result and rejected evidence

`header_adopt_lane run --class WorldHeightMap --header Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h --generate --variants data+methods+includes --jobs 4` reports 0/59 pass, 59 queued. Failures include field renames (41) and C2535 (13). Its empty decision queue does not establish a valid header: the contract selects size 16 by majority, bases=[], and three prefix fields, while its own retail_layout evidence reports allocation_observed 0x120F0 and extent_lower_bound 73940. The generated header was removed by the tournament. The refuted contract remains scratch only at build/qc11-refuted-WorldHeightMap.json.

The separate REA/Ghidra xref attempt failed with provider_timeout after the 330000 ms startup deadline while importing this 10,969,600-byte PE; it yielded no lookup result. No provider configuration was changed. The binary session was closed. Direct PE/Capstone reads and the existing matched rows supplied the facts above; raw byte-pattern hits were not treated as xrefs (a candidate in Player's bit-test was instruction bytes, not an address operand).

## Remaining work

Establish the native table boundary, recover the full allocation-backed member surface (including the RefCountClass base and vector/record arrays), and write the canonical header by hand at the lane destination. Distinguish target layout from constructor carrier element types and BFME1/ZH donor names. A 16-byte prefix is not a complete class definition. No Code source was changed or left nonmatching, no header was registered, and no adoption/link gain is claimed.
