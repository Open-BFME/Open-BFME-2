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
            first frame >= the save's frame, then --min-frames more. --save PATH
            (with --saved-frame) loads another run's save: a cross-build load.
  reload    a --player skirmish saves at --save-frame, loads in game at --load-frame
            and plays on; its CRCs after the load are kept, and so is the save
            (build/game/reload_<image>.BfME2Skirmish), for another build to load.
  suite     G4/G5's judge, run anywhere (no game): `suite RUN.json|JOBDIR... [--bar BAR]`.
            Runs are grouped by their `scenario` (the arguments that decide what is
            simulated); every CRC scheduled by it (every --crc-every frames up to
            --until-frame, after the load for reload/load) must be present. Two
            complete retail runs of a scenario set its bar: the frames retail repeats
            against itself (any shortfall is the bar's reduction, reported). Every
            other run must equal retail at every bar frame; a --perturb-frame run must
            equal it before the perturbation and differ after (caught). --bar takes an
            earlier suite's output, so an image can be judged against retail's bar.

--real-image EXE runs a linked image (exit.exe, exit.map and image_receipt.json
together) instead of a boot_image overlay: tools/real_image.py checks it, and every
harness address (RVA below) is placed through the map before launch, fail-closed: code
by its functions.csv row's name and a byte comparison of the whole body (so a
mid-function address is the row's place plus its offset), data by retail's own
references inside such bodies. Anything unplaceable refuses the run (`image-refused`).
A stray int3 (a stub) is a fault, and crashes are named as in boot_smoke.

User data: the game keeps options, saves and replays under
SHGetSpecialFolderPathW(CSIDL_APPDATA) + "My Battle for Middle-earth II Files"
(one call site, retail 0x237C33). The appdata lie points that IAT slot at a
stub returning --appdata (default SANDBOX/../appdata), so nothing reaches the
owner's profile. The sandbox profile is seeded with a fixed Options.ini
(without one the game runs a first-start CPU benchmark that faults under
the debugger). The redirect, the seeded options and the guard below are
boot_smoke's (one implementation for both tools); a run whose redirect cannot
be installed is killed at the loader breakpoint (`profile-redirect-failed`).
The real profile is still snapshotted (names, sizes, mtimes,
SHA-256 of Options.ini) before and after; any change fails the run with
`profile-changed`, as does any change under HKCU\\Software\\Electronic Arts.

record, reload and load runs carry a `scenario` block for the suite judge, and with
--perturb-frame N each xors the logic random seed once at frame N (reload and load: after
the load), named <scenario>_perturbed: the negative control.

Outcomes (build/game/<scenario>.json, also printed): pass, desync, no-game,
no-frames, no-picture, blank-window, crash-at-<row>, exit-<code>, profile-changed,
guard-violation. skirmish and load need a picture at the end (boot_smoke.window_picture:
PrintWindow on Windows, the Xvfb root under Wine); a black or missing one fails.
"""
import argparse
import collections
import ctypes
import ctypes.wintypes as wt
import hashlib
import json
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
                        EXIT_PROCESS, LOAD_DLL, LOADER_BREAKPOINTS, QUIET, STARTUPINFO,
                        PROCESS_INFORMATION, WOW64_CONTEXT)

OUT = ROOT / "build" / "game"
CREATE_THREAD, EXIT_THREAD = 2, 4
INT3 = {0x80000003, 0x4000001F}
SINGLE_STEP = {0x80000004, 0x4000001E}

# Retail game.dat (1.06) RVAs, from the matched tree and retail's own code.
RVA = {
    "TheGameLogic": 0x9FE78C,     # GameLogic*: +0x40 logic frame, +0x110 game mode
    "TheRecorder": 0xA02290,      # RecorderClass*
    "TheSkirmishGameInfo": 0xA02EF0,
    "TheGameInfo": 0xA02EEC,
    "TheGlobalData": 0x9FE758,    # GlobalData*: +0x1228 fixed seed (-1 = none), honoured by InitRandom 0x233F82      # GameInfo* of the game being played; the skirmish menu sets it
    "theGameLogicSeed": 0x9BA3D0,
    "theGameLogicBaseSeed": 0x9FE734,
    "InitRandom": 0x233F82,       # InitRandom(seed): all three RNGs; GlobalData+0x1228 overrides seed unless -1
    "InitGameLogicRandom": 0x233FC7,  # the seed InitRandom/InitGameLogicRandom last used  # GetGameLogicRandomValueReal's seed block (6 dwords)
    "fileSlotsSet": 0x2300DC,     # GameEngine::init -file branch, just after setSlot(0, "Test")
    "handleCRCMessage": 0x37D0A7,  # RecorderClass::handleCRCMessage(crc, player, fromPlayback, frame), ret 0x10
    "TheGameState": 0x9FF08C,     # GameState*
    "GameEngine::update": 0x225DA9,  # GameEngine vtable slot 10, called once per engine frame by execute()
    "GameState::autoSave": 0x2DD7E6,
    "GameState::loadByName": 0x2DF2F6,    # int (const UnicodeString &name), the in-game load
    "GameLogic::getCRC": 0x23CB2C,  # thiscall getCRC(int mode), ret 4; GameLogic::update calls it with 0
    "crcInProgress": 0xA02D87,
    # GameLogic::getCRC's blocks; with crcInProgress clear, a set byte skips its block
    "crcSkip:objects": 0xA02D7C, "crcSkip:partition": 0xA02D7D, "crcSkip:dfe754": 0xA02D7E,
    "crcSkip:shroud": 0xA02D7F, "crcSkip:dfe750": 0xA02D80, "crcSkip:dfeef8": 0xA02D81,
    "crcSkip:players": 0xA02D83, "crcSkip:ai": 0xA02D84, "crcSkip:livingworld": 0xA02D88,    # byte GameLogic::update sets around its own getCRC(0) call  # thiscall, no arguments; saveGame(<__AUTO#SAVE__ name>, ...) -> SaveCode
    "Debug::AssertDone/exit": 0x3AAA3,  # `push 1; call exit` after an assertion report (ebx = Debug)
    "Debug::CrashDone/exit": 0x3B0DC,   # the same after a crash report
}
FRAME_OFF, MODE_OFF = 0x40, 0x110
SLOTS_OFF, SLOT_STATE, SLOT_EASY_AI = 0x18, 4, 2
# GameSlot+0x18 is the player template (GameSlot::setPlayerTemplate, retail 0x400E33).
# GameSlot::setState leaves -2, the observer, so a -file game has no factions and an
# empty world; -1 (random) is resolved at game start from the game's seed.
SLOT_TEMPLATE, TEMPLATE_RANDOM = 0x18, -1
FIXED_SEED_OFF = 0x1228
USE_FPS_LIMIT_OFF = 0x26          # GlobalData UseFPSLimit (bool; INI field table 0x7E85A0)
AI_STATES = {"easy": 2, "medium": 3, "hard": 4, "brutal": 5}   # GameSlot states (isAI 0x3FF127)
SEED_OFF = 0x50                   # GameInfo::setSeed (retail 0x3FF328) stores here; -file seeds it with time(0)
# -file takes the short form: ConvertShortMapPathToLongMapPath (retail 0x3BA06E)
# turns "maps\<name>.map" into "maps\<name>\<name>.map", the map cache's key.
SKIRMISH_MAP = r"maps\map mp tournament udun.map"
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


def coverage_report(units, covered):
    """Summary of a --coverage run: units probed / run, their bytes, how many first
    ran before the skirmish's first logic frame, and the units that ran (retail
    RVA, size, name, first logic frame), in order of first execution."""
    ran = []
    for t, frame, rva in covered:
        if rva in units:
            r, size, name = units[rva]
            ran.append([hex(r), size, name, frame])
    return {"units": len(units), "units_run": len(ran),
            "bytes": sum(z for _, z, _ in units.values()), "bytes_run": sum(x[1] for x in ran),
            "run_before_game": sum(1 for x in ran if not x[3]), "run": ran}


def ledger_units(rows, code):
    """--coverage-units ledger: [retail RVA, size, name] for every functions.csv row
    (real_image.Rows' (start, size, name, source)) whose start is in retail's code, one per
    start in RVA order: rows sharing a start keep their names sorted and joined by "|" and the
    largest size. A start inside an earlier unit's range is left out (its probe could land
    mid-instruction), as is a start outside code. Returns (units, {why left out: count})."""
    by_start = {}
    for start, size, name, _ in rows:
        by_start.setdefault(start, (set(), []))
        by_start[start][0].add(name)
        by_start[start][1].append(size)
    units, skipped, end = [], {"not code": 0, "inside another row": 0}, 0
    for start in sorted(by_start):
        names, sizes = by_start[start]
        if not code(start):
            skipped["not code"] += 1
            continue
        if start < end:
            skipped["inside another row"] += 1
            continue
        units.append([start, max(sizes), "|".join(sorted(names))])
        end = max(end, start + max(sizes))
    return units, skipped


def units_digest(units):
    """SHA-256 of a coverage unit list, as compact JSON: what a receipt names it by."""
    return hashlib.sha256(json.dumps(units, separators=(",", ":")).encode()).hexdigest()


def coverage_units(a):
    """(units, source) for --coverage: build/boot/IMAGE.json's authored units (the default), or
    with --coverage-units ledger every reverse/functions.csv row of this checkout probed in
    retail's own image (no link, no boot image). source says where the list came from, with its
    hash and the ledger's, for the receipt."""
    if a.coverage_units != "ledger":
        path = boot_smoke.OUT / f"{a.image}.json"
        units = json.loads(path.read_text())["authored"]
        return units, {"units_from": "authored", "file": path.relative_to(ROOT).as_posix(), "units": len(units),
                       "units_sha256": units_digest(units)}
    import real_image
    ledger = real_image.FUNCTIONS
    units, skipped = ledger_units(real_image.Rows(ledger).rows, real_image.Sections(boot_smoke.boot_image.build.EXE).code)
    return units, {"units_from": "ledger", "ledger": ledger.relative_to(ROOT).as_posix(),
                   "ledger_sha256": real_image.sha256_file(ledger), "units": len(units),
                   "units_sha256": units_digest(units), "skipped": skipped}


def coverage_receipt(cov, file):
    """The receipt's coverage section: where the unit list came from and its hash, how many
    probes were armed and how many units ran, and the file holding the units that ran."""
    return dict(cov["source"], armed=cov.get("armed"), units_run=cov["units_run"], bytes_run=cov["bytes_run"],
                run_before_game=cov["run_before_game"], file=file)


def block_diff(a, b):
    """{block: first logic frame whose per-block CRC differs} between two runs'
    FrameHook.blocks lists (only frames both sampled)."""
    bb = dict((f, x) for f, x in b)
    out = {}
    for f, x in a:
        for k, v in x.items():
            if f in bb and k in bb[f] and bb[f][k] != v and k not in out:
                out[k] = f
    return out


