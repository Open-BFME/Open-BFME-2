# Siege target canonical Module storage

Replace the private 0x20-byte Module with canonical Module8 and an explicitly
partial derived storage view. The unchanged SiegeDockInterface remains at
module+0x20. Target instructions at 0x0029CD7F/0x0029CD8E/0x0029CD95 establish
the findModule call, receiver adjustment and slot1 call. The existing 43-byte
findModule owner at 0x0028B6D6 returns the raw module pointer. Keep the lookup
and interface prototypes; no complete module identity or hierarchy is claimed.

The five source rows and parent EH remain EXACT. Private before/trial and final
strict-current objects preserve all ten external code definitions, all loadable
definitions, every non-debug section, relocations and undefined names. SafeSEH
COFF indices are compared by handler name. The owning Module acceptance tool
retires one header key; ordinary preview retains LINKS/451 bytes against
ccafe54d1d. No census gain, new implementation, table, thunk, pin or path move.
Native facts and object fingerprints are in proof.json; no donor facts are used.
