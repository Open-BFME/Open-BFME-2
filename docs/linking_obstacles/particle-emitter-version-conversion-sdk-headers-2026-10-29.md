### Particle emitter version conversion SDK headers (2026-10-29)

At base `29d5549d56`, the version-conversion unit replaces its two local
Windows macros and both winbase shim includes with the Microsoft windef/winbase
headers. The unused reference win.h include and sweep search roots are removed;
SDK component includes keep WWSaveLoad's persist.h selected. The header auditor
reports the source clean. All three function rows and the parent EH graph remain
exact; all eight external COMDAT digests, eight definitions and eleven undefined
names equal the pre-edit object. Strict current preparation passes, and ordinary
preview preserves LINKS for 778 authored bytes against index `85f6b7f40c`
(2026-10-29 15:08). This clears the local declaration cleanup only. Full affected
consumer verification and census confirmation remain pending; carry the provider
and affected consumers into the next scheduled census. No census gain is claimed.
