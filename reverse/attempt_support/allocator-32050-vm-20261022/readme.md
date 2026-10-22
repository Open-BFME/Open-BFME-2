# 0x32050: helper, type and lifetime probes; argument-slot erratum

BFME 2 inputs: a649b275f7; BFME 1 pin 37c3022de1ab944c7ffe536440d637dc8199091c.
Compiler: pinned MSVC 13.10.3077, cl.exe SHA256
`2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515`.
Fresh compilation runs in a Debian 12 x86_64 QEMU guest using Wine 8. Normal
byte-gate code is unchanged. The source share is read-only, cache=none; objects
are compiled to guest temporary files and copied back without modification.

## Corrected retail evidence

The latest handoff `../00032050_general_allocator.md` incorrectly concludes that
retail never reads the flags/requested-size argument. At entry ESP=S, the two
arguments are S+4 and S+8. After ESI/EDI/EBX saves and `push ebx`, ESP=S-16;
`mov [esp+14h],eax` stores the masked size to S+4, the dead first argument slot.
The called 0x31F90 ends with `ret 4` at 0x32040. Afterwards ESP=S-12, so the final
`mov edx,[esp+14h]` reads S+8, the original second argument. The bank's
`size >= flags + 0x10` is correct. Do not replace it with `size >= size + 0x10`.

The native boundary remains 0x32050..0x320DC, 140 bytes, RET8. All ten other
bodies in the served 147-line d_0002dfe2.asm file already have C++ owners.
The 0x31F90 provider is now a 179-byte matched body in memory_pool.cpp.

## Trials and result

The unchanged bank reproduces 140 bytes and fitness 0.89754 using the repository
Scorer. Its first difference is +0x46: the size<0x10 adjustment is scheduled late.
`results.txt` preserves all measurements. COFF extents were checked separately
in the new chain/type/lifetime probes; target-sized slicing is not extent proof.

- Latest CheckCount helper, corrected to compare against flags: standalone
  adds remain 141B with this/lock allocation exchanged. Forceinline and a barrier
  after the call are inert; single-expression helper chains regress.
- Eighteen helper/plain-term mixes with a barrier after the third or fourth
  adjustment: 143..168B, none improves the bank.
- Empty asm scheduling boundaries emit no instructions but produce 141B with
  wrong allocation/order. ALIGN 1 variants are rejected by the compiler. None
  belongs in production.
- /Oa, /Ow, /Ob1: bank unchanged at 140B, helper unchanged at 141B.
  /Og- regresses to 190B/336B.
- Unsigned, byte, bool, 64-bit and reference helper returns: no improvement.
  A 64-bit bank accumulator is 167B.
- Counter objects with implicit/user copy constructors, by-reference/by-value
  addition, and barrier placement: 141..168B. Qualified returns and six-argument
  sum helpers are also worse. These test object lifetime/evaluation structure
  rather than replaying the older arithmetic-permutation sweep.

No Code/, ledger, pin or verifier edit was made. Retain the existing bank.
The unresolved prerequisite is still a real compiler allocation/scheduling
explanation; repeating the same term/flag/lifetime families is not supported.

A read-only compile/placement search of the pinned BFME 1 clean memory-pool
allocator donor also returned zero bodies and zero pins. Its allocator layout
is not evidence for BFME 2's PPMalloc class.
