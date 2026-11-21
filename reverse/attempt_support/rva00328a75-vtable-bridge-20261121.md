# Rva00328A75 vtable bridge (0x0080D8C4): handoff

Queue item: vtable-bridge `??_7Rva00328A75@@6B@` at 0x0080D8C4. The bridged copy is
emitted by `Code/GameEngine/Source/Common/Rva000AD6F4Members.cpp`.

## Target facts (game.dat 1.06)

- Table 0x0080D8C4 has two slots, 0x00329653 and 0x0032965B. The next word,
  0x0081E6F3, belongs to another table. There is no deleting-destructor slot.
- 0x00329653 is `mov ecx,[ecx+4]; jmp 0x003294D6`, and 0x0032965B is
  `mov ecx,[ecx+4]; jmp 0x003295B4`. The jump targets are the rowed
  `OldPolygonTriggerDataChunkParserBase::Impl::parsePolygonTriggersChunkImpl`
  and `parseWaterAreasChunkImpl` (`Code/GameEngine/Source/GameLogic/Map/OldPolygonTrigger.cpp`).
- Constructor 0x00328D4A stores 0x00C0D8C4 at [this], news 0x28 bytes, and runs
  ctor 0x00328C5E on them. It stores the result at +4. `Impl`'s rowed view is
  0x28 bytes, so `Rva00328C5E` is very likely `Impl`, but this is an inference.
- Destructor 0x00328A75 (14 bytes) stores 0x00C0D8C4 at [ecx], then `add ecx,4;
  jmp 0x000AD6F4`. It is the class's destructor, but it is not virtual: the table
  has no slot for it.
- Derived constructor 0x00328D9D calls 0x00328D4A, then installs 0x00C0D8F0,
  which is `[0x00329663, 0x0032965B]`. Slot 0 is overridden by the rowed
  `?parse@Rva00329663@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z`
  (OldPolygonTrigger.cpp).
- No data word refers to 0x004ADE29 (`??_GRva000AD71D`) or 0x004AD71D.

## Why it is not landed

Retail's shape is:

```
class Rva00328A75 {
  ~Rva00328A75();                                     // non-virtual
  virtual bool slot0(DataChunkInput &, DataChunkInfo *); // 0x00329653
  virtual bool slot1(DataChunkInput &, DataChunkInfo *); // 0x0032965B
  Impl *m_impl;                                         // +4
};
```

The ledger contradicts that shape in three ways:

1. `??1Rva00328A75@@UAE@XZ` (0x00328A75) is spelled virtual. Four class views
   declare `virtual ~Rva00328A75()`: Rva000AD6F4Members.cpp,
   Rva00328D9DCtor.cpp, and WorldHeightMap.cpp (where `Rva000AD71D` derives
   from it). Ctor.cpp avoids the issue by naming the table through
   `__identifier`. `rename.py function --virtual` only respells toward
   virtual, so no tool respells `UAE` to `QAE`.
2. The slot bodies are rowed as non-virtual members of private placeholder
   classes, `?rva00329653@Rva00329653Forwarder@@QAEXHH@Z` and
   `?rva0032965B@Rva0032965BForwarder@@QAEXHH@Z`
   (`Code/GameEngine/Source/Common/VslotMemberForwarders.cpp`). They need
   `rename.py class --fold` into `Rva00328A75` (or its real name) and then
   `function --virtual`. Their `(int,int)` signature also differs from the
   derived override's `(DataChunkInput &, DataChunkInfo *)`.
3. The derived class appears as `Rva00328D9D` in its constructor unit and as
   `Rva00329663` in OldPolygonTrigger.cpp, so it needs a fold as well.

## Next step

This is naming-lane work. Fold the classes, respell the two forwarders as
virtual with the override's signature, and add a tool path, or a
tooling-seat change, for a virtual-to-non-virtual destructor respell. Then
give one shared header to every view: Members, Ctor, D9DCtor,
WorldHeightMap, OldPolygonTrigger and VslotMemberForwarders. With that header,
the Ctor unit emits the table and the `__identifier` vptr store goes away.
