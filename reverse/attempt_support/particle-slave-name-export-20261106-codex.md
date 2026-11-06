# ParticleSystemTemplate slave-name export

Base `9fddc460cc9e32703d9481f410011bca8987da9e`. The authoritative real link at 0e8f5c6e8f
reports this missing export in ParticleSys.cpp. Retail export ordinal 1883
proves `?setSlaveSystemName@ParticleSystemTemplate@FXParticleSystem@@QAEXABVAsciiString@@@Z` at RVA `0x001F3FD0`.
The existing 26-byte matched placeholder already assigns the +0x68
AsciiString and clears the cache at +0xA0.

The member view retains the complete body, relocations and all other
external code definitions. The old name had one local object hit before
the edit and zero after. Its only source spelling was the original unit.
The existing row is retained at the same address and verified under the
exported identity. The retired spelling has a tombstone.

```text
Code/GameEngine/Source/GameClient/System/ParticleSys.cpp: LINKS  LINKED 5,092 -> 5,092 bytes (census 2026-11-05 23:16 at 2d7376f084; file's own bytes 5,092)
Code/GameEngine/Source/GameClient/System/ParticleSys.cpp: LINKS  LINKED 5,092 -> 5,092 bytes (census 2026-11-05 23:16 at 2d7376f084; file's own bytes 5,092)
```

The next authoritative real link must confirm the exported name clears.
