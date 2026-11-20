/* BFME II modernizer loader; tools/modern_blob.py builds it and its blob.
 *
 * Built as dinput8.dll and placed in the game folder. game.dat imports one
 * function from dinput8.dll (DirectInput8Create), so Windows loads this DLL
 * before the game starts. At load it
 *   1. hashes the running game.dat and picks the bfme2-modern-*.blob next to
 *      this DLL that was linked for it;
 *   2. maps the blob's code and data at its link address, or anywhere else
 *      (the blob lists every site to relocate);
 *   3. gives the blob's thread-local variables a home in this DLL's TLS block;
 *   4. checks that every hook site still holds the retail bytes, then writes
 *      the jumps and routes the CRT's WinMain call through the blob's init stub.
 * Until step 4 writes, any failure leaves the game untouched; the writes are
 * made only once every site is writable. game.dat on disk is never modified.
 * DirectInput8Create forwards to the system dinput8.dll.
 * BFME2_MODERN_DISABLE=1 skips everything; bfme2-modern.log records the run.
 * DllMain runs under the loader lock, so this file loads no DLL there: the
 * hash is computed here, not through bcrypt.
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>

/* Home of the blob's thread-local variables: the blob's TLS template is copied
 * here and its SECREL offsets are biased to this block. Initialised so that it
 * sits in the TLS template rather than its zero fill. */
__declspec(thread) __declspec(align(16)) static unsigned char g_tlsHome[256] = { 1 };

static HMODULE g_self;
static HMODULE g_real;
static FILE *g_log;

static void trace(const char *fmt, ...)
{
    va_list args;
    if (!g_log)
        return;
    va_start(args, fmt);
    vfprintf(g_log, fmt, args);
    va_end(args);
    fputc('\n', g_log);
    fflush(g_log);
}

typedef HRESULT(WINAPI *DirectInput8CreateFn)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);

HRESULT WINAPI DirectInput8Create(HINSTANCE inst, DWORD version, REFIID iid, LPVOID *out, LPUNKNOWN outer)
{
    DirectInput8CreateFn fn;
    if (!g_real) {
        wchar_t path[MAX_PATH];
        UINT n = GetSystemDirectoryW(path, MAX_PATH);
        if (n == 0 || n > MAX_PATH - 16)
            return E_FAIL;
        wcscat_s(path, MAX_PATH, L"\\dinput8.dll");
        g_real = LoadLibraryW(path);
    }
    fn = g_real ? (DirectInput8CreateFn)GetProcAddress(g_real, "DirectInput8Create") : 0;
    return fn ? fn(inst, version, iid, out, outer) : E_FAIL;
}

/* ------------------------------------------------------------------ SHA-256 */

static const DWORD K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

#define ROR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

