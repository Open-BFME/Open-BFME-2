// cl: /MD
// ?Rva005B0E60Get@@YGHPAX@Z @0x005B0E60 63B
// Evidence: AsciiString at +0x88 str pattern plus empty global; strstr needle g_00BBD3F0 plus atoi; caller 0x005B1ACB; ret 4 stdcall.
// g_00BBD3F0: VA 0x00BBD3F0 (.rdata); retail bytes are the string "_".
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *s, const char *sub);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

int __stdcall Rva005B0E60Get(void *obj)
{
	if (!obj)
		return -1;
	char *t = *(char **)((char *)obj + 0x88);
	const char *s = t ? t + 8 : "";
	const char *found = strstr(s, "_");
	if (!found)
		return -1;
	return atoi(found + 1);
}
