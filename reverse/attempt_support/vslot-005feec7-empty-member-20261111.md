# Battle-prompt clip empty member

Retail constructor `0x005FED2A` installs the 24-byte vtable at VA
`0x00C7A448`. Its zero-based slots 3 and 4 point to `0x005FEEC7` and
`0x005FEEE6`. Each passes ECX and a pushed index to `0x0047A69C`, at call
sites `0x005FEED0` and `0x005FEEEF`. The target is `C2 04 00` with no
relocations, the same retail fold as `FXParticleSystem::EmissionVelocityInfo::DoXfer`.
The member spelling follows the existing canonical declaration and call
sites. The fold alone does not establish the original class or member name.

An empty member defined in the caller TU made MSVC omit both calls even with
`__declspec(noinline)`. Scoped verification refused those two caller rows
and the trial was reverted. Defining the member in the existing clip
constructor unit preserves the calls and matches all four provider rows and
all ten caller rows. The published link index plus the current objects resolves
the missing symbol in the local preview.
