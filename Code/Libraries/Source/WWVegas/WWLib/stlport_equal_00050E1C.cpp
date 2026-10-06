// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Rva00050E1CEqual@@YG_NPBX0@Z @0x00050E1C 41B null-safe dword-at-+8 equality; callers 0x53FD2 0x54BC3 0x54C93 hashtable equals unblocks 3
bool __stdcall Rva00050E1CEqual(const void *a, const void *b)
{
	if (a == 0 || b == 0)
		return a == b;
	return !(*(const unsigned int *)((const char *)a + 8) - *(const unsigned int *)((const char *)b + 8));
}
