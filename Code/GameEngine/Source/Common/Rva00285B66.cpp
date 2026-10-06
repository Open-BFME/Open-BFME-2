// cl: /O1 /arch:SSE
// ?rva00285B66@@YA_NPBX0@Z @0x00285B66 43B converts two ints to floats and calls pinned 0x0030B7C2 evidence caller pointInTrigger 0x002E3A13 and LINK BONUS file
bool __cdecl rva00285B66(const void *point, const void *region);
void __cdecl rva0030B7C2(const void *floats, void *region);

#pragma warning(disable: 4716)
bool __cdecl rva00285B66(const void *point, const void *region)
{
	float f[2];
	f[0] = (float)((const int *)point)[0];
	f[1] = (float)((const int *)point)[1];
	rva0030B7C2(f, (void *)region);
}
