### Native network factory constructor binding

Status: repaired locally; full real-link confirmation pending.

The real link at `1ffed447e60475f63b29d0d56d4b41ff4fe06578` could not
resolve `??0Pinger@@QAE@XZ` from
`GameNetwork/GameSpy/Thread/PingThread_PingerInterface_createNewPingerInterface.cpp`.
The factory at RVA `0x005590FC` allocates `0xA8` bytes and calls RVA
`0x00558EC1`, already owned by the 173-byte `BFMENetwork` constructor.
Its borrowed private Pinger declaration selected an undefined symbol instead.

The factory now uses a declaration-only BFMENetwork allocation view and the
existing constructor. The historical factory interface name is retained;
this is not evidence that the donor Pinger class has BFME II's layout.
No constructor body, alias, pin, data definition or vtable was added.

Validation: official scoped build 3/3 rows; factory EH graph EXACT; all 53
factory bytes unchanged, with its sole changed relocation now naming the
existing constructor. Before/after provider comparison adds or removes no
definitions and changes only the factory. The provider-inclusive preview
passes 2/2 sources (63 factory bytes, 173 BFMENetwork bytes). Its census index
is `0534e78db3`, so this is scoped evidence, not a new whole-game link result.

See [handoff](../../reverse/attempt_support/native-network-factory-constructor.md).
