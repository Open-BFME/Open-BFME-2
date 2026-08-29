#!/usr/bin/env python3
"""The measured relationship between a candidate's shape and whether it lands.

Work selection is only worth biasing on features that predict the outcome. This
module holds the ones that survived measurement, so both queue tools weight the
same way and a refit happens in one place.

Fitted over the 743 drift candidates that reached an outcome in the 1,000
commits ending 2038d3a0d — 190 landed (newly claimed, or converted from a MASM
or naked body to clean C++), 553 carrying a standing dead-end verdict.
Selection was uniform across that window, so the sample is unbiased by the
selector.

WHAT DID NOT PREDICT, and must not be reintroduced as a weight without new
evidence:

* drift `aligned_pct`. Landed candidates averaged 22.7% alignment against 24.9%
  for dead ends (Cohen's d = -0.18 — very slightly the WRONG way), and the
  per-band land rate has no trend at all: 15.1 / 36.4 / 16.3 / 35.1 / 16.8%.
* how much of a candidate's source file was already matched (d = -0.17, flat).

What did predict, but is not usable at draw time: how many sibling rows in the
same source file land in the same window (d = +0.41 with the candidate's own
landing excluded). That is outcome information, and plausibly reflects an agent
choosing to focus on a file rather than the file being tractable. Turning it
into a draw-time feature needs per-commit ordering that nothing records yet.
"""
import math

# P(a served candidate is eventually landed), by target size in bytes.
LAND_RATE_BY_SIZE = ((64, 0.140), (128, 0.273), (256, 0.413), (512, 0.206))
LAND_RATE_LARGE = 0.088


def land_rate(size):
    """Measured probability that a candidate of this size is eventually landed."""
    for limit, rate in LAND_RATE_BY_SIZE:
        if size < limit:
            return rate
    return LAND_RATE_LARGE


def weight(size):
    """Selection weight for a candidate of this size.

    P(land) is measured. The size term is deliberately NOT the byte yield:
    nothing records how long an attempt takes, so the cost model is unknown and
    the two plausible ones disagree about which end of the queue to serve.

      cost constant       -> value is P(land) * size  -> mean draw 891B
      cost scales w/ size -> value is P(land)         -> mean draw 314B

    Simulated against the live 493-candidate queue, P(land)*size wins on
    bytes-per-attempt (107.7 against 70.4 for a uniform draw) but LOSES to
    uniform once cost scales with size (37.0 against 39.4) — it is a bet that a
    1kB body at 9% success costs the same hour as a 176B body at 41%.
    sqrt(size) is the geometric middle and the only option that beats uniform
    under both models: 81.6 bytes/attempt (+16%) and 45.1 (+14%).

    Replace this with a fitted curve once attempt durations are recorded. Until
    then, robustness to the unknown cost model is worth more than peak yield
    under a guessed one.
    """
    size = max(1, int(size))
    return max(1, int(land_rate(size) * math.sqrt(size) * 1000))
