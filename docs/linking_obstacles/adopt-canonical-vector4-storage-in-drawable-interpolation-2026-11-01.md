### Adopt canonical Vector4 storage in Drawable interpolation (2026-11-01)

Drawable interpolation now uses canonical Vector4 row storage with local component copying. Complete normal/frozen/EH/strict checks and owning acceptance preserve the existing native scope and retire one Vector4 key. No current census or full runtime gain is claimed.
[Evidence](../../reverse/attempt_support/drawable-interpolation-vector4-20261101.md).
