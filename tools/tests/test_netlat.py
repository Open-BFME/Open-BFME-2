#!/usr/bin/env python3
"""Hold tools/netlat.py against streams whose answer is already known.

The analysis is what pronounces the verdict on the network-delay spike, so an
error in it is not a wrong number on a screen: it is the spike passing. The
project's stated failure mode is a fix that was credited with an improvement it
never made, and every assertion here is aimed at that:

  * a synthesised baseline (the pump runs at 5 Hz, so a command waits for the
    next tick) and a synthesised fix (it leaves within a frame) must come out
    far enough apart that an inert change cannot be mistaken for the fix;
  * one GameMessage is appended TWICE, to TheMessageStream and then to
    TheCommandList. Counted twice it halves every wrap delay -- silently, and in
    the direction that flatters a fix;
  * game speed is read from the frame field, not from counting events, and one
    stall must not move it. Counting lines measures the instrument;
  * a file that says nothing must raise rather than report zero.
"""
import json
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import netlat  # noqa: E402

FREQ = 10_000_000          # a 10 MHz QueryPerformanceCounter, as modern hosts report
TICK = 200.0               # ms per logic frame at the engine's compiled-in 5 Hz
FIRST_FRAME = 100


def q(ms):
    ticks = int(ms * FREQ / 1000.0)
    return ticks & 0xFFFFFFFF, ticks >> 32


def line(ev, t, frame, ceiling, slot, router, **rest):
    lo, hi = q(t)
    out = dict(ev=ev, qlo=lo, qhi=hi, f=frame, c=ceiling, slot=slot,
               router=int(router))
    out.update(rest)
    return out


def match(path, slot, router, wrap, count=120, backlog=0, stall_at=None,
          duplicate_appends=True, seconds=None):
    """One seat's file.

    `wrap` is how long a command waits to be sent: the 5 Hz pump makes it
    whatever is left of the current tick, and a send-side fix makes it a small
    constant. That difference is the whole measurement."""
    events = [dict(ev="open", qfreqlo=FREQ & 0xFFFFFFFF, qfreqhi=FREQ >> 32)]
    span = seconds if seconds is not None else count * 0.5 + 4
    nframes = int(span * 1000.0 / TICK)

    drift = 0.0
    for k in range(nframes):
        t = k * TICK + drift
        if stall_at is not None and k == stall_at:
            drift += 2000.0          # a two-second router stall
            t = k * TICK + drift
        frame = FIRST_FRAME + k
        events.append(line("frame", t, frame, frame + backlog, slot, router,
                           exec=frame, desync=0, stalls=0))
        if router:
            events.append(line("ceiling", t + 1.0, frame, frame, slot, router))

    # Commands, phase-spread across the tick so the wait is not always the same.
    for i in range(count):
        t = 137.0 + i * 47.0
        if t > nframes * TICK - 400:
            break
        sent = t + (wrap(t) if callable(wrap) else wrap)
        frame = FIRST_FRAME + int(t / TICK)
        msg = 0x0B000000 + (i % 64) * 0x40     # the allocator recycles addresses
        if duplicate_appends:
            # TheMessageStream first, then TheCommandList once the translators
            # have run: one message, two appends, and the second is when the
            # pump could first have taken it.
            events.append(line("input", t - 5.0, frame, frame + backlog, slot, router,
                               type=0x3EA, msg=msg, list=0x012ED5EC, owner=0))
        events.append(line("input", t, frame, frame + backlog, slot, router,
                           type=0x3EA, msg=msg, list=0x012ED5F0, owner=0x012ED5EC))
        events.append(line("send", sent, FIRST_FRAME + int(sent / TICK),
                           FIRST_FRAME + int(sent / TICK) + backlog, slot, router,
                           type=4, cmd=i, player=slot, exec=-1))
        # The per-tick frame info every client sends; noise the join must ignore.
        events.append(line("send", sent + 2.0, frame, frame + backlog, slot, router,
                           type=3, cmd=0, player=slot, exec=-1))

    events.sort(key=lambda e: 0 if e["ev"] == "open" else e["qlo"] + (e["qhi"] << 32))
    Path(path).write_text("".join(json.dumps(e) + "\n" for e in events))
    return path


