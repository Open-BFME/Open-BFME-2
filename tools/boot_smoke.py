#!/usr/bin/env python3
"""Build, link and launch the boot image in a sandbox; classify how far startup gets.

  python3 tools/boot_smoke.py --game-dir SANDBOX [--retail] [--timeout 90] [--base 0x10000000]

SANDBOX is a copy of the game's data files (never the install itself: this tool
writes game.dat into it). The image under test is `tools/boot_image.py link` at
`--base` (or retail's own game.dat with --retail, the control run). It runs
under a minimal Win32 debugger with `-win` and is killed at the timeout.

Outcome (build/boot/smoke.json, also printed):
  link-error            the link failed or the image check found a difference
  crash-at-<row>        an unhandled (second-chance) exception; the address is
                        mapped back to retail's RVA and the ledger row holding it
  exit-<code>           the process exited by itself before the timeout
  no-window             alive at the timeout without a visible window
  reached-menu          alive at the timeout with the main menu's button bar
                        visible (a screenshot is saved; compare with --retail)
  crash-dialog          alive at the timeout behind the game's own crash box ("Game
                        crash", "Error hit", "Assertion failed", "Exception"); its text
                        and DebugStackwalk addresses, mapped, are in `crash.dialog`
  no-picture            alive with a window, but no picture was captured or it is
                        black (under Wine the client area comes from the Xvfb root,
                        since PrintWindow is black there)
  title-splash          alive showing the game's title splash: nothing past it is proven
  loading-screen        alive with another picture, but the main menu's button bar
                        is not up yet (an intro movie, or the shell map before the menu)
  hang-on-<picture>     one of the pictures above with the main thread spinning: about
                        a sample a second over the run's last 30 seconds, all inside
                        SPIN_WINDOW bytes of the game's own image (main_thread_span). How
                        far it ran is the picture; it is not still getting there. A run
                        too short to sample that long never gets this label, and neither
                        does a thread parked outside the image: retail waits in a system
                        call for 29 s at a time while its intro movies play. Failed reads
                        or a hole in the good ones withhold it too: at most SPIN_MAX_FAILURES,
                        at most SPIN_MAX_GAP seconds apart. A heuristic: a long copy in the
                        image can satisfy it, and a wider spin, a spin in a system DLL or a
                        deadlock in a wait keep the picture's label
  profile-redirect-failed  the appdata lie could not be installed (nothing ran)
  profile-changed       the owner's profile or HKCU EA keys changed

The focus lie (on unless --no-focus-lie): BFME2 stops loading while its window
lacks focus (WndProc's WM_ACTIVATEAPP(FALSE) arm sets isWinMainActive and
TheGameEngine->setIsActive(false)). One breakpoint on that arm, located by its
bytes in the image under test, rewrites wParam 0 to 1, so a run need not keep
the focus (`focus_lie` in the outcome counts hits and rewrites). --defocus N
minimises the window N s after launch to prove it.

The owner's profile: the game writes options, saves and replays under
SHGetSpecialFolderPathW(CSIDL_APPDATA) + "My Battle for Middle-earth II Files".
Every run points that import at a stub answering --appdata (default
GAME_DIR/../appdata; its profile is seeded with a fixed Options.ini) at
game.dat's loader breakpoint, before any game code runs. There is no opt-out:
if the redirect cannot be installed the run is killed there
(`profile-redirect-failed`), and an --appdata inside the real AppData is
refused. The real profile (names, sizes, mtimes, Options.ini SHA-256) and
HKCU's Electronic Arts keys are also snapshotted before and after; any change
fails the run (`profile-changed`, which another program writing the profile
during the run also triggers).

--guard DIR (repeatable) snapshots DIR's file names, sizes and mtimes before
and after the run and fails the outcome (`guard-violation`) if anything changed,
so a run that could reach a real install is proven not to have written there.
The image is scaffolding unless boot_image overlays authored code; no outcome
is progress by itself.

--overlay SET (as `boot_image.py link --overlay`) links authored units in. A
crash names the authored unit it is in, if any. --probes puts a one-shot
breakpoint on each unit's first byte once the loader has relocated the image,
so the outcome says which authored code actually ran (`authored_executed`);
every hit is a debugger round trip, so a large overlay boots slower probed.
--bisect: when the overlay does not reach the menu, halve it deterministically
(with --probes only units the failing run executed are candidates; each half
is run alone)
down to the rows that fail by themselves, and write them to
build/boot/boot_queue.json, which tools/repair_queue.py serves (`boot-crash`).

--real-image EXE runs a linked image (exit_link's exit.exe with exit.map and
image_receipt.json beside it) instead of building one: tools/real_image.py checks the
hashes against the receipt and judges the image in place of boot_image.image_ok
(`image-refused` when it may not run), an int3 the harness did not plant is a fault,
and a crash names the map symbol, the stubbed name when it is a stub (through the
caller for a shared stub body) and the retail row. --rebase BASE runs a relocated copy.
The outcome JSON carries a `receipt` section the game queue completes (contract.md).

--relayout / --own-data build the image with tools/boot_relayout.py instead
(units moved out of retail's order, their old ranges int3; data from our
objects). With --relayout an int3 the debugger did not plant is a fault
(--int3-faults): without it the debugger would step through a moved unit's
int3-filled old range into whatever follows.
"""
import argparse
import bisect
import collections
import csv
import ctypes
import ctypes.wintypes as wt
import functools
import json
import math
import os
import queue
import re
import shutil
import struct
import sys
import threading
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402
import real_image  # noqa: E402

OUT = ROOT / "build" / "boot"
DEBUG_PROCESS = 0x1
DBG_CONTINUE, DBG_NOT_HANDLED = 0x00010002, 0x80010001
EXCEPTION, CREATE_PROCESS, EXIT_PROCESS, LOAD_DLL = 1, 3, 5, 6
BREAKPOINTS = {0x80000003, 0x4000001F}          # int3, WOW64 int3


@functools.cache
def under_wine():
    """Wine's ntdll exports wine_get_version; Windows' does not."""
    try:
        return hasattr(ctypes.WinDLL("ntdll"), "wine_get_version")
    except (AttributeError, OSError):
        return False


# A process's loader breakpoint: imports bound, no game code run. Windows raises
# it from the 32-bit ntdll as the WOW64 int3, after a native int3 that comes
# before the imports are bound. Wine's WoW64 raises only a plain int3, with the
# imports already bound (measured: game.dat's SHGetSpecialFolderPathW slot holds
# shell32's address there), so under Wine a process's first int3 is the one.
LOADER_BREAKPOINTS = {0x4000001F, 0x80000003} if sys.platform == "win32" and under_wine() else {0x4000001F}


def alloc32(k, hproc, size):
    """RWX memory in the 32-bit game the stubs can address (32-bit pointers to it).
    Windows places a WOW64 process's allocations below 4 GiB; Wine's WoW64 may
    hand a 64-bit debugger an address above it, so then ask for one low down."""
    k.VirtualAllocEx.restype = ctypes.c_void_p
    k.VirtualAllocEx.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD, wt.DWORD]
    k.VirtualFreeEx.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD]
    mem = k.VirtualAllocEx(hproc, None, size, 0x3000, 0x40)
    if mem and mem + size <= 1 << 32:
        return mem
    if mem:
        k.VirtualFreeEx(hproc, mem, 0, 0x8000)              # MEM_RELEASE
    for at in range(0x7F000000, 0x01000000, -0x10000):      # below the 2 GiB user limit
        mem = k.VirtualAllocEx(hproc, at, size, 0x3000, 0x40)
        if mem:
            return mem
    return None


# share of green pixels in the band of the main menu's button bar (menu_bar):
# 0.74-0.75 with the buttons up (also over a white, unrendered shell map),
# 0.13 on the loading splash, under 0.01 on the shell map before the buttons
MENU_BAR = 0.4
QUIET = {0x406D1388, 0xE06D7363, 0x40010006}    # thread naming, C++ throw, OutputDebugString


class STARTUPINFO(ctypes.Structure):
    _fields_ = [("cb", wt.DWORD), ("r", wt.LPWSTR), ("d", wt.LPWSTR), ("t", wt.LPWSTR)] + \
               [(n, wt.DWORD) for n in ("x", "y", "w", "h", "cx", "cy", "fill", "flags")] + \
               [("show", wt.WORD), ("cb2", wt.WORD), ("r2", ctypes.c_void_p),
                ("hin", wt.HANDLE), ("hout", wt.HANDLE), ("herr", wt.HANDLE)]


class PROCESS_INFORMATION(ctypes.Structure):
    _fields_ = [("hProcess", wt.HANDLE), ("hThread", wt.HANDLE), ("pid", wt.DWORD), ("tid", wt.DWORD)]


def k32():
    k = ctypes.WinDLL("kernel32", use_last_error=True)
    k.GetCurrentProcess.argtypes = []
    k.GetCurrentProcess.restype = wt.HANDLE
    k.DuplicateHandle.argtypes = [wt.HANDLE, wt.HANDLE, wt.HANDLE, ctypes.POINTER(wt.HANDLE),
                                  wt.DWORD, wt.BOOL, wt.DWORD]
    k.DuplicateHandle.restype = wt.BOOL
    k.WaitForDebugEvent.argtypes = [ctypes.c_void_p, wt.DWORD]
    k.WaitForDebugEvent.restype = wt.BOOL
    k.ContinueDebugEvent.argtypes = [wt.DWORD, wt.DWORD, wt.DWORD]
    k.ContinueDebugEvent.restype = wt.BOOL
    k.CloseHandle.argtypes = [wt.HANDLE]
    k.CloseHandle.restype = wt.BOOL
    k.TerminateProcess.argtypes = [wt.HANDLE, wt.UINT]
    k.TerminateProcess.restype = wt.BOOL
    k.WaitForSingleObject.argtypes = [wt.HANDLE, wt.DWORD]
    k.WaitForSingleObject.restype = wt.DWORD
    k.CreateProcessW.argtypes = [wt.LPCWSTR, wt.LPWSTR, ctypes.c_void_p, ctypes.c_void_p, wt.BOOL, wt.DWORD,
                                 ctypes.c_void_p, wt.LPCWSTR, ctypes.c_void_p, ctypes.c_void_p]
    k.CreateProcessW.restype = wt.BOOL
    return k


def windows_of(pid):
    """[(title, (l, t, r, b))] of the visible top-level windows of pid."""
    u = ctypes.WinDLL("user32")
    found = []

    @ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
    def cb(h, _):
        p = wt.DWORD()
        u.GetWindowThreadProcessId(h, ctypes.byref(p))
        if p.value == pid and u.IsWindowVisible(h):
            rc = wt.RECT()
            u.GetWindowRect(h, ctypes.byref(rc))
            buf = ctypes.create_unicode_buffer(256)
            u.GetWindowTextW(h, buf, 256)
            found.append((buf.value, (rc.left, rc.top, rc.right, rc.bottom), h))
        return True
    u.EnumWindows(cb, 0)
    return found


# The game's own fatal boxes: Debug::CrashDone and Debug::AssertDone call
# MessageBoxA(0, text, "Game crash") with the crash message and DebugStackwalk's
# addresses; "Error hit" and "Assertion failed" are the same family, "Exception" the
# release crash dialog. One of these up at the timeout is a crash, not a slow load.
CRASH_DIALOGS = ("game crash", "error hit", "assertion failed", "exception")
HEX_WORD = re.compile(r"(?<![0-9A-Za-z])(?:0[xX])?([0-9A-Fa-f]{8})(?![0-9A-Za-z])")


