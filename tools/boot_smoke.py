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
  no-picture            alive with a window that renders nothing (black)
  loading-screen        alive with a picture, but the main menu's button bar is
                        not up yet (the splash, or the shell map before the menu)

The focus lie (on unless --no-focus-lie): BFME2 stops loading while its window
lacks focus (WndProc's WM_ACTIVATEAPP(FALSE) arm sets isWinMainActive and
TheGameEngine->setIsActive(false)). One breakpoint on that arm, located by its
bytes in the image under test, rewrites wParam 0 to 1, so a run need not keep
the focus (`focus_lie` in the outcome counts hits and rewrites). --defocus N
minimises the window N s after launch to prove it.

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
"""
import argparse
import bisect
import collections
import csv
import ctypes
import ctypes.wintypes as wt
import json
import os
import re
import shutil
import struct
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402

OUT = ROOT / "build" / "boot"
DEBUG_PROCESS = 0x1
DBG_CONTINUE, DBG_NOT_HANDLED = 0x00010002, 0x80010001
EXCEPTION, CREATE_PROCESS, EXIT_PROCESS, LOAD_DLL = 1, 3, 5, 6
BREAKPOINTS = {0x80000003, 0x4000001F}          # int3, WOW64 int3
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
    k.WaitForDebugEvent.argtypes = [ctypes.c_void_p, wt.DWORD]
    k.ContinueDebugEvent.argtypes = [wt.DWORD, wt.DWORD, wt.DWORD]
    k.CloseHandle.argtypes = [wt.HANDLE]
    k.TerminateProcess.argtypes = [wt.HANDLE, wt.UINT]
    k.CreateProcessW.argtypes = [wt.LPCWSTR, wt.LPWSTR, ctypes.c_void_p, ctypes.c_void_p, wt.BOOL, wt.DWORD,
                                 ctypes.c_void_p, wt.LPCWSTR, ctypes.c_void_p, ctypes.c_void_p]
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
    k.VirtualAllocEx.restype = ctypes.c_void_p
    k.VirtualAllocEx.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD, wt.DWORD]
    mem = k.VirtualAllocEx(hproc, None, 0x1000, 0x3000, 0x40)
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


def run(launcher, game_dir, args, timeout, version_lie=True, probes=(), focus_rva=None, defocus_at=None):
    """Start `launcher` (retail's lotrbfme2.exe, which hands game.dat its start-up
    token; game.dat started directly exits 0 at once) under a debugger that
    follows children; the child whose image is game.dat is the one classified.
    `probes` (RVAs) get one-shot breakpoints once the loader has relocated the
    image; the ones reached are listed in res["probes_hit"]. `focus_rva`: the
    WM_ACTIVATEAPP arm, where a deactivation is rewritten to an activation (the
    focus lie). `defocus_at` (seconds): minimise the game window then (Windows
    activates another one), and show it again unactivated 15 s before the end."""
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
    res = {"first_chance": [], "first_chance_count": 0, "processes": [], "probes_hit": []}
    armed, focus, stepping = {}, {}, {}
    if focus_rva is not None:
        res["focus_lie"] = {"rva": hex(focus_rva), "hits": 0, "rewritten": 0}
    u = ctypes.WinDLL("user32")
    u.ShowWindowAsync.argtypes = [wt.HWND, ctypes.c_int]   # never wait on a thread stopped at a breakpoint
    t0 = time.time()
    try:
        while True:
            left = timeout - (time.time() - t0)
            if left <= 0:
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
            if not k.WaitForDebugEvent(ev, int(min(left, 1.0) * 1000)):
                continue
            code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
            status = DBG_CONTINUE
            game = pid == res.get("pid")
            if code == CREATE_PROCESS:
                k.CloseHandle(int.from_bytes(ev.raw[16:24], "little"))
                h = int.from_bytes(ev.raw[24:32], "little")
                buf, n = ctypes.create_unicode_buffer(1024), wt.DWORD(1024)
                k.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(n))
                procs[pid] = (h, buf.value, int.from_bytes(ev.raw[40:48], "little"))
                if Path(buf.value).name.lower() == "game.dat":
                    res["main_thread"] = int.from_bytes(ev.raw[32:40], "little")
                res["processes"].append(Path(buf.value).name)
                if Path(buf.value).name.lower() == "game.dat":
                    res.update(pid=pid, image_base=procs[pid][2], started=round(time.time() - t0, 1))
            elif code == LOAD_DLL:
                h = int.from_bytes(ev.raw[16:24], "little")
                if h:
                    k.CloseHandle(h)
            elif code == EXIT_PROCESS and game:
                res.update(outcome="exit", exit_code=int.from_bytes(ev.raw[16:20], "little"),
                           seconds=round(time.time() - t0, 1))
                k.ContinueDebugEvent(pid, tid, DBG_CONTINUE)
                break
            elif code == EXCEPTION:
                exc = int.from_bytes(ev.raw[16:20], "little")
                addr = int.from_bytes(ev.raw[32:40], "little")
                first = int.from_bytes(ev.raw[168:172], "little")
                nparam = int.from_bytes(ev.raw[40:44], "little")
                info = [int.from_bytes(ev.raw[48 + 8 * i:56 + 8 * i], "little") for i in range(min(nparam, 2))]
                hit = next((a for a in (addr, addr - 1) if a in armed), None) if exc in BREAKPOINTS and game else None
                at_focus = next((a for a in (addr, addr - 1) if a in focus), None) \
                    if exc in BREAKPOINTS and game else None
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
                elif exc == 0x4000001F and pid in procs and len(procs[pid]) == 3:
                    h, path, base = procs[pid]
                    procs[pid] += (xp_version_lie(k, h, base, path) if version_lie else [],)
                    res.setdefault("version_lie", {})[Path(path).name] = procs[pid][3]
                    if game and probes:
                        armed.update(set_probes(k, h, base, probes))
                        res["probes_armed"] = len(armed)
                    if game and focus_rva is not None:
                        focus.update(set_probes(k, h, base, [focus_rva]))
                        res["focus_lie"]["armed"] = bool(focus)
                if exc not in BREAKPOINTS and not handled:
                    status = DBG_NOT_HANDLED
                    if first and game:
                        res["first_chance_count"] += 1
                        if exc not in QUIET and len(res["first_chance"]) < 10:
                            res["first_chance"].append([hex(exc), addr, info])
                            if exc == 0xC0000005 and "stack" not in res:   # the fault itself, not the WOW64 rethrow
                                res["stack"] = stack_words(k, procs[pid][0], tid)
                                res["fault"] = addr
                    elif not first and game:
                        res.update(outcome="crash", code=hex(exc), address=res.get("fault", addr), info=info,
                                   seconds=round(time.time() - t0, 1))
                        res.setdefault("stack", stack_words(k, procs[pid][0], tid))
                        break
            k.ContinueDebugEvent(pid, tid, status)
        if res["outcome"] == "timeout":
            res["main_eips"] = sample_eips(k, res["main_thread"])
            res["windows"] = [(t, r) for t, r, _ in windows_of(res["pid"])]
            res["screenshot"] = screenshot(res["pid"])
    finally:
        for pid, (h, *_rest) in procs.items():
            k.TerminateProcess(h, 1)
        for pid, (h, *_rest) in procs.items():      # gone before game.dat is written again
            k.WaitForSingleObject(wt.HANDLE(h), 30000)
        k.CloseHandle(pi.hThread)
        k.CloseHandle(pi.hProcess)
    return res


class WOW64_CONTEXT(ctypes.Structure):
    _fields_ = [("flags", wt.DWORD), ("dr", wt.DWORD * 6), ("fpu", ctypes.c_byte * 112), ("seg", wt.DWORD * 4),
                ("edi", wt.DWORD), ("esi", wt.DWORD), ("ebx", wt.DWORD), ("edx", wt.DWORD), ("ecx", wt.DWORD),
                ("eax", wt.DWORD), ("ebp", wt.DWORD), ("eip", wt.DWORD), ("cs", wt.DWORD), ("eflags", wt.DWORD),
                ("esp", wt.DWORD), ("ss", wt.DWORD), ("ext", ctypes.c_byte * 512)]


def stack_words(k, hproc, tid, n=2048):
    """(esp, [dwords from esp]) of the faulting WOW64 thread: return-address candidates."""
    k.OpenThread.restype = wt.HANDLE
    h = k.OpenThread(0x1FFFFF, False, tid)
    ctx = WOW64_CONTEXT()
    ctx.flags = 0x10003                       # WOW64_CONTEXT_CONTROL | INTEGER
    if not h or not k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
        return None
    k.CloseHandle(h)
    buf, got = ctypes.create_string_buffer(n * 4), ctypes.c_size_t()
    k.ReadProcessMemory(wt.HANDLE(hproc), ctypes.c_void_p(ctx.esp), buf, n * 4, ctypes.byref(got))
    return {"esp": ctx.esp, "ebp": ctx.ebp, "regs": {r: hex(getattr(ctx, r)) for r in
                                                      ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "eip")},
            "words": [int.from_bytes(buf.raw[i:i + 4], "little") for i in range(0, got.value, 4)]}


def sample_eips(k, hthread, n=8):
    """EIPs of the game's main thread sampled 250 ms apart (where a hang spins)."""
    out = []
    for _ in range(n):
        ctx = WOW64_CONTEXT()
        ctx.flags = 0x10001
        k.Wow64SuspendThread(wt.HANDLE(hthread))
        if k.Wow64GetThreadContext(wt.HANDLE(hthread), ctypes.byref(ctx)):
            out.append(ctx.eip)
        k.ResumeThread(wt.HANDLE(hthread))
        time.sleep(0.25)
    return out


