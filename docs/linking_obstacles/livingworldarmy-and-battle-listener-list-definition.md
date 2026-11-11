# LivingWorldArmy and LivingWorldBattle listener-list definition

Including both canonical headers in ConsumeGarrisonUnitsFromRTS.cpp exposed
C2011 for Rva00330757Member. LivingWorldBattle.h duplicated its four fields
and its constructor and destructor declarations. Both headers now include
the same definition of the 16-byte listener list.

The adoption gate accepts the army-member dispatcher, unit swapper selection,
garrison settlement and post-battle army visitor. Their 32 functions match;
all four units retain their combined 3,141 bytes at census 1380d51e2c.
This clears the duplicate declaration for those consumers. Five other
LivingWorldArmy consumers remain in the header queue.
