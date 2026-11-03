### Use canonical Matrix3D storage in matrix comparisons (2026-11-02)

This source removes its private Matrix3D definition. Direct access to the existing canonical rows preserves native comparison bodies and relocation targets; bounded predictions remain separate from full current linking and runtime proof.
[Evidence](../../reverse/attempt_support/matrix-comparison-matrix3d-20261102-1509.md).
