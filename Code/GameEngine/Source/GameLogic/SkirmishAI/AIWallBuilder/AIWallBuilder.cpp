// cl: /MD
// ?Rva004E98B4Get@@YGMH@Z @0x004E98B4 42B free stdcall float Get(int unused) wraps rowed GetGameLogicRandomValueReal 0x00234092 with globals file-line 180 caller 0x004E9DA8
float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
extern float g_00C62800;
// g_00C62800: matched references place it at VA 0xc62800 (retail .rdata value 1.1e+02f).
float g_00C62800 = 1.1e+02f;
extern float g_00C62804;
// g_00C62804: matched references place it at VA 0xc62804 (retail .rdata value 7e+01f).
float g_00C62804 = 7e+01f;
extern char g_00C62808[];

float __stdcall Rva004E98B4Get(int unused)
{
    return GetGameLogicRandomValueReal(g_00C62804, g_00C62800, g_00C62808, 0xB4);
}
