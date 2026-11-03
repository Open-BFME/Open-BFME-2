### Drawable serializer canonical Module data access (2026-10-30)

Cleared for `Drawable_xferDrawableModules.cpp`: use canonical Module's protected
data getter through an access view, then the unchanged ModuleData tag getter.
Native module+4/data+4 chains, all three rows/EH and six retained definitions
remain exact under the one access-name normalization. The old seven-byte tag
forwarder is removed. All indexed touching objects for it and the last public
data-getter copy are inspected directly: Drawable, GiantBird and Foundation
have no remaining definition or reference to either removed name, and keep the
identical protected getter. The owning acceptance tool retires the remaining
Module key. Preview preserves LINKS/409 bytes against `ccafe54d1d`; no census
or whole-image loss clearance is claimed.
[Raw consumer audit and native fields](../../reverse/attempt_support/module-drawable-xfer-data-access-20261030/README.md).
