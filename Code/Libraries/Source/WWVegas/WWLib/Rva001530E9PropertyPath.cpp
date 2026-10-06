// cl: /MD /Oi-
// Banked C++ source: reverse/attempts/0x001530e9.cpp at 4615be509614819810bca848d60a47a6921bb6d0.
// Target Ghidra boundary 0x001530E9..0x001531C9, 224B, plain cdecl RET.
// Callers 0x0007FFED/0x00080E30/0x000E1F42/0x0014FE33/0x001F4A90 parse
// a property name then compare its prefix. Target writes char[64], two flags
// at +0x40/+0x41, index at +0x44 and extension pointer at +0x48. It uses
// strchr('.'), strlen, strcmp("[*]"), strrchr('['), sscanf("%d") and strncpy.
// Original class/function/field names remain unknown; view names are structural.
// The local pointer parameter is volatile to preserve retail's suffix spill
// into its dead argument slot. A separate cand value keeps the strcmp push
// in a register. This qualifier describes our codegen, not a target API fact.
// Preserve the target's 64-byte clamp, flags and terminator order verbatim.
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" int __cdecl strcmp(const char *a, const char *b);
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);
extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *s, int c);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, unsigned int n);

struct Rva001530E9Parts {
    char m_name[64];
    bool m_hasStar;
    bool m_hasBracket;
    char m_pad[2];
    int m_index;
    const char *m_ext;
};

void __cdecl Rva001530E9Parse(const char *src, void *volatile dstRaw)
{
    Rva001530E9Parts *dst = (Rva001530E9Parts *)dstRaw;
    dst->m_name[0] = 0;
    dst->m_hasStar = false;
    dst->m_hasBracket = false;
    dst->m_index = 0;
    dst->m_ext = 0;
    if (!src)
        return;
    const char *dot = strchr(src, '.');
    const char *end = dot;
    if (dot) {
        dst->m_ext = dot + 1;
    } else {
        end = src + strlen(src);
        dst->m_ext = 0;
    }
    if ((int)(end - src) > 3) {
        const char *cand = end - 3;
        dstRaw = (void *)cand;
        if (strcmp(cand, "[*]") == 0) {
            end = (const char *)dstRaw;
            dst->m_hasStar = true;
        } else if (*(end - 1) == ']') {
            const char *br = strrchr(src, '[');
            if (br) {
                dst->m_hasBracket = true;
                sscanf(br + 1, "%d", &dst->m_index);
                end = br;
            }
        }
    }
    int maxLen = 64;
    int curLen = (int)(end - src);
    int &useLen = (curLen > maxLen ? maxLen : curLen);
    int copyLen = useLen;
    strncpy(dst->m_name, src, copyLen);
    // copyLen==64 intentionally clears the flag at +0x40.
    reinterpret_cast<char *>(dst)[copyLen] = 0;
}
