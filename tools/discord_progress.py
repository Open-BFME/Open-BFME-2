#!/usr/bin/env python3
"""Post BFME2 progress using progress.py's existing headline calculation."""
import argparse
import json
import os
from datetime import datetime, timezone
from urllib.error import HTTPError, URLError
from urllib.request import Request, urlopen

import progress


def announcement(current, previous):
    percentage = progress.percent(current["rebuilt"], current["total"])
    filled = round(percentage / 10)
    change = ""
    if previous:
        delta = percentage - progress.percent(previous["rebuilt"], previous["total"])
        change = f"\n{delta:+.2f} percentage points since the last update"
    return {
        "allowed_mentions": {"parse": []},
        "embeds": [{
            "title": "BFME 2 · Rebuild progress",
            "color": 0x3FB950,
            "description": f"**{percentage:.2f}%**\n\n"
                           + "🟩" * filled + "⬛" * (10 - filled)
                           + f"\n{change}\n"
                           + f"{current['rebuilt']:,} / {current['total']:,} code bytes",
        }],
    }


def notify(current):
    state_path = progress.ROOT / "docs" / "discord-progress.json"
    previous = json.loads(state_path.read_text(encoding="utf-8")) if state_path.exists() else None
    run_id = os.environ.get("GITHUB_RUN_ID")
    if run_id and previous and previous.get("run_id") == run_id:
        print("Discord: this run already posted")
        return
    webhook = os.environ.get("DISCORD_PROGRESS_WEBHOOK", "").strip()
    if not webhook.startswith("https://discord.com/api/webhooks/"):
        raise SystemExit("DISCORD_PROGRESS_WEBHOOK is missing or invalid")
    url = webhook + "?wait=true"
    request = Request(url, data=json.dumps(announcement(current, None)).encode("utf-8"),
                      headers={"Content-Type": "application/json", "User-Agent": "OpenBFME-Progress/1.0"},
                      method="POST")
    try:
        with urlopen(request, timeout=30) as response:
            message = json.load(response)
    except HTTPError as exc:
        raise SystemExit(f"Discord update failed: HTTP {exc.code}") from None
    except URLError:
        raise SystemExit("Discord update failed: connection error") from None
    state_path.write_text(json.dumps({**current, "updated_at": datetime.now(timezone.utc).isoformat(),
                                     "message_id": message["id"], "run_id": run_id}, indent=2) + "\n", encoding="utf-8")
    print("Discord: new progress message posted")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--discord", action="store_true", help="post a new main Discord progress message")
    args = parser.parse_args()
    matched = progress.matched_at(None)
    start, size = progress.retail_text()
    naked = progress.naked_cpp_rows_at(matched, None)
    split = progress.source_split(matched, progress.notes_at(None), start, size, naked)
    _, total = progress.real_code_denominator(start, size)
    rebuilt = progress.rebuildable(split)
    if args.discord:
        notify({"rebuilt": rebuilt, "total": total})


if __name__ == "__main__":
    main()