def dialog_text(win):
    """What a dialog says: its static controls' text in order (buttons left out), else
    every child's text."""
    kids = win.get("children") or []
    statics = [c["text"] for c in kids if c.get("class", "").lower() == "static" and c.get("text")]
    return "\n".join(statics or [c["text"] for c in kids if c.get("text")])


def dialog_addresses(text, limit=48):
    """The 8-digit hex words in a dialog's text (DebugStackwalk's addresses), in order,
    each once; values below 0x10000 are not addresses."""
    out = []
    for m in HEX_WORD.finditer(text or ""):
        v = int(m.group(1), 16)
        if v >= 0x10000 and v not in out:
            out.append(v)
    return out[:limit]


def crash_dialog(dialogs):
    """{"title", "text", "addresses"} of the first of the game's windows titled as a crash
    box (CRASH_DIALOGS), else None. Pure: `dialogs` is window_texts()'s list."""
    for w in dialogs or []:
        if (w.get("title") or "").strip().lower() in CRASH_DIALOGS:
            text = dialog_text(w)
            return {"title": w["title"], "text": text[:8000], "addresses": dialog_addresses(text)}
    return None


def window_texts(pid, limit=4096):
    """[{"title", "class", "rect", "children": [{"class", "id", "text"}]}] of pid's visible
    top-level windows. Text comes from InternalGetWindowText, which never sends a message,
    so a game thread stopped in the debugger or a modal box cannot hang the read."""
    u = ctypes.WinDLL("user32")
    u.InternalGetWindowText.argtypes = [wt.HWND, wt.LPWSTR, ctypes.c_int]
    u.GetClassNameW.argtypes = [wt.HWND, wt.LPWSTR, ctypes.c_int]
    u.GetDlgCtrlID.argtypes = [wt.HWND]

    def text(h):
        buf = ctypes.create_unicode_buffer(limit)
        u.InternalGetWindowText(h, buf, limit)
        return buf.value

    def cls(h):
        buf = ctypes.create_unicode_buffer(256)
        u.GetClassNameW(h, buf, 256)
        return buf.value
    tops = []

    @ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
    def top(h, _):
        p = wt.DWORD()
        u.GetWindowThreadProcessId(h, ctypes.byref(p))
        if p.value == pid and u.IsWindowVisible(h):
            tops.append(h)
        return True
    u.EnumWindows(top, 0)
    out = []
    for h in tops:
        kids = []

        @ctypes.WINFUNCTYPE(wt.BOOL, wt.HWND, wt.LPARAM)
        def child(c, _):
            kids.append({"class": cls(c), "id": u.GetDlgCtrlID(c) & 0xFFFF, "text": text(c)})
            return len(kids) < 64
        u.EnumChildWindows(h, child, 0)
        rc = wt.RECT()
        u.GetWindowRect(h, ctypes.byref(rc))
        out.append({"title": text(h), "class": cls(h), "rect": [rc.left, rc.top, rc.right, rc.bottom],
                    "children": kids})
    return out


def read_memory(k, hproc, va, n):
    buf, got = ctypes.create_string_buffer(n), ctypes.c_size_t()
    ok = k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(va), buf, n, ctypes.byref(got))
    return buf.raw[:got.value] if ok else b""


def thrown_type(read, throw_info):
    """The decorated name (".?AV...@@") of the first catchable type of the MSVC x86
    ThrowInfo at throw_info (ThrowInfo+12 -> CatchableTypeArray, +4 -> CatchableType,
    +4 -> TypeDescriptor, +8 -> name), or None. `read(va, n)` gives bytes, b"" if unreadable."""
    try:
        cta = struct.unpack("<I", read(throw_info + 12, 4))[0]
        ct0 = struct.unpack("<I", read(cta + 4, 4))[0]
        td = struct.unpack("<I", read(ct0 + 4, 4))[0]
        name = read(td + 8, 256).split(b"\0")[0].decode("latin-1")
    except (struct.error, TypeError):
        return None
    return name or None


def quiet_exception(k, hproc, tid, exc, addr, params):
    """A compact record of a first-chance exception the run lets the game handle: a C++
    throw's thrown type and stack, or an OutputDebugString's text."""
    out = {"code": hex(exc), "address": hex(addr)}
    read = lambda va, n: read_memory(k, hproc, va, n)            # noqa: E731
    if exc == 0x40010006 and len(params) >= 2:                   # OutputDebugStringA: length, text
        out["text"] = read(params[1], max(0, min(params[0], 1024))).split(b"\0")[0].decode("latin-1")
    elif exc == 0xE06D7363 and len(params) >= 3:                 # C++ throw: magic, object, ThrowInfo
        out.update(magic=hex(params[0]), object=hex(params[1]), throw_info=hex(params[2]),
                   type=thrown_type(read, params[2]))
        out["stack"] = (stack_words(k, hproc, tid, n=128) or {}).get("words", [])
    return out


def main_stack(k, hproc, hthread, tid):
    """The game's main thread's registers and stack, read with the thread suspended
    (at the timeout it may sit in a modal box's message loop), or None if it could not be suspended.
    Raises ThreadNotResumed when it stays suspended: the reads after this one decide the label."""
    return while_suspended(k, hthread, lambda: stack_words(k, hproc, tid, n=1024))[0]


def snapshot(d):
    out = {}
    for root, _, files in os.walk(d):
        for f in files:
            p = os.path.join(root, f)
            try:
                st = os.stat(p)
            except OSError:
                continue
            out[p] = (st.st_size, st.st_mtime_ns)
    return out


def xp_version_lie(k, hproc, base, exe):
    """Point the image's GetVersion / GetVersionExA IAT slots at stubs reporting
    Windows XP SP3 (5.1.2600, the version-lie part of the WINXPSP3 layer the
    installs use; that layer itself needs elevation here). Without it retail
    crashes in CPUDetectClass::Init_Compact_Log formatting an unknown OS."""
    import pefile
    pe = pefile.PE(str(exe))
    slots = {}
    for d in pe.DIRECTORY_ENTRY_IMPORT:
        for imp in d.imports:
            if d.dll.lower() == b"kernel32.dll" and imp.name in (b"GetVersion", b"GetVersionExA"):
                slots[imp.name] = imp.address - pe.OPTIONAL_HEADER.ImageBase + base
    mem = alloc32(k, hproc, 0x1000)
    info = struct.pack("<IIIII", 156, 5, 1, 2600, 2) + b"Service Pack 3".ljust(128, bytes(1)) \
        + struct.pack("<HHHBB", 3, 0, 0x100, 1, 0)
    get_version = bytes.fromhex("B8 05 01 28 0A C3")                      # mov eax, 0x0A280105; ret
    get_version_ex = (bytes.fromhex("56 57 8B7C240C 8B0F 81F99C000000 7605 B99C000000 83E904 83C704 BE")
                      + struct.pack("<I", mem + 0x104)                     # esi = template + 4
                      + bytes.fromhex("F3A4 5F 5E B801000000 C20400"))     # rep movsb; return TRUE
    blob = get_version.ljust(0x40, b"\xCC") + get_version_ex.ljust(0xC0, b"\xCC") + info
    k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(mem), blob, len(blob), None)
    for name, va in slots.items():
        old = wt.DWORD()
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(va), 4, 0x04, ctypes.byref(old))
        ptr = struct.pack("<I", mem if name == b"GetVersion" else mem + 0x40)
        k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(va), ptr, 4, None)
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(va), 4, old.value, ctypes.byref(old))
    return sorted(n.decode() for n in slots)


# --------------------------------------------------------------------------- the owner's profile
# The game keeps options, saves, replays and map previews under
# SHGetSpecialFolderPathW(CSIDL_APPDATA) + PROFILE_LEAF (retail has one
# CSIDL_APPDATA call site, 0x237C33). Every run redirects that call to a
# sandbox profile (the appdata lie) and refuses to start if it cannot; the real
# profile is snapshotted around the run as a second line of defence.
PROFILE_LEAF = "My Battle for Middle-earth II Files"
CSIDL_APPDATA, CSIDL_MYPICTURES = 0x1A, 0x27
# Without Options.ini the game benchmarks the CPU on its first start
# (bench_with_confidence), which faults in AllocateMemory under the debugger and
# exits 1; the sandbox profile is seeded with these fixed, low-cost options.
SANDBOX_OPTIONS = """AudioLOD = Low
FixedStaticGameLOD = Low
FlashTutorial = 0
HasGotOnline = yes
HasSeenLogoMovies = yes
IdealStaticGameLOD = Low
IsThreadedLoad = yes
Resolution = 1024 768
StaticGameLOD = Low
TimesInGame = 1
"""


class RedirectError(RuntimeError):
    """The appdata lie could not be put in place: the run must not go on."""


def real_appdata():
    """The owner's roaming AppData (where the game would put its profile)."""
    return Path(os.environ.get("APPDATA") or Path.home() / "AppData" / "Roaming")


def real_profile():
    return real_appdata() / PROFILE_LEAF


def _norm(p):
    return os.path.normcase(os.path.abspath(str(p))).rstrip("\\/")


def check_sandbox_appdata(appdata, real=None):
    """Refuse a sandbox root that is the real AppData or lies inside it: the game
    would then be handed the owner's profile (or a folder beside it)."""
    a, r = _norm(appdata), _norm(real if real is not None else real_appdata())
    if a == r or a.startswith(r + os.sep):
        raise RedirectError(f"sandbox appdata {appdata} is (inside) the real AppData {r}")
    return Path(appdata)


def prepare_sandbox_profile(appdata, real=None):
    """Check the sandbox root, create its profile and seed Options.ini (only if
    missing). Returns the sandbox profile directory."""
    prof = check_sandbox_appdata(appdata, real) / PROFILE_LEAF
    prof.mkdir(parents=True, exist_ok=True)
    if not (prof / "Options.ini").exists():
        (prof / "Options.ini").write_text(SANDBOX_OPTIONS)
    return prof


def appdata_stub(mem, orig, appdata):
    """The SHGetSpecialFolderPathW replacement written at `mem` in the game:
    CSIDL_APPDATA and CSIDL_MYPICTURES (low byte of csidl, so the CREATE flag is
    ignored) copy `appdata` into pszPath and return TRUE; every other folder
    jumps to the real function (`orig`, kept at mem+0x80)."""
    path = (str(appdata).rstrip("\\") + "\0").encode("utf-16-le")
    if len(path) > 2 * 260:
        raise RedirectError(f"sandbox appdata path longer than MAX_PATH: {appdata}")
    code = (bytes.fromhex("8B44240C 25FF000000")                       # mov eax, [esp+0Ch] (csidl); and eax, 0FFh
            + b"\x83\xF8" + bytes([CSIDL_APPDATA]) + b"\x74\x0B"        # cmp eax, 1Ah; je redirect
            + b"\x83\xF8" + bytes([CSIDL_MYPICTURES]) + b"\x74\x06"     # cmp eax, 27h; je redirect
            + b"\xFF\x25" + struct.pack("<I", mem + 0x80)               # jmp [orig]
            + bytes.fromhex("56 57 8B7C2410 BE") + struct.pack("<I", mem + 0x100)   # edi = pszPath; esi = path
            + b"\xB9" + struct.pack("<I", len(path))                    # ecx = bytes
            + bytes.fromhex("F3A4 5F 5E B801000000 C21000"))            # rep movsb; return TRUE (stdcall, 16)
    return code.ljust(0x80, b"\xCC") + struct.pack("<I", orig).ljust(0x80, b"\0") + path


