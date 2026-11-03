# WWMath common-profile follow-up, 2026-11-03

Inspected revision: 678d949f99. No source, ledger, compiler override or provider changed.

`./build.sh Code/Libraries/Source/WWVegas/WWLib/wwmath.cpp Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp` passes 8/8 rows, one float reference and one import reference. `find_declared_unmatched.py` reports no unmatched definitions. The supported merge dry run still rejects Random_Float with `bytes`; both original units are census-linked. This is source consolidation, not a link regression.

The new hypothesis was that changing the integer-to-float conversion might avoid the O1 local frame while retaining the seed's 42-byte areApproxEqual. Six ordinary C++ variants (signed/unsigned/volatile integer locals, double conversion, double denominator and reciprocal multiplication) all retain the seven seed rows but fail Random_Float. The imported rand call is correct under MD; native Random_Float uses ESP-relative scratch storage, whereas the O1 reconstruction uses an EBP frame. The disassembly in probe.log is limited to the ledger extent; the longer candidate is truncated there, not claimed exact.

Mixed-profile trials isolate the size/speed preference: O1+Ot recovers Random_Float and the six wrappers, but changes the tolerance comparison's true return from xor/inc to mov-immediate, losing areApproxEqual. Ob2, Oy and G6 retain the size-profile boundary. Op also loses wrapper rows. O2+Og- and O2+Op lose all rows. No new common-profile solution emerged; the existing source and header profiles remain intact. Scripts use tu_skeleton.Verifier's scratch compiler and never write build/match.

The useful next step is a common-profile C++ reconstruction or a separately justified compiler-profile repair, rather than further rand conversion rewrites or O1/O2/Os/Ot permutations. Full probe scripts and output are attached; nothing is a banked matching body or a claimed headline gain.
