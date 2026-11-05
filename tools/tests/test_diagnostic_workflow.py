"""Offline workflow checks: no compiler, linker, game, dispatch or network."""
import hashlib
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest import mock
import yaml

ROOT = Path(__file__).resolve().parents[2]
WORKFLOW = yaml.load((ROOT / ".github/workflows/diagnostic-link.yml").read_text(), Loader=yaml.BaseLoader)
STEPS = WORKFLOW["jobs"]["diagnostic"]["steps"]
HISTORY = next(s["run"] for s in STEPS if s.get("name") == "Fetch root history for ref validation")
RESOLVE = next(s["run"] for s in STEPS if s.get("id") == "source")
STAGE = next(s["run"] for s in STEPS if s.get("name") == "Stage diagnostic image")

class Workflow(unittest.TestCase):
    def test_isolation_and_parity(self):
        self.assertEqual(set(WORKFLOW["on"]), {"workflow_dispatch"})
        self.assertEqual(WORKFLOW["permissions"], {"contents": "read"})
        self.assertTrue(WORKFLOW["concurrency"]["group"].startswith("diagnostic-link-"))
        real = yaml.load((ROOT / ".github/workflows/real-link.yml").read_text(), Loader=yaml.BaseLoader)
        realsteps = real["jobs"]["measure"]["steps"]
        self.assertEqual(WORKFLOW["env"], real["env"])
        self.assertEqual(WORKFLOW["jobs"]["diagnostic"]["runs-on"], real["jobs"]["measure"]["runs-on"])
        fields = ("uses", "with", "run", "shell", "env", "timeout-minutes")
        shared = ("Install dependencies", "Full build with retail byte verification",
                  "Diagnostic link", "Analyze diagnostic linked image")
        pairs = [(next(s for s in STEPS if s.get("name") == name),
                  next(s for s in realsteps if s.get("name") == name)) for name in shared]
        pairs.append((next(s for s in STEPS if s.get("uses", "").startswith("actions/setup-python@")),
                      next(s for s in realsteps if s.get("uses", "").startswith("actions/setup-python@"))))
        for diagnostic, measured in pairs:
            with self.subTest(step=diagnostic.get("name", diagnostic.get("uses"))):
                for field in fields:
                    self.assertEqual(diagnostic.get(field), measured.get(field), field)
                # Every other field is identical, except the permitted stricter
                # diagnostic failure behavior.
                for field in set(diagnostic) | set(measured):
                    if field not in ("if", "continue-on-error"):
                        self.assertEqual(diagnostic.get(field), measured.get(field), field)
                    elif diagnostic.get(field) != measured.get(field):
                        self.assertNotIn(field, diagnostic)
                        self.assertEqual(measured[field], "always()" if field == "if" else "true")
        checkouts = [s for s in STEPS if s.get("uses", "").startswith("actions/checkout@")]
        self.assertEqual(len(checkouts), 2)
        real_checkout = realsteps[0]
        for checkout in checkouts:
            self.assertEqual(checkout["uses"], real_checkout["uses"])
            for key, default in (("submodules", "false"), ("fetch-depth", "1"),
                                 ("persist-credentials", "true")):
                self.assertEqual(checkout["with"].get(key, default),
                                 real_checkout["with"].get(key, default))
            self.assertEqual(checkout["with"]["fetch-depth"], "1")
            self.assertNotIn("filter", checkout["with"])
        self.assertEqual(real_checkout["with"]["submodules"], "true")
        history_index = next(i for i, s in enumerate(STEPS) if s.get("name") == "Fetch root history for ref validation")
        resolve_index = next(i for i, s in enumerate(STEPS) if s.get("id") == "source")
        self.assertLess(0, history_index)
        self.assertLess(history_index, resolve_index)
        self.assertEqual(WORKFLOW["concurrency"]["group"], "diagnostic-link-" + "$" + "{{ github.run_id }}")
        for step in STEPS:
            if "uses" in step:
                self.assertRegex(step["uses"], r"@[a-f0-9]{40}$")
            if step.get("shell") == "python":
                compile(step["run"], step["name"], "exec")
        text = (ROOT / ".github/workflows/diagnostic-link.yml").read_text()
        for forbidden in ("secrets.", "scoreboard", "Discord", "--link", "real-link-measurement"):
            self.assertNotIn(forbidden, text)

    def test_history_fetch_expands_only_root_and_keeps_submodule_shallow(self):
        with tempfile.TemporaryDirectory() as d:
            base = Path(d)
            def git(repo, *args, check=True):
                return subprocess.run(["git", "-C", str(repo), *args], text=True,
                                      stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=check)
            def init(path):
                path.mkdir()
                git(path, "init", "-q", "-b", "master")
                git(path, "config", "user.name", "Offline test")
                git(path, "config", "user.email", "offline@example.invalid")
                git(path, "config", "uploadpack.allowFilter", "true")
            sub = base / "sub-origin"
            init(sub)
            git(sub, "commit", "--allow-empty", "-qm", "submodule pin")
            pin = git(sub, "rev-parse", "HEAD").stdout.strip()
            git(sub, "commit", "--allow-empty", "-qm", "submodule tip")
            origin = base / "origin"
            init(origin)
            (origin / ".gitmodules").write_text(
                '[submodule "reference/open-bfme-1"]\n'
                ' path = reference/open-bfme-1\n'
                f' url = {sub.as_uri()}\n')
            git(origin, "add", ".gitmodules")
            git(origin, "update-index", "--add", "--cacheinfo",
                "160000", pin, "reference/open-bfme-1")
            git(origin, "commit", "-qm", "root ancestor")
            ancestor = git(origin, "rev-parse", "HEAD").stdout.strip()
            git(origin, "commit", "--allow-empty", "-qm", "root bootstrap")
            clone = base / "clone"
            subprocess.run(["git", "-c", "protocol.file.allow=always", "clone", "-q",
                            "--depth=1", "--branch=master", "--recurse-submodules",
                            "--shallow-submodules", origin.as_uri(), str(clone)],
                           capture_output=True, check=True)
            child = clone / "reference/open-bfme-1"
            self.assertEqual(git(child, "rev-parse", "--is-shallow-repository").stdout.strip(), "true")
            self.assertNotEqual(git(clone, "cat-file", "-e", ancestor + "^{commit}", check=False).returncode, 0)
            # A new root tip requires an absent submodule commit. Even a clone
            # configured to recurse must leave that submodule untouched.
            git(sub, "commit", "--allow-empty", "-qm", "new submodule commit")
            new_pin = git(sub, "rev-parse", "HEAD").stdout.strip()
            git(origin, "update-index", "--cacheinfo",
                "160000", new_pin, "reference/open-bfme-1")
            git(origin, "commit", "-qm", "new root tip")
            git(origin, "branch", "swarm/test/fix")
            git(clone, "config", "submodule.recurse", "true")
            shallow_file = clone / ".git/modules/reference/open-bfme-1/shallow"
            shallow_before = shallow_file.read_bytes()
            old = os.getcwd()
            try:
                os.chdir(clone)
                exec(HISTORY, {})
                self.assertEqual(git(clone, "rev-parse", "--is-shallow-repository").stdout.strip(), "false")
                self.assertEqual(shallow_file.read_bytes(), shallow_before)
                self.assertEqual(git(child, "rev-parse", "HEAD").stdout.strip(), pin)
                self.assertNotEqual(git(child, "cat-file", "-e", new_pin + "^{commit}", check=False).returncode, 0)
                for ref in (ancestor, "swarm/test/fix"):
                    with mock.patch.dict(os.environ, REQUESTED_REF=ref, GITHUB_OUTPUT=str(base / "output")):
                        exec(RESOLVE, {})
            finally:
                os.chdir(old)

    def test_resolver(self):
        with tempfile.TemporaryDirectory() as d:
            old = os.getcwd()
            os.chdir(d)
            try:
                def git(*args):
                    return subprocess.check_output(["git", *args], text=True, stderr=subprocess.DEVNULL).strip()
                git("init", "-q")
                git("config", "user.name", "Offline test")
                git("config", "user.email", "offline@example.invalid")
                git("commit", "--allow-empty", "-qm", "repository")
                sha = git("rev-parse", "HEAD")
                git("update-ref", "refs/remotes/origin/swarm/test/fix", sha)
                git("commit", "--allow-empty", "-qm", "fork only")
                fork = git("rev-parse", "HEAD")
                for ref in ("swarm/test/fix", "refs/heads/swarm/test/fix", sha):
                    Path("output").write_text("")
                    with mock.patch.dict(os.environ, REQUESTED_REF=ref, GITHUB_OUTPUT="output"):
                        exec(RESOLVE, {})
                    self.assertEqual(Path("output").read_text(), "sha=" + sha + "\n")
                for ref in (fork, "refs/pull/1/head", "https://github.com/fork/repo",
                            "--help", "missing", "master\nsha=bad"):
                    with self.subTest(ref=ref), mock.patch.dict(os.environ, REQUESTED_REF=ref, GITHUB_OUTPUT="output"):
                        with self.assertRaises((SystemExit, subprocess.CalledProcessError)):
                            exec(RESOLVE, {})
            finally:
                os.chdir(old)

    def test_stage(self):
        with tempfile.TemporaryDirectory() as d:
            old = os.getcwd()
            os.chdir(d)
            try:
                out = Path("build/diagnostic_link")
                out.mkdir(parents=True)
                (out / "exit.exe").write_bytes(b"MZ fixture")
                (out / "exit.map").write_bytes(b"fixture map")
                receipt = dict(kind="diagnostic", commit="a" * 40,
                               image_sha256=hashlib.sha256(b"MZ fixture").hexdigest(),
                               map_sha256=hashlib.sha256(b"fixture map").hexdigest())
                rp = out / "image_receipt.json"
                rp.write_text(json.dumps(receipt))
                env = dict(IMAGE_SHA="a" * 40, REQUESTED_REF="swarm/test/fix",
                           DIAGNOSTIC_LABEL='packet "quoted"\nline', GITHUB_RUN_ID="123")
                with mock.patch.dict(os.environ, env):
                    exec(STAGE, {})
                    data = json.loads((out / "image/image_receipt.json").read_text())
                    self.assertEqual((data["ref"], data["label"], data["kind"]),
                                     (env["REQUESTED_REF"], env["DIAGNOSTIC_LABEL"], "diagnostic"))
                    for bad in (dict(receipt, kind="real"), dict(receipt, commit="b" * 40),
                                dict(receipt, map_sha256="bad")):
                        rp.write_text(json.dumps(bad))
                        with self.assertRaises(SystemExit):
                            exec(STAGE, {})
            finally:
                os.chdir(old)

if __name__ == "__main__":
    unittest.main()