def install_appdata_lie(k, hproc, base, exe, appdata):
    """At the game's WOW64 loader breakpoint (imports bound, no game code run):
    point the image's SHGetSpecialFolderPathW IAT slot at appdata_stub, read
    both back, and raise RedirectError on any failure."""
    import pefile
    appdata = check_sandbox_appdata(Path(appdata).resolve())
    pe = pefile.PE(str(exe), fast_load=True)
    pe.parse_data_directories([1])
    slots = [imp.address - pe.OPTIONAL_HEADER.ImageBase + base for d in getattr(pe, "DIRECTORY_ENTRY_IMPORT", [])
             for imp in d.imports if d.dll.lower() == b"shell32.dll" and imp.name == b"SHGetSpecialFolderPathW"]
    pe.close()
    if len(slots) != 1:
        raise RedirectError(f"{len(slots)} SHGetSpecialFolderPathW import slots in {exe}")
    slot = slots[0]

    def read(va, n):
        buf, got = ctypes.create_string_buffer(n), ctypes.c_size_t()
        ok = k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(va), buf, n, ctypes.byref(got))
        return buf.raw[:got.value] if ok else b""
    orig = read(slot, 4)
    mem = alloc32(k, hproc, 0x1000)
    if len(orig) != 4 or not mem:
        raise RedirectError(f"cannot read the import slot {slot:#x} or allocate the stub")
    blob = appdata_stub(mem, struct.unpack("<I", orig)[0], appdata)
    old = wt.DWORD()
    k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(mem), blob, len(blob), None)
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(slot), 4, 0x04, ctypes.byref(old))
    k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(slot), struct.pack("<I", mem), 4, None)
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(slot), 4, old.value, ctypes.byref(old))
    if read(mem, len(blob)) != blob or read(slot, 4) != struct.pack("<I", mem):
        raise RedirectError(f"the redirect did not stick (slot {slot:#x})")
    return {"slot": hex(slot), "appdata": str(appdata)}


def profile_snapshot(d):
    """{relative path: (size, mtime_ns)} plus the SHA-256 of Options.ini."""
    import hashlib
    d = Path(d)
    files = {os.path.relpath(p, d): v for p, v in snapshot(d).items()} if d.exists() else {}
    opt = d / "Options.ini"
    sha = hashlib.sha256(opt.read_bytes()).hexdigest() if opt.exists() else None
    return {"files": files, "options_sha256": sha}


def profile_diff(before, after):
    """Changed, added or removed files (and an Options.ini content change)."""
    a, b = before["files"], after["files"]
    changed = sorted(set(a) ^ set(b) | {p for p in a if p in b and a[p] != b[p]})
    if before["options_sha256"] != after["options_sha256"]:
        changed.append("Options.ini (content)")
    return changed


def registry_snapshot(path=r"Software\Electronic Arts"):
    """{key\\value: repr(data)} of everything under HKCU\\path (read only)."""
    import winreg
    out = {}

    def walk(sub):
        try:
            key = winreg.OpenKey(winreg.HKEY_CURRENT_USER, sub)
        except OSError:
            return
        with key:
            i = 0
            while True:
                try:
                    n, v, _ = winreg.EnumValue(key, i)
                except OSError:
                    break
                out[f"{sub}\\{n}"] = repr(v)
                i += 1
            i = 0
            while True:
                try:
                    s = winreg.EnumKey(key, i)
                except OSError:
                    break
                walk(f"{sub}\\{s}")
                i += 1
    walk(path)
    return out


class ProfileGuard:
    """Snapshot the owner's profile and HKCU's EA keys before a run; `check()`
    afterwards returns the report and whether anything changed."""

    def __init__(self, profile=None):
        self.profile = Path(profile) if profile is not None else real_profile()
        self.before, self.hkcu = profile_snapshot(self.profile), registry_snapshot()

    def check(self):
        changed = profile_diff(self.before, profile_snapshot(self.profile))
        hk, old = registry_snapshot(), self.hkcu
        hk_changed = sorted(set(hk) ^ set(old) | {x for x in hk if x in old and hk[x] != old[x]})
        report = {"dir": str(self.profile), "files": len(self.before["files"]),
                  "options_sha256": self.before["options_sha256"], "changed": changed[:20],
                  "hkcu_values": len(old), "hkcu_changed": hk_changed[:20]}
        return report, bool(changed or hk_changed)


def set_probes(k, hproc, base, rvas):
    """One-shot int3 at each RVA (authored unit starts): {address: original byte}."""
    out = {}
    for rva in sorted(rvas):
        a, b, old = base + rva, ctypes.create_string_buffer(1), wt.DWORD()
        if not k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(a), b, 1, None):
            continue
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(a), 1, 0x40, ctypes.byref(old))
        if k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(a), b"\xCC", 1, None):
            out[a] = b.raw
        k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(a), 1, old.value, ctypes.byref(old))
    k.FlushInstructionCache(wt.HANDLE(hproc), None, 0)
    return out


def clear_probe(k, hproc, tid, addr, byte):
    """Put the original byte back and re-run the instruction the probe replaced."""
    old = wt.DWORD()
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(addr), 1, 0x40, ctypes.byref(old))
    k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(addr), byte, 1, None)
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(addr), 1, old.value, ctypes.byref(old))
    k.FlushInstructionCache(wt.HANDLE(hproc), ctypes.c_void_p(addr), 1)
    k.OpenThread.restype = wt.HANDLE
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10001                       # WOW64_CONTEXT_CONTROL
    if h and k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        ctx.eip = addr
        k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
    if h:
        k.CloseHandle(h)


# WndProc's WM_ACTIVATEAPP arm (WinMain.cpp; retail 0x0019A5): `cmp ebx, 1Ch; jne
# default`, then `cmp dword [ebp+10h], 0; setne al; cmp al, [isWinMainActive]`. The
# breakpoint sits on the `cmp [ebp+10h]` (wParam), so only this message costs a
# debug event; the isWinMainActive operand is relocated, so it is a wildcard.
FOCUS_ARM = re.compile(rb"\x83\xFB\x1C\x0F\x85....(\x83\x7D\x10\x00)\x0F\x95\xC0\x3A\x05", re.DOTALL)
SINGLE_STEP = {0x80000004, 0x4000001E}          # single step, WOW64 single step


def focus_arm_rva(exe):
    """RVA of the WM_ACTIVATEAPP arm's wParam test in `exe` (retail or a boot image,
    found by its bytes), or None unless exactly one place matches."""
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    hits = []
    for sec in pe.sections:
        if sec.Characteristics & 0x20000000:          # executable
            hits += [sec.VirtualAddress + m.start(1) for m in FOCUS_ARM.finditer(sec.get_data())]
    pe.close()
    return hits[0] if len(hits) == 1 else None


def write_code(k, hproc, addr, data):
    old = wt.DWORD()
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(addr), len(data), 0x40, ctypes.byref(old))
    k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(addr), data, len(data), None)
    k.VirtualProtectEx(wt.HANDLE(hproc), ctypes.c_void_p(addr), len(data), old.value, ctypes.byref(old))
    k.FlushInstructionCache(wt.HANDLE(hproc), ctypes.c_void_p(addr), len(data))


def focus_lie(k, hproc, tid, addr, byte):
    """At the WM_ACTIVATEAPP arm a deactivation (wParam 0) becomes an activation, so
    the engine never stops for focus loss. The original instruction then runs under
    the trap flag; the breakpoint goes back on the single step. True if rewritten."""
    k.OpenThread.restype = wt.HANDLE
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10001                       # WOW64_CONTEXT_CONTROL: ebp, eip, eflags, esp
    rewritten = False
    if h and k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        slot, buf = ctx.ebp + 0x10, ctypes.create_string_buffer(4)
        if k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(slot), buf, 4, None) and buf.raw == bytes(4):
            rewritten = bool(k.WriteProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(slot), struct.pack("<I", 1), 4,
                                                  None))
        write_code(k, hproc, addr, byte)
        ctx.eip, ctx.eflags = addr, ctx.eflags | 0x100
        k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
    if h:
        k.CloseHandle(h)
    return rewritten


def main_window(pid):
    wins = [w for w in windows_of(pid) if w[1][2] - w[1][0] > 100 and w[1][3] - w[1][1] > 100]
    return max(wins, key=lambda w: (w[1][2] - w[1][0]) * (w[1][3] - w[1][1]))[2] if wins else None


