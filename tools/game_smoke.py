#!/usr/bin/env python3
"""Unattended BFME2 gameplay scenarios (skirmish, save/load, replay determinism), judged deterministically.

  python3 tools/game_smoke.py skirmish --game-dir SANDBOX [--retail] [--seconds 120]
  python3 tools/game_smoke.py record   --game-dir SANDBOX --retail --seconds 120
  python3 tools/game_smoke.py determinism --game-dir SANDBOX [--retail] [--perturb-frame N]
  python3 tools/game_smoke.py playback --game-dir SANDBOX [--retail] --replay NAME
  python3 tools/game_smoke.py save     --game-dir SANDBOX [--retail] --save-after 30
  python3 tools/game_smoke.py load     --game-dir SANDBOX [--retail]

Every scenario starts the game through retail's lotrbfme2.exe under the same
Win32 debugger as tools/boot_smoke.py (XP version lie, child following) and
drives it with the engine's own start-up switches, not clicks:

  skirmish  `-file "maps\\<name>.map"`: GameEngine::init builds a skirmish game
            with slot 0 "Test" (retail 0x22FF4A..0x23010F). A breakpoint after
            `setSlot(0, ...)` finishes what the skirmish menu would do: it sets
            TheGameInfo (retail's -file path leaves it null and crashes) and
            makes slot 1 an easy AI. Judged from GameLogic's own state, read
            every second: pass = game mode is skirmish (2), the logic frame
            advanced at least --min-frames, no crash, a non-blank window.
  record    the reference run: a seeded (--seed, GameInfo+0x50) AI skirmish
            whose logic CRCs the harness takes every --crc-every frames by
            remote-calling GameLogic::getCRC(0) between logic frames (from a
            GameEngine::update breakpoint). Retail makes no CRCs of its own in
            a skirmish and records replays only for LAN/online games.
  determinism  the same seeded skirmish again (no human input, so identical
            logic input); pass = its CRCs equal the record run's on every
            common frame (>= --min-crcs). --perturb-frame N xors the logic
            random seed at frame N: the positive control, which must end
            `desync`. A rebuilt image is judged against retail's record.
  playback  (LAN/online replays; not exercised yet) `-file <name>.rep` (from
            <appdata>/.../Replays): the engine plays a replay back; the
            harness CRCs are compared with --record-json and the engine's own
            RecorderClass::handleCRCMessage (retail 0x37D0A7) calls are logged.
  save      a skirmish; --save-after seconds in, GameState::autoSave() is
            called on the main thread at the top of an engine frame (remote
            call from the GameEngine::update breakpoint); the new save is kept
            as SANDBOX/<--save-name>.
  load      `-file <save>.BfME2Skirmish`: GameEngine::execute loads a save
            named on the command line (retail 0x22D290). pass = skirmish mode,
            first frame >= the save's frame, then --min-frames more.

User data: the game keeps options, saves and replays under
SHGetSpecialFolderPathW(CSIDL_APPDATA) + "My Battle for Middle-earth II Files"
(one call site, retail 0x237C33). The appdata lie points that IAT slot at a
stub returning --appdata (default SANDBOX/../appdata), so nothing reaches the
owner's profile. The sandbox profile is seeded with a fixed Options.ini
(without one the game runs a first-start CPU benchmark that faults under
the debugger). The real profile is still snapshotted (names, sizes, mtimes,
SHA-256 of Options.ini) before and after; any change fails the run with
`profile-changed`, as does any change under HKCU\\Software\\Electronic Arts.

Outcomes (build/game/<scenario>.json, also printed): pass, desync, no-game,
no-frames, crash-at-<row>, exit-<code>, profile-changed, guard-violation.
"""
import argparse
import ctypes
import ctypes.wintypes as wt
import hashlib
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
import boot_smoke  # noqa: E402
from boot_smoke import (DEBUG_PROCESS, DBG_CONTINUE, DBG_NOT_HANDLED, EXCEPTION, CREATE_PROCESS,  # noqa: E402
                        EXIT_PROCESS, LOAD_DLL, QUIET, STARTUPINFO, PROCESS_INFORMATION, WOW64_CONTEXT)

OUT = ROOT / "build" / "game"
CREATE_THREAD, EXIT_THREAD = 2, 4
INT3 = {0x80000003, 0x4000001F}
SINGLE_STEP = {0x80000004, 0x4000001E}
LEAF = "My Battle for Middle-earth II Files"

# Retail game.dat (1.06) RVAs, from the matched tree and retail's own code.
RVA = {
    "TheGameLogic": 0x9FE78C,     # GameLogic*: +0x40 logic frame, +0x110 game mode
    "TheRecorder": 0xA02290,      # RecorderClass*
    "TheSkirmishGameInfo": 0xA02EF0,
    "TheGameInfo": 0xA02EEC,      # GameInfo* of the game being played; the skirmish menu sets it
    "theGameLogicSeed": 0x9BA3D0,  # GetGameLogicRandomValueReal's seed block (6 dwords)
    "fileSlotsSet": 0x2300DC,     # GameEngine::init -file branch, just after setSlot(0, "Test")
    "handleCRCMessage": 0x37D0A7,  # RecorderClass::handleCRCMessage(crc, player, fromPlayback, frame), ret 0x10
    "TheGameState": 0x9FF08C,     # GameState*
    "GameEngine::update": 0x225DA9,  # GameEngine vtable slot 10, called once per engine frame by execute()
    "GameState::autoSave": 0x2DD7E6,
    "GameLogic::getCRC": 0x23CB2C,  # thiscall getCRC(int mode), ret 4; GameLogic::update calls it with 0
    "crcInProgress": 0xA02D87,    # byte GameLogic::update sets around its own getCRC(0) call  # thiscall, no arguments; saveGame(<__AUTO#SAVE__ name>, ...) -> SaveCode
    "Debug::AssertDone/exit": 0x3AAA3,  # `push 1; call exit` after an assertion report (ebx = Debug)
    "Debug::CrashDone/exit": 0x3B0DC,   # the same after a crash report
}
FRAME_OFF, MODE_OFF = 0x40, 0x110
SLOTS_OFF, SLOT_STATE, SLOT_EASY_AI = 0x18, 4, 2
SEED_OFF = 0x50                   # GameInfo::setSeed (retail 0x3FF328) stores here; -file seeds it with time(0)
# -file takes the short form: ConvertShortMapPathToLongMapPath (retail 0x3BA06E)
# turns "maps\<name>.map" into "maps\<name>\<name>.map", the map cache's key.
SKIRMISH_MAP = r"maps\map mp tournament udun.map"
# A fresh profile has no Options.ini, and then the game benchmarks the CPU on
# start-up (bench_with_confidence), which faults in AllocateMemory under the
# debugger and exits 1. The sandbox profile gets these fixed, low-cost options.
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

