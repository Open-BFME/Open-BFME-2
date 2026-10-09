// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) char * __cdecl strrchr(const char *text, int character);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *a, const char *b, unsigned int n);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);

// ?bfmePathLeafAfterMarker@@YAPBDPBD@Z
const char *__cdecl bfmePathLeafAfterMarker(const char *path)
{
	if (path == 0)
		return 0;

	const char *marker = strrchr(path, '~');
	if (marker != 0)
		return marker + 1;

	marker = strrchr(path, '/');
	if (marker != 0)
		return marker + 1;

	return path;
}

// ?SkipLevelN@AptUtils@@YAPBDPBD@Z, retail 0x00412845: WorldBuilder's
// AptUtils::SkipLevelN (AptUtils.cpp:531), the same "_level" prefix skip.
namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
const char *__cdecl AptUtils::SkipLevelN(const char *path)
{
	if (path == 0)
		return 0;
	if (strncmp(path, "_level", 6) != 0)
		goto ret_path;
	path += 6;
	char c = *path;
	if (c == 0)
		goto ret_path;
loop:
	if (c == '/' || c == '.')
		goto found;
	path++;
	c = *path;
	if (c != 0)
		goto loop;
found:
	if (*path == 0)
		goto ret_path;
	path++;
ret_path:
	return path;
}

// ?LevelIndexFromTarget@AptUtils@@YAHPBD@Z, retail 0x004128BB: WorldBuilder's
// AptUtils::LevelIndexFromTarget (AptUtils.cpp:656), the same "_level%d" scan.
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }
int __cdecl AptUtils::LevelIndexFromTarget(const char *path)
{
	if (path == 0)
		return -1;
	int level;
	if (sscanf(path, "_level%d", &level) == 1)
		return level;
	return -1;
}
