# BuildAssistant Module lookup storage

Adopt the registered eight-byte Module base and retain a partial view of the
CastleMemberBehavior lookup result, with the existing ObjectID at +0x18.
This is an observed storage view, not a recovered complete derived hierarchy.

The complete native lookup helper at 0x00395708 calls Object::findModule at
0x00395748 and returns its EAX without adjustment. The complete 43-byte finder
returns the raw module-list entry. isLocationClearOfObjects calls the helper
at 0x003949F6, then reads [EAX+0x18] at 0x00394A00. The proof records these
instructions and both helper bodies. The historical deferral's attribution to
moveObjectsForConstruction does not identify the current field access.

Private before/trial objects retain all 69 rows, nine EXACT EH graphs, and all
222 external code definitions with identical raw bytes and symbolic relocation
targets. Relative includes in the private copies are anchored to the actual
source paths so they use the same coordinate headers. The final strict-current
normal-build object reproduces every retained definition.

Normal verification passes 69/69 rows, one data row, both string literals and
42 float literals. The owning header acceptance tool passes and retires one
Module key. Ordinary preview against ccafe54d1d retains LINKS and 11,630
authored bytes. No new coverage or census gain is claimed; ModuleData and
other independent class contracts are outside this adoption.