def run(launcher, game_dir, args, timeout, version_lie=True, probes=(), focus_rva=None, defocus_at=None,
        int3_faults=False, *, appdata, shots_at=()):
    """Start `launcher` (retail's lotrbfme2.exe, which hands game.dat its start-up
    token; game.dat started directly exits 0 at once) under a debugger that
    follows children; the child whose image is game.dat is the one classified.
    `probes` (RVAs) get one-shot breakpoints once the loader has relocated the
    image; the ones reached are listed in res["probes_hit"]. `focus_rva`: the
    WM_ACTIVATEAPP arm, where a deactivation is rewritten to an activation (the
    focus lie). `defocus_at` (seconds): minimise the game window then (Windows
    activates another one), and show it again unactivated 15 s before the end.
    `appdata` (required): the sandbox AppData root the game is given instead of
    the owner's; if the redirect cannot be installed at game.dat's loader
    breakpoint, before any game code runs, every process is killed and the
    outcome is `profile-redirect-failed`. With `int3_faults` an int3 in the game
    after its loader breakpoint that is neither a probe nor the focus arm is passed
    to the game as an exception (an int3 filler was executed)."""
    check_sandbox_appdata(appdata)
    k = k32()
    k.QueryFullProcessImageNameW.argtypes = [wt.HANDLE, wt.DWORD, wt.LPWSTR, ctypes.POINTER(wt.DWORD)]
    si, pi = STARTUPINFO(), PROCESS_INFORMATION()
    si.cb = ctypes.sizeof(si)
    cmd = ctypes.create_unicode_buffer(f'"{launcher}" {args}')
    if not k.CreateProcessW(None, cmd, None, None, False, DEBUG_PROCESS, None, str(game_dir),
                            ctypes.byref(si), ctypes.byref(pi)):
        raise SystemExit(f"boot_smoke: CreateProcess failed ({ctypes.get_last_error()})")
    ev = ctypes.create_string_buffer(256)
    procs = {}                                        # pid -> (hProcess, image path, base)
    res = {"first_chance": [], "first_chance_count": 0, "quiet": [], "processes": [], "probes_hit": [],
           "debugger_errors": [], "cleanup": {"terminate": [], "exit_events": [], "wait": [],
                                               "close": [], "uncertain_handles": []}}
    armed, focus, stepping = {}, {}, {}
    exited, termination_requested = set(), set()
    continuation_failed = False
    game_handle = None

    def debugger_error(operation, error):
        res["debugger_errors"].append({"operation": operation, "error": error})
        res["outcome"] = "debugger-error"

    def close_handle(handle, label):
        if handle and handle != (1 << (ctypes.sizeof(wt.HANDLE) * 8)) - 1:
            if not k.CloseHandle(wt.HANDLE(handle)):
                res["cleanup"]["uncertain_handles"].append({"label": label, "handle": handle})
                debugger_error(f"CloseHandle:{label}", ctypes.get_last_error())

    if focus_rva is not None:
        res["focus_lie"] = {"rva": hex(focus_rva), "hits": 0, "rewritten": 0}
    u = ctypes.WinDLL("user32")
    u.ShowWindowAsync.argtypes = [wt.HWND, ctypes.c_int]   # never wait on a thread stopped at a breakpoint

    def wait_ran_out():
        """After WaitForDebugEvent returned no event: whether it only ran out; anything else is recorded."""
        error = ctypes.get_last_error()
        if error != 121:
            debugger_error("WaitForDebugEvent", error)
        return error == 121

    t0 = time.time()
    next_spin_sample = 0.0
    shots = TimedShots(shots_at, t0)
    try:
        # The event boundary. A run ends at the first look that finds nothing pending at or past the deadline,
        # so what is already delivered is served before every sample and before calling the run out of time:
        # losing a real crash is the worse error. An event that arrives just past the deadline, during a sample or a
        # wait that returned late, therefore counts, deliberately: nothing about a real fault is favourable to the
        # build. Only two things are not recorded, and cleanup continues them: an event after that look, and
        # with a stream of events holding every look busy, whatever is still queued EVENT_GRACE past the deadline.
        while True:
            left = timeout - (time.time() - t0)
            if left <= -EVENT_GRACE:
                res["outcome"] = "timeout" if "pid" in res else "no-game-process"
                break
            if defocus_at is not None and "pid" in res:
                d = res.setdefault("defocus", {})
                if "minimised" not in d and time.time() - t0 >= defocus_at:
                    d["hwnd"] = main_window(res["pid"])
                    if d["hwnd"]:
                        u.ShowWindowAsync(d["hwnd"], 6)     # SW_MINIMIZE: another window is activated
                        d["minimised"] = round(time.time() - t0, 1)
                if d.get("hwnd") and "shown" not in d and left <= 15:
                    u.ShowWindowAsync(d["hwnd"], 4)         # SW_SHOWNOACTIVATE: back for the capture, unfocused
                    d["shown"] = round(time.time() - t0, 1)
            if not k.WaitForDebugEvent(ev, 0):
                if not wait_ran_out():
                    break
                left = timeout - (time.time() - t0)
                if left <= 0:
                    res["outcome"] = "timeout" if "pid" in res else "no-game-process"
                    break
                if "pid" in res:
                    shots.ask(res["pid"], time.time() - t0)
                if "main_thread" in res and left <= SPIN_SPAN and time.time() >= next_spin_sample:
                    next_spin_sample = time.time() + SPIN_EVERY
                    try:
                        eip = thread_eip(k, res["main_thread"])
                    except ThreadNotResumed as failure:
                        debugger_error("ResumeThread:spin-sample", failure.error)
                        break
                    if eip is None:
                        res["spin_sample_failures"] = res.get("spin_sample_failures", 0) + 1
                    else:
                        res.setdefault("spin_samples", []).append((round(time.time() - t0, 1), eip))
                    continue                            # the sample took time: look again before anything else
                if not k.WaitForDebugEvent(ev, int(min(left, 1.0) * 1000)):
                    if not wait_ran_out():
                        break
                    continue
            code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
            status = DBG_CONTINUE
            stop_after_continue = False
            game = pid == res.get("pid")
            if code == CREATE_PROCESS:
                close_handle(int.from_bytes(ev.raw[16:24], "little"), f"create-process:{pid}")
                h = int.from_bytes(ev.raw[24:32], "little")
                buf, n = ctypes.create_unicode_buffer(1024), wt.DWORD(1024)
                k.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(n))
                procs[pid] = (h, buf.value, int.from_bytes(ev.raw[40:48], "little"))
                if Path(buf.value).name.lower() == "game.dat":
                    res["main_thread"] = int.from_bytes(ev.raw[32:40], "little")
                    res["main_tid"] = tid
                res["processes"].append(Path(buf.value).name)
                if Path(buf.value).name.lower() == "game.dat":
                    if "pid" in res:
                        debugger_error("CREATE_PROCESS:multiple-game", pid)
                    else:
                        res.update(pid=pid, image_base=procs[pid][2], started=round(time.time() - t0, 1))
                        duplicated = wt.HANDLE()
                        current = k.GetCurrentProcess()
                        if not k.DuplicateHandle(current, wt.HANDLE(h), current, ctypes.byref(duplicated),
                                                 0, False, 0x2) or not duplicated.value:
                            debugger_error("DuplicateHandle:game-process", ctypes.get_last_error())
                        else:
                            game_handle = duplicated.value
            elif code == LOAD_DLL:
                h = int.from_bytes(ev.raw[16:24], "little")
                close_handle(h, f"load-dll:{pid}")
            elif code == EXIT_PROCESS and game:
                res.update(outcome="exit", exit_code=int.from_bytes(ev.raw[16:20], "little"),
                           seconds=round(time.time() - t0, 1))
                stop_after_continue = True
            elif code == EXCEPTION:
                exc = int.from_bytes(ev.raw[16:20], "little")
                addr = int.from_bytes(ev.raw[32:40], "little")
                first = int.from_bytes(ev.raw[168:172], "little")
                nparam = int.from_bytes(ev.raw[40:44], "little")
                params = [int.from_bytes(ev.raw[48 + 8 * i:56 + 8 * i], "little") for i in range(min(nparam, 3))]
                info = params[:2]
                if not first and game:
                    status = DBG_NOT_HANDLED
                    res.update(outcome="crash", code=hex(exc), address=res.get("fault", addr), info=info,
                               seconds=round(time.time() - t0, 1))
                    res.setdefault("stack", stack_words(k, procs[pid][0], tid))
                    stop_after_continue = True
                else:
                    hit = next((a for a in (addr, addr - 1) if a in armed), None) if exc in BREAKPOINTS and game else None
                    at_focus = next((a for a in (addr, addr - 1) if a in focus), None) \
                        if exc in BREAKPOINTS and game else None
                    stray = (int3_faults and game and hit is None and at_focus is None and exc in BREAKPOINTS
                             and len(procs.get(pid, ())) > 3)
                    handled = at_focus is not None or (exc in SINGLE_STEP and game and tid in stepping)
                    if at_focus is not None:
                        res["focus_lie"]["hits"] += 1
                        res["focus_lie"]["rewritten"] += focus_lie(k, procs[pid][0], tid, at_focus, focus[at_focus])
                        stepping[tid] = at_focus
                    elif handled:
                        write_code(k, procs[pid][0], stepping.pop(tid), b"\xCC")
                    elif hit is not None:
                        clear_probe(k, procs[pid][0], tid, hit, armed.pop(hit))
                        res["probes_hit"].append(hit - procs[pid][2])
                    elif exc in LOADER_BREAKPOINTS and pid in procs and len(procs[pid]) == 3:
                        h, path, base = procs[pid]
                        if game:                            # first, so a failure leaves nothing running
                            try:
                                res["appdata_lie"] = install_appdata_lie(k, h, base, path, appdata)
                            except (RedirectError, OSError, ImportError) as e:
                                res.update(outcome="profile-redirect-failed", redirect_error=str(e))
                                for hp, *_ in procs.values():   # killed before the thread is let go
                                    if not k.TerminateProcess(hp, 1):
                                        debugger_error("TerminateProcess:profile-redirect", ctypes.get_last_error())
                                    else:
                                        termination_requested.add(hp)
                                if res["outcome"] == "debugger-error":
                                    continuation_failed = True
                                    break
                                if not k.ContinueDebugEvent(pid, tid, DBG_CONTINUE):
                                    debugger_error("ContinueDebugEvent:profile-redirect", ctypes.get_last_error())
                                    continuation_failed = True
                                break
                        procs[pid] += (xp_version_lie(k, h, base, path) if version_lie else [],)
                        res.setdefault("version_lie", {})[Path(path).name] = procs[pid][3]
                        if game and probes:
                            armed.update(set_probes(k, h, base, probes))
                            res["probes_armed"] = len(armed)
                        if game and focus_rva is not None:
                            focus.update(set_probes(k, h, base, [focus_rva]))
                            res["focus_lie"]["armed"] = bool(focus)
                    if (exc not in BREAKPOINTS and not handled) or stray:
                        status = DBG_NOT_HANDLED
                    if status == DBG_NOT_HANDLED and first and game:
                        res["first_chance_count"] += 1
                        if exc in QUIET and exc != 0x406D1388 and len(res["quiet"]) < 20:
                            res["quiet"].append(quiet_exception(k, procs[pid][0], tid, exc, addr, params))
                        if exc not in QUIET and len(res["first_chance"]) < 10:
                            res["first_chance"].append([hex(exc), addr, info])
                            if (exc == 0xC0000005 or stray) and "stack" not in res:   # the fault, not the rethrow
                                res["stack"] = stack_words(k, procs[pid][0], tid)
                                res["fault"] = addr
            if not k.ContinueDebugEvent(pid, tid, status):
                debugger_error("ContinueDebugEvent", ctypes.get_last_error())
                continuation_failed = True
                break
            if code == EXIT_PROCESS:
                exited.add(pid)
            if stop_after_continue or res.get("outcome") == "debugger-error":
                break
        if res["outcome"] == "timeout":
            try:
                res["main_eips"] = sample_eips(k, res["main_thread"])
            except ThreadNotResumed as failure:
                debugger_error("ResumeThread:final-sample", failure.error)
            try:
                res["main_stack"] = main_stack(k, procs[res["pid"]][0], res["main_thread"], res.get("main_tid"))
            except ThreadNotResumed as failure:
                debugger_error("ResumeThread:main-stack", failure.error)
            res["windows"] = [(t, r) for t, r, _ in windows_of(res["pid"])]
            res["dialogs"] = window_texts(res["pid"])
            res["screenshot"] = screenshot(res["pid"])
    finally:
        if shots.asked:
            res["timed_shots"] = shots.finish()
        cleanup_targets = {pid: h for pid, (h, *_rest) in procs.items() if pid not in exited}
        if pi.pid not in cleanup_targets:
            if pi.pid not in exited:
                cleanup_targets[pi.pid] = pi.hProcess
        for pid, handle in cleanup_targets.items():
            terminated = handle in termination_requested
            if handle not in termination_requested:
                terminated = bool(k.TerminateProcess(wt.HANDLE(handle), 1))
                if not terminated:
                    debugger_error(f"TerminateProcess:{pid}", ctypes.get_last_error())
            res["cleanup"]["terminate"].append({"pid": pid, "ok": terminated})
        deadline = time.monotonic() + 5.0
        pending = set(cleanup_targets)
        if continuation_failed:
            debugger_error("cleanup:uncontinued-event", "previous continuation failed or was withheld")
        else:
            while pending and time.monotonic() < deadline:
                remaining = max(1, min(250, int((deadline - time.monotonic()) * 1000)))
                if not k.WaitForDebugEvent(ev, remaining):
                    error = ctypes.get_last_error()
                    if error == 121:
                        continue
                    debugger_error("WaitForDebugEvent:cleanup", error)
                    break
                code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
                if code in (CREATE_PROCESS, LOAD_DLL):
                    close_handle(int.from_bytes(ev.raw[16:24], "little"), f"cleanup-event:{pid}")
                if code == CREATE_PROCESS and pid not in pending and pid not in exited:
                    handle = int.from_bytes(ev.raw[24:32], "little")
                    cleanup_targets[pid] = handle
                    pending.add(pid)
                    if not k.TerminateProcess(wt.HANDLE(handle), 1):
                        debugger_error(f"TerminateProcess:cleanup-child:{pid}", ctypes.get_last_error())
                status = DBG_NOT_HANDLED if code == EXCEPTION else DBG_CONTINUE
                if not k.ContinueDebugEvent(pid, tid, status):
                    debugger_error("ContinueDebugEvent:cleanup", ctypes.get_last_error())
                    break
                if code == EXIT_PROCESS:
                    exited.add(pid)
                    pending.discard(pid)
                    res["cleanup"]["exit_events"].append(pid)
        if pending:
            debugger_error("cleanup:missing-exit-events", sorted(pending))
        remaining = max(0, int((deadline - time.monotonic()) * 1000))
        result = k.WaitForSingleObject(wt.HANDLE(pi.hProcess), remaining)
        res["cleanup"]["wait"].append({"pid": pi.pid, "result": result})
        if result != 0:
            debugger_error(f"WaitForSingleObject:{pi.pid}", ctypes.get_last_error() if result == 0xFFFFFFFF else result)
        if game_handle is not None:
            remaining = max(0, int((deadline - time.monotonic()) * 1000))
            result = k.WaitForSingleObject(wt.HANDLE(game_handle), remaining)
            res["cleanup"]["wait"].append({"pid": res["pid"], "result": result})
            if result != 0:
                debugger_error(f"WaitForSingleObject:{res['pid']}",
                               ctypes.get_last_error() if result == 0xFFFFFFFF else result)
            if not k.CloseHandle(wt.HANDLE(game_handle)):
                res["cleanup"]["uncertain_handles"].append({"label": "game-process", "handle": game_handle})
                debugger_error("CloseHandle:game-process", ctypes.get_last_error())
            else:
                res["cleanup"]["close"].append("game-process")
        for label, handle in (("pi-thread", pi.hThread), ("pi-process", pi.hProcess)):
            if not k.CloseHandle(handle):
                res["cleanup"]["uncertain_handles"].append({"label": label, "handle": handle})
                debugger_error(f"CloseHandle:{label}", ctypes.get_last_error())
            else:
                res["cleanup"]["close"].append(label)
    return res