def judge_record(outcome, crcs, min_crcs=3):
    """A reference run is usable only if its skirmish passed, it has enough CRCs,
    and they change: a constant CRC means a world where nothing happens (no
    factions), which any image would trivially reproduce."""
    if outcome != "pass":
        return outcome
    if len(crcs) < min_crcs:
        return "no-crcs"
    if len({c for _, c in crcs}) == 1:
        return "crc-constant"
    return "pass"


def judge_skirmish(samples, want_mode, min_frames, crash=None, shot=None):
    """Outcome of a skirmish from (seconds, frame, mode) samples and the end-of-run
    capture. A pass needs a picture: no capture, or a black one, is `no-picture`
    and a flat one `blank-window` (boot_smoke.classify_picture's rules)."""
    if crash:
        return crash
    game = [(t, f) for t, f, m in samples if m == want_mode and f is not None]
    if not game:
        return "no-game"
    if game[-1][1] - game[0][1] < min_frames:
        return "no-frames"
    if not shot or "path" not in shot or shot.get("black", True):
        return "no-picture"
    if shot.get("stddev", 0) <= 8:
        return "blank-window"
    return "pass"


def stub_code(calls, results):
    """x86 for a run of thiscalls: per call, optionally `mov byte [flag], 1`,
    push the args (right to left), `mov ecx, this; mov eax, fn; call eax`,
    `mov [results + 4*i], eax`, clear the flag; then int3. A call's "pre" and
    "post" [(byte va, value)] are stored before and after it."""
    code = b""
    for i, c in enumerate(calls):
        for va, v in c.get("pre", ()):
            code += b"\xC6\x05" + struct.pack("<I", va) + bytes([v & 0xFF])
        if c.get("flag"):
            code += b"\xC6\x05" + struct.pack("<I", c["flag"]) + b"\x01"
        for arg in reversed(c.get("args", [])):
            code += b"\x68" + struct.pack("<I", arg & 0xFFFFFFFF)
        code += b"\xB9" + struct.pack("<I", c["ecx"]) + b"\xB8" + struct.pack("<I", c["call"]) + b"\xFF\xD0"
        code += b"\xA3" + struct.pack("<I", results + 4 * i)
        if c.get("flag"):
            code += b"\xC6\x05" + struct.pack("<I", c["flag"]) + b"\x00"
        for va, v in c.get("post", ()):
            code += b"\xC6\x05" + struct.pack("<I", va) + bytes([v & 0xFF])
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
        self.rng = []                 # (logic frame, logic RNG state hex, base seed) beside each CRC
        self.blocks = []              # (logic frame, {block: CRC of that block + the RNG seed alone})
        self.save_requested, self.save = False, {}
        self.load_name, self.load, self.after_load = None, {}, False
        self.save_at, self.load_at, self.find_save, self.before_load = None, None, None, []
        self.perturb_at, self.perturbed = None, {}   # --perturb-frame: the negative control

    def perturb(self, game, frame, mode):
        """Xor the logic random seed once, at the first engine frame whose logic frame is at least perturb_at, and
        record that frame as read here. In a reload only the loaded game is perturbed: once the first CRC after the
        load has been taken, so the frame is the loaded state's own, never one from before the load."""
        if self.perturb_at is None or self.perturbed or frame is None or mode not in self.modes or frame < self.perturb_at:
            return
        if self.load_at is not None and not self.load.get("first_crc"):
            return
        seed = game.va("theGameLogicSeed")
        v = game.u32(seed)
        game.write(seed, struct.pack("<I", v ^ 0x5A5A5A5A))
        self.perturbed = {"frame": frame, "seed_before": hex(v)}

    def due(self, frame, mode):
        """None, "crc" or "save" for an engine frame at this logic frame/mode."""
        if frame is None or mode not in self.modes:
            return None
        if self.save_at is not None and frame >= self.save_at and not self.save_requested:
            self.save_requested = True
        if self.save_requested and not self.save:
            return "save"
        if self.load_at is not None and frame >= self.load_at and self.save and not self.load_name:
            self.load_name = self.find_save()
        if self.load_name and not self.load:
            return "load"
        if self.after_load:
            return "crc"
        if any(f == frame for f, _ in self.crcs):
            return None
        if self.at_first and not self.crcs:
            return "crc"
        if self.every and frame > 0 and frame % self.every == 0:
            return "crc"
        return None

    def __call__(self, game, tid, ctx):
        frame, mode = game.logic()
        self.perturb(game, frame, mode)
        what = self.due(frame, mode)
        if what is None:
            return True
        crc = {"call": game.va("GameLogic::getCRC"), "ecx": game.global_ptr("TheGameLogic"), "args": [0],
               "flag": game.va("crcInProgress")}
        if what == "load":
            self.load["requested_frame"] = frame
            name = game.unicode_string(self.load_name)
            load = {"call": game.va("GameState::loadByName"), "ecx": game.global_ptr("TheGameState"), "args": [name]}

            def loaded(g, r):
                self.load.update(from_frame=frame, code=r[0], seconds=g.seconds())
                self.after_load = True
                self.before_load, self.crcs = self.crcs, []
            return {"calls": [load], "keep": True, "done": loaded}
        if what == "crc":
            first_after_load, self.after_load = self.after_load, False
            self.rng.append((frame, (game.read(game.va("theGameLogicSeed"), 24) or b"").hex(),
                             game.u32(game.va("theGameLogicBaseSeed"))))
            skips = {n.split(":", 1)[1]: game.va(n) for n in RVA if n.startswith("crcSkip:")}
            orig = {b: (game.read(va, 1) or bytes(1))[0] for b, va in skips.items()}
            calls = [crc]
            for b in skips:                          # each block alone: crcInProgress clear, the others skipped
                calls.append({"call": crc["call"], "ecx": crc["ecx"], "args": [0],
                              "pre": [(va, 0 if o == b else 1) for o, va in skips.items()],
                              "post": [(va, orig[o]) for o, va in skips.items()]})

            def done(g, r):
                self.crcs.append((frame, r[0]))
                if first_after_load:
                    self.load["first_crc"] = (frame, r[0])
                self.blocks.append((frame, dict(zip(skips, r[1:]))))
            return {"calls": calls, "keep": True, "done": done}
        self.save["requested_frame"] = frame
        save = {"call": game.va("GameState::autoSave"), "ecx": game.global_ptr("TheGameState")}
        self.rng.append((frame, (game.read(game.va("theGameLogicSeed"), 24) or b"").hex(),
                         game.u32(game.va("theGameLogicBaseSeed"))))
        skips = {n.split(":", 1)[1]: game.va(n) for n in RVA if n.startswith("crcSkip:")}
        orig = {b: (game.read(va, 1) or bytes(1))[0] for b, va in skips.items()}
        blocks = [{"call": crc["call"], "ecx": crc["ecx"], "args": [0],
                   "pre": [(va, 0 if o == b else 1) for o, va in skips.items()],
                   "post": [(va, orig[o]) for o, va in skips.items()]} for b in skips]

        def saved(g, r):
            self.crcs.append((frame, r[0]))
            self.blocks.append((frame, dict(zip(skips, r[1:-1]))))
            self.save.update(frame=frame, crc=r[0], code=r[-1], seconds=g.seconds())
        return {"calls": [crc, *blocks, save], "keep": True, "done": saved}


# --------------------------------------------------------------------------- debugger