# WndProc's WM_ACTIVATEAPP arm (the same pattern fix/p4-boot-bfme2's boot_smoke
# focus lie uses): `cmp ebx,1Ch; jne; cmp dword [ebp+10h],0; setne al; cmp al,[..]`.
FOCUS_ARM = re.compile(rb"\x83\xFB\x1C\x0F\x85....(\x83\x7D\x10\x00)\x0F\x95\xC0\x3A\x05", re.DOTALL)


# --------------------------------------------------------------------------- pure parts (tested)

def pair_crcs(events):
    """Pair the CRC log of a playback run. `events` are (frame, crc, from_playback)
    in call order, as RecorderClass::handleCRCMessage saw them: the recorded
    CRC of a frame arrives with from_playback False, the one this image just
    computed for it with True. Returns {"pairs", "mismatches": [(frame, recorded,
    computed)], "unpaired_recorded", "unpaired_computed", "last_frame"}."""
    rec, comp = {}, {}
    for frame, crc, from_playback in events:
        (comp if from_playback else rec).setdefault(frame, []).append(crc)
    pairs, mism = 0, []
    for frame in sorted(set(rec) & set(comp)):
        for r, c in zip(rec[frame], comp[frame]):
            pairs += 1
            if r != c:
                mism.append((frame, r, c))
    paired = set(rec) & set(comp)
    return {"pairs": pairs, "mismatches": mism,
            "unpaired_recorded": sorted(set(rec) - paired), "unpaired_computed": sorted(set(comp) - paired),
            "last_frame": max(paired) if paired else None}


def judge_playback(crc, recorded_last=None, played_last=None, min_pairs=3, crash=None, slack=50):
    """Outcome of a playback run from its pair_crcs() summary. `recorded_last`
    is the last logic frame the record run saw, `played_last` the last one the
    playback reached; the tail of a recording killed mid-game may be unflushed,
    so `slack` frames of it may be missing."""
    if crash:
        return crash
    if crc["mismatches"]:
        return "desync"
    if crc["pairs"] < min_pairs:
        return "no-crcs"
    if recorded_last is not None and (played_last or 0) < recorded_last - slack:
        return "playback-short"
    return "pass"


def judge_skirmish(samples, want_mode, min_frames, crash=None, shot=None):
    """Outcome of a skirmish from (seconds, frame, mode) samples."""
    if crash:
        return crash
    game = [(t, f) for t, f, m in samples if m == want_mode and f is not None]
    if not game:
        return "no-game"
    if game[-1][1] - game[0][1] < min_frames:
        return "no-frames"
    if shot is not None and shot.get("stddev", 0) <= 8:
        return "blank-window"
    return "pass"


def stub_code(calls, results):
    """x86 for a run of thiscalls: per call, optionally `mov byte [flag], 1`,
    push the args (right to left), `mov ecx, this; mov eax, fn; call eax`,
    `mov [results + 4*i], eax`, clear the flag; then int3."""
    code = b""
    for i, c in enumerate(calls):
        if c.get("flag"):
            code += b"\xC6\x05" + struct.pack("<I", c["flag"]) + b"\x01"
        for arg in reversed(c.get("args", [])):
            code += b"\x68" + struct.pack("<I", arg & 0xFFFFFFFF)
        code += b"\xB9" + struct.pack("<I", c["ecx"]) + b"\xB8" + struct.pack("<I", c["call"]) + b"\xFF\xD0"
        code += b"\xA3" + struct.pack("<I", results + 4 * i)
        if c.get("flag"):
            code += b"\xC6\x05" + struct.pack("<I", c["flag"]) + b"\x00"
    return code + b"\xCC"


class FrameHook:
    """Handler for the GameEngine::update entry breakpoint (once per engine
    frame, between logic frames). At chosen logic frames it remote-calls
    GameLogic::getCRC(0) the way GameLogic::update does (crcInProgress set
    around it), so two runs can be compared frame by frame; on request it
    takes a CRC and then GameState::autoSave() in the same stop."""

    def __init__(self, every=None, at_first=False, modes=(2,)):
        self.every, self.at_first, self.modes = every, at_first, set(modes)
        self.crcs = []                # (logic frame, crc)
        self.save_requested, self.save = False, {}

    def due(self, frame, mode):
        """None, "crc" or "save" for an engine frame at this logic frame/mode."""
        if frame is None or mode not in self.modes:
            return None
        if self.save_requested and not self.save:
            return "save"
        if any(f == frame for f, _ in self.crcs):
            return None
        if self.at_first and not self.crcs:
            return "crc"
        if self.every and frame > 0 and frame % self.every == 0:
            return "crc"
        return None

    def __call__(self, game, tid, ctx):
        frame, mode = game.logic()
        what = self.due(frame, mode)
        if what is None:
            return True
        crc = {"call": game.va("GameLogic::getCRC"), "ecx": game.global_ptr("TheGameLogic"), "args": [0],
               "flag": game.va("crcInProgress")}
        if what == "crc":
            return {"calls": [crc], "keep": True, "done": lambda g, r: self.crcs.append((frame, r[0]))}
        self.save["requested_frame"] = frame
        save = {"call": game.va("GameState::autoSave"), "ecx": game.global_ptr("TheGameState")}

        def saved(g, r):
            self.crcs.append((frame, r[0]))
            self.save.update(frame=frame, crc=r[0], code=r[1], seconds=g.seconds())
        return {"calls": [crc, save], "keep": True, "done": saved}


def profile_snapshot(d):
    """{relative path: (size, mtime_ns)} plus the SHA-256 of Options.ini, so a
    run can prove it never wrote the owner's profile."""
    d = Path(d)
    snap = {str(Path(p).relative_to(d)): v for p, v in boot_smoke.snapshot(d).items()} if d.exists() else {}
    opt = d / "Options.ini"
    sha = hashlib.sha256(opt.read_bytes()).hexdigest() if opt.exists() else None
    return {"files": snap, "options_sha256": sha}


