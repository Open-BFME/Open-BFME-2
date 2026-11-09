# Debug::CrashDone dialog flag extern probe

At retail RVA 0x0003AED0 (1,132 bytes including the switch table),
the case 5 and case 7 stores to VA 0x00DE089D come after the
`wsprintfA` argument loads and pushes. The source with the local
static emits those stores at offsets 558 and 635, with their DIR32
operands at 560 and 637. The paired baseline compiled and verified
both debug dialog bodies.

Changing the declaration to reference the existing owner in
`Debug_AssertDone.cpp` retains all 64 relocation sites in number
but moves these two DIR32 operands to offsets 534 and 611. Caching
the line and filename before the external store recovers offsets
560 and 637. The remaining byte mismatch is in the argument-load
register allocation, starting at offset 540, or 542 with line-first
temporaries. An ordering barrier does not recover the original
register sequence. Comma-expression variants still move the stores
early.

No tested source was retained. The existing consolidation prerequisite
in the attempt log remains relevant. Any future extern form must
preserve the operand targets, argument-load instructions, and
complete switch body as well as the store offsets.