class Game:
    """One debugged game run: retail's launcher starts game.dat; the debugger
    follows it, applies the lies at the WOW64 loader breakpoint and serves
    breakpoints (RVA -> handler(game, tid, ctx) returning True to keep it)."""

    def __init__(self, game_dir, args, appdata, rva_map=None, focus_lie=True, version_lie=True, int3_faults=False):
        self.game_dir, self.args, self.appdata = Path(game_dir), args, Path(appdata)
        self.rva_map = rva_map or (lambda r: r)
        boot_smoke.check_sandbox_appdata(self.appdata)
        self.want_focus, self.want_version = focus_lie, version_lie
        self.int3_faults = int3_faults  # a real image: an int3 the harness did not plant (a stub) is a fault
        self.focus_va = None          # boot_smoke's focus lie (WM_ACTIVATEAPP arm), served by boot_smoke.focus_lie
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
        self.probe_units = {}         # --coverage: RVA in the image -> (retail RVA, size, name)
        self.covered = []             # (seconds, logic frame, image RVA) of each first execution
        self.stub = None
        self.procs = {}
        self.pid = self.hproc = self.base = None
        self.size = 0xC00000
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

    def unicode_string(self, text):
        """The address of a UnicodeString in the game: a pointer to a StringBase header whose
        reference count never reaches zero (+0 count, +4 length, +6 capacity, +8 the characters)."""
        body = struct.pack("<IHH", 0x4000, len(text), len(text) + 1) + (text + "\0").encode("utf-16-le")
        at = boot_smoke.alloc32(self.k, self.hproc, 0x1000)
        self.write(at + 16, body)
        self.write(at, struct.pack("<I", at + 16))
        return at

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
        self.hit_va = va                              # the breakpoint's address (eip may be past the int3)
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
            self.stub = boot_smoke.alloc32(self.k, self.hproc, 0x4000)
        calls = req.get("calls") or [req]
        results = self.stub + 0x3000                  # code before, one dword per call here
        code = stub_code(calls, results)
        if len(code) > 0x3000:
            raise RuntimeError(f"remote-call stub of {len(code)} bytes does not fit")
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
        next_note = self.t0 + 30
        res = self.res
        res["debugger_errors"] = []
        res["cleanup"] = {"terminate": [], "exit_events": [], "wait": [], "close": [], "uncertain_handles": []}
        exited = set()
        termination_requested = set()
        continuation_failed = False
        game_handle = None

        def debugger_error(operation, error):
            res["debugger_errors"].append({"operation": operation, "error": error})
            res["stopped"] = "debugger-error"

        def close_handle(handle, label):
            if handle and handle != (1 << (ctypes.sizeof(wt.HANDLE) * 8)) - 1:
                if not k.CloseHandle(wt.HANDLE(handle)):
                    res["cleanup"]["uncertain_handles"].append({"label": label, "handle": handle})
                    debugger_error(f"CloseHandle:{label}", ctypes.get_last_error())
                else:
                    res["cleanup"]["close"].append(label)

        try:
            while True:
                now = time.time()
                if now - self.t0 >= timeout:
                    res["stopped"] = "timeout"
                    break
                if tick and self.pid and now >= next_tick:
                    next_tick = now + tick_every
                    if now >= next_note:                 # progress on stderr, so a stuck run shows where
                        next_note = now + 30
                        print(f"game_smoke: {self.seconds()} s, logic {self.logic()}, {len(self.bps)} bps",
                              file=sys.stderr, flush=True)
                    why = tick(self)
                    if why:
                        res["stopped"] = why
                        break
                if not k.WaitForDebugEvent(ev, 200):
                    error = ctypes.get_last_error()
                    if error != 121:
                        debugger_error("WaitForDebugEvent", error)
                        break
                    continue
                code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
                status = DBG_CONTINUE
                stop_after_continue = False
                game = pid == self.pid
                if code == CREATE_PROCESS:
                    close_handle(int.from_bytes(ev.raw[16:24], "little"), f"create-process:{pid}")
                    h = int.from_bytes(ev.raw[24:32], "little")
                    buf, n = ctypes.create_unicode_buffer(1024), wt.DWORD(1024)
                    k.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(n))
                    self.procs[pid] = [h, buf.value, int.from_bytes(ev.raw[40:48], "little"), False]
                    res["processes"].append(Path(buf.value).name)
                    if Path(buf.value).name.lower() == "game.dat":
                        if self.pid is not None:
                            debugger_error("CREATE_PROCESS:multiple-game", pid)
                        else:
                            self.pid, self.hproc = pid, h
                            self.base = int.from_bytes(ev.raw[40:48], "little")
                            self.size = image_size(buf.value)
                            self.exe = buf.value
                            res.update(image_base=hex(self.base), started=self.seconds())
                            duplicated = wt.HANDLE()
                            current = k.GetCurrentProcess()
                            if not k.DuplicateHandle(current, wt.HANDLE(h), current, ctypes.byref(duplicated),
                                                     0, False, 0x2) or not duplicated.value:
                                debugger_error("DuplicateHandle:game-process", ctypes.get_last_error())
                            else:
                                game_handle = duplicated.value
                elif code == LOAD_DLL:
                    h = int.from_bytes(ev.raw[16:24], "little")
                    if h:
                        if game:
                            buf = ctypes.create_unicode_buffer(1024)
                            if k.GetFinalPathNameByHandleW(wt.HANDLE(h), buf, 1024, 0):
                                self.dlls.append((int.from_bytes(ev.raw[24:32], "little"), buf.value.split("\\")[-1]))
                        close_handle(h, f"load-dll:{pid}")
                elif code == EXIT_PROCESS and game:
                    res.update(stopped="exit", exit_code=int.from_bytes(ev.raw[16:20], "little"),
                               seconds=self.seconds())
                    stop_after_continue = True
                elif code == EXCEPTION:
                    exc = int.from_bytes(ev.raw[16:20], "little")
                    addr = int.from_bytes(ev.raw[32:40], "little")
                    first = int.from_bytes(ev.raw[168:172], "little")
                    if exc in LOADER_BREAKPOINTS and pid in self.procs and not self.procs[pid][3]:
                        self.procs[pid][3] = True
                        h, path, base, _ = self.procs[pid]
                        if game and not self._loaded():
                            res.update(stopped="profile-redirect-failed")
                            for hp, *_ in self.procs.values():     # killed before the thread is let go
                                if not k.TerminateProcess(wt.HANDLE(hp), 1):
                                    debugger_error("TerminateProcess:profile-redirect", ctypes.get_last_error())
                                else:
                                    termination_requested.add(hp)
                            stop_after_continue = True
                        elif self.want_version:      # the launcher gets the same version lie as boot_smoke
                            boot_smoke.xp_version_lie(k, h, base, path)
                    elif game and exc in INT3 and (addr in self.calls or addr - 1 in self.calls):
                        self._returned(tid, addr if addr in self.calls else addr - 1)
                    elif game and exc in INT3 and self.focus_va in (addr, addr - 1):
                        hits = self.res["lies"]["focus"]
                        hits["hits"] += 1
                        hits["rewritten"] += boot_smoke.focus_lie(k, self.hproc, tid, self.focus_va,
                                                                  self.bps[self.focus_va][0])
                        self.stepping[tid] = self.focus_va
                    elif game and exc in INT3 and (addr in self.bps or addr - 1 in self.bps):
                        self._hit(tid, addr if addr in self.bps else addr - 1)
                    elif game and exc in SINGLE_STEP and tid in self.stepping:
                        va = self.stepping.pop(tid)
                        if va in self.bps:
                            self.write(va, b"\xCC", code=True)
                    elif game and exc in INT3 and self.int3_faults and self.procs[pid][3]:
                        status = DBG_NOT_HANDLED              # a stub (or filler) ran: the game's fault
                        if first:
                            res["first_chance"].append([hex(exc), hex(addr)])
                            if "fault" not in res:
                                res.update(fault=addr, fault_code=hex(exc), fault_where=self.where(addr))
                                self.capture_fault(tid, res)
                        else:
                            res.update(stopped="crash", code=hex(exc), address=res.get("fault", addr),
                                       seconds=self.seconds())
                            stop_after_continue = True
                    elif exc not in INT3:
                        status = DBG_NOT_HANDLED
                        if first and game:
                            if exc not in QUIET and len(res["first_chance"]) < 10:
                                res["first_chance"].append([hex(exc), hex(addr)])
                                if exc == 0xC0000005 and "fault" not in res:
                                    res["fault"] = addr
                                    res["fault_code"] = hex(exc)
                                    res["fault_where"] = self.where(addr)
                                    res["fault_stack"] = self.stack_frames(tid)
                                    self.capture_fault(tid, res)
                        elif not first and game:
                            status = DBG_NOT_HANDLED
                            res.update(stopped="crash", code=hex(exc), address=res.get("fault", addr),
                                       seconds=self.seconds())
                            stop_after_continue = True
                if not k.ContinueDebugEvent(pid, tid, status):
                    debugger_error("ContinueDebugEvent", ctypes.get_last_error())
                    continuation_failed = True
                    break
                if code == EXIT_PROCESS:
                    exited.add(pid)
                if stop_after_continue or res["debugger_errors"]:
                    break
            if res.get("stopped") not in ("exit", "crash", "profile-redirect-failed") and self.pid:
                if not res["debugger_errors"]:
                    res["windows"], res["screenshot"] = self._while_serving(lambda: (
                        [(t, r) for t, r, _ in boot_smoke.windows_of(self.pid)],
                        capture(self.pid, OUT / f"{self.pid}.png")))
        finally:
            cleanup_targets = {pid: proc[0] for pid, proc in self.procs.items() if pid not in exited}
            if pi.pid not in exited and pi.pid not in cleanup_targets:
                cleanup_targets[pi.pid] = pi.hProcess
            for pid, handle in cleanup_targets.items():
                terminated = handle in termination_requested
                if not terminated:
                    terminated = bool(k.TerminateProcess(wt.HANDLE(handle), 1))
                    if not terminated:
                        debugger_error(f"TerminateProcess:{pid}", ctypes.get_last_error())
                res["cleanup"]["terminate"].append({"pid": pid, "ok": terminated})
            deadline = time.monotonic() + 5.0
            pending = set(cleanup_targets)
            if continuation_failed:
                debugger_error("cleanup:uncontinued-event", "previous continuation failed")
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
                debugger_error(f"WaitForSingleObject:{pi.pid}",
                               ctypes.get_last_error() if result == 0xFFFFFFFF else result)
            if game_handle is not None:
                remaining = max(0, int((deadline - time.monotonic()) * 1000))
                result = k.WaitForSingleObject(wt.HANDLE(game_handle), remaining)
                res["cleanup"]["wait"].append({"pid": self.pid, "result": result})
                if result != 0:
                    debugger_error(f"WaitForSingleObject:{self.pid}",
                                   ctypes.get_last_error() if result == 0xFFFFFFFF else result)
                close_handle(game_handle, "game-process")
            close_handle(pi.hThread, "pi-thread")
            close_handle(pi.hProcess, "pi-process")
        if res["debugger_errors"]:
            res["stopped"] = "debugger-error"
        return res

    def where(self, va):
        """'module+offset' (or 'image+rva') of an address."""
        if self.base and self.base <= va < self.base + self.size:
            return f"image+{va - self.base:#x}"
        below = [(b, n) for b, n in self.dlls if b <= va]
        if below:
            b, n = max(below)
            return f"{n}+{va - b:#x}"
        return hex(va)

    def capture_fault(self, tid, res, n=256):
        """boot_smoke's fault capture: fault_words, the dwords from esp (return-address candidates,
        for a real image's map), and fault_context, the registers and what each points at."""
        st = boot_smoke.fault_capture(self.k, self.hproc, tid, n) or {}
        res["fault_words"] = st.get("words", [])
        res["fault_context"] = {key: st[key] for key in ("esp", "ebp", "regs", "memory") if key in st}

    def stack_frames(self, tid, n=24):
        """Return-address candidates in the image on tid's stack, as image RVAs."""
        h, ctx = self._context(tid)
        if ctx is None:
            return []
        self.k.CloseHandle(h)
        stack = self.read(ctx.esp, 0x1000) or b""
        words = [struct.unpack_from("<I", stack, i)[0] for i in range(0, len(stack) - 3, 4)]
        return [self.where(w) for w in words if self.base <= w < self.base + self.size][:n]

    def _seeding(self, tid, ctx):
        """Log every RNG seeding: (seconds, which, seed argument, GlobalData fixed
        seed, logic frame, caller RVA). Rare, so it stays armed."""
        glob = self.global_ptr("TheGlobalData")
        arg, ret = self.u32(ctx.esp + 4), self.u32(ctx.esp)
        which = "InitRandom" if self.hit_va - self.base == self.rva_map(RVA["InitRandom"]) else "InitGameLogicRandom"
        self.res.setdefault("seeding", []).append(
            [self.seconds(), which, arg, self.u32(glob + 0x1228) if glob else None, self.logic()[0],
             hex(ret - self.base) if ret else None])
        return True

    def _debug_exit(self, tid, ctx):
        """The game's own assertion/crash report is about to exit(1): keep its
        text (printable runs in the Debug object) and the return addresses."""
        blob = self.read(ctx.ebx, 0xA000) or b""
        texts = sorted({m.group().decode("latin1") for m in re.finditer(rb"[\x20-\x7E\r\n\t]{12,}", blob)},
                       key=len, reverse=True)[:8]
        stack = self.read(ctx.esp, 0x800) or b""
        words = [struct.unpack_from("<I", stack, i)[0] for i in range(0, len(stack) - 3, 4)]
        size = self.size
        msg = self.read(self.u32(ctx.ebp - 8) or 0, 0x800) or b""      # the report AssertDone/CrashDone built
        self.res["debug_exit"] = {"at": hex(ctx.eip - self.base), "texts": texts,
                                  "report": msg.split(b"\0")[0].decode("latin1"),
                                  "returns": [hex(w - self.base) for w in words if self.base <= w < self.base + size][:24]}
        return False

    def _while_serving(self, work, limit=30.0):
        """Run `work` (window enumeration and capture send messages to the game's
        main thread) on a worker thread while this, the debugger thread, keeps
        serving debug events: with a breakpoint left armed the main thread would
        sit in a debug event nobody continues and the capture would hang. All
        breakpoints are taken out first; a remote call already under way still
        returns through _returned."""
        import threading
        k = self.k
        removed = set(self.bps)
        for va, (orig, _) in list(self.bps.items()):
            self.write(va, orig, code=True)
        self.bps.clear()
        box = {}
        worker = threading.Thread(target=lambda: box.update(r=work()), daemon=True)
        worker.start()
        ev = ctypes.create_string_buffer(256)
        t_end = time.time() + limit
        while worker.is_alive() and time.time() < t_end:
            if not k.WaitForDebugEvent(ev, 100):
                continue
            code, pid, tid = (int.from_bytes(ev.raw[o:o + 4], "little") for o in (0, 4, 8))
            status = DBG_CONTINUE
            if code == CREATE_PROCESS:
                k.CloseHandle(int.from_bytes(ev.raw[16:24], "little"))
            elif code == LOAD_DLL and int.from_bytes(ev.raw[16:24], "little"):
                k.CloseHandle(int.from_bytes(ev.raw[16:24], "little"))
            elif code == EXCEPTION:
                exc = int.from_bytes(ev.raw[16:20], "little")
                addr = int.from_bytes(ev.raw[32:40], "little")
                at = next((x for x in (addr, addr - 1) if x in self.calls), None)
                old = next((x for x in (addr, addr - 1) if x in removed), None)
                if pid == self.pid and exc in INT3 and at is not None:
                    self._returned(tid, at)
                elif pid == self.pid and exc in INT3 and old is not None:   # hit just before the byte went back
                    h, ctx = self._context(tid)
                    if ctx is not None:
                        ctx.eip = old
                        k.Wow64SetThreadContext(wt.HANDLE(h), ctypes.byref(ctx))
                        k.CloseHandle(h)
                elif exc in SINGLE_STEP and pid == self.pid:
                    self.stepping.pop(tid, None)
                elif exc not in INT3:
                    status = DBG_NOT_HANDLED
            k.ContinueDebugEvent(pid, tid, status)
            if code == EXIT_PROCESS and pid == self.pid:
                break
        worker.join(1.0)
        return box.get("r", (None, None))

    def _loaded(self):
        """WOW64 loader breakpoint of game.dat: imports are bound, nothing ran yet.
        The appdata lie goes first; False (the run must stop) if it failed."""
        lies = self.res["lies"]
        try:
            lies["appdata"] = boot_smoke.install_appdata_lie(self.k, self.hproc, self.base, self.exe, self.appdata)
        except (boot_smoke.RedirectError, OSError, ImportError) as e:
            self.res["redirect_error"] = str(e)
            return False
        if self.want_version:
            lies["version"] = boot_smoke.xp_version_lie(self.k, self.hproc, self.base, self.exe)
        if self.want_focus:
            rva = boot_smoke.focus_arm_rva(self.exe)
            lies["focus"] = {"rva": hex(rva) if rva is not None else "WM_ACTIVATEAPP arm not found",
                             "hits": 0, "rewritten": 0}
            if rva is not None:
                self.focus_va = self.base + rva
                self._arm(self.focus_va, None)
        for name in ("Debug::AssertDone/exit", "Debug::CrashDone/exit"):
            self._arm(self.va(name), Game._debug_exit)
        for name in ("InitRandom", "InitGameLogicRandom"):
            self._arm(self.va(name), Game._seeding)
        for rva, handler in self.handlers.items():
            self._arm(self.base + rva, handler)
        armed = 0
        for rva in self.probe_units:                 # one-shot; never on top of a harness breakpoint
            if self.base + rva not in self.bps:
                self._arm(self.base + rva, Game._probe)
                armed += 1
        if self.probe_units:
            self.res["coverage_armed"] = armed
        return True

    def _probe(self, tid, ctx):
        """--coverage: a probed unit's entry ran (first time only)."""
        self.covered.append((self.seconds(), self.logic()[0], self.hit_va - self.base))
        return False