def profile_diff(before, after):
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
            k = winreg.OpenKey(winreg.HKEY_CURRENT_USER, sub)
        except OSError:
            return
        with k:
            i = 0
            while True:
                try:
                    n, v, _ = winreg.EnumValue(k, i)
                except OSError:
                    break
                out[f"{sub}\\{n}"] = repr(v)
                i += 1
            i = 0
            while True:
                try:
                    s = winreg.EnumKey(k, i)
                except OSError:
                    break
                walk(f"{sub}\\{s}")
                i += 1
    walk(path)
    return out


# --------------------------------------------------------------------------- debugger

class Game:
    """One debugged game run: retail's launcher starts game.dat; the debugger
    follows it, applies the lies at the WOW64 loader breakpoint and serves
    breakpoints (RVA -> handler(game, tid, ctx) returning True to keep it)."""

    def __init__(self, game_dir, args, appdata, rva_map=None, focus_lie=True, version_lie=True):
        self.game_dir, self.args, self.appdata = Path(game_dir), args, Path(appdata)
        self.rva_map = rva_map or (lambda r: r)
        self.want_focus, self.want_version = focus_lie, version_lie
        self.k = boot_smoke.k32()
        self.k.QueryFullProcessImageNameW.argtypes = [wt.HANDLE, wt.DWORD, wt.LPWSTR, ctypes.POINTER(wt.DWORD)]
        self.k.OpenThread.restype = wt.HANDLE
        self.k.GetFinalPathNameByHandleW.argtypes = [wt.HANDLE, wt.LPWSTR, wt.DWORD, wt.DWORD]
        self.k.VirtualAllocEx.restype = ctypes.c_void_p
        self.k.VirtualAllocEx.argtypes = [wt.HANDLE, ctypes.c_void_p, ctypes.c_size_t, wt.DWORD, wt.DWORD]
        self.handlers = {}            # rva -> handler
        self.bps = {}                 # va -> (original byte, handler)
        self.stepping = {}            # tid -> va to re-arm after the single step
        self.calls = {}               # stub int3 va -> (saved full context, bp va, keep, done callback)
        self.dlls = []                # (base, file name) of the game's DLLs
        self.stub = None
        self.procs = {}
        self.pid = self.hproc = self.base = None
        self.res = {"first_chance": [], "processes": [], "lies": {}}
        self.t0 = None

    # memory -----------------------------------------------------------------
    def read(self, va, n):
        buf, got = ctypes.create_string_buffer(n), ctypes.c_size_t()
        if not self.k.ReadProcessMemory(wt.HANDLE(self.hproc), ctypes.c_void_p(va), buf, n, ctypes.byref(got)):
            return None
        return buf.raw[:got.value]

    def u32(self, va):
        b = self.read(va, 4)
        return struct.unpack("<I", b)[0] if b and len(b) == 4 else None

    def write(self, va, data, code=False):
        old = wt.DWORD()
        self.k.VirtualProtectEx(wt.HANDLE(self.hproc), ctypes.c_void_p(va), len(data), 0x40, ctypes.byref(old))
        ok = self.k.WriteProcessMemory(wt.HANDLE(self.hproc), ctypes.c_void_p(va), data, len(data), None)
        self.k.VirtualProtectEx(wt.HANDLE(self.hproc), ctypes.c_void_p(va), len(data), old.value,
                                ctypes.byref(old))
        if code:
            self.k.FlushInstructionCache(wt.HANDLE(self.hproc), ctypes.c_void_p(va), len(data))
        return bool(ok)

    def va(self, name):
        return self.base + self.rva_map(RVA[name])

    def global_ptr(self, name):
        return self.u32(self.va(name))

    def logic(self):
        """(frame, mode) of TheGameLogic, or (None, None) before it exists."""
        gl = self.global_ptr("TheGameLogic") if self.base else None
        if not gl:
            return None, None
        return self.u32(gl + FRAME_OFF), self.u32(gl + MODE_OFF)

    def seconds(self):
        return round(time.time() - self.t0, 1)

    # lies -------------------------------------------------------------------
    def appdata_lie(self, exe):
        """SHGetSpecialFolderPathW: CSIDL_APPDATA (0x1A) and CSIDL_MYPICTURES
        (0x27) answer `self.appdata`; every other folder goes to the real call."""
        import pefile
        pe = pefile.PE(str(exe), fast_load=True)
        pe.parse_data_directories([1])
        slot = None
        for d in pe.DIRECTORY_ENTRY_IMPORT:
            for imp in d.imports:
                if d.dll.lower() == b"shell32.dll" and imp.name == b"SHGetSpecialFolderPathW":
                    slot = imp.address - pe.OPTIONAL_HEADER.ImageBase + self.base
        pe.close()
        if slot is None:
            return "no SHGetSpecialFolderPathW import"
        mem = self.k.VirtualAllocEx(self.hproc, None, 0x1000, 0x3000, 0x40)
        path = (str(self.appdata.resolve()).rstrip("\\") + "\0").encode("utf-16-le")
        code = (bytes.fromhex("8B44240C 25FF000000 83F81A 740B 83F827 7406 FF25") + struct.pack("<I", mem + 0x80)
                + bytes.fromhex("56 57 8B7C2410 BE") + struct.pack("<I", mem + 0x100)
                + b"\xB9" + struct.pack("<I", len(path)) + bytes.fromhex("F3A4 5F 5E B801000000 C21000"))
        orig = self.u32(slot)
        blob = code.ljust(0x80, b"\xCC") + struct.pack("<I", orig).ljust(0x80, b"\0") + path
        self.write(mem, blob)
        self.write(slot, struct.pack("<I", mem))
        return {"slot": hex(slot), "appdata": str(self.appdata.resolve())}

    def focus_rva(self, exe):
        import pefile
        pe = pefile.PE(str(exe), fast_load=True)
        hits = []
        for sec in pe.sections:
            if sec.Characteristics & 0x20000000:
                hits += [sec.VirtualAddress + m.start(1) for m in FOCUS_ARM.finditer(sec.get_data())]
        pe.close()
        return hits[0] if len(hits) == 1 else None

    def _focus(self, tid, ctx):
        """A WM_ACTIVATEAPP(FALSE) becomes TRUE: the engine never pauses for focus loss."""
        slot = ctx.ebp + 0x10
        if self.read(slot, 4) == bytes(4):
            self.write(slot, struct.pack("<I", 1))
            self.res["lies"]["focus_rewritten"] = self.res["lies"].get("focus_rewritten", 0) + 1
        return True

    # breakpoints ------------------------------------------------------------
    def on(self, name, handler):
        """Break at retail RVA[name] (moved by rva_map for a rebuilt image)."""
        self.handlers[self.rva_map(RVA[name])] = handler

    def _arm(self, va, handler):
        orig = self.read(va, 1)
        if orig and self.write(va, b"\xCC", code=True):
            self.bps[va] = (orig, handler)

    def _context(self, tid, flags=0x10003):
        h = self.k.OpenThread(0x1FFFFF, False, tid)
        ctx = WOW64_CONTEXT()
        ctx.flags = flags
        if not h or not self.k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx)):
            if h:
                self.k.CloseHandle(h)
            return None, None
        return h, ctx

    def arm(self, name, handler):
        """Arm a breakpoint at run time (from a tick)."""
        self._arm(self.va(name), handler)

    def _hit(self, tid, va):
        orig, handler = self.bps[va]
        h, ctx = self._context(tid)
        if ctx is None:
            return
        eip = ctx.eip
        keep = handler(self, tid, ctx)
        self.write(va, orig, code=True)
        if isinstance(keep, dict):                    # {"call": va, "ecx": this, "done": f(game, eax)}
            self._call(h, tid, va, keep)
            return
        if ctx.eip == eip:                            # resume at the breakpoint (else the handler jumped)
            ctx.eip = va
        if keep:
            ctx.eflags |= 0x100
            self.stepping[tid] = va
        else:
            del self.bps[va]
        self.k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
        self.k.CloseHandle(h)

    def _call(self, h, tid, va, req):
        """Run req["calls"] (each {"call": va, "ecx": this, "args": [...], "flag":
        byte va set to 1 around it}; or one such dict as req itself) on this
        thread from the breakpoint at `va`, then resume exactly where it
        stopped: the full context is saved here and restored at the stub's
        int3, where req["done"](game, [eax of each call]) runs."""
        full = WOW64_CONTEXT()
        full.flags = 0x1003F                       # WOW64_CONTEXT_ALL (FPU and SSE state too)
        self.k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(full))
        if self.stub is None:
            self.stub = self.k.VirtualAllocEx(self.hproc, None, 0x1000, 0x3000, 0x40)
        calls = req.get("calls") or [req]
        results = self.stub + 0x800
        code = stub_code(calls, results)
        self.write(self.stub, code, code=True)
        self.calls[self.stub + len(code) - 1] = (full, va, req.get("keep", False), req.get("done"), results, len(calls))
        ctx = WOW64_CONTEXT()
        ctx.flags = 0x10003
        self.k.Wow64GetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
        ctx.eip, ctx.esp = self.stub, (ctx.esp - 0x200) & ~0xF
        self.k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
        self.k.CloseHandle(h)

    def _returned(self, tid, at):
        full, va, keep, done, results, n = self.calls.pop(at)
        h, ctx = self._context(tid)
        if done and ctx is not None:
            done(self, list(struct.unpack(f"<{n}I", self.read(results, 4 * n))))
        full.eip = va
        if keep and va in self.bps:
            full.eflags |= 0x100
            self.stepping[tid] = va
        elif va in self.bps:
            del self.bps[va]
        self.k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(full))
        self.k.CloseHandle(h)

    # run --------------------------------------------------------------------
    def run(self, timeout, tick=None, tick_every=1.0):
        """Debug until the game exits, crashes, `tick(game)` returns a reason to
        stop, or `timeout` seconds pass. Returns self.res."""
        k = self.k
        si, pi = STARTUPINFO(), PROCESS_INFORMATION()
        si.cb = ctypes.sizeof(si)
        cmd = ctypes.create_unicode_buffer(f'"{self.game_dir.resolve() / "lotrbfme2.exe"}" {self.args}')
        if not k.CreateProcessW(None, cmd, None, None, False, DEBUG_PROCESS, None, str(self.game_dir.resolve()),
                                ctypes.byref(si), ctypes.byref(pi)):
            raise SystemExit(f"game_smoke: CreateProcess failed ({ctypes.get_last_error()})")
        ev = ctypes.create_string_buffer(256)
        self.t0 = time.time()
        next_tick = self.t0 + tick_every
        res = self.res
        try:
            while True:
                now = time.time()
                if now - self.t0 >= timeout:
                    res["stopped"] = "timeout"
                    break
                if tick and self.pid and now >= next_tick:
                    next_tick = now + tick_every
                    why = tick(self)
                    if why:
                        res["stopped"] = why
                        break
                if not k.WaitForDebugEvent(ev, 200):
                    continue
                code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
                status = DBG_CONTINUE
                game = pid == self.pid
                if code == CREATE_PROCESS:
                    k.CloseHandle(int.from_bytes(ev.raw[16:24], "little"))
                    h = int.from_bytes(ev.raw[24:32], "little")
                    buf, n = ctypes.create_unicode_buffer(1024), wt.DWORD(1024)
                    k.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(n))
                    self.procs[pid] = [h, buf.value, int.from_bytes(ev.raw[40:48], "little"), False]
                    res["processes"].append(Path(buf.value).name)
                    if Path(buf.value).name.lower() == "game.dat":
                        self.pid, self.hproc = pid, h
                        self.base = int.from_bytes(ev.raw[40:48], "little")
                        self.exe = buf.value
                        res.update(image_base=hex(self.base), started=self.seconds())
                elif code == LOAD_DLL:
                    h = int.from_bytes(ev.raw[16:24], "little")
                    if h:
                        if game:
                            buf = ctypes.create_unicode_buffer(1024)
                            if k.GetFinalPathNameByHandleW(wt.HANDLE(h), buf, 1024, 0):
                                self.dlls.append((int.from_bytes(ev.raw[24:32], "little"), buf.value.split("\\")[-1]))
                        k.CloseHandle(h)
                elif code == EXIT_PROCESS and game:
                    res.update(stopped="exit", exit_code=int.from_bytes(ev.raw[16:20], "little"),
                               seconds=self.seconds())
                    k.ContinueDebugEvent(pid, tid, DBG_CONTINUE)
                    break
                elif code == EXCEPTION:
                    exc = int.from_bytes(ev.raw[16:20], "little")
                    addr = int.from_bytes(ev.raw[32:40], "little")
                    first = int.from_bytes(ev.raw[168:172], "little")
                    if exc == 0x4000001F and pid in self.procs and not self.procs[pid][3]:
                        self.procs[pid][3] = True
                        h, path, base, _ = self.procs[pid]
                        if game:
                            self._loaded()
                        elif self.want_version:      # the launcher gets the same version lie as boot_smoke
                            boot_smoke.xp_version_lie(k, h, base, path)
                    elif game and exc in INT3 and (addr in self.calls or addr - 1 in self.calls):
                        self._returned(tid, addr if addr in self.calls else addr - 1)
                    elif game and exc in INT3 and (addr in self.bps or addr - 1 in self.bps):
                        self._hit(tid, addr if addr in self.bps else addr - 1)
                    elif game and exc in SINGLE_STEP and tid in self.stepping:
                        va = self.stepping.pop(tid)
                        if va in self.bps:
                            self.write(va, b"\xCC", code=True)
                    elif exc not in INT3:
                        status = DBG_NOT_HANDLED
                        if first and game:
                            if exc not in QUIET and len(res["first_chance"]) < 10:
                                res["first_chance"].append([hex(exc), hex(addr)])
                                if exc == 0xC0000005 and "fault" not in res:
                                    res["fault"] = addr
                                    res["fault_where"] = self.where(addr)
                                    res["fault_stack"] = self.stack_frames(tid)
                        elif not first and game:
                            res.update(stopped="crash", code=hex(exc), address=res.get("fault", addr),
                                       seconds=self.seconds())
                            break
                k.ContinueDebugEvent(pid, tid, status)
            if res.get("stopped") not in ("exit", "crash") and self.pid:
                res["windows"] = [(t, r) for t, r, _ in boot_smoke.windows_of(self.pid)]
                res["screenshot"] = capture(self.pid, OUT / f"{self.pid}.png")
        finally:
            for h, *_ in self.procs.values():
                k.TerminateProcess(h, 1)
            k.CloseHandle(pi.hThread)
            k.CloseHandle(pi.hProcess)
        return res

    def where(self, va):
        """'module+offset' (or 'image+rva') of an address."""
        if self.base and self.base <= va < self.base + 0xC00000:
            return f"image+{va - self.base:#x}"
        below = [(b, n) for b, n in self.dlls if b <= va]
        if below:
            b, n = max(below)
            return f"{n}+{va - b:#x}"
        return hex(va)

    def stack_frames(self, tid, n=24):
        """Return-address candidates in the image on tid's stack, as image RVAs."""
        h, ctx = self._context(tid)
        if ctx is None:
            return []
        self.k.CloseHandle(h)
        stack = self.read(ctx.esp, 0x1000) or b""
        words = [struct.unpack_from("<I", stack, i)[0] for i in range(0, len(stack) - 3, 4)]
        return [self.where(w) for w in words if self.base <= w < self.base + 0xC00000][:n]

    def _debug_exit(self, tid, ctx):
        """The game's own assertion/crash report is about to exit(1): keep its
        text (printable runs in the Debug object) and the return addresses."""
        blob = self.read(ctx.ebx, 0xA000) or b""
        texts = sorted({m.group().decode("latin1") for m in re.finditer(rb"[\x20-\x7E\r\n\t]{12,}", blob)},
                       key=len, reverse=True)[:8]
        stack = self.read(ctx.esp, 0x800) or b""
        words = [struct.unpack_from("<I", stack, i)[0] for i in range(0, len(stack) - 3, 4)]
        size = 0xC00000
        msg = self.read(self.u32(ctx.ebp - 8) or 0, 0x800) or b""      # the report AssertDone/CrashDone built
        self.res["debug_exit"] = {"at": hex(ctx.eip - self.base), "texts": texts,
                                  "report": msg.split(b"\0")[0].decode("latin1"),
                                  "returns": [hex(w - self.base) for w in words if self.base <= w < self.base + size][:24]}
        return False

    def _loaded(self):
        """WOW64 loader breakpoint of game.dat: imports are bound, nothing ran yet."""
        lies = self.res["lies"]
        if self.want_version:
            lies["version"] = boot_smoke.xp_version_lie(self.k, self.hproc, self.base, self.exe)
        lies["appdata"] = self.appdata_lie(self.exe)
        if self.want_focus:
            rva = self.focus_rva(self.exe)
            lies["focus"] = hex(rva) if rva is not None else "WM_ACTIVATEAPP arm not found"
            if rva is not None:
                self._arm(self.base + rva, Game._focus)
        for name in ("Debug::AssertDone/exit", "Debug::CrashDone/exit"):
            self._arm(self.va(name), Game._debug_exit)
        for rva, handler in self.handlers.items():
            self._arm(self.base + rva, handler)


