# Shared two-pointer hash lookup result

Base `bc1ac42b01d`. The default picker served all three remaining queued
Rva0041534BIter consumers: particle template replacement, Miles audio file
lookup, and Miles audio event lookup. They now include the existing registered
header instead of defining private typed versions of its eight-byte result.

The header is unchanged. Its node and owner remain opaque pointers. Each
consumer casts only the node at its existing payload dereference to that
consumer's existing node view; particle templates, cached files and counted
audio event information are not claimed to share a payload type. Null checks,
lookup bodies and visibility, constructor use, lifetime operations, flags and
exception specifications are preserved.

`./build.sh` passes **22/22 rows** across all three files, one empty-string
reference and three named imports. The owning `header_adopt_lane.py accept`
passes all three consumers and retires exactly their three header-queue rows.
Its ordinary link guard preserves each source's census-linked bytes. A saved
scoped preview at index `0e4b2640a1` retains **3/3 LINKS, 1,441 -> 1,441 bytes**
(352, 842 and 247 respectively).

All **70 external COMDAT bodies** retain their bytes and symbolic relocation
digests: 67 keep their names, and each source replaces its typed two-pointer
iterator constructor with the header's void-pointer constructor, with an
identical body and extent. No other definition is added or removed. The
adjacent JSON records the comparisons and source hashes; current original
controls and logs are under `build/root-iterator/`.

This retires header debt, not bridges. No source path, row identity, pin, alias,
runtime image or authoritative link measurement is changed by this adoption.