def image_size(exe):
    """SizeOfImage of `exe` (relayout images are larger than retail's)."""
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    size = pe.OPTIONAL_HEADER.SizeOfImage
    pe.close()
    return size


def capture(pid, path):
    """Client-area picture of pid's largest window: boot_smoke.window_picture (PrintWindow
    on Windows, the Xvfb root under Wine, where PrintWindow is black)."""
    return boot_smoke.window_picture(pid, path)


# --------------------------------------------------------------------------- scenarios

def sandbox_profile(appdata):
    return Path(appdata) / boot_smoke.PROFILE_LEAF


def skirmish_setup(ai, seed=None, player=False, players=2, difficulty="easy", fast=False):
    """At GameEngine::init's -file branch, after slot 0 became "Test", finish
    what the skirmish menu would have done: TheGameInfo = TheSkirmishGameInfo
    (retail's -file path leaves it null and GameLogic::update's CRC step then
    faults at 0x24578B), and with `ai` slot 1 becomes an easy AI (state 2,
    accepted and has-map set as GameSlot::setState does). A `seed` replaces the
    time(0) seed, so two runs of one image simulate the same game.

    By default slot 0 (the local player) stays an observer and slots 1 and 2 are
    easy AIs with random factions: nothing typed or clicked into the window can
    issue a command, so outside input cannot change the game (seen live: a run
    with focus changes desynced from frame 25 while its RNG still matched).
    `player` gives slot 0 a random faction instead (and only slot 1 an AI).
    `players` AIs (slots 1..N) of `difficulty` play; `fast` lifts the FPS cap."""
    def handler(game, tid, ctx):
        info = game.global_ptr("TheSkirmishGameInfo")
        if not info:
            return False
        game.write(game.va("TheGameInfo"), struct.pack("<I", info))
        game.res["setup"] = {"TheGameInfo": hex(info)}
        if seed is not None:
            game.write(info + SEED_OFF, struct.pack("<I", seed & 0xFFFFFFFF))
            game.res["setup"]["seed"] = seed
            # -randomSeed's value is back to -1 by now (seen live: the logic RNG base
            # seed was time(0)), so the fixed seed is set here, after start-up parsing
            # and before the game starts; every InitRandom/InitGameLogicRandom uses it.
            glob = game.global_ptr("TheGlobalData")
            if glob:
                game.res["setup"]["fixed_seed_before"] = game.u32(glob + FIXED_SEED_OFF)
                game.write(glob + FIXED_SEED_OFF, struct.pack("<I", seed & 0xFFFFFFFF))
        n_ai = (1 if player else players) if ai else 0
        slots = [game.u32(info + SLOTS_OFF + 4 * i) for i in range(1 + max(n_ai, 2))]
        game.res["setup"]["templates_before"] = [game.u32(sl + SLOT_TEMPLATE) if sl else None for sl in slots]
        ais = list(range(1, 1 + n_ai))
        for i in ([0] if player else []) + ais:
            if slots[i]:
                game.write(slots[i] + SLOT_TEMPLATE, struct.pack("<i", TEMPLATE_RANDOM))
        for i in ais:
            if slots[i]:
                game.res["setup"][f"slot{i}_state_before"] = game.u32(slots[i] + SLOT_STATE)
                game.write(slots[i] + SLOT_STATE, struct.pack("<I", AI_STATES[difficulty]))
                game.write(slots[i] + 8, b"\x01\x01")
        game.res["setup"]["players"] = ("slot 0 player, " if player else "slot 0 observer, ") + \
            ", ".join(f"slot {i} {difficulty} AI" for i in ais)
        if fast:
            # GameEngine::execute copies GlobalData's UseFPSLimit (+0x26) into its
            # frame limiter every frame (retail 0x22D5B3) and GameEngine::update runs
            # one logic frame per 6 client frames (0x225E53): without the cap the
            # game runs as fast as it renders. Logic frames are unchanged, so CRCs
            # stay comparable with an uncapped or capped reference.
            glob = game.global_ptr("TheGlobalData")
            if glob:
                game.write(glob + USE_FPS_LIMIT_OFF, b"\x00")
                game.res["setup"]["fps_limit"] = "off"
        if seed is not None:
            # The logic RNG is seeded once, by GameEngine::init's start-up
            # InitRandom(time(0)) (0x23424C), before GlobalData exists, and a -file
            # skirmish never reseeds (seen live: base seed = time(0) in both runs).
            # The skirmish menu calls InitRandom(seed); so does the harness, here.
            return {"call": game.va("InitRandom"), "ecx": 0, "args": [seed & 0xFFFFFFFF],
                    "done": lambda g, r: g.res["setup"].update(reseeded=g.u32(g.va("theGameLogicBaseSeed")))}
        return False
    return handler


def skirmish_tick(a, samples, want_mode, hook=None):
    """Sample the logic every tick; stop --seconds after the skirmish started, or with
    --until-frame once the logic reaches that frame (and, with a CRC `hook`, once the
    hook has its CRC at or past it), whatever the time."""
    until = getattr(a, "until_frame", None)

    def tick(game):
        frame, mode = game.logic()
        samples.append((game.seconds(), frame, mode))
        modes = game.res.setdefault("modes", [])
        if not modes or modes[-1][1] != mode:
            modes.append((game.seconds(), mode, frame))
        if mode == want_mode and frame is not None:
            a.reached = max(getattr(a, "reached", None) or 0, frame)     # finish() judges --until-frame
        if until is not None:
            if mode == want_mode and frame is not None and frame >= until and \
                    (hook is None or any(f >= until for f, _ in hook.crcs)):
                return "done"
            return None
        started = [t for t, f, m in samples if m == want_mode and f]
        if started and samples[-1][0] - started[0] >= a.seconds:
            return "done"
        return None
    return tick


OURS = (".text$r", ".ordata", ".odata")     # boot_relayout: moved units, our own read-only / writable data


def piece_mover(pieces):
    """Retail RVA -> RVA in a boot image, from boot_image's pieces map
    [[name, retail start, new start, size]]. A relayout image lists a moved unit
    twice: the int3 filler left at its retail range (scaffold name) and the moved
    copy (`.text$r...`); --own-data's `.ordata`/`.odata` copies likewise stand for
    retail's data. The moved/owned copy wins, the filler never does; an address
    in no piece, or in two of one kind, raises KeyError. There is no fall-back
    to the retail RVA."""
    import bisect
    kinds = {True: [], False: []}
    for name, rs, ns, size in pieces:
        kinds[name.startswith(OURS)].append((rs, rs + size, ns, name))
    for v in kinds.values():
        v.sort()
    starts = {k: [x[0] for x in v] for k, v in kinds.items()}

    def find(ours, r):
        v = kinds[ours]
        i = bisect.bisect_right(starts[ours], r) - 1
        hit = [x for x in v[max(0, i - 1):i + 1] if x[0] <= r < x[1]]
        if len(hit) > 1:
            raise KeyError(f"{r:#x} lies in {len(hit)} pieces ({', '.join(h[3] for h in hit)})")
        return hit[0] if hit else None

    def move(r):
        x = find(True, r) or find(False, r)
        if x is None:
            raise KeyError(f"{r:#x} lies in no piece")
        return x[2] + r - x[0]
    move.ours = lambda r: find(True, r) is not None
    return move