def capture(pid, path):
    """Client-area screenshot of pid's largest window (PrintWindow, so a covered
    window is still seen); {"path", "mean", "stddev"} or None."""
    from PIL import Image, ImageStat
    wins = [w for w in boot_smoke.windows_of(pid) if w[1][2] - w[1][0] > 100 and w[1][3] - w[1][1] > 100]
    if not wins:
        return None
    h = max(wins, key=lambda w: (w[1][2] - w[1][0]) * (w[1][3] - w[1][1]))[2]
    u, g = ctypes.WinDLL("user32"), ctypes.WinDLL("gdi32")
    rc = wt.RECT()
    u.GetClientRect(h, ctypes.byref(rc))
    w, ht = rc.right, rc.bottom
    if w <= 0 or ht <= 0:
        return None
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
    ok = u.PrintWindow(h, mdc, 3)                    # PW_CLIENTONLY | PW_RENDERFULLCONTENT
    info = struct.pack("<IiiHHIIiiII", 40, w, -ht, 1, 32, 0, 0, 0, 0, 0, 0)
    buf = ctypes.create_string_buffer(w * ht * 4)
    got = g.GetDIBits(mdc, bmp, 0, ht, buf, ctypes.create_string_buffer(info, 44), 0)
    g.DeleteObject(bmp)
    g.DeleteDC(mdc)
    u.ReleaseDC(None, sdc)
    if not ok or got != ht:
        return None
    img = Image.frombuffer("RGBX", (w, ht), buf.raw, "raw", "BGRX", 0, 1).convert("RGB")
    img.save(path)
    stat = ImageStat.Stat(img.convert("L"))
    return {"path": str(path), "mean": round(stat.mean[0], 1), "stddev": round(stat.stddev[0], 1)}


