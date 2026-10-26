// Shared backing storage for the key-record tree at retail RVA 0x00A02E50.
// Its existing initializer 0x007AF8CD constructs the tree and registers
// cleanup 0x007B80F1. Keep this storage trivial: no second initializer.
// The STLport tree view is 12 bytes; its first two words are header and count.
#ifndef LARGE_GROUP_AUDIO_KEY_TREE_STORAGE_H
#define LARGE_GROUP_AUDIO_KEY_TREE_STORAGE_H

extern unsigned int g_lgaKeyRecords[3];

#endif // LARGE_GROUP_AUDIO_KEY_TREE_STORAGE_H
