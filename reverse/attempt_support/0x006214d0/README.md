# Enumeration recovery verification

The 224-byte body at `0x006214D0` is recovered in `Find_Asset.cpp` from
Open-BFME-1's complete `Get_Current_Asset.cpp` donor at
`ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f`.
The normal gate verifies all six rows, including the older unwind row
whose compiler label changed from `$L6338` to `$L7155`; the parent's EH
data independently identifies it. All three EH records are exact.

The hook reports a shadow divergence for
`??R?$equal_to@I@_STL@@QBE_NABI0@Z`.
The previous source and updated source were compiled through
`explain_mismatch.py`, with the original flags and donor inputs.
Reading their normal-tool objects gives the same bytes and no relocations:

`8b4424048b008b4c24082b01f7d81bc040c20800`

Thus this copy is pre-existing; the recovery does not introduce the divergence.
No identity baseline or verifier was changed. The link preview using the
existing index at `6963cc017c` reports that the updated source links, covering
634 ordinary-body bytes. This is an index prediction, not a fresh census or
runtime result. The required placement resweep finds zero new bodies or pins.