# --------------------------------------------------------------------------- scenarios

def profile_dir():
    return Path(os.environ["APPDATA"]) / LEAF


def sandbox_profile(appdata):
    return Path(appdata) / LEAF


def skirmish_setup(ai, seed=None):
    """At GameEngine::init's -file branch, after slot 0 became "Test", finish
    what the skirmish menu would have done: TheGameInfo = TheSkirmishGameInfo
    (retail's -file path leaves it null and GameLogic::update's CRC step then
    faults at 0x24578B), and with `ai` slot 1 becomes an easy AI (state 2,
    accepted and has-map set as GameSlot::setState does). A `seed` replaces the
    time(0) seed, so two runs of one image simulate the same game."""
    def handler(game, tid, ctx):
        info = game.global_ptr("TheSkirmishGameInfo")
        if not info:
            return False
        game.write(game.va("TheGameInfo"), struct.pack("<I", info))
        game.res["setup"] = {"TheGameInfo": hex(info)}
        if seed is not None:
            game.write(info + SEED_OFF, struct.pack("<I", seed & 0xFFFFFFFF))
            game.res["setup"]["seed"] = seed
        slot = game.u32(info + SLOTS_OFF + 4)
        if ai and slot:
            game.res["setup"]["slot1_state_before"] = game.u32(slot + SLOT_STATE)
            game.write(slot + SLOT_STATE, struct.pack("<I", SLOT_EASY_AI))
            game.write(slot + 8, b"\x01\x01")
            game.res["setup"]["ai"] = "slot 1 easy AI"
        return False
    return handler