class WOW64_CONTEXT(ctypes.Structure):
    _fields_ = [("flags", wt.DWORD), ("dr", wt.DWORD * 6), ("fpu", ctypes.c_byte * 112), ("seg", wt.DWORD * 4),
                ("edi", wt.DWORD), ("esi", wt.DWORD), ("ebx", wt.DWORD), ("edx", wt.DWORD), ("ecx", wt.DWORD),
                ("eax", wt.DWORD), ("ebp", wt.DWORD), ("eip", wt.DWORD), ("cs", wt.DWORD), ("eflags", wt.DWORD),
                ("esp", wt.DWORD), ("ss", wt.DWORD), ("ext", ctypes.c_byte * 512)]


def stack_words(k, hproc, tid, n=2048):
    """(esp, [dwords from esp]) of the faulting WOW64 thread: return-address candidates.
    The n dwords (8 KB by default) are read a page at a time: a thread near its stack's
    top has fewer, and one read across the end would return none."""
    k.OpenThread.restype = wt.HANDLE
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10003                       # WOW64_CONTEXT_CONTROL | INTEGER
    if not h or not k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        return None
    k.CloseHandle(h)
    data, at, end = b"", ctx.esp, ctx.esp + n * 4
    buf, got = ctypes.create_string_buffer(0x1000), ctypes.c_size_t()
    while at < end:
        size = min(end, (at & ~0xFFF) + 0x1000) - at
        got.value = 0
        ok = k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(at), buf, size, ctypes.byref(got))
        data += buf.raw[:min(got.value, size)]
        if not ok or got.value != size:
            break
        at += size
    return {"esp": ctx.esp, "ebp": ctx.ebp, "regs": {r: hex(getattr(ctx, r)) for r in
                                                      ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp",
                                                       "eip", "eflags")},
            "words": [int.from_bytes(data[i:i + 4], "little") for i in range(0, len(data) - 3, 4)]}


class ThreadNotResumed(Exception):
    """The sampler suspended the game's main thread and could not resume it: what the run shows from
    here is the sampler's doing, so it is a debugger error, never evidence."""

    def __init__(self, error):
        super().__init__(error)
        self.error = error


THREAD_CALL_FAILED = 0xFFFFFFFF
RESUME_ATTEMPTS = 3


def resume_thread(k, hthread):
    """ResumeThread until it answers, and the suspend count it found; ThreadNotResumed if it never does,
    whether it failed or raised (ctypes raises OSError for a fault inside the call)."""
    error = None
    for _ in range(RESUME_ATTEMPTS):
        try:
            count = k.ResumeThread(wt.HANDLE(hthread)) & 0xFFFFFFFF
        except OSError as failure:
            error = str(failure)
            continue
        if count != THREAD_CALL_FAILED:
            return count
        error = ctypes.get_last_error()
    raise ThreadNotResumed(error)


def while_suspended(k, hthread, read):
    """(read(), clean) with the thread suspended, or (None, False) when it could not be suspended and read()
    was not called. Clean means it was running and no other suspend or resume landed meanwhile. Raises
    ThreadNotResumed when it stays suspended; what read() raises leaves after the resume."""
    # Wine 9 has no Wow64SuspendThread; SuspendThread stops a 32-bit thread the same way here.
    before = getattr(k, "Wow64SuspendThread", k.SuspendThread)(wt.HANDLE(hthread)) & 0xFFFFFFFF
    if before == THREAD_CALL_FAILED:
        return None, False
    try:
        value = read()
    finally:
        after = resume_thread(k, hthread)
    return value, before == 0 and after == 1


def thread_eip(k, hthread):
    """The thread's EIP while it was running, or None when this read proves nothing: it could not be
    suspended or read, someone else already held it suspended (an EIP that cannot move is no sign of a
    spin), or the resume's count does not add up. Raises ThreadNotResumed when it stays suspended."""
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10001
    eip, clean = while_suspended(
        k, hthread, lambda: ctx.eip if k.Wow64GetThreadContext(wt.HANDLE(hthread), ctypes.byref(ctx)) else None)
    return eip if clean else None


def sample_eips(k, hthread, n=8):
    """EIPs of the game's main thread sampled 250 ms apart (where a hang spins)."""
    out = []
    for _ in range(n):
        eip = thread_eip(k, hthread)
        if eip is not None:
            out.append(eip)
        time.sleep(0.25)
    return out


SHOT_WAIT = 5.0     # seconds run() waits, after the run is over, for captures still in flight


class TimedShots:
    """--shots-at pictures, for reading how a run's window changes. They decide nothing: the outcome comes from the
    last picture alone. The event loop only asks; a worker thread captures, so a slow capture cannot delay an event,
    a hang sample or the deadline. That matters on Windows too, where PrintWindow sends the game a message and can
    wait on a target stopped at a debug event. A capture that never returns is recorded as not finished.

    Limits. Captures run one at a time, so a stuck one blocks later timed shots: those are recorded as skipped. The last
    picture is still taken on the event loop's thread, through PrintWindow on Windows, so SHOT_WAIT bounds neither it
    nor the whole shutdown. How this behaves on native Windows is reasoned, not run: every measurement is under Wine."""

    def __init__(self, times, t0):
        self.due, self.t0 = sorted(times), t0
        self.asked, self.results, self.requests, self.worker = [], {}, queue.Queue(), None
        self.lock, self.started, self.ended = threading.Lock(), set(), False

    def ask(self, pid, elapsed):
        """On the event loop: never waits. A late look asks for everything that has fallen due."""
        while self.due and elapsed >= self.due[0]:
            at = self.due.pop(0)
            self.requests.put((len(self.asked), pid, at))
            self.asked.append(dict(at=at, asked=round(elapsed, 1)))
            if self.worker is None:
                self.worker = threading.Thread(target=self.work, daemon=True)
                self.worker.start()

    def work(self):
        while (request := self.requests.get()) is not None:
            number, pid, at = request
            with self.lock:
                if self.ended:              # the run is over: its game is going away, and nobody reads the result
                    return
                self.started.add(number)
            try:
                picture = window_picture(pid, OUT / f"smoke_{pid}_at{number:02d}_{at:g}.png")
            except Exception as error:      # this thread's last stop: anything raised is that picture's record
                picture = {"capture": "none", "why": str(error)}
            self.results[number] = dict(picture if picture is not None else {"capture": "none", "why": "no window"},
                                        taken=round(time.time() - self.t0, 1))

    def finish(self):
        """Every picture asked for, in order, waiting at most SHOT_WAIT for those in flight. From here the worker
        takes no more: one past a stuck capture is recorded as skipped, not taken during teardown."""
        if self.worker is not None:
            self.requests.put(None)
            self.worker.join(SHOT_WAIT)
        with self.lock:
            self.ended = True
            started = set(self.started)
        late = {"capture": "none", "why": "not finished when the run ended"}
        skipped = {"capture": "none", "why": "skipped: an earlier capture had not finished when the run ended"}
        return [dict(self.results.get(number, late if number in started else skipped), **asked)
                for number, asked in enumerate(self.asked)]


def screenshot(pid):
    """The game window's own picture (window_picture), with the menu-bar share and,
    when a retail control exists, the distance from its picture."""
    out = window_picture(pid, OUT / f"smoke_{pid}.png")
    if not out or "path" not in out:
        return out
    ref = OUT / "smoke_retail.json"
    try:
        shot = json.loads(ref.read_text())["run"]["screenshot"]["path"]
        from PIL import Image
        out["differs_from_retail"] = image_distance(Image.open(out["path"]), shot)
    except (OSError, KeyError, TypeError, ValueError):
        pass
    return out


# A grey level at or below this is black: a frame with nothing above it shows nothing
# (menu_bar and image_distance crop to content above the same level).
BLACK = 8


def picture_stats(img):
    """Grey-level mean, standard deviation and maximum of a frame, and whether it is
    black (no pixel above BLACK). Pure, so a black frame's refusal is tested."""
    from PIL import ImageStat
    g = img.convert("L")
    st = ImageStat.Stat(g)
    top = g.getextrema()[1]
    return {"mean": round(st.mean[0], 1), "stddev": round(st.stddev[0], 1), "max": top, "black": top <= BLACK}


# The title splash at 16x12 grey, from a boot's own 800x600 capture. Two boots' captures give these
# same numbers. A picture this close (mean absolute grey difference) is that splash.
TITLE_SPLASH = bytes.fromhex(
    "1a212d618288929797968b928e7e7a7015293b5f80919fa2a79d8b8c7e75613c"
    "0f2a334f515173709588788372644c35183129272432343c4a3e4d5e6e645444"
    "272d1919132037353d353a3d52655b421c211e1a1f27393a3930303747574e38"
    "251b2e38383c3b3439433f3b3d3e322e161629363139433c41373a3237352e26"
    "1b201a1818234a5155402a202221251e131512110e1115272c211c191615120b"
    "0f0f11121311153d3c17161614110c0a0b0b0d0f1111142c3314100f0f0d0b09")
TITLE_SPLASH_DISTANCE = 6


def title_splash(img):
    """Is `img` the game's title splash? Coarse on purpose: a capture's scale varies, the picture does not."""
    grey = img.convert("L").resize((16, 12)).tobytes()
    return sum(abs(a - b) for a, b in zip(grey, TITLE_SPLASH)) / len(TITLE_SPLASH) <= TITLE_SPLASH_DISTANCE


# The hang test, a heuristic. run() samples the main thread about once a second over the run's last SPIN_SPAN
# seconds. A copy or a decompression can sit in one loop for seconds, and one lasting the whole span inside
# the image would satisfy this. In the other direction, a wider spin, a spin in a system DLL or a deadlock in a
# wait keep their more favourable picture label: this catches a tight spin in the game's own code, no more.
# The limits on failures and gaps are about the evidence: a failed read or a hole in the good ones can hide work
# between two samples. Real hangs measured no failures and a largest gap of 1.0 s; healthy retail, 2.7 s.
SPIN_SPAN = 30.0
SPIN_EVERY = 1.0
SPIN_WINDOW = 64        # bytes: wider than one tight loop's few instructions, narrower than most functions
SPIN_MIN_SECONDS = 25.0
SPIN_MIN_SAMPLES = 20
SPIN_MAX_FAILURES = 2   # reads over the span that proved nothing
SPIN_MAX_GAP = 3.0      # seconds between two good samples
EVENT_GRACE = 2.0       # seconds past the deadline that a stream of events can keep the run open: run()'s boundary


