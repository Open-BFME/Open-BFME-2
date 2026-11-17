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

The native rate helper at 0055B9BD is also recovered as calculateRates (128 bytes). Typed RGB keyframes and current/rate colours retain every constructor byte; the helper's complete body and floating references match retail. Paired normal verification passes 7/7 rows.

Primary slot 1 update at 0055BA3D is recovered too (287 bytes): advance RGB weights; test the clock and next key; calculate rates; clamp each component. The same-TU helper preserves retail's xmm1 lifetime across the call. Normal paired verification passes 8/8 rows, with all three floating references exact.

The base keyframe transfer at 0055B96D is recovered as Rva005E95C0::xfer (80 bytes). It uses canonical Xfer to skip light CRC, transfer Version1, eight RGB/frame pairs and the trailing float. Both view declarations are synchronized; paired normal verification passes 9/9 rows.

The derived transfer at 0055BB5C is recovered (82 bytes), together with its compiler-emitted minus-Ch Snapshot adjustment thunk at 003AC9A7 (8 bytes; parent xfer). The measured parent primary table 0081D164 has pure slots 1-3, now declared so the derived transfer occupies both native tables. All 11/11 rows pass normal paired verification.

Primary slot 4 testColor at 0055BBAE now uses the actual keyframe and RGB members (139 bytes). Blend modes 1/2/6 compare the component sum with 0.03; mode 5 compares the product with 0.97. Complete bytes and floating references match; normal paired verification passes 12/12 rows.