def skirmish_tick(a, samples, want_mode):
    """Sample the logic every tick; stop --seconds after the skirmish started."""
    def tick(game):
        frame, mode = game.logic()
        samples.append((game.seconds(), frame, mode))
        modes = game.res.setdefault("modes", [])
        if not modes or modes[-1][1] != mode:
            modes.append((game.seconds(), mode, frame))
        started = [t for t, f, m in samples if m == want_mode and f]
        if started and samples[-1][0] - started[0] >= a.seconds:
            return "done"
        return None
    return tick


def piece_mover(pieces):
    """Retail RVA -> RVA in a boot image, from boot_image's pieces map."""
    def move(r):
        for _, rstart, nstart, size in pieces:
            if rstart <= r < rstart + size:
                return nstart + r - rstart
        raise KeyError(hex(r))
    return move


def other_games():
    """[(pid, image path)] of running game.dat processes (any install)."""
    k = ctypes.WinDLL("kernel32")
    k.OpenProcess.restype = wt.HANDLE
    pids, got = (wt.DWORD * 4096)(), wt.DWORD()
    ctypes.WinDLL("psapi").EnumProcesses(pids, ctypes.sizeof(pids), ctypes.byref(got))
    out = []
    for pid in pids[:got.value // 4]:
        h = k.OpenProcess(0x1000, False, pid)            # PROCESS_QUERY_LIMITED_INFORMATION
        if not h:
            continue
        buf, n = ctypes.create_unicode_buffer(1024), wt.DWORD(1024)
        if k.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(n)) and buf.value.lower().endswith("\\game.dat"):
            out.append((pid, buf.value))
        k.CloseHandle(h)
    return out


def launch(a, extra, handlers=(), tick=None, timeout=None):
    """Copy the image under test into the sandbox, run it with the lies, and
    guard the owner's profile, HKCU's EA keys and --guard dirs around the run."""
    OUT.mkdir(parents=True, exist_ok=True)
    gd = a.game_dir
    running = other_games()
    if running:                     # a second instance never starts: say so instead of timing out
        raise SystemExit(f"game_smoke: another game.dat is running: {running}")
    if a.retail:
        exe, rva_map = boot_smoke.boot_image.build.EXE, None
    else:
        rep = json.loads((boot_smoke.OUT / "boot.json").read_text())
        exe, rva_map = boot_smoke.OUT / "boot.exe", piece_mover(rep["pieces_map"])
    shutil.copyfile(exe, gd / "game.dat")
    prof = sandbox_profile(a.appdata)
    prof.mkdir(parents=True, exist_ok=True)
    if not (prof / "Options.ini").exists():
        (prof / "Options.ini").write_text(SANDBOX_OPTIONS)
    before = {"profile": profile_snapshot(profile_dir()), "hkcu": registry_snapshot(),
              "guard": {str(g): boot_smoke.snapshot(g) for g in a.guard}}
    game = Game(gd, f"{a.args} {extra}".strip(), a.appdata, rva_map, focus_lie=not a.no_focus_lie)
    for name, h in handlers:
        game.on(name, h)
    t0 = time.time()
    res = game.run(timeout or a.timeout, tick)
    out = {"args": game.args, "retail": a.retail, "wall_seconds": round(time.time() - t0, 1), "run": res}
    changed = profile_diff(before["profile"], profile_snapshot(profile_dir()))
    hk = registry_snapshot()
    old = before["hkcu"]
    hk_changed = sorted(set(hk) ^ set(old) | {x for x in hk if x in old and hk[x] != old[x]})
    out["profile_guard"] = {"dir": str(profile_dir()), "files": len(before["profile"]["files"]),
                            "options_sha256": before["profile"]["options_sha256"], "changed": changed,
                            "hkcu_values": len(old), "hkcu_changed": hk_changed}
    out["sandbox_profile"] = sorted(str(Path(p).relative_to(a.appdata))
                                    for p in boot_smoke.snapshot(Path(a.appdata)))[:40]
    out["guard"] = {}
    for g, snap in before["guard"].items():
        after = boot_smoke.snapshot(Path(g))
        out["guard"][g] = sorted(set(after) ^ set(snap) | {p for p in snap if p in after and after[p] != snap[p]})[:20]
    return game, out


def crash_outcome(res):
    if res.get("stopped") == "crash":
        return f"crash-at-{res.get('address', 0):#x}"
    if res.get("stopped") == "exit":
        return f"exit-{res.get('exit_code', 0):#x}"
    return None