static void sha256Block(DWORD s[8], const BYTE *p)
{
    DWORD w[64], a = s[0], b = s[1], c = s[2], d = s[3], e = s[4], f = s[5], g = s[6], h = s[7], t1, t2;
    int i;
    for (i = 0; i < 16; ++i)
        w[i] = (DWORD)p[4 * i] << 24 | (DWORD)p[4 * i + 1] << 16 | (DWORD)p[4 * i + 2] << 8 | p[4 * i + 3];
    for (i = 16; i < 64; ++i)
        w[i] = w[i - 16] + (ROR(w[i - 15], 7) ^ ROR(w[i - 15], 18) ^ (w[i - 15] >> 3)) + w[i - 7] +
               (ROR(w[i - 2], 17) ^ ROR(w[i - 2], 19) ^ (w[i - 2] >> 10));
    for (i = 0; i < 64; ++i) {
        t1 = h + (ROR(e, 6) ^ ROR(e, 11) ^ ROR(e, 25)) + ((e & f) ^ (~e & g)) + K[i] + w[i];
        t2 = (ROR(a, 2) ^ ROR(a, 13) ^ ROR(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g, g = f, f = e, e = d + t1, d = c, c = b, b = a, a = t1 + t2;
    }
    s[0] += a, s[1] += b, s[2] += c, s[3] += d, s[4] += e, s[5] += f, s[6] += g, s[7] += h;
}

static void sha256(const BYTE *data, DWORD len, BYTE out[32])
{
    DWORD s[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    BYTE tail[128] = {0};
    DWORD full = len & ~63u, rest = len - full, tailLen = rest < 56 ? 64 : 128, i;
    unsigned __int64 bits = (unsigned __int64)len * 8;
    for (i = 0; i < full; i += 64)
        sha256Block(s, data + i);
    memcpy(tail, data + full, rest);
    tail[rest] = 0x80;
    for (i = 0; i < 8; ++i)
        tail[tailLen - 1 - i] = (BYTE)(bits >> (8 * i));
    for (i = 0; i < tailLen; i += 64)
        sha256Block(s, tail + i);
    for (i = 0; i < 32; ++i)
        out[i] = (BYTE)(s[i / 4] >> (24 - 8 * (i % 4)));
}

/* ------------------------------------------------------------------ blob */

#pragma pack(push, 1)
typedef struct {
    char magic[8];
    DWORD version;
    BYTE sha256[32];
    DWORD base, size, runs, tlsIndexVa, tlsStart, tlsLen;
    DWORD entrySite, entryOrig, stubVa;
    DWORD hooks, absCount, relCount, secrelCount;
} BlobHeader;
typedef struct {
    DWORD va, target;
    BYTE orig[5], pad[3];
} BlobHook;
#pragma pack(pop)

static BYTE *readFile(const wchar_t *path, DWORD *size)
{
    HANDLE file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    BYTE *data = 0;
    DWORD got = 0, len;
    if (file == INVALID_HANDLE_VALUE)
        return 0;
    len = GetFileSize(file, 0);
    if (len != INVALID_FILE_SIZE && (data = (BYTE *)HeapAlloc(GetProcessHeap(), 0, len ? len : 1)) != 0 &&
        (!ReadFile(file, data, len, &got, 0) || got != len)) {
        HeapFree(GetProcessHeap(), 0, data);
        data = 0;
    }
    CloseHandle(file);
    *size = got;
    return data;
}

/* This DLL's folder, with a trailing backslash. */
static void selfDir(wchar_t *dir, DWORD cap)
{
    wchar_t *slash;
    GetModuleFileNameW(g_self, dir, cap);
    slash = wcsrchr(dir, L'\\');
    if (slash)
        slash[1] = 0;
}

static BYTE *findBlob(const BYTE gameHash[32], DWORD *blobSize, wchar_t *name, DWORD nameCap)
{
    wchar_t dir[MAX_PATH], pattern[MAX_PATH], path[MAX_PATH];
    WIN32_FIND_DATAW found;
    HANDLE search;
    selfDir(dir, MAX_PATH);
    swprintf_s(pattern, MAX_PATH, L"%sbfme2-modern-*.blob", dir);
    search = FindFirstFileW(pattern, &found);
    if (search == INVALID_HANDLE_VALUE)
        return 0;
    do {
        DWORD size;
        BYTE *blob;
        swprintf_s(path, MAX_PATH, L"%s%s", dir, found.cFileName);
        blob = readFile(path, &size);
        if (blob && size >= sizeof(BlobHeader) && memcmp(blob, "BFME2MDL", 8) == 0 &&
            ((BlobHeader *)blob)->version == 1 && memcmp(((BlobHeader *)blob)->sha256, gameHash, 32) == 0) {
            FindClose(search);
            *blobSize = size;
            wcscpy_s(name, nameCap, found.cFileName);
            return blob;
        }
        if (blob)
            HeapFree(GetProcessHeap(), 0, blob);
    } while (FindNextFileW(search, &found));
    FindClose(search);
    return 0;
}

#define MAX_SITES 512

/* Make every site writable first, then write them all, so a refused page never
 * leaves the game half-patched. */
static int writeAll(DWORD count, const DWORD *va, const BYTE (*bytes)[5], const DWORD *len)
{
    DWORD old[MAX_SITES], i, unused;
    for (i = 0; i < count; ++i) {
        if (!VirtualProtect((void *)va[i], len[i], PAGE_EXECUTE_READWRITE, &old[i])) {
            while (i--)
                VirtualProtect((void *)va[i], len[i], old[i], &unused);
            return 0;
        }
    }
    for (i = 0; i < count; ++i)
        memcpy((void *)va[i], bytes[i], len[i]);
    for (i = 0; i < count; ++i)
        VirtualProtect((void *)va[i], len[i], old[i], &unused);
    FlushInstructionCache(GetCurrentProcess(), 0, 0);
    return 1;
}

static int install(BYTE *blob, DWORD blobSize)
{
    const BlobHeader *h = (const BlobHeader *)blob;
    const BlobHook *hooks = (const BlobHook *)(h + 1);
    const DWORD *absSites = (const DWORD *)(hooks + h->hooks);
    const DWORD *relSites = absSites + h->absCount;
    const DWORD *secrelSites = relSites + h->relCount;
    BYTE *cursor = (BYTE *)(secrelSites + h->secrelCount), *end = blob + blobSize, *mem;
    DWORD delta, tlsBias = 0, i, n;
    static DWORD siteVa[MAX_SITES], siteLen[MAX_SITES];
    static BYTE siteBytes[MAX_SITES][5];

    if (cursor > end || h->hooks + 1 > MAX_SITES)
        return trace("blob is truncated or has too many hooks"), 0;
    for (i = 0; i < h->hooks; ++i)
        if (memcmp((void *)hooks[i].va, hooks[i].orig, 5) != 0)
            return trace("hook %u at %08X does not hold the expected bytes", i, hooks[i].va), 0;
    if (*(DWORD *)h->entrySite != h->entryOrig)
        return trace("entry call at %08X is not the expected one", h->entrySite), 0;

    mem = (BYTE *)VirtualAlloc((void *)h->base, h->size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!mem)
        mem = (BYTE *)VirtualAlloc(0, h->size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!mem)
        return trace("cannot allocate %u bytes", h->size), 0;
    delta = (DWORD)mem - h->base;
    trace("modern section at %08X (linked for %08X)", (DWORD)mem, h->base);

    for (i = 0; i < h->runs; ++i) {
        DWORD off, len;
        if (cursor + 8 > end)
            goto truncated;
        off = ((DWORD *)cursor)[0];
        len = ((DWORD *)cursor)[1];
        cursor += 8;
        if (cursor + len > end || off + len > h->size)
            goto truncated;
        memcpy(mem + off, cursor, len);
        cursor += len;
    }
#define AT(va) ((DWORD *)(mem + ((va) - h->base)))
    for (i = 0; i < h->absCount; ++i)
        *AT(absSites[i]) += delta;
    for (i = 0; i < h->relCount; ++i)
        *AT(relSites[i]) -= delta;

    if (h->tlsLen) {
        IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)((BYTE *)g_self + ((IMAGE_DOS_HEADER *)g_self)->e_lfanew);
        IMAGE_DATA_DIRECTORY *dir = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS];
        IMAGE_TLS_DIRECTORY32 *tls = (IMAGE_TLS_DIRECTORY32 *)((BYTE *)g_self + dir->VirtualAddress);
        DWORD index, old, unused;
        BYTE *templ;
        if (!dir->VirtualAddress || h->tlsLen > sizeof(g_tlsHome)) {
            trace("no TLS home for %u bytes", h->tlsLen);
            goto fail;
        }
        index = *(DWORD *)tls->AddressOfIndex;
        tlsBias = (DWORD)(g_tlsHome - ((BYTE **)__readfsdword(0x2C))[index]);
        templ = (BYTE *)tls->StartAddressOfRawData + tlsBias;
        if (templ + h->tlsLen > (BYTE *)tls->EndAddressOfRawData ||
            !VirtualProtect(templ, h->tlsLen, PAGE_READWRITE, &old)) {
            trace("TLS home is not in a writable initialised template");
            goto fail;
        }
        /* threads created later copy the template; this one has its block */
        memcpy(templ, mem + (h->tlsStart - h->base), h->tlsLen);
        VirtualProtect(templ, h->tlsLen, old, &unused);
        memcpy(g_tlsHome, mem + (h->tlsStart - h->base), h->tlsLen);
        *AT(h->tlsIndexVa) = index;
        for (i = 0; i < h->secrelCount; ++i)
            *AT(secrelSites[i]) += tlsBias;
    }
#undef AT

    for (n = 0; n < h->hooks; ++n) {
        siteVa[n] = hooks[n].va;
        siteLen[n] = 5;
        siteBytes[n][0] = 0xE9;
        *(DWORD *)(siteBytes[n] + 1) = hooks[n].target + delta - (hooks[n].va + 5);
    }
    siteVa[n] = h->entrySite;
    siteLen[n] = 4;
    *(DWORD *)siteBytes[n] = h->stubVa + delta - (h->entrySite + 4);
    if (!writeAll(n + 1, siteVa, (const BYTE (*)[5])siteBytes, siteLen)) {
        trace("a hook site is not writable");
        goto fail;
    }
    trace("installed %u hooks, TLS bias %u", h->hooks, tlsBias);
    return 1;

truncated:
    trace("blob data is truncated");
fail:
    VirtualFree(mem, 0, MEM_RELEASE);
    return 0;
}

static void run(void)
{
    wchar_t game[MAX_PATH], blobName[MAX_PATH];
    BYTE hash[32], *gameFile, *blob;
    DWORD gameSize, blobSize;

    GetModuleFileNameW(0, game, MAX_PATH);
    gameFile = readFile(game, &gameSize);
    if (!gameFile) {
        trace("cannot read the game executable");
        return;
    }
    sha256(gameFile, gameSize, hash);
    HeapFree(GetProcessHeap(), 0, gameFile);
    blob = findBlob(hash, &blobSize, blobName, MAX_PATH);
    if (!blob) {
        trace("no blob for this game executable; the game runs unmodified");
        return;
    }
    trace("blob %ls", blobName);
    install(blob, blobSize);
    HeapFree(GetProcessHeap(), 0, blob);
}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved)
{
    (void)reserved;
    if (reason == DLL_PROCESS_ATTACH) {
        wchar_t path[MAX_PATH];
        char disable[8];
        g_self = inst;
        selfDir(path, MAX_PATH);
        wcscat_s(path, MAX_PATH, L"bfme2-modern.log");
        _wfopen_s(&g_log, path, L"w");
        if (GetEnvironmentVariableA("BFME2_MODERN_DISABLE", disable, sizeof(disable)) && disable[0] == '1')
            trace("BFME2_MODERN_DISABLE=1: the game runs unmodified");
        else
            run();
        if (g_log) {
            fclose(g_log);
            g_log = 0;
        }
    }
    return TRUE;
}