def router_binding(path, guest_files, slot=0, count=120, seconds=None):
    """The router's own file, plus the relay records that bind each guest
    command to a frame -- the only place a guest's execution frame exists."""
    match(path, slot, True, wrap=8.0, count=count, seconds=seconds)
    events = [json.loads(x) for x in Path(path).read_text().splitlines()]
    for guest in guest_files:
        gslot = json.loads(Path(guest).read_text().splitlines()[1])["slot"]
        for e in [json.loads(x) for x in Path(guest).read_text().splitlines()]:
            if e.get("ev") == "send" and e.get("type") == 4:
                # Arrives at the router a moment later and is pinned to the next
                # frame everyone will run: the frame already in flight has had
                # its command set closed, which is the structural quantum a
                # guest pays and the host does not.
                t = (e["qlo"] + (e["qhi"] << 32)) * 1000.0 / FREQ + 6.0
                frame = FIRST_FRAME + int(t / TICK) + 1
                events.append(line("relay", t, frame, frame, slot, True,
                                   type=4, cmd=e["cmd"], player=gslot, exec=-1, mask=255))
    events.sort(key=lambda e: 0 if e["ev"] == "open" else e["qlo"] + (e["qhi"] << 32))
    Path(path).write_text("".join(json.dumps(e) + "\n" for e in events))
    return path


def to_next_tick(t):
    """What retail does: the pump only runs on a logic tick."""
    return TICK - (t % TICK)


@pytest.fixture
def baseline(tmp_path):
    return match(tmp_path / "guest_baseline.jsonl", 1, False, wrap=to_next_tick)


@pytest.fixture
def fixed(tmp_path):
    return match(tmp_path / "guest_fixed.jsonl", 1, False, wrap=16.0)


def test_the_wrap_delay_separates_retail_from_a_fix(baseline, fixed):
    """The placebo killer. Retail's pump makes a command wait most of a 200 ms
    tick; a send-side fix makes it wait a frame. If the analysis cannot tell
    these apart it cannot tell a working fix from an inert one."""
    b = netlat.wrap_delays(netlat.load(baseline))["wrap"]
    f = netlat.wrap_delays(netlat.load(fixed))["wrap"]
    assert 60 <= netlat.pct(b, 50) <= 160, netlat.describe(b)
    assert netlat.pct(f, 50) <= 35, netlat.describe(f)
    assert netlat.pct(b, 50) - netlat.pct(f, 50) >= 60, "the gate could not resolve the fix"


def test_one_message_appended_twice_is_one_command(baseline, tmp_path):
    """A GameMessage lands in TheMessageStream and then in TheCommandList. Taken
    as two commands the FIFO join pairs each send with the previous command's
    input and every wrap delay comes out too small."""
    once = match(tmp_path / "once.jsonl", 1, False, wrap=to_next_tick,
                 duplicate_appends=False)
    twice = netlat.wrap_delays(netlat.load(baseline))
    single = netlat.wrap_delays(netlat.load(once))
    assert twice["ready"] == single["ready"], "the second append was counted as a command"
    assert abs(netlat.pct(twice["wrap"], 50) - netlat.pct(single["wrap"], 50)) < 1.0


def test_two_commands_reusing_one_address_stay_two_commands(tmp_path):
    """The allocator hands a freed GameMessage's address straight back out, so
    two unrelated commands can share one within a tick. Merged on the address
    they collapse into a single command whose "wait" spans both, and the FIFO
    join then pairs every later send with the wrong input -- which is how this
    was found. The engine says which case it is: `owner` is the list the message
    was in before this append, and a fresh command's is zero."""
    events = [dict(ev="open", qfreqlo=FREQ, qfreqhi=0)]
    for k in range(6):
        events.append(line("frame", k * TICK, FIRST_FRAME + k, FIRST_FRAME + k, 1, False,
                           exec=FIRST_FRAME + k, desync=0, stalls=0))
    for i, t in enumerate((10.0, 60.0, 110.0)):          # all inside one 200 ms tick
        events.append(line("input", t, FIRST_FRAME, FIRST_FRAME, 1, False,
                           type=0x3EA, msg=0x0B000040, list=0x012ED5F0, owner=0))
        events.append(line("send", 200.0 + i, FIRST_FRAME + 1, FIRST_FRAME + 1, 1, False,
                           type=4, cmd=i, player=1, exec=-1))
    p = tmp_path / "reuse.jsonl"
    p.write_text("".join(json.dumps(e) + "\n" for e in events))

    j = netlat.wrap_delays(netlat.load(p))
    assert j["ready"] == 3, "three commands at one address were collapsed"
    assert len(j["wrap"]) == 3
    assert netlat.pct(j["wrap"], 50) == pytest.approx(141.0, abs=1.0)


