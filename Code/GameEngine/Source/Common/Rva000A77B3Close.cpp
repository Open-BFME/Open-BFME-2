// cl: /MD
// platformsdk
//
// ?rva000A77B3@AudioFileCache@@QAEXXZ, retail 0x000A77B3, 38 bytes.
// Closes the thread handle at +0x48 after waiting on it, sets byte at +0x4C.
// Imports WaitForSingleObject and CloseHandle from KERNEL32 (IAT). No EH.
// Callers at 0x0006101B (~MilesAudioManager, on m_audioFileCache) and
// 0x000A7D0F (~AudioFileCache, on its own this); +0x48/+0x4C are the cache's
// loader thread handle and quit flag.

#include <windows.h>

#include "../../../GameEngineDevice/Include/MilesAudioDevice/AudioFileCache.h"

void AudioFileCache::rva000A77B3()
{
	void *handle = field48;
	field4C = true;
	if (handle != 0)
	{
		WaitForSingleObject(handle, 0xFFFFFFFF);
		CloseHandle(field48);
		field48 = 0;
	}
}