def map_addresses(rva_map, names=None):
    """{name: (new RVA, moved-or-owned?)} for every RVA the harness uses, or
    SystemExit naming the ones the image cannot place (never retail's RVA)."""
    out, bad = {}, []
    for name in names or RVA:
        try:
            out[name] = (rva_map(RVA[name]), bool(getattr(rva_map, "ours", lambda r: False)(RVA[name])))
        except KeyError as e:
            bad.append(f"{name} ({RVA[name]:#x}): {e}")
    if bad:
        raise SystemExit("game_smoke: the image cannot place " + "; ".join(bad))
    return out


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
    a.ri = None
    if a.real_image:
        import real_image
        try:
            ri = real_image.load(a.real_image)
            a.ri = ri
            ok, rep = real_image.check(ri)
            placed = map_addresses(ri.rva_map()) if ok else {}    # every harness address, before launching
        except (real_image.RealImageError, SystemExit) as e:
            ok, rep = False, {"refused": str(e)}
        if not ok:
            refuse_image(a, rep)
        rep["folds"] = sorted(map(list, ri.folds))
        a.real_report = rep
        exe, rva_map = Path(a.real_image), ri.rva_map()
        if a.rebase:
            exe = real_image.rebased_copy(ri, a.rebase, OUT / "rebased.exe")
            rep["rebased"] = {"base": hex(a.rebase), "sha256": real_image.sha256_file(exe)}
        a.address_map = {n: [hex(ri.base + v), ours] for n, (v, ours) in placed.items()}
        a.relayout = None
    elif a.retail:
        exe, rva_map = boot_smoke.boot_image.build.EXE, None
    else:
        rep = json.loads((boot_smoke.OUT / f"{a.image}.json").read_text())
        if not boot_smoke.boot_image.image_ok(rep):
            raise SystemExit(f"game_smoke: build/boot/{a.image} did not link and check clean")
        exe, rva_map = boot_smoke.OUT / f"{a.image}.exe", piece_mover(rep["pieces_map"])
        placed = map_addresses(rva_map)               # refuse before launching if anything is unplaceable
        a.address_map = {n: [hex(v), ours] for n, (v, ours) in placed.items()}
        a.relayout = rep.get("relayout")
    boot_smoke.prepare_sandbox_profile(a.appdata)       # refuses an appdata inside the real AppData
    try:                                                # never a leftover image: refused by hash
        a.game_dat_sha256 = boot_smoke.real_image.install_game_dat(exe, gd)
    except boot_smoke.real_image.RealImageError as e:
        raise SystemExit(f"game_smoke: {e}")
    before = {"guard": {str(g): boot_smoke.snapshot(g) for g in a.guard}}
    profile_guard = boot_smoke.ProfileGuard()
    # -randomSeed sets GlobalData's fixed seed (+0x1228, parseRandomSeed 0x3B9D2C):
    # InitRandom / InitGameLogicRandom then ignore the time they are given, so
    # two runs of one image start the logic RNG identically (seen live: without
    # it two retail runs differ from the first CRC on).
    seed = f"-randomSeed {a.seed}" if a.seed is not None else ""
    game = Game(gd, f"{a.args} {seed} {extra}".strip(), a.appdata, rva_map, focus_lie=not a.no_focus_lie,
                int3_faults=a.ri is not None)
    a.started, a.t_start = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), time.time()
    for name, h in handlers:
        game.on(name, h)
    if a.coverage:
        units, a.coverage_source = coverage_units(a)
        move = rva_map or (lambda r: r)
        for rva, size, name in units:
            try:
                game.probe_units[move(rva)] = (rva, size, name)
            except KeyError:
                pass
    t0 = time.time()
    res = game.run(timeout or a.timeout, tick)
    out = {"args": game.args, "retail": a.retail, "wall_seconds": round(time.time() - t0, 1), "run": res}
    if not a.retail:
        out["addresses"], out["relayout"] = a.address_map, a.relayout
    if a.ri is not None:
        out["real_image"] = a.real_report
        loaded = int(res["image_base"], 16) if res.get("image_base") else a.ri.base
        if res.get("stopped") == "crash" or (res.get("stopped") == "exit" and res.get("fault") and res.get("exit_code")):
            import real_image
            out["crash"] = crash_record(a.ri, res, loaded)
            res["crash_name"] = real_image.crash_name(out["crash"])
    if a.coverage:
        out["coverage"] = coverage_report(game.probe_units, game.covered)
        out["coverage"].update(source=a.coverage_source, armed=res.get("coverage_armed"))
    out["profile_guard"], out["profile_touched"] = profile_guard.check()
    out["sandbox_profile"] = sorted(str(Path(p).relative_to(a.appdata))
                                    for p in boot_smoke.snapshot(Path(a.appdata)))[:40]
    out["guard"] = {}
    for g, snap in before["guard"].items():
        after = boot_smoke.snapshot(Path(g))
        out["guard"][g] = sorted(set(after) ^ set(snap) | {p for p in snap if p in after and after[p] != snap[p]})[:20]
    return game, out


def crash_record(ri, res, loaded):
    """The contract's crash dict for a real image's fault, with boot_smoke's `stack` (the
    registers, what they point at, the stack words and frames) when the fault was captured."""
    import real_image
    crash = real_image.crash_fields(ri, res["address"] if res["stopped"] == "crash" else res["fault"],
                                    loaded, res.get("fault_words", []), res.get("code") or res.get("fault_code"))
    if res.get("fault_context"):
        crash["stack"] = boot_smoke.fault_stack(dict(res["fault_context"], words=res.get("fault_words", [])),
                                                loaded, ri, None)
    return crash


def crash_outcome(res):
    if res.get("stopped") == "debugger-error":
        return "debugger-error"
    if res.get("stopped") == "profile-redirect-failed":
        return "profile-redirect-failed"
    if res.get("crash_name"):
        return f"crash-at-{res['crash_name']}"
    if res.get("stopped") == "crash":
        return f"crash-at-{res.get('address', 0):#x}"
    if res.get("stopped") == "exit":
        return f"exit-{res.get('exit_code', 0):#x}"
    return None


MODES = {"skirmish": "skirmish", "record": "determinism", "determinism": "determinism", "reload": "reload",
         "save": "reload", "load": "reload", "playback": "determinism"}


def refuse_image(a, rep):
    """A real image that may not run: build/game/<scenario>_real.json says why; exit 1."""
    import real_image
    out = {"image": "real", "outcome": "image-refused", "real_image": rep,
           "receipt": real_image.receipt_fields("game_smoke", MODES.get(a.scenario, a.scenario), "image-refused",
                                                real_image.summary(a.ri) if a.ri is not None else {}, None,
                                                time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), 0)}
    OUT.mkdir(parents=True, exist_ok=True)
    (OUT / f"{a.scenario}_real.json").write_text(json.dumps(out, indent=1, default=str))
    print(json.dumps(out, indent=1, default=str))
    raise SystemExit(1)


def short_of_frame(a, crcs=None):
    """With --until-frame N, why a run is short of it (the logic never reached N, or with
    CRCs none was taken at or past N), else None."""
    until = getattr(a, "until_frame", None)
    if until is None:
        return None
    reached = getattr(a, "reached", None)
    if reached is None or reached < until:
        return f"the logic reached frame {reached}, short of --until-frame {until}"
    if crcs is not None and not any(f >= until for f, _ in crcs):
        return f"no CRC at or past --until-frame {until} (last {crcs[-1][0] if crcs else None})"
    return None


SCENARIO_KINDS = {"record": "determinism", "record_perturbed": "determinism", "determinism": "determinism",
                  "determinism_perturbed": "determinism", "reload": "reload", "reload_perturbed": "reload",
                  "load": "load", "load_perturbed": "load"}


def scenario_of(a, name):
    """What decides a run's simulation, for the suite judge to group equivalent runs by; None for other scenarios.
    The image is not in it: comparing images is the point."""
    kind = SCENARIO_KINDS.get(name)
    if kind is None:
        return None
    arg = lambda name: getattr(a, name, None)        # noqa: E731
    s = {"kind": kind, "map": arg("map"), "seed": arg("seed"), "players": arg("players"), "player": arg("player"),
         "ai": not arg("no_ai"), "difficulty": arg("difficulty"), "fast": arg("fast"), "mode": arg("mode"),
         "crc_every": arg("crc_every"), "until_frame": arg("until_frame")}
    if kind == "reload":
        s.update(save_frame=arg("save_frame"), load_frame=arg("load_frame"))
    if kind == "load":
        s.update(saved_frame=(arg("loaded_save") or {}).get("frame"), save_sha256=(arg("loaded_save") or {}).get("sha256"))
    s["perturb_frame"] = arg("perturb_frame")
    return s


def file_sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def finish(a, name, out):
    short = short_of_frame(a, out.get("crcs") if name in SCENARIO_KINDS else None)
    if short:
        out["until_frame"] = short
        if out["outcome"] == "pass":
            out["outcome"] = "short-of-frame"
    if out["run"].get("stopped") == "profile-redirect-failed":
        out["outcome"] = "profile-redirect-failed"
    if out["profile_touched"]:
        out["outcome"] = "profile-changed"
    if any(out["guard"].values()):
        out["outcome"] = "guard-violation"
    if out["run"].get("stopped") == "debugger-error":
        out["outcome"] = "debugger-error"
    out["image"] = "retail" if a.retail else a.image
    if scenario_of(a, name) is not None:
        out["scenario"] = scenario_of(a, name)
    import real_image
    image = (real_image.summary(a.ri) if getattr(a, "ri", None) is not None else
             real_image.retail_summary() if a.retail else {"image_kind": "overlay", "image_commit": None})
    if out["run"].get("image_base"):
        image["base"] = out["run"]["image_base"]
    scenario = getattr(a, "scenario", name)
    out["receipt"] = real_image.receipt_fields("game_smoke", MODES.get(scenario, scenario), out["outcome"], image,
                                               out.get("crash"), getattr(a, "started", None),
                                               time.time() - getattr(a, "t_start", time.time()))
    if "coverage" in out:                            # the unit list goes to its own file
        cov = OUT / f"coverage_{name}_{out['image']}.json"
        cov.write_text(json.dumps(out["coverage"], indent=1))
        out["receipt"]["coverage"] = coverage_receipt(out["coverage"], cov.name)
        out["coverage"] = {k: v for k, v in out["coverage"].items() if k != "run"} | {"file": str(cov)}
    (OUT / f"{name}_{out['image']}.json").write_text(json.dumps(out, indent=1, default=str))
    print(json.dumps(out, indent=1, default=str))
    return 0 if out["outcome"] == "pass" else 1


