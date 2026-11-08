# AutoDeposit canonical Thing include, 2026-11-08

AutoDepositUpdateCtor.cpp now explicitly includes the canonical Thing header.
The served queue item referred to a former m_08 view; the current file has
already moved its game-frame read to GameLogicObjectLookupView and has no
private Thing body. Owning-tool acceptance retires this one header debt with
the explicit include in place. No function body, name, flag or path changes.

Normal verification passes both rows, the file is unfrozen, and strict
preparation passes. All 62 retained code COMDAT facts, relocation bindings,
flags and policies agree. All three externally named data allocations and
all undefined references remain identical. The sole added definition is the
34-byte compiler vector-constructor iterator: its entire bytes match native
0x00001423, and its flags/policy match the existing ATL provider. No provider
is removed. EH verification finds no EH-bearing row. Current-object preview
conserves LINKS/144 authored bytes at d171e84869.

This clears the stated header debt only. The unchanged table allocations are
not a new full-table or image proof, and the bounded preview is not a census
or runtime result. No new coverage, class-layout recovery or table bridge
retirement is claimed.

Published as a2b72d5896; first attempt landed in 40.7 seconds. Required
row/scoped-DIR32/data checks pass. Broader audit remains INCONCLUSIVE: index
d171e84869 versus outgoing base e834581c00d638d23b569831da5d7be01f7c999f;
Common/AICowerState_onEnter.cpp lacks a current receipt. No wider closure
or runtime claim is made.
