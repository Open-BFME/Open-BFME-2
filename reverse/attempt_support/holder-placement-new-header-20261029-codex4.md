# Holder placement construction: use the Microsoft header

Base: `d17e3dcdeb82`, 2026-10-29. The Microsoft-header picker claimed
`Code/GameEngine/Source/Common/Rva004F6B69Construct.cpp`; the copy-constructor
provider `Rva004F6966CopyCtor.cpp` was also claimed before editing.

Replace the local placement-new implementation with the toolchain's `<new>`.
Declare the called copy constructor nonthrowing in both units, including its
definition. Its entire matched 32-byte body at RVA `0x004F6966` only copies
the pointer and two integers and conditionally increments the pointed-to
reference count; it has no calls or explicit exception path. The 18-byte
placement constructor at RVA `0x004F6B69` retains its null check and direct
call to that same provider. No original type identity or TU placement is
inferred from these bodies.

The first direct `<new>` substitution, with the old copy-constructor
declaration, failed byte verification by adding placement-delete unwind
machinery. That trial was restored. The paired nonthrowing declarations let
the real header preserve both complete retail bodies without changing flags,
adding a local replacement, or suppressing header declarations.

Verification:

- Before and after, `./build.sh` verifies both rows (50 bytes), with no string,
  float or import findings. Both declared-unmatched checks pass.
- Strict `link_check.py --prepare-current` passes for both explicit providers.
- Every COMDAT name, digest, size and retail verdict, plus all strong,
  undefined and weak external facts from `link_census.object_facts`, compares
  equal before and after for both objects.
- Both ordinary link previews retain LINKS: 18 and 32 authored bytes, against
  index `85f6b7f40c` (2026-10-29 15:08). These are existing bytes, with no
  census gain claimed.
- The Microsoft-header auditor reports both sources clean. Its scoped
  `refresh_queue` removes the construct source's one finding while preserving
  unrelated records. Neither source has a header, data-identity, code-identity
  or hatch register entry.

The staged-tree outgoing batch audit remains INCONCLUSIVE: the index predates
the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry these providers and their affected consumers into the next
scheduled census. Full consumer closure and runtime verification remain
pending; the scoped previews do not establish either.