def cmd_skirmish(a, keep_replay=None):
    samples = []
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed, a.player, a.players, a.difficulty, a.fast))]
    hook = FrameHook(every=a.crc_every, modes=(a.mode,)) if keep_replay else None
    if hook:
        handlers.append(("GameEngine::update", hook))
    if hook:
        hook.perturb_at = a.perturb_frame
    game, out = launch(a, f'-file "{a.map}"', handlers, skirmish_tick(a, samples, a.mode, hook))
    out["samples"] = samples
    if hook:
        out["crcs"], out["rng"], out["blocks"] = hook.crcs, hook.rng, hook.blocks
        out["perturbed"] = hook.perturbed or None
    res = out["run"]
    out["outcome"] = judge_skirmish(samples, a.mode, a.min_frames, crash_outcome(res), res.get("screenshot"))
    if keep_replay:
        out["outcome"] = judge_record(out["outcome"], hook.crcs, a.min_crcs)
    if not keep_replay:
        return finish(a, "skirmish", out)
    return finish(a, "record_perturbed" if a.perturb_frame is not None else "record", out)


def find_saves(appdata):
    d = sandbox_profile(appdata) / "Save"
    return sorted(d.glob("*.*"), key=lambda q: q.stat().st_mtime) if d.exists() else []


def saves_state(appdata):
    """{name: (mtime, size)} of the profile's saves, to tell later which this run wrote."""
    return {q.name: (q.stat().st_mtime_ns, q.stat().st_size) for q in find_saves(appdata)}


def new_saves(appdata, before):
    """The saves written since `before`, oldest first. By content too: autoSave's name is fixed ("Auto Save for <map>"),
    so in a profile that kept an earlier run's save the name alone says nothing was written."""
    return [q for q in find_saves(appdata) if before.get(q.name) != (q.stat().st_mtime_ns, q.stat().st_size)]


def cmd_save(a):
    """Skirmish vs AI; --save-after seconds in, GameState::autoSave() runs at the
    top of the next engine frame (GameEngine::update entry). The save is kept as
    GAME_DIR/<--save-name> for the load run. pass = autoSave returned 0, a new
    save file appeared and the game kept simulating afterwards."""
    samples = []
    before = saves_state(a.appdata)
    hook = FrameHook(modes=(a.mode,))
    saved = hook.save
    base_tick = skirmish_tick(a, samples, a.mode)

    def tick(game):
        why = base_tick(game)
        started = [t for t, f, m in samples if m == a.mode and f]
        if started and not hook.save_requested and samples[-1][0] - started[0] >= a.save_after:
            hook.save_requested = True
        return why
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed, a.player, a.players, a.difficulty, a.fast)), ("GameEngine::update", hook)]
    game, out = launch(a, f'-file "{a.map}"', handlers, tick)
    res = out["run"]
    new = new_saves(a.appdata, before)
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


def loaded_setup(hook):
    """A load has no skirmish set-up to record: its setup is the loaded state's own, read beside its first CRC (the
    logic frame it resumed at and the logic RNG base seed), for the suite judge to hold equivalent loads to."""
    first = hook.rng[0] if hook.rng else None
    return {"loaded_frame": first[0] if first else None, "base_seed": first[2] if first else None}


def cmd_load(a):
    """`-file <save>`: GameEngine::execute loads a .BfME2Skirmish save given on
    the command line (retail 0x22D290..0x22D3F1). pass = skirmish mode, the
    first logic frame seen is at or past the frame the save was taken at (a new
    game would start at 0) and the logic then advances --min-frames."""
    samples = []
    if a.save is not None:                          # another run's save (a cross-build load), where `save` would put it
        if a.saved_frame is None:
            raise SystemExit("game_smoke: load --save needs --saved-frame, the logic frame the save was taken at")
        shutil.copyfile(a.save, a.game_dir / a.save_name)
    rec = json.loads((OUT / f"save_{'retail' if a.retail else a.image}.json").read_text()) if a.saved_frame is None else None
    saved_frame = a.saved_frame if a.saved_frame is not None else rec["save"]["frame"]
    hook = FrameHook(every=a.crc_every, at_first=True, modes=(a.mode,))
    # GameEngine::execute reads the save's header through the path as given
    # (relative to the game folder), and loadGame then looks for the same name
    # in the profile's Save folder (seen live: with only the first, the game
    # quits at once), so the save is in both places.
    save_dir = sandbox_profile(a.appdata) / "Save"
    save_dir.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(a.game_dir / a.save_name, save_dir / a.save_name)
    a.loaded_save = {"sha256": file_sha256(a.game_dir / a.save_name), "frame": saved_frame}
    hook.perturb_at = a.perturb_frame
    game, out = launch(a, f"-file {a.save_name}", [("GameEngine::update", hook)], skirmish_tick(a, samples, a.mode, hook))
    out["perturbed"] = hook.perturbed or None
    res = out["run"]
    res["setup"] = loaded_setup(hook)
    game_frames = [f for t, f, m in samples if m == a.mode and f]
    out.update(samples=samples[::5], saved_frame=saved_frame, first_game_frame=game_frames[0] if game_frames else None,
               first_crc=hook.crcs[:1], crcs=hook.crcs, rng=hook.rng)
    if rec and hook.crcs and hook.crcs[0][0] == saved_frame:        # informational: is the loaded state the saved one?
        out["crc_matches_save"] = hook.crcs[0][1] == rec["save"].get("crc")
    out["outcome"] = judge_skirmish(samples, a.mode, a.min_frames, crash_outcome(res), res.get("screenshot"))
    if out["outcome"] == "pass" and game_frames[0] < saved_frame:
        out["outcome"] = "not-restored"
    return finish(a, "load_perturbed" if a.perturb_frame is not None else "load", out)


def cmd_reload(a):
    """Load as a player does: skirmish, GameState::autoSave at --save-frame, play on to --load-frame,
    then call retail's in-game load from the top of an engine frame. Exact frames let two runs be
    compared; a load keeps the running random state, so its CRCs differ from the save's. The
    Use --player: a game whose local slot is an observer cannot load (retail throws in
    CHUNK_TeamFactory), and the menu does not start one. pass = load returned 0, the logic frame went
    back, and the game kept simulating. crc_matches_save is reported, not judged: retail's own run
    resumes at the saved frame with a different CRC."""
    samples = []
    before = saves_state(a.appdata)
    hook = FrameHook(every=a.crc_every, modes=(a.mode,))
    hook.save_at, hook.load_at = a.save_frame, a.load_frame
    hook.find_save = lambda: ([q.name for q in new_saves(a.appdata, before)] or [None])[-1]
    hook.perturb_at = a.perturb_frame               # the negative control perturbs the loaded game only
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed, a.player, a.players, a.difficulty, a.fast)), ("GameEngine::update", hook)]
    game, out = launch(a, f'-file "{a.map}"', handlers, skirmish_tick(a, samples, a.mode, hook))
    res = out["run"]
    load, save = hook.load, hook.save
    out["perturbed"] = hook.perturbed or None
    name = "reload_perturbed" if a.perturb_frame is not None else "reload"
    written = sandbox_profile(a.appdata) / "Save" / hook.load_name if hook.load_name else None
    if written is not None and written.is_file():   # kept beside the result, for another build to load (load --save)
        kept = OUT / f"{name}_{'retail' if a.retail else a.image}{written.suffix}"
        shutil.copyfile(written, kept)
        out["save_file"] = {"name": hook.load_name, "kept_as": kept.name, "sha256": file_sha256(kept),
                            "frame": save.get("frame")}
    after = [f for t, f, m in samples if load.get("seconds") and t > load["seconds"] and m == a.mode and f]
    first = load.get("first_crc")
    out.update(samples=samples[::5], save=save, load=load, crcs=hook.crcs, crcs_before_load=hook.before_load,
               load_name=hook.load_name, frames_after_load=after[:3] + after[-3:])
    if first and save.get("crc") is not None:
        out["crc_matches_save"] = first == (save.get("frame"), save["crc"])
        same_frame = [b for f, b in hook.blocks if f == save.get("frame")]
        out["blocks"] = hook.blocks
        if len(same_frame) >= 2:
            out["blocks_differ_after_load"] = sorted(k for k in same_frame[0] if same_frame[0][k] != same_frame[1][k])
            out["blocks_compared"] = sorted(same_frame[0])
        states = [r for r in hook.rng if r[0] == save.get("frame")]
        if len(states) >= 2:
            out["rng_matches_save"] = states[0][1:] == states[1][1:]
            out["rng_at_save_and_load"] = states[:2]
    crash = crash_outcome(res)
    if crash:
        out["outcome"] = crash
    elif "code" not in save or save["code"] != 0:
        out["outcome"] = "save-failed"
    elif "code" not in load:
        out["outcome"] = "load-not-called"
    elif load["code"] != 0:
        out["outcome"] = f"load-failed-{load['code']}"
    elif not after or after[0] >= load["from_frame"]:
        out["outcome"] = "not-restored"
    elif after[-1] - after[0] < a.min_frames // 4:
        out["outcome"] = "no-frames-after-load"
    else:
        out["outcome"] = "pass"
    return finish(a, name, out)


def perturb_tick(a, game, frame, perturbed):
    """Positive control for playback: xor the logic random seed once at --perturb-frame (the others use FrameHook)."""
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
    samples = []
    hook = FrameHook(every=a.crc_every, modes=(a.mode,))
    hook.perturb_at = a.perturb_frame
    tick = skirmish_tick(a, samples, a.mode, hook)
    handlers = [("fileSlotsSet", skirmish_setup(not a.no_ai, a.seed, a.player, a.players, a.difficulty, a.fast)), ("GameEngine::update", hook)]
    game, out = launch(a, f'-file "{a.map}"', handlers, tick)
    crc = pair_crcs([(f, c, False) for f, c in record.get("crcs", [])] + [(f, c, True) for f, c in hook.crcs])
    out["blocks_differ"] = block_diff(record.get("blocks", []), hook.blocks)
    out.update(samples=samples[::5], crcs=hook.crcs, rng=hook.rng, blocks=hook.blocks, perturbed=hook.perturbed or None, record_seed=record["run"].get(
        "setup", {}).get("seed"), crc=dict(crc, mismatches=crc["mismatches"][:10],
                                           unpaired_recorded=crc["unpaired_recorded"][:10],
                                           unpaired_computed=crc["unpaired_computed"][:10]))
    res = out["run"]
    out["outcome"] = judge_playback(crc, None, None, a.min_crcs, crash_outcome(res))
    if out["outcome"] == "pass" and out["record_seed"] != a.seed:
        out["outcome"] = "seed-differs"
    mine, theirs = out["run"].get("setup", {}), record["run"].get("setup", {})
    if out["outcome"] in ("pass", "desync") and (mine.get("players"), mine.get("fps_limit")) !=             (theirs.get("players"), theirs.get("fps_limit")):
        out["outcome"] = "setup-differs"              # players/difficulty must match the reference
    return finish(a, "determinism_perturbed" if a.perturb_frame is not None else "determinism", out)