def test_wrap_is_measured_from_the_last_append_not_the_first(baseline):
    """The pump can only take a command once it is in TheCommandList; the stream
    append is earlier by the translator's own delay, which is not wait."""
    j = netlat.wrap_delays(netlat.load(baseline))
    assert netlat.pct(j["pipeline"], 50) - netlat.pct(j["wrap"], 50) == pytest.approx(5.0, abs=0.5)


def test_the_per_tick_frame_info_is_not_joined_as_a_command(baseline):
    """Every client sends a type-3 frame info on every logic tick. Joined in, it
    is ~5 events a second of something else inside every median."""
    seat = netlat.load(baseline)
    sends = [e for e in seat["events"] if e["ev"] == "send"]
    assert any(e["type"] == 3 for e in sends), "the fixture stopped exercising this"
    assert netlat.wrap_delays(seat)["sends"] == sum(1 for e in sends if e["type"] == 4)


def test_game_speed_comes_from_the_frame_field_and_survives_a_stall(tmp_path):
    """5 logic frames a wall second is the invariant a latency fix must not move.
    One stall must not be able to move it either, or both arms fail for reasons
    that have nothing to do with the patch."""
    clean = netlat.logic_rate(netlat.load(
        match(tmp_path / "clean.jsonl", 1, False, wrap=16.0)))[0]
    rate, stalls, _ = netlat.logic_rate(netlat.load(
        match(tmp_path / "stalled.jsonl", 1, False, wrap=16.0, stall_at=40)))
    assert clean == pytest.approx(5.0, abs=0.01)
    assert rate == pytest.approx(5.0, abs=0.01), "a stall leaked into the game-speed number"
    assert len(stalls) == 1, "the stall was not reported as excluded"


def test_a_backlogged_guest_is_visible(tmp_path):
    """The one term reading the binary could not settle: a guest that falls
    behind the published ceiling carries a delay no send-side fix can touch."""
    seat = netlat.load(match(tmp_path / "behind.jsonl", 1, False, wrap=16.0, backlog=3))
    backlog = [e["c"] - e["f"] for e in seat["events"] if e["ev"] == "frame"]
    assert netlat.pct(backlog, 50) == 3


def test_end_to_end_uses_the_router_s_binding(tmp_path):
    """A guest never learns its own execution frame -- it sends unstamped and the
    router pins it. The number a player feels only exists across two files."""
    guest = match(tmp_path / "guest.jsonl", 1, False, wrap=to_next_tick)
    host = router_binding(tmp_path / "host.jsonl", [guest])
    g, r = netlat.load(guest), netlat.load(host)
    paired = netlat.wrap_delays(g)["paired"]
    e2e, unbound, impossible = netlat.end_to_end(g, r, paired)
    assert e2e, f"no command could be tied to a frame ({unbound} unbound)"
    assert impossible == 0, "commands came out executing before they were issued"
    # input -> ready(5) -> wait for the tick -> reaches the router -> the frame
    # it was pinned to. Never less than the wrap it already waited.
    assert netlat.pct(e2e, 50) >= netlat.pct(netlat.wrap_delays(g)["wrap"], 50)
    assert netlat.pct(e2e, 50) < 700


def test_a_command_that_executed_before_it_was_issued_is_refused(tmp_path):
    """The join is across two files, and a mispaired one produces a negative
    latency. Averaged in it shortens exactly the number the spike is decided on,
    so it has to be an error rather than a small median."""
    guest = match(tmp_path / "g.jsonl", 1, False, wrap=to_next_tick, count=40, seconds=30)
    host = router_binding(tmp_path / "h.jsonl", [], slot=0, count=40, seconds=30)
    events = [json.loads(x) for x in Path(host).read_text().splitlines()]
    # Bind this seat's commands to the very first frame, which ran before any
    # of them was issued.
    for i in range(10):
        events.append(line("relay", 1000.0 + i, FIRST_FRAME + 5, FIRST_FRAME + 5, 0, True,
                           type=4, cmd=i, player=1, exec=FIRST_FRAME, mask=255))
    events.sort(key=lambda e: 0 if e["ev"] == "open" else e["qlo"] + (e["qhi"] << 32))
    Path(host).write_text("".join(json.dumps(e) + "\n" for e in events))

    g, r = netlat.load(guest), netlat.load(host)
    _, _, impossible = netlat.end_to_end(g, r, netlat.wrap_delays(g)["paired"])
    assert impossible >= 10, "a negative latency was folded into the result"


