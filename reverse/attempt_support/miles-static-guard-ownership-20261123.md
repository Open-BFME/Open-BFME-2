# MilesAudioManager local-static guard ownership

The exact EH graph of the reset at `0x00061C87` places the compiler's 13-byte
rollback at `0x0075E42F`. Its two DIR32 fields at +1 and +8 and both guard
references in the parent resolve to the same four-byte flag at `0x009E1E68`.
The retail unwind entry at `0x009008A0` is the only pointer to the rollback
found by the all-section scan. The donor defined the standalone clearer and
had the only executable reference to its external guard.

The fresh object identifies the reset rollback as `$L63911`. The correction
retracts the standalone row with a tombstone and uses `add_match_batch.py` to
admit the exact emitter at the same address. It removes the duplicate external
storage and retires the three associated address-named occurrences through
`hatch_counters.py`. The original function-local initialization, guard logic,
and EH graph keep their C++ definitions. The donor continues to own the
matched data at `0x009E1E48` and `0x009E1E70`.

The generated data inventory records one definition and four references for
the reset guard. The refresh imports that single row. The generator reported
three missing objects elsewhere in its input set.

## Update guard

The exact EH graph of `update` at `0x00062690` places `$L65393` at
`0x0075E4D4`. Both 13-byte rollback relocations and the two parent operands
resolve to `0x009E1E70`. The retail unwind entry at `0x00900988` is the only
pointer to this rollback found by the all-section scan.

The candidate data row for `?$S2@?M@??update@MilesAudioManager@@UAEXXZ@4IA`
fails the existing `data_rows.verify_row` check with “is not defined once.”
The current object has exactly one such symbol, with STATIC storage, at
offset zero in its own four-byte zero-filled COFF COMDAT. The verifier
selects EXTERNAL definitions and its local-static sizing pattern excludes
the compiler's `?$S` names. The matched data row for the external spelling
and its associated rollback remain pending a verifier that can preserve the
four-byte claim for the compiler-owned symbol.