def shot_times(text):
    """--shots-at's value: ascending seconds, each finite and above zero."""
    times = {float(part) for part in text.split(",")}
    if not times or not all(math.isfinite(value) and value > 0 for value in times):
        raise ValueError(text)
    return sorted(times)


def main_thread_span(samples, image_low, image_high, failures):
    """What samples [(seconds into the run, eip)] say, with `failures` the reads that proved nothing, or None
    when there are no samples: where the thread sat, over how long, and `spinning` only when all of it is the
    game's own code, [image_low, image_high), and fits SPIN_WINDOW over at least SPIN_MIN_SECONDS and
    SPIN_MIN_SAMPLES, with at most SPIN_MAX_FAILURES failures and no gap over SPIN_MAX_GAP. A thread outside the
    image is waiting in a system call, as retail's does for 29 s at a stretch, which proves nothing. The
    numbers stay in the receipt either way, so a miss can be read."""
    if not samples:
        return None
    times, eips = [t for t, _ in samples], [e for _, e in samples]
    seconds, spread = round(times[-1] - times[0], 1), max(eips) - min(eips)
    gap = round(max((b - a for a, b in zip(times, times[1:])), default=0.0), 1)
    inside = image_low <= min(eips) and max(eips) < image_high
    return {"low": hex(min(eips)), "high": hex(max(eips)), "spread": spread, "samples": len(samples), "seconds": seconds,
            "inside_image": inside, "failures": failures, "largest_gap": gap,
            "spinning": inside and spread < SPIN_WINDOW and seconds >= SPIN_MIN_SECONDS and len(samples) >= SPIN_MIN_SAMPLES
            and failures <= SPIN_MAX_FAILURES and gap <= SPIN_MAX_GAP}


def classify_picture(shot):
    """The boot outcome a capture supports: no-window (none to capture), no-picture
    (capture failed, or the frame is black), blank-window (one flat colour), title-splash,
    loading-screen (another picture without the main menu's button bar) or reached-menu.
    Only a captured, non-black, non-flat frame with the button bar reaches the menu."""
    if not shot:
        return "no-window"
    if "path" not in shot or shot.get("black", True):
        return "no-picture"
    if shot.get("stddev", 0) <= 8:
        return "blank-window"
    if shot.get("menu_bar", 0) < MENU_BAR:
        return "title-splash" if shot.get("title_splash") else "loading-screen"
    return "reached-menu"


def window_picture(pid, path):
    """Client-area picture of pid's largest visible window, saved to `path`:
    {"path", "capture", stats, "menu_bar"}; {"capture": "none", "why"} when nothing
    usable was captured; None when there is no window.

    Windows: PrintWindow, never the screen (a screen grab shows whatever lies on top
    of the window, which may be anything on the owner's desktop). Wine: PrintWindow
    comes back black for the game's GL surface (measured 2026-11-05), so the client
    rectangle is copied from the screen, which there is the X server's root window.
    That needs the window wholly on the screen, no Win32 window above it overlapping
    its client area (before and after the copy), and DISPLAY declared private by the
    queue (BFME_PRIVATE_DISPLAY), since native X windows cannot be seen from here;
    otherwise nothing is captured."""
    wins = [w for w in windows_of(pid) if w[1][2] - w[1][0] > 100 and w[1][3] - w[1][1] > 100]
    if not wins:
        return None
    h = max(wins, key=lambda w: (w[1][2] - w[1][0]) * (w[1][3] - w[1][1]))[2]
    if under_wine():
        img, how, why = root_capture(h)
    else:
        img, how = print_window(h), "PrintWindow"
        why = None if img is not None else "PrintWindow failed"
    if img is None:
        return {"capture": "none", "method": how, "why": why}
    img.save(path)
    out = {"path": str(path), "capture": how} | picture_stats(img)
    out["menu_bar"] = menu_bar(img)
    out["title_splash"] = title_splash(img)
    if how == "xvfb-root":
        out["display"] = os.environ.get("DISPLAY")
        out["display_private"] = "declared by the queue (BFME_PRIVATE_DISPLAY); native X windows not checked"
    return out


def _gdi():
    u, g = ctypes.WinDLL("user32"), ctypes.WinDLL("gdi32")
    u.GetDC.restype = g.CreateCompatibleDC.restype = g.CreateCompatibleBitmap.restype = wt.HANDLE
    u.GetDC.argtypes = [wt.HWND]
    g.SelectObject.argtypes = [wt.HANDLE, wt.HANDLE]
    g.CreateCompatibleDC.argtypes = [wt.HANDLE]
    g.CreateCompatibleBitmap.argtypes = [wt.HANDLE, ctypes.c_int, ctypes.c_int]
    g.DeleteObject.argtypes = g.DeleteDC.argtypes = [wt.HANDLE]
    g.BitBlt.argtypes = [wt.HANDLE] + [ctypes.c_int] * 4 + [wt.HANDLE, ctypes.c_int, ctypes.c_int, wt.DWORD]
    u.ReleaseDC.argtypes = [wt.HWND, wt.HANDLE]
    u.PrintWindow.argtypes = [wt.HWND, wt.HANDLE, wt.UINT]
    u.GetWindow.argtypes = [wt.HWND, wt.UINT]
    u.GetWindow.restype = wt.HWND
    g.GetDIBits.argtypes = [wt.HANDLE, wt.HANDLE, wt.UINT, wt.UINT, ctypes.c_void_p, ctypes.c_void_p, wt.UINT]
    return u, g


def _bitmap(draw, w, ht):
    """Run draw(user32, gdi32, screen DC, memory DC) into a w x ht bitmap: its
    pixels as an RGB image, or None when draw or the read-back fails."""
    from PIL import Image
    if w <= 0 or ht <= 0:
        return None
    u, g = _gdi()
    sdc = u.GetDC(None)
    mdc = g.CreateCompatibleDC(sdc)
    bmp = g.CreateCompatibleBitmap(sdc, w, ht)
    g.SelectObject(mdc, bmp)
    ok = draw(u, g, sdc, mdc)
    info = struct.pack("<IiiHHIIiiII", 40, w, -ht, 1, 32, 0, 0, 0, 0, 0, 0)
    buf = ctypes.create_string_buffer(w * ht * 4)
    got = g.GetDIBits(mdc, bmp, 0, ht, buf, ctypes.create_string_buffer(info, 44), 0)
    g.DeleteObject(bmp)
    g.DeleteDC(mdc)
    u.ReleaseDC(None, sdc)
    if not ok or got != ht:
        return None
    return Image.frombuffer("RGBX", (w, ht), buf.raw, "raw", "BGRX", 0, 1).convert("RGB")


def print_window(h):
    """The window's own client-area pixels (PrintWindow, PW_CLIENTONLY |
    PW_RENDERFULLCONTENT), so a window under another one is still seen."""
    rc = wt.RECT()
    ctypes.WinDLL("user32").GetClientRect(h, ctypes.byref(rc))
    return _bitmap(lambda u, g, sdc, mdc: u.PrintWindow(h, mdc, 3), rc.right, rc.bottom)


GW_HWNDPREV = 3
# Set by the game queue to the Xvfb display it started for this game alone (with its
# own auth cookie). Windows-side code cannot see native X windows, so a screen capture
# under Wine is only trusted on a display declared private this way.
PRIVATE_DISPLAY = "BFME_PRIVATE_DISPLAY"


def _rect(u, call, h):
    rc = wt.RECT()
    call(h, ctypes.byref(rc))
    return rc.left, rc.top, rc.right, rc.bottom


def client_on_screen(u, h):
    """(left, top, right, bottom) of h's client area in screen coordinates."""
    _, _, w, ht = _rect(u, u.GetClientRect, h)
    pt = wt.POINT(0, 0)
    u.ClientToScreen(h, ctypes.byref(pt))
    return pt.x, pt.y, pt.x + w, pt.y + ht


def windows_above(u, h, limit=4096):
    """[(hwnd, window rectangle)] of every visible top-level window above h in the
    z-order (the game's own popups included)."""
    out, w = [], u.GetWindow(h, GW_HWNDPREV)
    while w and len(out) < limit:
        if u.IsWindowVisible(w):
            out.append((w, _rect(u, u.GetWindowRect, w)))
        w = u.GetWindow(w, GW_HWNDPREV)
    return out


def overlaps(a, b):
    return max(a[0], b[0]) < min(a[2], b[2]) and max(a[1], b[1]) < min(a[3], b[3])


def capture_refusal(rect, screen, above, display=None, private=None):
    """Why a screen capture of `rect` would not show the window alone, or None.
    `screen` is (width, height); `above`, [(hwnd, rectangle)] of the visible windows
    above it; `display`/`private`, DISPLAY and the display the queue declared private.
    Pure (tested): a window partly off screen, any window over any part of the client
    area, or a display not declared private is refused."""
    l, t, r, b = rect
    if r - l <= 0 or b - t <= 0:
        return "empty client area"
    if l < 0 or t < 0 or r > screen[0] or b > screen[1]:
        return f"client area {list(rect)} not wholly on the {screen[0]}x{screen[1]} screen"
    over = [(w, list(o)) for w, o in above if overlaps(rect, o)]
    if over:
        return f"{len(over)} window(s) above the game overlap its client area: {over[:3]}"
    if not display or display != private:
        return f"display {display!r} is not the private one the queue declared ({PRIVATE_DISPLAY}={private!r})"
    return None


def root_capture(h, u=None):
    """(image, "xvfb-root", why) of h's client area copied from the screen (the X
    root under Wine); the image is None when the capture is refused or fails. The
    window's position and the windows above it are read again after the copy, and
    the capture is refused unless both are unchanged and still clear."""
    u = u or _gdi()[0]
    screen = (u.GetSystemMetrics(0), u.GetSystemMetrics(1))
    display, private = os.environ.get("DISPLAY"), os.environ.get(PRIVATE_DISPLAY)

    def state():
        return client_on_screen(u, h), windows_above(u, h)
    rect, above = state()
    why = capture_refusal(rect, screen, above, display, private)
    if why:
        return None, "xvfb-root", why
    l, t, r, b = rect
    img = _bitmap(lambda u, g, sdc, mdc: g.BitBlt(mdc, 0, 0, r - l, b - t, sdc, l, t, 0x00CC0020 | 0x40000000),
                  r - l, b - t)                       # SRCCOPY | CAPTUREBLT
    if img is None:
        return None, "xvfb-root", "BitBlt from the screen failed"
    rect2, above2 = state()
    if rect2 != rect:
        return None, "xvfb-root", f"the client area moved during the capture ({list(rect)} to {list(rect2)})"
    why = capture_refusal(rect2, screen, above2, display, private)
    if why:
        return None, "xvfb-root", f"after the capture: {why}"
    return img, "xvfb-root", None


def menu_bar(img):
    """Share of green pixels (the menu buttons) in the bottom band of the content."""
    g = img.convert("L")
    rgb = img.convert("RGB").crop(g.point(lambda v: 255 if v > 8 else 0).getbbox() or (0, 0) + g.size)
    w, h = rgb.size
    band = rgb.crop((0, int(h * 0.89), w, int(h * 0.97))).resize((256, 16))
    px = [band.getpixel((x, y)) for y in range(16) for x in range(256)]
    return round(sum(1 for r, gr, b in px if gr > r + 12 and gr > b + 12) / len(px), 3)


