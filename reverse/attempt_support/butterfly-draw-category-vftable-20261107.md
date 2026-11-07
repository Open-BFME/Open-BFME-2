# ButterflyDraw category vftable

The retail export `??_7ButterflyDrawModuleTemplate@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@` has RVA `0x0081C780`. The folded table has one entry and points to `__purecall` at RVA `0x0003B810`. The current constructor emits an eight-byte secondary table under the local `SecondaryModuleBase` name.

Using the category-six base shape from QuadDraw and StreakDraw with local constructors emits the exact four-byte table and preserves all common vtables. The two code rows and EH pass, and the constructor's DIR32 store resolves to the original RVA. The link preview against census `436fb45367` drops from 115 bytes to zero because the two shared category-six constructors now have incompatible COMDAT copies.

Importing either category constructor, or both, avoids local provider emission but removes the 28-byte scalar deleting destructor owned by this translation unit at `0x001F4471`. That fails native byte verification. All source variants were reverted. The next source trial needs a byte-verified owner for that destructor while the shared category-six constructor providers stay consistent.