# --------------------------------------------------------------------------- the suite judge (G4, G5)
def suite_run(path):
    """One run's result file, as the suite judge reads it; None when it is not a scenario run."""
    d = json.loads(Path(path).read_text())
    if not isinstance(d, dict) or not isinstance(d.get("scenario"), dict):
        return None
    crcs = {}
    for f, c in d.get("crcs") or []:
        crcs.setdefault(f, c)
    receipt = d.get("receipt") or {}
    setup = (d.get("run") or {}).get("setup") or {}
    keys = ("loaded_frame", "base_seed") if d["scenario"].get("kind") == "load" else ("seed", "players", "fps_limit")
    return {"file": str(path), "scenario": d["scenario"], "outcome": d.get("outcome"), "crcs": crcs,
            "retail": receipt.get("image_kind") == "retail", "image_sha256": receipt.get("image_sha256"),
            "setup": {k: setup.get(k) for k in keys}, "perturbed": d.get("perturbed")}


def suite_key(scenario):
    return json.dumps({k: v for k, v in scenario.items() if k != "perturb_frame"}, sort_keys=True)


def suite_schedule(scenario):
    """The CRC frames a scenario's runs must all hold: every crc_every to until_frame, after the load for reload/load."""
    start = {"reload": scenario.get("save_frame"), "load": scenario.get("saved_frame")}.get(scenario.get("kind"), 0)
    every, until = scenario.get("crc_every"), scenario.get("until_frame")
    if not every or not until or start is None:
        return None
    return [f for f in range(every, until + 1, every) if f > start]


def expected_setup(scenario):
    """The setup a run of this scenario reports (skirmish_setup's game.res["setup"]), for every run to be held to;
    None for a load, whose setup is its loaded state's (loaded_setup), which only equivalent runs can vouch for."""
    if scenario.get("kind") == "load":
        return None
    ais = range(1, 1 + ((1 if scenario.get("player") else scenario.get("players") or 0) if scenario.get("ai") else 0))
    players = ("slot 0 player, " if scenario.get("player") else "slot 0 observer, ") + \
        ", ".join(f"slot {i} {scenario.get('difficulty')} AI" for i in ais)
    return {"seed": scenario.get("seed"), "players": players, "fps_limit": "off" if scenario.get("fast") else None}


def suite_verdict(run, ref, frames, bar_frames, setup):
    """One run: every scheduled frame present, then equal to the reference CRCs over the bar's frames."""
    pf = run["scenario"].get("perturb_frame")
    if pf is None and run["outcome"] != "pass":
        return f"run-{run['outcome']}"
    if run["setup"] != setup:
        return "metadata-differs"
    missing = [f for f in frames if f not in run["crcs"]]
    if missing:
        return f"incomplete-from-{missing[0]}"
    diffs = [f for f in bar_frames if run["crcs"][f] != ref[f]]
    if pf is None:
        return f"differs-at-{diffs[0]}" if diffs else "matches"
    at = (run["perturbed"] or {}).get("frame")
    if at is None:
        return "not-perturbed"
    if any(f < at for f in diffs):
        return f"differs-before-perturbation-at-{diffs[0]}"
    if not any(f >= at for f in bar_frames):
        return "perturbed-past-the-bar"
    return f"caught-at-{diffs[0]}" if diffs else "missed"


def judge_suite(runs, bar=None, target=None):
    """G4/G5's verdict over result files (suite_run dicts). A scenario's bar is what its retail runs repeat (two
    complete unperturbed retail runs, compared over the schedule), or the one `bar` (an earlier suite's output)
    gives; every other run is judged against it."""
    groups = collections.defaultdict(list)
    for r in runs:
        groups[suite_key(r["scenario"])].append(r)
    out = {"groups": {}, "problems": []}
    for key, members in sorted(groups.items()):
        sc = json.loads(key)
        frames = suite_schedule(sc)
        g = {"scenario": sc, "runs": len(members)}
        out["groups"][key] = g
        if frames is None:
            g["verdict"] = "unscheduled"           # no --until-frame or --crc-every: nothing says what must be there
            out["problems"].append(f"{sc.get('kind')} {sc.get('map')} seed {sc.get('seed')}: unscheduled")
            continue
        g["scheduled"] = [frames[0], frames[-1], len(frames)]
        expected = expected_setup(sc)
        given = (bar or {}).get("groups", {}).get(key, {}).get("bar")
        refs = [r for r in members if r["retail"] and r["scenario"].get("perturb_frame") is None and r["outcome"] == "pass"
                and all(f in r["crcs"] for f in frames)]
        if expected is None and bar is not None:   # a load: the loaded state the bar's references agreed on
            expected = (given or {}).get("setup")
        elif expected is None:                     # a load: the first reference that resumed at or past the save
            resumed = [r for r in refs if r["setup"].get("base_seed") is not None
                       and (r["setup"].get("loaded_frame") or -1) >= sc["saved_frame"]]
            expected = resumed[0]["setup"] if resumed else None
        g["expected_setup"] = expected
        for r in [r for r in refs if r["setup"] != expected] if bar is None else []:
            out["problems"].append(f"{sc['map']} seed {sc['seed']}: retail run {r['file']} ran {r['setup']}, not {expected}")
            refs.remove(r)
        if bar is not None:                        # an explicit bar wins: every run here, retail too, is held to it
            if not given:
                g["verdict"] = "not-in-the-bar"
                out["problems"].append(f"{sc['map']} seed {sc['seed']}: not in the bar given")
                continue
            g["bar"] = given
            judged = members
        elif len(refs) >= 2:
            ref = refs[0]
            diffs = sorted({f for other in refs[1:] for f in frames if other["crcs"][f] != ref["crcs"][f]})
            through = [f for f in frames if not diffs or f < diffs[0]]
            if not through:
                g["verdict"] = "no-bar"
                out["problems"].append(f"{sc['map']} seed {sc['seed']}: retail differs from itself at {diffs[0]}")
                continue
            g["bar"] = {"through": through[-1], "frames": len(through), "reference": {str(f): ref["crcs"][f] for f in through},
                        "setup": ref["setup"], "retail_runs": [r["file"] for r in refs]}
            if diffs:
                g["bar"]["reduction"] = f"retail differs from itself at frame {diffs[0]}; the bar ends at {through[-1]}"
            judged = [r for r in members if r is not ref and r not in refs]
            g["retail_repeat"] = "repeats" if not diffs else f"differs-at-{diffs[0]}"
        else:
            g["verdict"] = "no-bar"                # one retail run or none, and no bar given
            out["problems"].append(f"{sc['map']} seed {sc['seed']}: {len(refs)} complete retail run(s), no bar given")
            continue
        bar_frames = [f for f in frames if f <= g["bar"]["through"]]
        ref_crcs = {int(f): c for f, c in g["bar"]["reference"].items()}
        g["judged"] = [{"file": r["file"], "retail": r["retail"], "perturb_frame": r["scenario"].get("perturb_frame"),
                        "verdict": suite_verdict(r, ref_crcs, frames, bar_frames, expected)} for r in judged]
        bad = [j for j in g["judged"] if j["verdict"] != "matches" and not j["verdict"].startswith("caught-at-")]
        g["verdict"] = "pass" if not bad else "fail"
        if bad:
            out["problems"] += [f"{sc['map']} seed {sc['seed']}: {j['file']} {j['verdict']}" for j in bad]
    for key in sorted(set((bar or {}).get("groups", {})) - set(groups)):
        out["problems"].append(f"{json.loads(key).get('map')} seed {json.loads(key).get('seed')}: in the bar, not run")
    caught = [j for g in out["groups"].values() for j in g.get("judged", []) if j["verdict"].startswith("caught-at-")]
    if not caught:
        out["problems"].append("no perturbed run was caught: the suite has no negative control")
    reductions = [f"{json.loads(k)['map']} seed {json.loads(k)['seed']}: {g['bar']['reduction']}"
                  for k, g in out["groups"].items() if g.get("bar", {}).get("reduction")]
    if target:
        cells = {(g["scenario"].get("map"), g["scenario"].get("seed")) for g in out["groups"].values() if g.get("bar")}
        maps, seeds = {m for m, _ in cells}, {s for _, s in cells}
        if len(maps) < target["maps"] or len(seeds) < target["seeds"]:
            reductions.append(f"{len(maps)} map(s) x {len(seeds)} seed(s) with a bar, target {target['maps']} x {target['seeds']}")
        short = sorted({g["bar"]["through"] for g in out["groups"].values() if g.get("bar")} - {target["until"]})
        if short:
            reductions.append(f"bars end at {short}, target frame {target['until']}")
    out["reductions"] = reductions
    out["verdict"] = "fail" if out["problems"] else "pass"
    return out


def suite_main(argv):
    ap = argparse.ArgumentParser(prog="game_smoke.py suite", description="G4/G5's judge over record/reload/load results")
    ap.add_argument("runs", nargs="+", type=Path, help="result files, or job folders holding them")
    ap.add_argument("--bar", type=Path, help="an earlier suite's output: retail's bar, to judge image runs against")
    ap.add_argument("--target", help="MAPSxSEEDSxUNTIL the bar should cover, e.g. 3x5x5000: any shortfall is reported")
    ap.add_argument("--out", type=Path, help="write the verdict here too")
    a = ap.parse_args(argv)
    runs, skipped = [], []
    for p in a.runs:
        for f in (sorted(p.glob("*.json")) if p.is_dir() else [p]):
            try:
                r = suite_run(f)
            except (OSError, ValueError):
                r = None
            (runs if r else skipped).append(r or str(f))
    target = None
    if a.target:
        m, s, u = (int(x) for x in a.target.lower().split("x"))
        target = {"maps": m, "seeds": s, "until": u}
    out = judge_suite(runs, json.loads(a.bar.read_text()) if a.bar else None, target)
    out["not_scenario_runs"] = [s for s in skipped if not s.endswith(("receipt.json", "job.json"))]
    text = json.dumps(out, indent=1)
    if a.out:
        a.out.write_text(text)
    print(text)
    return 0 if out["verdict"] == "pass" else 1


