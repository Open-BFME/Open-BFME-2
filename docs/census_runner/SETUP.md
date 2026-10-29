# Set up a BFME 2 census runner

Written for an agent (Claude Code, DeepSeek, …) or a person setting up a new
census host. A census builds the whole game from `Code/` with MSVC 7.1 (run under
Wine) and links it. It records the result as a row in
`reverse/link_census_history.csv` and publishes the `census-index` release
asset, which every seat's link checks read. `runner.sh` in this directory does
one cycle per run, and the systemd timer repeats it. Several runners can
coexist: each starts a census only when the newest recorded census, anyone's,
is more than `CENSUS_MIN_AGE` (110) minutes old.

## Rules

Read `AGENTS.md` at the repository root. It wins wherever it's stricter.
- Never run `tools/nightly_measure.py`, `tools/boot_smoke.py`,
  `tools/link_cycle.py`, the nightly workflow or the shadow publisher.
- Never use `--no-verify` or bypass a hook.
- The runner commits only its two census files. Commit nothing else to master
  from this host.
- Don't edit the project's code from this host. Report anything that doesn't
  work here, with the exact error.

## Host

- 16+ cores. A fast single core helps the final link. 32 GB+ RAM. 50 GB free
  on an SSD (the runner uses about 11 GB).
- Ubuntu 24.04, or WSL2 Ubuntu on Windows. Always on, with outbound HTTPS to
  github.com.
- Preferably not shared with another heavy job. Contention made one host take
  6–14 hours per census and crash.

## Steps

1. **Install the packages.**
   - `sudo dpkg --add-architecture i386`
   - `sudo apt update`
   - `sudo apt install -y git gh python3 python3-venv util-linux wine wine32 wine64`
   - Wine 9.x is known to work.
2. **GitHub access.** The account needs write access to `Open-BFME/Open-BFME-2`.
   - Make a fine-grained token for that one repository with **Contents: Read
     and write**.
   - Run `gh auth login --with-token`, then `gh auth setup-git`.
   - Run `git config --global user.name "<name>"` and
     `git config --global user.email "<id>+<login>@users.noreply.github.com"`.
     GitHub refuses pushes that expose a private email (GH007).
3. **Lay out the runner.**
   ```bash
   mkdir -p ~/bfme2-runner && cd ~/bfme2-runner
   git clone https://github.com/Open-BFME/Open-BFME-2 repo
   git -C repo config core.hooksPath .githooks
   git -C repo submodule update --init --depth 1 reference/open-bfme-1   # holds the MSVC 7.1 toolchain
   cp repo/docs/census_runner/runner.sh . && chmod +x runner.sh
   cp repo/docs/census_runner/README.md README.md
   python3 -m venv --system-site-packages venv
   venv/bin/pip install -c repo/.github/nightly-constraints.txt capstone pefile numpy unicorn pytest
   WINEPREFIX=$PWD/wine WINEDEBUG=-all DISPLAY= wineboot -i
   ```
4. **Install the systemd user units.**
   ```bash
   mkdir -p ~/.config/systemd/user
   cp repo/docs/census_runner/bfme2-runner.{service,timer} ~/.config/systemd/user/
   systemctl --user daemon-reload
   sudo loginctl enable-linger "$USER"
   ```
   Set the memory limits and build pool for this host with
   `systemctl --user edit bfme2-runner.service`:
   ```ini
   [Service]
   MemoryHigh=<about 40% of RAM>
   MemoryMax=<about 60% of RAM>
   Environment=BUILD_POOL=<about half the cores, at most 16>
   ```
5. **Smoke tests.** Note how long each takes.
   - `cd ~/bfme2-runner/repo && PATH=~/bfme2-runner/venv/bin:$PATH WINEPREFIX=~/bfme2-runner/wine ./build.sh Code/GameEngine/Source/Common/System/Xfer.cpp`
     (or any small `.cpp` listed in `reverse/functions.csv`). The first run
     takes 20–60 s.
   - `PATH=~/bfme2-runner/venv/bin:$PATH python3 tools/link_check.py --fetch-index`
6. **Run the first cycle by hand.**
   - `systemctl --user start bfme2-runner.service`
   - Follow it with `journalctl --user -u bfme2-runner.service -f` and
     `~/bfme2-runner/logs/`.
   - A census runs only when the newest one is more than 110 minutes old.
     Otherwise the cycle updates and publishes the index.
   - Leave the timer **disabled** until the owner has seen this result. Then
     `systemctl --user enable --now bfme2-runner.timer`.
7. **Report:**
   - CPU model and core count, RAM, disk, OS and Wine version;
   - the time of each step;
   - for a census: its time and the `link census …` summary lines;
   - any error, quoted exactly.