def image_distance(img, other_path):
    """Mean absolute grey difference (0..255) of 64x36 thumbnails of the two
    images' non-black content: a coarse 'same screen as the retail control'
    measure (the menu background moves; PrintWindow and a screen grab scale
    the client area differently)."""
    from PIL import Image, ImageChops, ImageStat

    def thumb(i):
        g = i.convert("L")
        return g.crop(g.point(lambda v: 255 if v > 8 else 0).getbbox() or (0, 0) + g.size).resize((64, 36))
    a, b = thumb(img), thumb(Image.open(other_path))
    return round(ImageStat.Stat(ImageChops.difference(a, b)).mean[0], 1)


def ledger_row(rva):
    """(name, start, status) of the functions.csv row holding retail RVA `rva`, else the
    ghidra function, else None."""
    best = None
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            s = int(row["target_rva"], 16)
            if s <= rva < s + int(row["target_size"] or 0):
                best = (row["name"], hex(s), row["status"])
                break
    if best:
        return best
    starts = []
    with open(ROOT / "reverse/ghidra_functions.csv", newline="", encoding="utf-8") as f:
        for row in csv.DictReader(f):
            starts.append((int(row["rva"], 16), int(row["size"] or 0), row["name"]))
    starts.sort()
    i = bisect.bisect_right(starts, (rva, 1 << 62)) - 1
    if i >= 0 and starts[i][0] <= rva < starts[i][0] + max(starts[i][1], 1):
        return (starts[i][2], hex(starts[i][0]), "ghidra-only")
    return None


def to_retail(addr, base, pieces_map):
    """Retail RVA of a run-time address in the boot image (None outside its pieces)."""
    rva = addr - base
    for name, rstart, nstart, size in pieces_map:
        if nstart <= rva < nstart + size:
            return rstart + rva - nstart, name
    return None, None


def smoke(a, rows=None, tag="boot"):
    """Build (unless --retail / --no-build), run once, classify: the outcome dict.
    `rows` (ledger rows) replaces the --overlay specs; the bisection uses it."""
    import real_image
    t_start, started = time.time(), time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
    out = {"retail": a.retail, "base": hex(a.base), "args": a.args,
           "overlay": a.overlay if rows is None else f"{len(rows)} row(s)"}
    authored = []
    ri = None
    if getattr(a, "real_image", None):
        try:
            ri = real_image.load(a.real_image)
            ok, rep = real_image.check(ri)
        except real_image.RealImageError as e:
            ok, rep = False, {"refused": str(e)}
        out["real_image"] = rep
        if not ok:
            out["outcome"] = "image-refused"
            out["receipt"] = real_image.receipt_fields("boot_smoke", "boot", out["outcome"],
                                                       real_image.summary(ri) if ri else {}, None, started,
                                                       time.time() - t_start)
            return out
        exe, pieces_map, base = Path(a.real_image), None, ri.base
        out["base"] = hex(ri.base)
        if getattr(a, "rebase", None):
            exe, base = real_image.rebased_copy(ri, a.rebase, OUT / "rebased.exe"), a.rebase
            rep["rebased"] = {"base": hex(a.rebase), "sha256": real_image.sha256_file(exe)}
            out["base"] = hex(a.rebase)
    elif a.retail:
        exe, pieces_map, base = boot_image.build.EXE, None, boot_image.RETAIL_BASE
    else:
        if a.no_build:
            rep = json.loads((OUT / f"{tag}.json").read_text())
        elif a.relayout or a.own_data:
            import boot_relayout
            rep = boot_relayout.build_image(a.base, OUT, tag, a.overlay, a.status, rows, relayout=a.relayout,
                                            own_data=a.own_data, seed=a.seed)
            out["relayout"] = rep.get("relayout")
            if rep.get("own_data"):
                out["own_data"] = rep["own_data"]
        else:
            rep = boot_image.build_image(a.base, OUT, tag, a.overlay, a.status, rows)
        chk = rep.get("check", {})
        out["link"] = {k: rep.get(k) for k in ("link_exit", "link_seconds", "imports_used")} | {"check": chk}
        if rep.get("overlay"):
            out["link"]["overlay"] = {k: v for k, v in rep["overlay"].items() if k != "rows_csv"}
        if not boot_image.image_ok(rep):
            out["outcome"] = "link-error"
            return out
        exe, pieces_map, base = OUT / f"{tag}.exe", rep["pieces_map"], a.base
        authored = rep.get("authored", [])
    prepare_sandbox_profile(a.appdata)
    try:                                          # never a leftover image: refused by hash
        out["game_dat_sha256"] = real_image.install_game_dat(exe, a.game_dir)
    except real_image.RealImageError as e:
        out["outcome"], out["game_dat_error"] = "game-dat-mismatch", str(e)
        return out
    before = {str(g): snapshot(g) for g in a.guard}
    profile_guard = ProfileGuard()
    if a.compat:
        os.environ["__COMPAT_LAYER"] = a.compat
    out["compat"] = a.compat
    moved = {}
    if pieces_map:
        start_of = {rs: ns for _, rs, ns, _ in pieces_map}
        moved = {start_of[rva]: (rva, size, name) for rva, size, name in authored}
    focus_rva = None if a.no_focus_lie else focus_arm_rva(exe)
    if not a.no_focus_lie and focus_rva is None:
        out["focus_lie"] = "WM_ACTIVATEAPP arm not found (no lie)"
    res = run(a.game_dir / "lotrbfme2.exe", a.game_dir.resolve(), a.args, a.timeout, not a.no_version_lie,
              sorted(moved) if a.probes else (), focus_rva, a.defocus, a.int3_faults or a.relayout or ri is not None,
              appdata=a.appdata, shots_at=a.shots_at)
    out["run"] = {k: v for k, v in res.items() if k not in ("first_chance", "stack", "probes_hit")}
    out["run"]["first_chance"] = [[c, hex(x), [hex(i) for i in info]] for c, x, info in res["first_chance"]]
    if authored:
        hit = [moved[x] for x in res["probes_hit"] if x in moved]
        out["authored_executed"] = {"units": len(hit), "of_units": len(authored),
                                    "bytes": sum(z for _, z, _ in hit), "of_bytes": sum(z for _, z, _ in authored),
                                    "probed": a.probes,
                                    "rows": [[hex(rva), name] for rva, _, name in sorted(hit)]}
    loaded = res.get("image_base", base)
    authored_at = sorted((rva, rva + size, name) for rva, size, name in authored)

    def blame(rva):
        """The authored unit holding retail RVA `rva`, if any."""
        i = bisect.bisect_right(authored_at, (rva, 1 << 62, "")) - 1
        return authored_at[i][2] if i >= 0 and authored_at[i][0] <= rva < authored_at[i][1] else None
    crashed = res["outcome"] == "crash" or (res["outcome"] == "exit" and res.get("fault") is not None
                                            and res["exit_code"])
    if ri is not None and crashed:                    # a real image: the map, the stubs, then retail's row
        st = res.get("stack") or {}
        exc = res.get("code") or next((c for c, x, _ in res["first_chance"] if x == res.get("fault")), None)
        out["crash"] = real_image.crash_fields(ri, res["address"] if res["outcome"] == "crash" else res["fault"],
                                               loaded, st.get("words", []), exc)
        if res["outcome"] == "exit":
            out["crash"]["handled_then_exit"] = res["exit_code"]
        if st:
            out["crash"]["stack"] = fault_stack(st, loaded, ri, pieces_map)
        out["run"]["regs"] = st.get("regs")
        out["outcome"] = f"crash-at-{real_image.crash_name(out['crash'])}"
    elif res["outcome"] == "crash":
        rva = res["address"] - loaded
        if pieces_map:
            rva, piece = to_retail(res["address"], loaded, pieces_map)
        else:
            piece = "retail"
        row = ledger_row(rva) if rva is not None else None
        frames = []
        size = boot_image.Retail().size_of_image if pieces_map is None else max(n + z for _, _, n, z in pieces_map)
        for w in (res.get("stack") or {}).get("words", []):
            if loaded <= w < loaded + size and len(frames) < 12:
                fr = (w - loaded, "retail") if pieces_map is None else to_retail(w, loaded, pieces_map)
                if fr[0] is not None and fr[1].startswith((".text", "retail")):
                    frames.append([hex(w), hex(fr[0]), ledger_row(fr[0]), blame(fr[0])])
        st = res.get("stack") or {}
        out["run"]["esp"] = hex(st.get("esp", 0))
        out["run"]["regs"] = st.get("regs")
        out["run"]["stack_top"] = [hex(w) for w in st.get("words", [])[:8]]
        if row is None and frames:                   # faulted outside the image: blame the first game frame
            row = frames[0][2]
        out.update(crash={"address": hex(res["address"]), "retail_rva": hex(rva) if rva is not None else None,
                          "piece": piece, "row": row, "stack_frames": frames,
                          "authored": blame(rva) if rva is not None else None})
        if st:
            out["crash"]["stack"] = fault_stack(st, loaded, ri, pieces_map)
        out["outcome"] = f"crash-at-{row[0] if row else (hex(rva) if rva is not None else 'outside-image')}"
    elif res["outcome"] == "exit" and res.get("fault") is not None and res["exit_code"]:
        # an access violation the game's own handler caught, then exited non-zero
        rva, piece = to_retail(res["fault"], loaded, pieces_map) if pieces_map else (res["fault"] - loaded, "retail")
        row = ledger_row(rva) if rva is not None else None
        out.update(crash={"address": hex(res["fault"]), "retail_rva": hex(rva) if rva is not None else None,
                          "piece": piece, "row": row, "handled_then_exit": res["exit_code"],
                          "authored": blame(rva) if rva is not None else None})
        if res.get("stack"):
            out["crash"]["stack"] = fault_stack(res["stack"], loaded, ri, pieces_map)
        out["outcome"] = f"crash-at-{row[0] if row else (hex(rva) if rva is not None else 'outside-image')}"
    elif res["outcome"] == "exit":
        out["outcome"] = f"exit-{res['exit_code']:#x}"
    elif res["outcome"] == "debugger-error":
        out["outcome"] = "debugger-error"
    else:
        shot = res.get("screenshot")
        titles = [t for t, _ in res.get("windows", [])]
        eips = []
        for e in res.get("main_eips", []) if ri is None else ():
            rva, piece = to_retail(e, loaded, pieces_map) if pieces_map else (e - loaded, "retail")
            eips.append([hex(e), hex(rva) if rva is not None else None, ledger_row(rva) if rva is not None else None])
        out["main_thread_samples"] = eips if ri is None else [
            [hex(e), ri.where(e - loaded + ri.base)["map_symbol"]] for e in res.get("main_eips", [])]
        st = res.get("main_stack") or {}
        if st:
            out["main_stack"] = {"regs": st.get("regs"), "esp": hex(st.get("esp", 0)),
                                 "frames": image_frames(st.get("words", []), loaded, ri, pieces_map, 16)}
        dialog = crash_dialog(res.get("dialogs") or [{"title": t} for t in titles])
        if dialog:                                  # the game's own crash box: a crash, whatever the picture
            addrs = dialog.pop("addresses")
            dialog["frames"] = [[hex(v), label] for v, label in zip(addrs, map_addresses(addrs, loaded, ri, pieces_map))]
            out["crash"] = {"exception": None, "address_image": None, "return_address_image": None,
                            "map_symbol": None, "stubbed_name": None, "retail_rva": None, "dialog": dialog}
            out["outcome"] = "crash-dialog"
        else:
            picture = classify_picture(shot)
            if ri is not None:
                image_size = ri.img.pe.OPTIONAL_HEADER.SizeOfImage
            elif pieces_map is None:
                image_size = boot_image.Retail().size_of_image
            else:
                image_size = max(n + z for _, _, n, z in pieces_map)
            span = main_thread_span(res.get("spin_samples", []), loaded, loaded + image_size,
                                    res.get("spin_sample_failures", 0))
            if span:
                out["main_thread_span"] = span
            out["picture"] = picture
            out["outcome"] = f"hang-on-{picture}" if span and span["spinning"] and picture != "reached-menu" else picture
    if res.get("quiet"):
        out["run"]["quiet"] = [dict({k: v for k, v in q.items() if k != "stack"},
                                    **({"frames": image_frames(q["stack"], loaded, ri, pieces_map, 4)}
                                       if q.get("stack") else {})) for q in res["quiet"]]
    for g, snap in before.items():
        after = snapshot(Path(g))
        changed = sorted(set(after) ^ set(snap) | {p for p in snap if p in after and after[p] != snap[p]})
        out.setdefault("guard", {})[g] = changed[:20]
        if changed:
            out["outcome"] = "guard-violation"
    if res.get("outcome") == "profile-redirect-failed":
        out["outcome"] = "profile-redirect-failed"
    out["profile_guard"], touched = profile_guard.check()
    if touched:
        out["outcome"] = "profile-changed"
    image = (real_image.summary(ri) if ri is not None else real_image.retail_summary() if a.retail else
             {"image_kind": "overlay", "image_sha256": real_image.sha256_file(exe), "image_commit": None})
    image["base"] = hex(loaded)
    out["receipt"] = real_image.receipt_fields("boot_smoke", "boot", out["outcome"], image, out.get("crash"),
                                               started, time.time() - t_start)
    return out