def finish(a, name, out):
    if out["profile_guard"]["changed"] or out["profile_guard"]["hkcu_changed"]:
        out["outcome"] = "profile-changed"
    if any(out["guard"].values()):
        out["outcome"] = "guard-violation"
    (OUT / f"{name}{'_retail' if a.retail else ''}.json").write_text(json.dumps(out, indent=1, default=str))
    print(json.dumps(out, indent=1, default=str))
    return 0 if out["outcome"] == "pass" else 1


def cmd_skirmish(a, keep_replay=None):
    samples = []
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed))]
    hook = FrameHook(every=a.crc_every, modes=(a.mode,)) if keep_replay else None
    if hook:
        handlers.append(("GameEngine::update", hook))
    game, out = launch(a, f'-file "{a.map}"', handlers, skirmish_tick(a, samples, a.mode))
    out["samples"] = samples
    if hook:
        out["crcs"] = hook.crcs
    res = out["run"]
    out["outcome"] = judge_skirmish(samples, a.mode, a.min_frames, crash_outcome(res), res.get("screenshot"))
    if keep_replay:
        rdir = sandbox_profile(a.appdata) / "Replays"
        last = sorted(rdir.glob("*.BfME2Replay"), key=lambda p: p.stat().st_mtime) if rdir.exists() else []
        if last:
            shutil.copyfile(last[-1], rdir / f"{keep_replay}.rep")
            out["replay"] = {"source": last[-1].name, "kept": str(rdir / f"{keep_replay}.rep"),
                             "bytes": last[-1].stat().st_size}
        elif out["outcome"] == "pass":
            out["outcome"] = "no-replay"
    return finish(a, "record" if keep_replay else "skirmish", out)


def find_saves(appdata):
    d = sandbox_profile(appdata) / "Save"
    return sorted(d.glob("*.*"), key=lambda q: q.stat().st_mtime) if d.exists() else []


def cmd_save(a):
    """Skirmish vs AI; --save-after seconds in, GameState::autoSave() runs at the
    top of the next engine frame (GameEngine::update entry). The save is kept as
    GAME_DIR/<--save-name> for the load run. pass = autoSave returned 0, a new
    save file appeared and the game kept simulating afterwards."""
    samples = []
    before = {q.name for q in find_saves(a.appdata)}
    hook = FrameHook(modes=(a.mode,))
    saved = hook.save
    base_tick = skirmish_tick(a, samples, a.mode)

    def tick(game):
        why = base_tick(game)
        started = [t for t, f, m in samples if m == a.mode and f]
        if started and not hook.save_requested and samples[-1][0] - started[0] >= a.save_after:
            hook.save_requested = True
        return why
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed)), ("GameEngine::update", hook)]
    game, out = launch(a, f'-file "{a.map}"', handlers, tick)
    res = out["run"]
    new = [q for q in find_saves(a.appdata) if q.name not in before]
    after = [f for t, f, m in samples if saved.get("seconds") and t > saved["seconds"] + 2 and m == a.mode]
    out.update(samples=samples[::5], save=saved, new_saves=[q.name for q in new])
    crash = crash_outcome(res)
    if crash:
        out["outcome"] = crash
    elif "code" not in saved:
        out["outcome"] = "save-not-called"
    elif saved["code"] != 0 or not new:
        out["outcome"] = f"save-failed-{saved['code']}"
    elif len(after) < 2 or after[-1] - after[0] < a.min_frames // 4:
        out["outcome"] = "no-frames-after-save"
    else:
        shutil.copyfile(new[-1], a.game_dir / a.save_name)
        out["kept"] = str(a.game_dir / a.save_name)
        out["outcome"] = "pass"
    return finish(a, "save", out)


def cmd_load(a):
    """`-file <save>`: GameEngine::execute loads a .BfME2Skirmish save given on
    the command line (retail 0x22D290..0x22D3F1). pass = skirmish mode, the
    first logic frame seen is at or past the frame the save was taken at (a new
    game would start at 0) and the logic then advances --min-frames."""
    samples = []
    rec = json.loads((OUT / f"save{'_retail' if a.retail else ''}.json").read_text()) if a.saved_frame is None else None
    saved_frame = a.saved_frame if a.saved_frame is not None else rec["save"]["frame"]
    hook = FrameHook(at_first=True, modes=(a.mode,))
    game, out = launch(a, f"-file {a.save_name}", [("GameEngine::update", hook)], skirmish_tick(a, samples, a.mode))
    res = out["run"]
    game_frames = [f for t, f, m in samples if m == a.mode and f]
    out.update(samples=samples[::5], saved_frame=saved_frame, first_game_frame=game_frames[0] if game_frames else None,
               first_crc=hook.crcs[:1])
    if rec and hook.crcs and hook.crcs[0][0] == saved_frame:        # informational: is the loaded state the saved one?
        out["crc_matches_save"] = hook.crcs[0][1] == rec["save"].get("crc")
    out["outcome"] = judge_skirmish(samples, a.mode, a.min_frames, crash_outcome(res), res.get("screenshot"))
    if out["outcome"] == "pass" and game_frames[0] < saved_frame:
        out["outcome"] = "not-restored"
    return finish(a, "load", out)


def perturb_tick(a, game, frame, perturbed):
    """Positive control: xor the logic random seed once at --perturb-frame."""
    if a.perturb_frame is not None and not perturbed and frame and frame >= a.perturb_frame:
        seed = game.va("theGameLogicSeed")
        v = game.u32(seed)
        game.write(seed, struct.pack("<I", v ^ 0x5A5A5A5A))
        perturbed.update(frame=frame, seed_before=hex(v))


def cmd_determinism(a):
    """Twin run: the same seeded AI skirmish as `record` (no human input, so the
    logic sees identical inputs) must produce the record run's harness CRCs
    frame for frame. Retail GameLogic only records a replay for LAN/online
    games (RecorderClass starts recording on MSG_NEW_GAME modes 1 and 5 only,
    retail 0x37D484..0x37D48E), so this is the replay check a skirmish allows.
    pass = at least --min-crcs common frames, none differ."""
    record = json.loads(Path(a.record_json or OUT / "record_retail.json").read_text())
    samples, perturbed = [], {}
    hook = FrameHook(every=a.crc_every, modes=(a.mode,))
    base_tick = skirmish_tick(a, samples, a.mode)

    def tick(game):
        perturb_tick(a, game, samples[-1][1] if samples else None, perturbed)
        return base_tick(game)
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed)), ("GameEngine::update", hook)]
    game, out = launch(a, f'-file "{a.map}"', handlers, tick)
    crc = pair_crcs([(f, c, False) for f, c in record.get("crcs", [])] + [(f, c, True) for f, c in hook.crcs])
    out.update(samples=samples[::5], crcs=hook.crcs, perturbed=perturbed or None, record_seed=record["run"].get(
        "setup", {}).get("seed"), crc=dict(crc, mismatches=crc["mismatches"][:10],
                                           unpaired_recorded=crc["unpaired_recorded"][:10],
                                           unpaired_computed=crc["unpaired_computed"][:10]))
    res = out["run"]
    out["outcome"] = judge_playback(crc, None, None, a.min_crcs, crash_outcome(res))
    if out["outcome"] == "pass" and out["record_seed"] != a.seed:
        out["outcome"] = "seed-differs"
    return finish(a, "determinism_perturbed" if a.perturb_frame is not None else "determinism", out)


