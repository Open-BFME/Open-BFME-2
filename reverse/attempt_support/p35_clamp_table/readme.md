# P35: the VP6 clamp table is one writable 768-byte global

Clean room: `reverse/vp6_cleanroom/specs/001b6520.md` plus retail only.

## Target facts (retail)

- InitPostProcessing (0x001B6520) stores `mov [eax+0x00E23100], cl` at 0x001B653B
  for eax = -256..511, writing each offset clamped into 0..255.
- So the table runs from VA 0x00E23000 to 0x00E232FF, with its zero point at 0x00E23100.
  Retail .data spans 0xDA4000..0xE23314, and the bytes there are all zero (the
  zero-filled tail).
- The next global is g_bfmeSharedJX at 0x00E23300.

## Our defect

- FilteringC.cpp defines `const unsigned char g_bfmeClampTable[0x200] = { 0 };`
  (`?g_bfmeClampTable@@3QBEB`, data_rows.csv at 0x00E23100, 512 bytes). It sits
  in read-only .rdata with no storage below the zero point.
- The first store (index -256) faults: a boot access violation at 66 s, receipt
  2026-11-08T042631Z-boot_smoke-3ff11879f1b2.

## Proven fix (scratch, in memory; no ledger edit)

- In FilteringC.cpp, the definition becomes `unsigned char g_bfmeClampTable[0x300];`
  (`?g_bfmeClampTable@@3PAEA`, compiled into .bss).
- In each of the 10 units, the `extern const unsigned char g_bfmeClampTable[];`
  line becomes:

      extern unsigned char g_bfmeClampTable[0x300];	// retail 0x00E23000..0x00E232FF, filled by InitPostProcessing
      #define BFME_CLAMP_ZERO (g_bfmeClampTable + 0x100)	// the zero point, 0x00E23100: indices -256..511

- Every code use of `g_bfmeClampTable` becomes `BFME_CLAMP_ZERO`, including
  InitPostProcessing's `(unsigned char *)g_bfmeClampTable`.
- Verified with `tu_skeleton.Verifier`; every row is exact:

  | Unit | Rows |
  |---|---|
  | FilteringC | 4/4 |
  | DeblockNonFilteredBandNewFilterC | 1/1 |
  | FilterHorizSimple2 | 1/1 |
  | FilterVertGeneric | 1/1 |
  | DeblockNonFilteredBandC | 1/1 |
  | DeblockVerticalEdges | 2/2 |
  | FilterHorizSimple | 1/1 |
  | FilterHorizGeneric | 1/1 |
  | FilterVertSimpleC | 1/1 |
  | InitPostProcessing | 1/1 |

- Every DIR32 site of the new symbol resolves to the single base 0x00E23000
  (in-place addend +0x100).

## Blocked on a route

Recorded as a false reject in `reverse/re_attempts.log` (`?g_bfmeClampTable@@3QBEB`, 0x00A23100):

- `rename.py global --retype` refuses const data, because the old name must end
  in `A` (rename.py:4999-5001). It also keeps the row's address, so it cannot
  move the owner down to 0x00E23000.
- `name_lane.py register-data` at 0x00E23000/768 refuses with "overlapping
  data_rows.csv owner". Its `--type` takes only an identifier.
- `name_globals.py` does not apply.

The route needed: retype a const datum and move a source-owned row to a lower
base, re-keying data_rows and data_ledger to 0x00A23000/768 and absorbing the
unrowed bytes 0x00A23000..0x00A230FF. Consumers re-address by in-place addend,
as above.
