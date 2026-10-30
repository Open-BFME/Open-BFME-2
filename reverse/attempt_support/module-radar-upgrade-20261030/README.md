# Radar upgrade Module view

Replace the private sixteen-byte Module class with the registered eight-byte
Module plus a partial storage base. The existing secondary upgrade interface
still starts at +0x10. This records the required receiver layout, not a complete
recovery of the original inheritance hierarchy.

Target evidence: the complete Object caller at 0x0028B8A6 calls findModule at
0x0028B8F5, retains that result in ESI, adjusts it by +0x10 at 0x0028B900, and
calls the returned interface's slot zero. It loads the module-data pointer at
module+4 and DisableProof at data+0x118. The complete 43-byte findModule owner
at 0x0028B6D6 returns the unadjusted +0x244 array entry. The evidence JSON
records both native bodies.

Before/trial private objects retain all three rows, the exact parent EH graph,
and both external code definitions with identical raw bytes and symbolic
relocations. The final normal-build object reproduces those definitions.
The normal build also verifies the string reference. The owning Module header
acceptance tool passes and retires one key. Ordinary preview against ccafe54d1d
retains LINKS and 195 authored bytes; no census gain is claimed.
