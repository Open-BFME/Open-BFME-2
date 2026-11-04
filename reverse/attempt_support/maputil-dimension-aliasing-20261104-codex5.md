# MapUtil dimension ownership follow-up, 2026-11-04

Revision inspected: e14a51cef5. This attempt changes no source, row, provider or
protected register. It does not retire the supply/tech baseline keys.

The existing `MapUtil.cpp` retirement boundary remains the duplicate dimension
definitions at 0x009FF124/128. The ledger's external definitions and the seed's
private statics cannot be unified by changing only linkage: external dimensions
may alias the output of `getExtent` (0x003000B5, 65 bytes), changing the compiler's
load/store schedule. Prior evidence includes
[the earlier dimension-sharing attempt](maputil-dimension-sharing-20261028-codexb.md)
and the existing log entries for this address.

New source trials were made only in the seed and reverted:

- External declarations plus explicit high-bound store ordering still change
  SSE register allocation.
- Caching both integer dimensions before the stores hoists the integer loads;
  the resulting conversion/store order still differs from retail.
- VC7 rejects `__restrict` with C4235, so it provides no usable alias contract.

After restoration, `./build.sh Code/GameEngine/Source/GameClient/MapUtil.cpp`
passes all 19 code rows. No nonmatching reconstruction remains under `Code/`.
The next step is unchanged: approved TU consolidation or a byte-exact C++
reconstruction that preserves retail's alias-sensitive schedule. This attempt
does not establish new TU-placement evidence or alter the linking obstacle.
