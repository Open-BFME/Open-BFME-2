// BFME2FileSystemFacade: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFME2FILESYSTEMFACADE_H
#define CANONICAL_BFME2FILESYSTEMFACADE_H

class BFME2FileSystemFacade
{
public:
	bool doesWideFileExist(const unsigned short *path);
};

#endif // CANONICAL_BFME2FILESYSTEMFACADE_H
