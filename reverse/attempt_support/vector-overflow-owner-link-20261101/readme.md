# Vector overflow provider prerequisite, 2026-11-01

Base: 64b496da64e27041f286d26c84c5adb51ef678ac. Model: GPT-6. Lane R,
30-minute body budget; implementation investigation stopped after 20 minutes.
No production source, row, pin, or hatch changed. No newly matched unique bytes,
no linking clearance and no census credit.

## Current target facts

The fresh official preview against index 12902e9e1b (2026-10-31 23:18)
still rejects StlSweepW4Rva00584405.cpp (280 authored bytes). Both the selected
COMDAT and its call require vector<Rva00584405Element>::_M_insert_overflow.
Its existing pin is 0x0058431D. The native 189-byte body is already rowed in
HordeMeleeSwarm.cpp under Rva0058431D::rva0058431D with an int/Arg5 ABI view.
The previously missing 49-byte copy constructor and 50-byte copy-backward twin
are already admitted; do not repeat their recovery. The other unit in the
preview, stlport_pod28_vector_resize_value.cpp, already LINKS 73 bytes with no
change here; that is not this attempt's gain.

The existing body's Arg5 puts its tag at EBP+0x1B, in the padding of the last
four-byte argument slot. Native code reserves eight local bytes. These are
instruction facts, not proof of the original C++ tag spelling or element name.
The native record fields and the existing helper calls are retained as views;
no canonical semantic identity is claimed from their 28-byte stride.

## Private member-specialization trials

A genuine member specialization, plus a trailing explicit instantiation to
make MSVC emit it, compiles. Named Tag and __false_type locals score
0.8811399102538343: twelve local bytes and the tag at EBP-1. Simply applying
noinline does not emit the symbol. In emission-trials.json its failed out-of-line
entry retains the previous Scorer.last byte fields; these are stale and are not
a second emitted body. Empty value-initialized temporaries introduce
zero stores and worsen the score to 0.6755973443871532. Short-lived empty tags
with an empty user constructor avoid those stores but get distinct addresses
EBP-1, EBP+0x17 and EBP+0x1B, still with twelve local bytes.

The final standalone candidate also calls the existing ledger spelling
Rva00030830FreeAllocation, pinned at 0x00030830, instead of accidentally resolving
plain C free to the CRT thunk. No pin was added. It scores
0.8929676511954994, unresolved=false, exact=false. banked-recheck.json records
the resolved 189-byte comparison. The candidate's full body exceeds that window;
the missing native tail byte in this window must not be called a match.
The empty tag constructor is a private code-generation experiment, not recovered
original source. Two namespace-free trials did not compile; no bytes are
attributed to them. Private trials used the official permute.Scorer and their
own objects, with explicit /O1 /G7 /arch:SSE to reproduce Code defaults.

## Remaining boundary

The correct member identity alone does not recover the native temporary/stack
layout. Do not read bool-parameter padding in C++ or add a wrapper/alias to hide
that gap. Keep the existing matched owner until a clean exact provider exists.
If recovered, re-admit the real member in the same owner with the required
separate retraction, suppress the consumer's wrong template emitter with a
specialization declaration, verify all owner rows and both affected units, then
run the normal consumer audit. The old provider is already real-rowed, so
--replace-rva is not a shortcut around its retraction. Linking remains pending.

The attempted compiler-output diagnostic was rejected by automatic review;
it was not executed. All recorded comparisons came from the permitted private
Scorer workflow. The production tree was unchanged throughout.

The commit hook correctly refused the first partial stash in reverse/attempts/:
the RVA already has real matched C++. That uncommitted partial verdict was
retracted through re_log.py void, and the same single investigation is recorded
as blocked. candidate.cpp.txt here preserves the alternative body; this handoff is
not a matching queue entry. No gate was changed or bypassed.

The source-placement hook also requires diagnostic source in handoffs to use
patches or .cpp.txt (docs/structural.md). The preserved candidate uses that
documented .cpp.txt evidence format; it is not a new production source.
