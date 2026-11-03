### WWMath random-helper consolidation boundary (2026-11-02)

The approved WWLib/wwmath.cpp Random_Float donor and WWMath/wwmath.cpp seed verify separately but not under the same tested compiler profile. O1 changes the native26B random helper's import/frame; O2 preserves it but grows areApproxEqual42B to44B. MD, Oy, Os and four source-control-flow trials establish the remaining boundary; no source or provider changed and both units remain census-linked. [Trial matrix and handoff](../../reverse/attempt_support/wwmath-tu-profile-20261102/README.md). WWMathInit remains mixed and outside this attempted merge.

2026-11-03: conversion and mixed-profile trials isolate the Os/Ot tradeoff; further integer/float rand rewrites do not recover a common profile. Existing sources still pass 8/8; next step remains a common-profile reconstruction. [Follow-up evidence](../../reverse/attempt_support/wwmath-common-profile-20261103/README.md).