def screenshot(pid):
    """The game window's own picture, never the screen: a screen grab shows whatever
    lies on top of the window, which may be anything on the owner's desktop."""
    from PIL import ImageStat
    wins = [w for w in windows_of(pid) if w[1][2] - w[1][0] > 100 and w[1][3] - w[1][1] > 100]
    if not wins:
        return None
    _, _, h = max(wins, key=lambda w: (w[1][2] - w[1][0]) * (w[1][3] - w[1][1]))
    u = ctypes.WinDLL("user32")
    rc = wt.RECT()
    u.GetClientRect(h, ctypes.byref(rc))
    img = window_image(h, rc.right, rc.bottom)
    if img is None:                           # nothing rendered (all black) or the capture failed
        return {"capture": "none"}
    how = "PrintWindow"
    path = OUT / f"smoke_{pid}.png"
    img.save(path)
    stat = ImageStat.Stat(img.convert("L"))
    out = {"path": str(path), "mean": round(stat.mean[0], 1), "stddev": round(stat.stddev[0], 1), "capture": how,
           "menu_bar": menu_bar(img)}
    ref = OUT / "smoke_retail.json"
    try:
        shot = json.loads(ref.read_text())["run"]["screenshot"]["path"]
        out["differs_from_retail"] = image_distance(img, shot)
    except (OSError, KeyError, TypeError, ValueError):
        pass
    return out