def cmd_playback(a):
    events, samples = [], []
    perturbed = {}

    def on_crc(game, tid, ctx):
        crc, player, from_pb, frame = struct.unpack("<IIII", game.read(ctx.esp + 4, 16))
        events.append((frame, crc, bool(from_pb & 0xFF), player))
        return True

    def tick(game):
        frame, mode = game.logic()
        samples.append((game.seconds(), frame, mode))
        modes = game.res.setdefault("modes", [])
        if not modes or modes[-1][1] != mode:
            modes.append((game.seconds(), mode, frame))
        perturb_tick(a, game, frame, perturbed)
        recent = [f for t, f, m in samples if t >= samples[-1][0] - 15]   # playback over: frame still for 15 s
        if len(samples) > 20 and frame and len(set(recent)) == 1:
            return "frames-stopped"
        return None
    record = json.loads(Path(a.record_json or OUT / "record_retail.json").read_text())
    hook = FrameHook(every=a.crc_every, modes=a.playback_modes)
    game, out = launch(a, f"-file {a.replay}.rep", [("handleCRCMessage", on_crc), ("GameEngine::update", hook)], tick)
    # retail GameLogic::update makes no CRCs in a skirmish (mode 2 clears the flag at
    # 0x24579D), so the engine's own replay check has nothing to compare; the
    # harness's getCRC samples are compared with the record run's instead.
    crc = pair_crcs([(f, c, False) for f, c in record.get("crcs", [])] + [(f, c, True) for f, c in hook.crcs])
    out.update(samples=samples[-5:], engine_crc_events=len(events), perturbed=perturbed or None,
               harness_crcs=len(hook.crcs),
               crc=dict(crc, mismatches=crc["mismatches"][:10], unpaired_recorded=crc["unpaired_recorded"][:10],
                        unpaired_computed=crc["unpaired_computed"][:10]))
    out["crc_head"] = [[f, hex(c), p, pl] for f, c, p, pl in events[:12]]
    res = out["run"]
    crashed = crash_outcome(res) if res.get("stopped") == "crash" else None
    if a.recorded_last is None:
        a.recorded_last = max((f for _, f, m in record["samples"] if f is not None and m == a.mode), default=None)
    played = max((f for _, f, m in samples if f is not None), default=None)
    out.update(recorded_last=a.recorded_last, played_last=played)
    out["outcome"] = judge_playback(crc, a.recorded_last, played, a.min_crcs, crashed)
    return finish(a, "playback_perturbed" if a.perturb_frame is not None else "playback", out)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("scenario", choices=["skirmish", "record", "determinism", "playback", "save", "load"])
    ap.add_argument("--game-dir", type=Path, required=True)
    ap.add_argument("--appdata", type=Path, help="sandbox user-data root (default GAME_DIR/../appdata)")
    ap.add_argument("--retail", action="store_true", help="control: retail's own game.dat")
    ap.add_argument("--args", default="-win -xres 1024 -yres 768")
    ap.add_argument("--map", default=SKIRMISH_MAP)
    ap.add_argument("--mode", type=int, default=2, help="GameLogic game mode of a skirmish")
    ap.add_argument("--no-ai", action="store_true")
    ap.add_argument("--seed", type=lambda v: int(v, 0), default=1, help="skirmish seed (GameInfo+0x50)")
    ap.add_argument("--seconds", type=float, default=60, help="skirmish seconds to simulate")
    ap.add_argument("--min-frames", type=int, default=100)
    ap.add_argument("--timeout", type=float, default=240)
    ap.add_argument("--replay", default="smoke")
    ap.add_argument("--perturb-frame", type=int)
    ap.add_argument("--recorded-last", type=int,
                    help="last logic frame of the recording (default: build/game/record_retail.json)")
    ap.add_argument("--min-crcs", type=int, default=3)
    ap.add_argument("--crc-every", type=int, default=25, help="logic frames between harness CRC samples")
    ap.add_argument("--record-json", type=Path, help="record run to compare with (default build/game/record_retail.json)")
    ap.add_argument("--playback-modes", type=lambda v: [int(x) for x in v.split(",")],
                    default=[0, 1, 2, 3, 4, 5, 6, 7, 8],
                    help="GameLogic modes sampled in playback (9, seen before a -file game starts, is left out)")
    ap.add_argument("--save-after", type=float, default=30, help="skirmish seconds before the autosave")
    ap.add_argument("--save-name", default="smoke.BfME2Skirmish", help="the save, kept in GAME_DIR")
    ap.add_argument("--saved-frame", type=int, help="load: frame the save was taken at (default: save run's)")
    ap.add_argument("--guard", type=Path, action="append", default=[])
    ap.add_argument("--no-focus-lie", action="store_true")
    a = ap.parse_args(argv)
    a.appdata = a.appdata or a.game_dir.resolve().parent / "appdata"
    ctypes.WinDLL("user32").SetProcessDPIAware()
    for g in a.guard:
        if a.game_dir.resolve() == g.resolve() or g.resolve() in a.game_dir.resolve().parents:
            raise SystemExit(f"game_smoke: --game-dir is inside guarded {g}")
    if a.scenario == "skirmish":
        return cmd_skirmish(a)
    if a.scenario == "record":
        return cmd_skirmish(a, keep_replay=a.replay)
    if a.scenario == "determinism":
        return cmd_determinism(a)
    if a.scenario == "save":
        return cmd_save(a)
    if a.scenario == "load":
        return cmd_load(a)
    return cmd_playback(a)


if __name__ == "__main__":
    sys.exit(main())