def test_a_file_that_says_nothing_raises(tmp_path):
    empty = tmp_path / "empty.jsonl"
    empty.write_text("")
    with pytest.raises(SystemExit, match="no open record"):
        netlat.load(empty)

    headless = tmp_path / "headless.jsonl"
    headless.write_text(json.dumps(line("frame", 0, 1, 1, 0, True, exec=1)) + "\n")
    with pytest.raises(SystemExit, match="no open record"):
        netlat.load(headless)

    silent = tmp_path / "silent.jsonl"
    silent.write_text(json.dumps(dict(ev="open", qfreqlo=FREQ, qfreqhi=0)) + "\n")
    with pytest.raises(SystemExit, match="no events"):
        netlat.load(silent)


def test_a_seat_with_no_frames_cannot_report_a_rate(tmp_path):
    p = tmp_path / "noframes.jsonl"
    p.write_text(json.dumps(dict(ev="open", qfreqlo=FREQ, qfreqhi=0)) + "\n" +
                 json.dumps(line("input", 5, 1, 1, 0, True, type=0x3EA, msg=1,
                                 list=0, owner=0)) + "\n")
    with pytest.raises(SystemExit, match="frame events"):
        netlat.logic_rate(netlat.load(p))


def test_two_routers_is_refused(tmp_path):
    a = router_binding(tmp_path / "a.jsonl", [], slot=0, count=20, seconds=20)
    b = router_binding(tmp_path / "b.jsonl", [], slot=2, count=20, seconds=20)
    r = subprocess.run([sys.executable, str(ROOT / "tools/netlat.py"), str(a), str(b)],
                       capture_output=True, text=True)
    assert r.returncode != 0
    assert "packet router" in r.stderr + r.stdout


def test_preflight_fails_when_the_input_hook_never_fired(tmp_path):
    """The one hook whose target was never confirmed to be the path input takes.
    Dead, every latency is uncomputable -- and a run that produced no numbers
    must not be reported as a run that found no delay."""
    p = match(tmp_path / "noinput.jsonl", 1, False, wrap=16.0)
    kept = [x for x in Path(p).read_text().splitlines()
            if json.loads(x).get("ev") != "input"]
    Path(p).write_text("\n".join(kept) + "\n")
    r = subprocess.run([sys.executable, str(ROOT / "tools/netlat.py"), "--preflight", str(p)],
                       capture_output=True, text=True)
    assert r.returncode != 0
    assert "input hook fires" in r.stdout and "PREFLIGHT FAILED" in r.stdout


def test_preflight_fails_when_the_seats_did_not_share_a_host(tmp_path):
    """Cross-seat latency is only meaningful because one host clock serves every
    wine prefix. Two clocks and the headline number is arithmetic on noise."""
    a = match(tmp_path / "a.jsonl", 0, True, wrap=8.0, count=20, seconds=20)
    b = match(tmp_path / "b.jsonl", 1, False, wrap=16.0, count=20, seconds=20)
    lines = Path(b).read_text().splitlines()
    head = json.loads(lines[0])
    head["qfreqlo"] = 3_579_545          # a different host's counter
    Path(b).write_text("\n".join([json.dumps(head)] + lines[1:]) + "\n")
    r = subprocess.run([sys.executable, str(ROOT / "tools/netlat.py"), "--preflight",
                        str(a), str(b)], capture_output=True, text=True)
    assert r.returncode != 0
    assert "one clock frequency" in r.stdout and "PREFLIGHT FAILED" in r.stdout


def test_preflight_passes_a_healthy_capture(tmp_path):
    guest = match(tmp_path / "g.jsonl", 1, False, wrap=to_next_tick)
    host = router_binding(tmp_path / "h.jsonl", [guest])
    r = subprocess.run([sys.executable, str(ROOT / "tools/netlat.py"), "--preflight",
                        str(host), str(guest)], capture_output=True, text=True)
    assert r.returncode == 0, r.stdout
    assert "PREFLIGHT PASSED" in r.stdout


def test_the_report_runs_end_to_end(tmp_path):
    guest = match(tmp_path / "g.jsonl", 1, False, wrap=to_next_tick)
    host = router_binding(tmp_path / "h.jsonl", [guest])
    r = subprocess.run([sys.executable, str(ROOT / "tools/netlat.py"),
                        "--check-clocks", str(host), str(guest)],
                       capture_output=True, text=True)
    assert r.returncode == 0, r.stderr
    for expected in ("logic rate", "send cadence", "backlog", "host vs guest",
                     "send->run", "frame skew"):
        assert expected in r.stdout, f"the report never mentions {expected}"