def window_image(h, w, ht):
    """The window's own client-area pixels (PrintWindow, PW_CLIENTONLY |
    PW_RENDERFULLCONTENT), so a window under another one is still seen; None
    when the capture fails or comes back black."""
    from PIL import Image
    if w <= 0 or ht <= 0:
        return None
    u, g = ctypes.WinDLL("user32"), ctypes.WinDLL("gdi32")
    u.GetDC.restype = g.CreateCompatibleDC.restype = g.CreateCompatibleBitmap.restype = wt.HANDLE
    g.SelectObject.argtypes = [wt.HANDLE, wt.HANDLE]
    g.CreateCompatibleDC.argtypes = [wt.HANDLE]
    g.CreateCompatibleBitmap.argtypes = [wt.HANDLE, ctypes.c_int, ctypes.c_int]
    g.DeleteObject.argtypes = g.DeleteDC.argtypes = [wt.HANDLE]
    u.ReleaseDC.argtypes = [wt.HWND, wt.HANDLE]
    u.PrintWindow.argtypes = [wt.HWND, wt.HANDLE, wt.UINT]
    g.GetDIBits.argtypes = [wt.HANDLE, wt.HANDLE, wt.UINT, wt.UINT, ctypes.c_void_p, ctypes.c_void_p, wt.UINT]
    sdc = u.GetDC(None)
    mdc = g.CreateCompatibleDC(sdc)
    bmp = g.CreateCompatibleBitmap(sdc, w, ht)
    g.SelectObject(mdc, bmp)
    ok = u.PrintWindow(h, mdc, 3)
    info = struct.pack("<IiiHHIIiiII", 40, w, -ht, 1, 32, 0, 0, 0, 0, 0, 0)
    buf = ctypes.create_string_buffer(w * ht * 4)
    got = g.GetDIBits(mdc, bmp, 0, ht, buf, ctypes.create_string_buffer(info, 44), 0)
    g.DeleteObject(bmp)
    g.DeleteDC(mdc)
    u.ReleaseDC(None, sdc)
    if not ok or got != ht:
        return None
    img = Image.frombuffer("RGBX", (w, ht), buf.raw, "raw", "BGRX", 0, 1).convert("RGB")
    return img if img.getextrema() != ((0, 0), (0, 0), (0, 0)) else None


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
    out = {"retail": a.retail, "base": hex(a.base), "args": a.args,
           "overlay": a.overlay if rows is None else f"{len(rows)} row(s)"}
    authored = []
    if a.retail:
        exe, pieces_map, base = boot_image.build.EXE, None, boot_image.RETAIL_BASE
    else:
        if a.no_build:
            rep = json.loads((OUT / f"{tag}.json").read_text())
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
    shutil.copyfile(exe, a.game_dir / "game.dat")
    before = {str(g): snapshot(g) for g in a.guard}
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
              sorted(moved) if a.probes else (), focus_rva, a.defocus)
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
    if res["outcome"] == "crash":
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
        out["outcome"] = f"crash-at-{row[0] if row else (hex(rva) if rva is not None else 'outside-image')}"
    elif res["outcome"] == "exit" and res.get("fault") is not None and res["exit_code"]:
        # an access violation the game's own handler caught, then exited non-zero
        rva, piece = to_retail(res["fault"], loaded, pieces_map) if pieces_map else (res["fault"] - loaded, "retail")
        row = ledger_row(rva) if rva is not None else None
        out.update(crash={"address": hex(res["fault"]), "retail_rva": hex(rva) if rva is not None else None,
                          "piece": piece, "row": row, "handled_then_exit": res["exit_code"],
                          "authored": blame(rva) if rva is not None else None})
        out["outcome"] = f"crash-at-{row[0] if row else (hex(rva) if rva is not None else 'outside-image')}"
    elif res["outcome"] == "exit":
        out["outcome"] = f"exit-{res['exit_code']:#x}"
    else:
        shot = res.get("screenshot")
        titles = [t for t, _ in res.get("windows", [])]
        eips = []
        for e in res.get("main_eips", []):
            rva, piece = to_retail(e, loaded, pieces_map) if pieces_map else (e - loaded, "retail")
            eips.append([hex(e), hex(rva) if rva is not None else None, ledger_row(rva) if rva is not None else None])
        out["main_thread_samples"] = eips
        if "Exception" in titles:                   # the game's own crash dialog
            out["outcome"] = "crash-dialog"
        else:
            out["outcome"] = ("no-window" if not shot else "no-picture" if "path" not in shot else
                              "reached-menu" if shot["stddev"] > 8 else "blank-window")
            if out["outcome"] == "reached-menu" and shot.get("menu_bar", 0) < MENU_BAR:
                out["outcome"] = "loading-screen"           # alive, but the main menu's button bar is not up
    for g, snap in before.items():
        after = snapshot(Path(g))
        changed = sorted(set(after) ^ set(snap) | {p for p in snap if p in after and after[p] != snap[p]})
        out.setdefault("guard", {})[g] = changed[:20]
        if changed:
            out["outcome"] = "guard-violation"
    return out


def broke(outcome):
    """A start-up the overlay broke: a crash, an exit, no or a blank window (not a slow
    load still showing the splash, not a link or guard failure)."""
    return outcome.startswith(("crash", "exit-")) or outcome in ("no-window", "blank-window")


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
    ap.add_argument("--base", type=lambda v: int(v, 0), default=0x10000000)
    ap.add_argument("--timeout", type=float, default=90)
    ap.add_argument("--args", default="-win")
    ap.add_argument("--guard", type=Path, action="append", default=[])
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
    ap.add_argument("--probes", action="store_true",
                    help="one-shot breakpoints at authored unit starts: which authored code ran (each hit is a "
                         "debugger round trip; 9,001 hits delayed a boot past 150 s)")
    ap.add_argument("--bisect", action="store_true",
                    help="when the overlay fails, halve it to the guilty rows (build/boot/boot_queue.json)")
    a = ap.parse_args(argv)
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
