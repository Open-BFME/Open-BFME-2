#!/usr/bin/env bash
# BFME 2 census runner: one cycle per invocation (bfme2-runner.timer).
#   - follower: pull master, link_check.py --update-index, --publish-index
#   - census:   link_census.py --build --history when the last census row is
#               older than CENSUS_MIN_AGE minutes and HEAD is not its commit;
#               commit + push the two census files, then --publish-index.
# One flock serializes everything. Setup: docs/census_runner/SETUP.md; operation: README.md.
set -uo pipefail

R=${BFME2_RUNNER_DIR:-$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)}   # the runner directory
REPO=$R/repo
LOGS=$R/logs
STATUS=$R/status.txt
CENSUS_MIN_AGE=${CENSUS_MIN_AGE:-110}     # minutes since the last history row (anyone's census)
PUSH_SPACING=${PUSH_SPACING:-300}         # seconds between pushes by this GitHub account
ACCOUNT=${GH_ACCOUNT:-$(gh api user --jq .login 2>/dev/null)}   # the GitHub login this runner pushes as
GH_REPO=Open-BFME/Open-BFME-2
export PATH=$R/venv/bin:$PATH   # capstone/pefile/numpy/unicorn (nightly constraints)
export BUILD_POOL=${BUILD_POOL:-8}
export WINEDEBUG=-all DISPLAY= WINEPREFIX=$R/wine
export PYTHONUNBUFFERED=1
GIT="git -c core.hooksPath=.githooks -c submodule.recurse=false"

# reference/open-bfme-1 follows the superproject's pin. A recursing `pull --rebase`
# tried to rebase the old pinned checkout onto a new pin (2026-10-28) and left an
# interactive rebase behind; sync the submodule to the pin explicitly instead.
sync_bfme1() {
    local pin sub
    pin=$(git ls-tree HEAD reference/open-bfme-1 | awk '{print $3}')
    sub=$(git -C reference/open-bfme-1 rev-parse HEAD 2>/dev/null)
    [ -n "$pin" ] && [ "$sub" = "$pin" ] && return 0
    git -C reference/open-bfme-1 -c gc.auto=0 fetch -q --depth 1 origin "$pin" &&
        git -C reference/open-bfme-1 -c advice.detachedHead=false checkout -q --detach "$pin" &&
        log "reference/open-bfme-1 -> $pin"
}

mkdir -p "$LOGS"
exec 9>"$R/runner.lock"
if ! flock -n 9; then echo "$(date -u '+%F %T') another cycle holds the lock; skipping"; exit 0; fi

RUNLOG=$LOGS/cycle-$(date -u +%Y%m%d-%H%M%S).log
exec > >(tee -a "$RUNLOG") 2>&1
find "$LOGS" -name 'cycle-*.log' -mtime +14 -delete
log() { echo "[$(date -u '+%F %T')] $*"; }

# status KEY VALUE: one line per key in status.txt
status() {
    local tmp; tmp=$(mktemp "$R/.status.XXXX")
    { grep -v "^$1=" "$STATUS" 2>/dev/null; echo "$1=$2"; } | sort > "$tmp" && mv "$tmp" "$STATUS"
}
# timed NAME CMD...: run, record NAME's time/result/duration in status.txt
timed() {
    local name=$1 start end rc; shift
    start=$(date +%s); log "start $name: $*"
    "$@"; rc=$?
    end=$(date +%s)
    log "end $name: rc=$rc in $((end - start))s"
    status "$name" "$(date -u '+%F %T') UTC rc=$rc seconds=$((end - start)) head=$(git -C "$REPO" rev-parse --short=10 HEAD)"
    return $rc
}

cd "$REPO" || exit 1
status last_cycle_start "$(date -u '+%F %T') UTC"

sync_bfme1 || { log "BFME 1 submodule sync failed"; status last_error "$(date -u '+%F %T') UTC submodule sync"; exit 1; }
if [ -n "$(git status --porcelain -uno)" ]; then
    log "tracked files are dirty; refusing to run (inspect $REPO by hand):"; git status --short -uno
    status last_error "$(date -u '+%F %T') UTC dirty tree"; exit 1
fi
if ! $GIT pull --rebase origin master; then
    git rebase --abort 2>/dev/null
    log "pull --rebase failed"; status last_error "$(date -u '+%F %T') UTC pull failed"; exit 1
fi
sync_bfme1 || { log "BFME 1 submodule sync failed"; status last_error "$(date -u '+%F %T') UTC submodule sync"; exit 1; }
HEAD=$(git rev-parse --short=10 HEAD)

# The newest census anyone recorded, and the census our local index derives from.
read -r ROW_DATE ROW_COMMIT < <(python3 - <<'PY'
import csv
rows = list(csv.DictReader(open("reverse/link_census_history.csv", newline="", encoding="utf-8")))
print(rows[-1]["date"].replace(" ", "T"), rows[-1]["commit"])
PY
)
index_census() {
    python3 - <<'PY'
import sys
sys.path.insert(0, "tools")
import link_check
meta = link_check.index_meta(link_check.INDEX) if link_check.INDEX.exists() else None
print(meta.get("census_commit", meta["commit"]) if meta else "none")
PY
}
same() { [ "${1:0:10}" = "${2:0:10}" ]; }

