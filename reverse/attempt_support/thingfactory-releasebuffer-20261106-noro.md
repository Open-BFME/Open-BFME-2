# ThingFactory.cpp: AsciiString::releaseBuffer unresolved

2026-11-06; base `36261d4a996`. Status: repair verified locally, awaiting the automated
real link.

## Facts

The real link at `cd7b00691f` lists `?releaseBuffer@AsciiString@@IAEXXZ` against this
unit. Its only AsciiString shim, `reference/shims/nat/Common/AsciiString.h`, declares that
member and leaves it undefined, relying on the pin at `0x00036410`. A pin does not give
the link a definition. Retail's export at that address is
`?releaseBuffer@?$StringBase@D@@AAEXXZ`, rowed in `StringBaseWideReleaseBuffer.cpp`.

## Change

`ThingFactory.cpp` includes the canonical `string_base.h` and defines the member as a
`__forceinline` forward to `StringBase<char>::releaseBuffer`. The compiled calls in
`??1AsciiString` and the hash functor now name the retail export.

The definition sits in the unit, not in the shim. `header_dependents.py` resolves a shim edit
through the path `Common/AsciiString.h` to 5,200 sources, which means the full gate, although
`nat` has this one user.

`?releaseBuffer@AsciiString@@IAEXXZ` is still emitted as a COMDAT in this object. Only its
own `.debug$F` record refers to it. Retail has no such function, so the source carries an
`absent-from-retail` marker. It is not a second body at `0x00036410`, and no row is added.

## Verification

- `./build.sh`: **3/3** rows exact.
- COFF relocations: the object's `.text` calls name only the StringBase export.
- `link_check.py`: LINKS, 60 -> 60 bytes against index `d707d2f53b`. This is a preview,
  not an export-link check.

The pin and the `dup_defs_baseline.tsv` line for the old name stay. They are worth retiring
through their owners' paths. No real-link or runtime result is claimed.
