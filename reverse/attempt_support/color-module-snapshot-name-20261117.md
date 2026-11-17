# Colour-module Snapshot name recovery

The served Rva005EA590 copy constructor stores primary table 0081D17C and
Snapshot table 0081D194. Native Snapshot slot 2 is the six-byte getter at
003AC9A1 returning the exact literal `DefaultParticleModule<CAT_COLOR>` at
0081C96C. The new GetSnapshotName override recovers that slot without changing
the constructor or introducing a private Snapshot copy.

Both Rva005E95C0 views now give the existing pure name slot its measured return
type and constness. Its own getter at 003ADDC7 is claimed by another contributor
and remains unrecovered here. The derived override occupies the existing
Snapshot slot directly; scratch COFF inspection shows no adjusting thunk and
no change to either primary or +8 interface table.

Private verification passes 3/3 rows in each producer. Normal build.sh over
both files passes 6/6 rows, including the exact name string. This is one
recovered virtual body, not a completed bridge cohort or a fresh real-link
result. Remaining destructor, transfer and primary slots still need recovery.