_ROWS = []


def address_label(va, loaded, ri, pieces_map):
    """'symbol+offset' of a run-time address: through the real image's map, or for retail
    through functions.csv; None outside the image or for an overlay image."""
    rva = va - loaded
    if ri is not None:
        if not ri.img.code(rva):
            return None
        sym, off = ri.map.holding(ri.base + rva)
        return f"{'|'.join(ri.map.names_at(sym))}+{off:#x}" if sym else None
    if pieces_map:
        return None
    if not _ROWS:
        _ROWS.append(real_image.Rows())
    held = _ROWS[0].holding(rva)
    return "|".join(f"{n}+{rva - s:#x}" for s, _, n, _ in held) or None


def map_addresses(vas, loaded, ri, pieces_map):
    return [address_label(v, loaded, ri, pieces_map) for v in vas]


FAULT_FRAMES = 64


def fault_stack(st, loaded, ri, pieces_map):
    """The crash record's `stack`: the faulting thread's esp, ebp and register file, every
    dword read from esp (`words[i]` is at esp + 4*i: return addresses with the arguments
    and locals between them) and the return addresses among them, symbolized as a hang's
    main_stack frames are. None when no stack was read."""
    if not st:
        return None
    words = st.get("words") or []
    return {"esp": hex(st.get("esp", 0)), "ebp": hex(st.get("ebp", 0)), "regs": st.get("regs"),
            "words": [hex(w) for w in words],
            "frames": image_frames(words, loaded, ri, pieces_map, FAULT_FRAMES)}


def image_frames(words, loaded, ri, pieces_map, limit):
    """[[address, 'symbol+offset']] of the stack words that are return addresses into the
    image (they follow a call), at most `limit`."""
    if pieces_map:
        return []
    img = ri.img if ri is not None else _retail_sections()
    size = img.pe.OPTIONAL_HEADER.SizeOfImage
    out = []
    for w in words or []:
        rva = w - loaded
        if 0 <= rva < size and img.code(rva) and real_image.follows_call(img, rva):
            out.append([hex(w), address_label(w, loaded, ri, pieces_map)])
            if len(out) >= limit:
                break
    return out


_RETAIL = []


def _retail_sections():
    if not _RETAIL:
        _RETAIL.append(real_image.Sections(boot_image.build.EXE))
    return _RETAIL[0]


def broke(outcome):
    """A start-up the overlay broke: a crash, an exit, no or a blank window, or a confirmed hang
    whatever its picture (not a slow load still showing the splash, not a link or guard failure)."""
    return outcome.startswith(("crash", "exit-", "hang-on-")) or outcome in ("no-window", "blank-window")


def bisect_rows(a, rows, executed=None):
    """Deterministic halving of a failing overlay to the rows that fail on their own.
    When the failing run was probed, only units it executed are candidates (code
    that never ran cannot have broken the boot). Each step runs one half alone; when
    neither half fails by itself the remaining set is reported together (an
    interaction). Returns (guilty rows, steps)."""
    by_rva = collections.defaultdict(list)
    for r in rows:
        by_rva[int(r["target_rva"], 16)].append(r)
    cand = sorted(by_rva if executed is None else set(by_rva) & set(executed))
    steps = []
    while len(cand) > 1:
        nxt = None
        for h in (cand[:len(cand) // 2], cand[len(cand) // 2:]):
            res = smoke(a, [r for x in h for r in by_rva[x]], tag="bisect")
            steps.append({"units": len(h), "first": hex(h[0]), "last": hex(h[-1]), "outcome": res["outcome"]})
            print(f"boot_smoke: bisect {len(h)} unit(s) {h[0]:#x}..{h[-1]:#x}: {res['outcome']}", flush=True)
            if broke(res["outcome"]):
                nxt = h
                break
        if nxt is None:
            break
        cand = nxt
    return [r for x in cand for r in by_rva[x]], steps


def write_queue(guilty, outcome, path=None):
    """build/boot/boot_queue.json: the rows repair_queue.py serves as `boot-crash` repairs."""
    path = Path(path or OUT / "boot_queue.json")
    alone = len({r["target_rva"] for r in guilty}) == 1
    items = [{"target_rva": r["target_rva"], "name": r["name"], "source": r["source"],
              "size": int(r["target_size"] or 0), "outcome": outcome,
              "why": (f"boot smoke {outcome} with this row's authored code overlaid alone" if alone else
                      f"boot smoke {outcome}: {len(guilty)} rows fail together, no half alone")} for r in guilty]
    path.write_text(json.dumps({"tool": "boot_smoke", "items": items}, indent=1), encoding="utf-8")
    return path


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--game-dir", type=Path, required=True)
    ap.add_argument("--retail", action="store_true", help="control: run retail's own game.dat")
    ap.add_argument("--real-image", type=Path, metavar="EXE",
                    help="a linked image (exit_link's exit.exe, with exit.map and image_receipt.json beside it): "
                         "hash-checked, judged by real_image.check instead of boot_image.image_ok, crashes "
                         "mapped through its map and stubs; an int3 the harness did not plant is a fault")
    ap.add_argument("--rebase", type=lambda v: int(v, 0), metavar="BASE",
                    help="with --real-image: run a copy relocated to BASE (a second non-retail base)")
    ap.add_argument("--base", type=lambda v: int(v, 0), default=0x10000000)
    ap.add_argument("--timeout", type=float, default=90)
    ap.add_argument("--args", default="-win")
    ap.add_argument("--guard", type=Path, action="append", default=[])
    ap.add_argument("--appdata", type=Path,
                    help="sandbox AppData root the game gets instead of the owner's (default GAME_DIR/../appdata)")
    ap.add_argument("--compat", default="", help="__COMPAT_LAYER for the child (WinXPSP3 needs elevation here)")
    ap.add_argument("--no-version-lie", action="store_true")
    ap.add_argument("--no-build", action="store_true", help="reuse build/boot/boot.exe")
    ap.add_argument("--overlay", action="append", default=[], metavar="SET",
                    help="authored units in the image (as boot_image.py link --overlay)")
    ap.add_argument("--status", type=Path, default=boot_image.LINK_STATUS)
    ap.add_argument("--no-focus-lie", action="store_true",
                    help="let WM_ACTIVATEAPP(FALSE) through (by default it is rewritten to TRUE: loading stalls "
                         "while the window lacks focus)")
    ap.add_argument("--defocus", type=float, metavar="SECONDS",
                    help="minimise the game window SECONDS after launch, show it unfocused 15 s before the end")
    ap.add_argument("--shots-at", type=shot_times, default=(), metavar="SECONDS,...",
                    help="also picture the window at these times into the run (run.timed_shots in the report, a PNG each); "
                         "the outcome still comes from the last picture alone")
    ap.add_argument("--probes", action="store_true",
                    help="one-shot breakpoints at authored unit starts: which authored code ran (each hit is a "
                         "debugger round trip; 9,001 hits delayed a boot past 150 s)")
    ap.add_argument("--bisect", action="store_true",
                    help="when the overlay fails, halve it to the guilty rows (build/boot/boot_queue.json)")
    ap.add_argument("--relayout", action="store_true", help="units moved out of retail order (boot_relayout.py)")
    ap.add_argument("--own-data", action="store_true", help="data from the units' objects (boot_relayout.py)")
    ap.add_argument("--seed", type=int, default=0, help="--relayout shuffle seed")
    ap.add_argument("--int3-faults", action="store_true",
                    help="an int3 the debugger did not plant is a fault (always on with --relayout)")
    a = ap.parse_args(argv)
    if a.real_image and (a.retail or a.overlay or a.relayout or a.own_data or a.no_build or a.bisect):
        raise SystemExit("boot_smoke: --real-image runs the linked image alone (no --retail, overlay or relayout)")
    if a.shots_at and a.shots_at[-1] >= a.timeout:
        ap.error(f"--shots-at {a.shots_at[-1]:g} is not before --timeout {a.timeout:g}")
    if a.rebase and not a.real_image:
        raise SystemExit("boot_smoke: --rebase needs --real-image")
    a.appdata = (a.appdata or a.game_dir.resolve().parent / "appdata").resolve()
    try:
        check_sandbox_appdata(a.appdata)
    except RedirectError as e:
        raise SystemExit(f"boot_smoke: {e}")
    ctypes.WinDLL("user32").SetProcessDPIAware()      # window and screen coordinates in physical pixels
    OUT.mkdir(parents=True, exist_ok=True)
    if (a.game_dir / "game.dat").exists() and (a.game_dir / "game.dat").stat().st_size == 0:
        raise SystemExit("boot_smoke: refusing an empty game.dat")
    for g in a.guard:
        if a.game_dir.resolve() == g.resolve() or g.resolve() in a.game_dir.resolve().parents:
            raise SystemExit(f"boot_smoke: --game-dir is inside guarded {g}")
    out = smoke(a)
    (OUT / ("smoke_retail.json" if a.retail else "smoke.json")).write_text(json.dumps(out, indent=1))
    if a.bisect and a.overlay and broke(out["outcome"]):
        with open(OUT / "boot.overlay.csv", newline="", encoding="utf-8") as f:
            kept = {(int(x["retail_rva"], 16), x["name"]) for x in csv.DictReader(f) if x["overlay"] == "overlaid"}
        rows = [r for r in boot_image.overlay_rows(a.overlay, a.status)
                if (int(r["target_rva"], 16), r["name"]) in kept]
        ex = out.get("authored_executed", {})
        executed = {int(x[0], 16) for x in ex.get("rows", [])} if ex.get("probed") else None
        guilty, steps = bisect_rows(a, rows, executed)
        out["bisect"] = {"steps": steps, "guilty": [[r["target_rva"], r["name"], r["source"]] for r in guilty],
                         "queue": str(write_queue(guilty, out["outcome"]))}
    (OUT / ("smoke_retail.json" if a.retail else "smoke.json")).write_text(json.dumps(out, indent=1))
    shown = dict(out)
    if "authored_executed" in out:
        shown["authored_executed"] = {k: v for k, v in out["authored_executed"].items() if k != "rows"}
    print(json.dumps(shown, indent=1))
    return 0 if out["outcome"] == "reached-menu" else 1


if __name__ == "__main__":
    sys.exit(main())