def desync_items(guilty, outcome, image_args):
    """repair_queue items for rows whose authored code makes the game diverge
    from retail's record (check `desync`; pass test: determinism with the row
    alone)."""
    alone = len({r["target_rva"] for r in guilty}) == 1
    return [{"target_rva": r["target_rva"], "name": r["name"], "source": r["source"],
             "size": int(r["target_size"] or 0), "outcome": outcome,
             "check": "desync" if outcome == "desync" else "boot-crash",
             "why": (f"game_smoke determinism {outcome} with this row's authored code alone ({image_args})"
                     if alone else f"game_smoke determinism {outcome}: {len(guilty)} rows together, no half alone "
                                   f"({image_args})"),
             "pass_test": f"python3 tools/boot_image.py link --tag one --overlay rva:{r['target_rva']} {image_args} && "
                          "python3 tools/game_smoke.py determinism --image one --game-dir SANDBOX "
                          "(exit 0: every CRC equals retail's record)"} for r in guilty]


def halve(cand, fails):
    """Deterministic halving: `cand` sorted unit RVAs, `fails(subset) -> bool`.
    Each step tests the lower half alone, then the upper; the first failing half
    is kept. Stops at one unit, or when neither half fails alone (an interaction:
    the remaining set is returned). Returns (guilty, steps)."""
    steps = []
    while len(cand) > 1:
        nxt = None
        for h in (cand[:len(cand) // 2], cand[len(cand) // 2:]):
            bad = fails(h)
            steps.append({"units": len(h), "first": hex(h[0]), "last": hex(h[-1]), "fails": bad})
            if bad:
                nxt = h
                break
        if nxt is None:
            break
        cand = nxt
    return cand, steps


def cmd_bisect(a):
    """Halve a desyncing relayout image's units to the ones that desync alone.
    Each half is linked (`boot_relayout.build_image`, same seed and modes, tag
    `bisect`) outside the game lock; each run goes through --lock (game_lock.py)
    as its own process. Writes build/game/desync_queue.json (repair_queue)."""
    import subprocess
    import boot_relayout
    bi = boot_smoke.boot_image
    if not a.lock or not Path(a.lock).exists():
        raise SystemExit("game_smoke: bisect needs --lock (game_lock.py): every run must hold the game lock")
    rep = json.loads((boot_smoke.OUT / f"{a.image}.json").read_text())
    specs = rep["overlay"]["specs"]
    own = "own-data" in rep.get("relayout", {}).get("mode", "")
    with open(boot_smoke.OUT / f"{a.image}.overlay.csv", newline="", encoding="utf-8") as f:
        import csv
        kept = {(int(x["retail_rva"], 16), x["name"]) for x in csv.DictReader(f) if x["overlay"] == "overlaid"}
    rows = [r for r in bi.overlay_rows(specs, a.status) if (int(r["target_rva"], 16), r["name"]) in kept]
    by_rva = {}
    for r in rows:
        by_rva.setdefault(int(r["target_rva"], 16), []).append(r)
    record = Path(a.record_json or OUT / "record_retail.json").resolve()
    log = []

    def fails(units):
        sub = [r for u in units for r in by_rva[u]]
        built = boot_relayout.build_image(a.base, boot_smoke.OUT, "bisect", specs, a.status, rows=sub,
                                          relayout=True, own_data=own, seed=rep["relayout"].get("seed", 0))
        if not bi.image_ok(built) or built.get("check", {}).get("reloc-bad"):
            log.append({"units": len(units), "outcome": "link-error"})
            return False
        cmd = [sys.executable, str(a.lock), sys.executable, str(Path(__file__).resolve()), "determinism",
               "--image", "bisect", "--game-dir", str(a.game_dir), "--appdata", str(a.appdata),
               "--record-json", str(record), "--seconds", str(a.seconds), "--timeout", str(a.timeout)] + \
            [x for g in a.guard for x in ("--guard", str(g))]
        subprocess.run(cmd, stdout=subprocess.DEVNULL)
        out = json.loads((OUT / "determinism_bisect.json").read_text())
        log.append({"units": len(units), "first": hex(units[0]), "outcome": out["outcome"],
                    "first_mismatch": (out.get("crc", {}).get("mismatches") or [[None]])[0][0]})
        print(f"game_smoke: bisect {len(units)} unit(s) {units[0]:#x}..: {out['outcome']}", file=sys.stderr, flush=True)
        if out["outcome"] in ("profile-changed", "guard-violation"):
            raise SystemExit(f"game_smoke: bisect stopped: {out['outcome']}")
        if out["outcome"] == "desync" or out["outcome"].startswith(("crash-at-", "exit-")):
            failed.setdefault("outcome", out["outcome"])
            return True
        return False
    failed = {}
    guilty, steps = halve(sorted(by_rva), fails)
    items = desync_items([r for u in guilty for r in by_rva[u]], failed.get("outcome", "desync"),
                         " ".join(f"--overlay {s}" for s in specs) + " --relayout" + (" --own-data" if own else ""))
    path = OUT / "desync_queue.json"
    path.write_text(json.dumps({"tool": "game_smoke", "items": items}, indent=1), encoding="utf-8")
    out = {"image": a.image, "units": len(by_rva), "steps": steps, "runs": log, "guilty": [
        [r["target_rva"], r["name"], r["source"]] for u in guilty for r in by_rva[u]][:50], "queue": str(path)}
    (OUT / f"bisect_{a.image}.json").write_text(json.dumps(out, indent=1))
    print(json.dumps(out, indent=1))
    return 0


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


def check_coverage_args(a):
    """--coverage-units needs --coverage, and its ledger list is for retail's own image only: a
    relayout or linked image would need each row moved (and, linked, its body checked and its
    folds kept apart) before a probe could be planted on it."""
    if a.coverage_units and not a.coverage:
        raise SystemExit("game_smoke: --coverage-units needs --coverage")
    if a.coverage_units == "ledger" and not a.retail:
        raise SystemExit("game_smoke: --coverage-units ledger probes retail's own image only (--retail)")


def main(argv=None):
    argv = sys.argv[1:] if argv is None else list(argv)
    if argv[:1] == ["suite"]:
        return suite_main(argv[1:])
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("scenario", choices=["skirmish", "record", "determinism", "playback", "save", "load", "reload", "bisect"])
    ap.add_argument("--game-dir", type=Path, required=True)
    ap.add_argument("--appdata", type=Path, help="sandbox user-data root (default GAME_DIR/../appdata)")
    ap.add_argument("--retail", action="store_true", help="control: retail's own game.dat")
    ap.add_argument("--real-image", type=Path, metavar="EXE",
                    help="a linked image (exit_link's exit.exe, exit.map and image_receipt.json together): "
                         "hash-checked, judged by real_image.check, every harness address mapped fail-closed "
                         "through its map and byte-checked bodies; an int3 the harness did not plant is a fault")
    ap.add_argument("--rebase", type=lambda v: int(v, 0), metavar="BASE",
                    help="with --real-image: run a copy relocated to BASE (a second non-retail base)")
    ap.add_argument("--image", default="boot",
                    help="without --retail: the image `boot_image.py link --tag TAG` wrote (build/boot/TAG.exe)")
    ap.add_argument("--args", default="-win -xres 1024 -yres 768")
    ap.add_argument("--map", default=SKIRMISH_MAP)
    ap.add_argument("--mode", type=int, default=2, help="GameLogic game mode of a skirmish")
    ap.add_argument("--no-ai", action="store_true")
    ap.add_argument("--players", type=int, default=2, help="AI players (slots 1..N; the map must have N starts)")
    ap.add_argument("--difficulty", choices=sorted(AI_STATES), default="easy")
    ap.add_argument("--fast", action="store_true", help="lift the FPS cap: logic runs at render rate / 6")
    ap.add_argument("--coverage", action="store_true",
                    help="one-shot probe on each authored unit's entry; report the units that ran")
    ap.add_argument("--coverage-units", choices=["authored", "ledger"], default=None,
                    help="with --coverage: the units to probe, build/boot/IMAGE.json's authored list (default) or, "
                         "with --retail only, every reverse/functions.csv row of this checkout (no link needed)")
    ap.add_argument("--player", action="store_true",
                    help="slot 0 plays (random faction) against one AI, instead of observing two AIs")
    ap.add_argument("--seed", type=lambda v: int(v, 0), default=1, help="-randomSeed and the skirmish seed (GameInfo+0x50)")
    ap.add_argument("--seconds", type=float, default=60, help="skirmish seconds to simulate")
    ap.add_argument("--until-frame", type=int,
                    help="simulate until this logic frame (with CRCs, until its CRC is taken) instead of --seconds")
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
    ap.add_argument("--save-frame", type=int, default=125, help="reload: logic frame to save at")
    ap.add_argument("--load-frame", type=int, default=175, help="reload: logic frame to load at")
    ap.add_argument("--save-name", default="smoke.BfME2Skirmish", help="the save, kept in GAME_DIR")
    ap.add_argument("--saved-frame", type=int, help="load: frame the save was taken at (default: save run's)")
    ap.add_argument("--save", type=Path, help="load: another run's save to load (a cross-build load); needs --saved-frame")
    ap.add_argument("--guard", type=Path, action="append", default=[])
    ap.add_argument("--no-focus-lie", action="store_true")
    ap.add_argument("--lock", type=Path, help="bisect: game_lock.py, which every bisection run goes through")
    ap.add_argument("--status", type=Path, default=boot_smoke.boot_image.LINK_STATUS)
    ap.add_argument("--base", type=lambda v: int(v, 0), default=boot_smoke.real_image.IMAGE_BASE)
    a = ap.parse_args(argv)
    check_coverage_args(a)
    if a.real_image:
        if a.retail or a.coverage or a.scenario == "bisect":
            raise SystemExit("game_smoke: --real-image runs the linked image alone (no --retail, --coverage, bisect)")
        a.image = "real"
    elif a.rebase:
        raise SystemExit("game_smoke: --rebase needs --real-image")
    a.appdata = (a.appdata or a.game_dir.resolve().parent / "appdata").resolve()
    try:
        boot_smoke.check_sandbox_appdata(a.appdata)
    except boot_smoke.RedirectError as e:
        raise SystemExit(f"game_smoke: {e}")
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
    if a.scenario == "bisect":
        return cmd_bisect(a)
    if a.scenario == "save":
        return cmd_save(a)
    if a.scenario == "load":
        return cmd_load(a)
    if a.scenario == "reload":
        return cmd_reload(a)
    return cmd_playback(a)


if __name__ == "__main__":
    sys.exit(main())
