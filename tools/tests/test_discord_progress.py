"""Persistent progress message behavior; no network requests."""
import io
import json
import sys
from datetime import datetime, timezone
from pathlib import Path
from urllib.error import URLError

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import discord_progress as daily


def setup_state(tmp_path, monkeypatch, state=None):
    (tmp_path / "docs").mkdir()
    monkeypatch.setattr(daily.progress, "ROOT", tmp_path)
    path = tmp_path / "docs/discord-progress.json"
    if state:
        path.write_text(json.dumps(state), encoding="utf-8")
    return path


def test_retry_does_not_duplicate_post(tmp_path, monkeypatch):
    monkeypatch.setenv("GITHUB_RUN_ID", "run-123")
    state = {"rebuilt": 50, "total": 100, "message_id": "123", "run_id": "run-123"}
    setup_state(tmp_path, monkeypatch, state)
    monkeypatch.setattr(daily, "urlopen", lambda *a, **k: pytest.fail("Unexpected post"))
    daily.notify({"rebuilt": 50, "total": 100})


def test_success_records_delivery_and_disables_mentions(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token\n")
    def send(request, timeout):
        assert request.full_url.endswith("token?wait=true")
        payload = json.loads(request.data)
        assert payload["allowed_mentions"] == {"parse": []}
        assert "url" not in payload["embeds"][0]
        assert "50.00%" in payload["embeds"][0]["description"]
        return io.BytesIO(b'{"id":"123"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify({"rebuilt": 50, "total": 100})
    assert json.loads(path.read_text())["message_id"] == "123"


@pytest.mark.parametrize("previous_count", [40, 50])
def test_each_run_posts_new_message_even_if_unchanged(tmp_path, monkeypatch, previous_count):
    monkeypatch.setenv("GITHUB_RUN_ID", "new-run")
    path = setup_state(tmp_path, monkeypatch, {"rebuilt": previous_count, "total": 100, "message_id": "123", "run_id": "old-run"})
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/token")
    def send(request, timeout):
        assert request.method == "POST"
        assert request.full_url.endswith("?wait=true")
        return io.BytesIO(b'{"id":"456"}')
    monkeypatch.setattr(daily, "urlopen", send)
    daily.notify({"rebuilt": 50, "total": 100})
    assert json.loads(path.read_text())["rebuilt"] == 50
    assert json.loads(path.read_text())["message_id"] == "456"


def test_failed_post_does_not_advance_state_or_leak_url(tmp_path, monkeypatch):
    path = setup_state(tmp_path, monkeypatch)
    monkeypatch.setenv("DISCORD_PROGRESS_WEBHOOK", "https://discord.com/api/webhooks/test/secret")
    def fail(*args, **kwargs):
        raise URLError("secret")
    monkeypatch.setattr(daily, "urlopen", fail)
    with pytest.raises(SystemExit, match="^Discord update failed: connection error$"):
        daily.notify({"rebuilt": 50, "total": 100})
    assert not path.exists()


def test_change_is_percentage_points():
    payload = daily.announcement({"rebuilt": 55, "total": 100}, {"rebuilt": 50, "total": 100})
    assert "+5.00 percentage points" in payload["embeds"][0]["description"]