LOCAL_CENSUS=$(index_census)
if ! same "$LOCAL_CENSUS" "$ROW_COMMIT"; then
    PUBLISHED=$(gh release view census-index --repo "$GH_REPO" --json body --jq .body 2>/dev/null \
                | sed -nE 's/.*census [0-9-]+ [0-9:]+ UTC at ([0-9a-f]+).*/\1/p')
    log "local index census $LOCAL_CENSUS, newest census row $ROW_COMMIT, published census ${PUBLISHED:-?}"
    if [ "$LOCAL_CENSUS" = none ] || { [ -n "$PUBLISHED" ] && same "$PUBLISHED" "$ROW_COMMIT"; }; then
        rm -f build/link_census/link_index.pkl
        timed last_fetch_index python3 tools/link_check.py --fetch-index || exit 1
        LOCAL_CENSUS=$(index_census)
    fi
fi

AGE_MIN=$(( ( $(date -u +%s) - $(date -u -d "${ROW_DATE/T/ } UTC" +%s) ) / 60 ))
log "HEAD $HEAD; last census row $ROW_COMMIT at $ROW_DATE UTC (${AGE_MIN} min ago); index census $LOCAL_CENSUS"

wait_push_slot() {
    local last ours now wait
    last=$(gh api "users/$ACCOUNT/events?per_page=50" \
           --jq "[.[] | select(.type==\"PushEvent\" and .repo.name==\"$GH_REPO\") | .created_at][0] // empty" 2>/dev/null)
    last=$([ -n "$last" ] && date -u -d "$last" +%s || echo 0)
    ours=$(cat "$R/.last_push" 2>/dev/null || echo 0)
    [ "$ours" -gt "$last" ] && last=$ours
    now=$(date -u +%s); wait=$(( last + PUSH_SPACING - now ))
    if [ "$wait" -gt 0 ]; then log "push spacing: waiting ${wait}s"; sleep "$wait"; fi
}

push_master() {
    local try
    for try in 1 2 3 4 5 6; do
        wait_push_slot
        if ! $GIT pull --rebase origin master; then
            git rebase --abort 2>/dev/null; log "rebase failed before push (try $try)"; return 1
        fi
        if $GIT push origin HEAD:master; then
            date -u +%s > "$R/.last_push"
            $GIT pull --rebase origin master || git rebase --abort 2>/dev/null
            return 0
        fi
        log "push rejected (try $try); retrying"; sleep 20
    done
    return 1
}

if [ "$AGE_MIN" -ge "$CENSUS_MIN_AGE" ] && ! same "$HEAD" "$ROW_COMMIT"; then
    CENSUS_HEAD=$(git rev-parse HEAD)
    if ! timed last_census python3 tools/link_census.py --build --history; then
        status last_error "$(date -u '+%F %T') UTC census failed at $HEAD (see $RUNLOG)"
        # a failed census records nothing; never leave its files half-written
        git checkout -- reverse/link_census_history.csv reverse/link_status.csv 2>/dev/null
        exit 1
    fi
    if git diff --quiet -- reverse/link_census_history.csv; then
        log "census recorded no history row"; status last_error "$(date -u '+%F %T') UTC census wrote no row"; exit 1
    fi
    git add reverse/link_census_history.csv reverse/link_status.csv
    MSG="link_census: census $(date -u '+%F %T') UTC at $CENSUS_HEAD

Census command: python3 tools/link_census.py --build --history"
    if ! timed last_census_commit $GIT commit -m "$MSG"; then
        status last_error "$(date -u '+%F %T') UTC census commit refused by hooks (see $RUNLOG)"; exit 1
    fi
    status last_census_figures "$(tail -1 reverse/link_census_history.csv | python3 -c '
import csv,sys
h=next(csv.reader(open("reverse/link_census_history.csv")))
r=next(csv.reader(sys.stdin)); d=dict(zip(h,r))
print("date=%s commit=%s linked_bytes=%s files_linked=%s/%s" % (d["date"], d["commit"], d["linked_bytes"], d["files_linked"], d["files"]))')"
    if ! timed last_push push_master; then
        # Another census landed meanwhile (the census files conflict) or the
        # push kept failing: drop our unpublished census commit, nothing else.
        if [ "$(git rev-list --count origin/master..HEAD)" = 1 ]            && git log -1 --format=%s | grep -q "^link_census: census .* at $CENSUS_HEAD$"; then
            git reset --hard origin/master
            log "census commit dropped; HEAD back at origin/master"
        fi
        status last_error "$(date -u '+%F %T') UTC census push failed (see $RUNLOG)"; exit 1
    fi
    status last_census_commit_sha "$(git log -1 --format=%H --grep="census .* at $CENSUS_HEAD")"
    timed last_publish python3 tools/link_check.py --publish-index || exit 1
    git rev-parse --short=10 HEAD > "$R/.last_index_head"   # the follower updates to the census commit next cycle
    exit 0
fi

if [ "$(cat "$R/.last_index_head" 2>/dev/null)" = "$HEAD" ]; then
    log "master has not moved since the last index update; nothing to do"; exit 0
fi
timed last_update_index python3 tools/link_check.py --update-index || {
    status last_error "$(date -u '+%F %T') UTC update-index failed at $HEAD (see $RUNLOG)"; exit 1; }
echo "$HEAD" > "$R/.last_index_head"
# Publishable once the index's commit is on origin/master (link_check.py
# publish_index checks it); master moving during the update is normal.
timed last_publish python3 tools/link_check.py --publish-index || {
    status last_error "$(date -u '+%F %T') UTC publish failed (see $RUNLOG)"; exit 1; }
