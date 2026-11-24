#!/usr/bin/env python3
"""Check consumer copies of provider-owned protocol headers.

The manifest is intentionally explicit. Each entry names a canonical provider
header and zero or more consumer headers. The check compares normalized C
declarations (comments and whitespace removed), so comments may differ while
ABI drift fails.

Provider entries may also carry ``provider_sha256``: the SHA-256 of the
normalized provider header. That lets a standalone driver repository, which
contains only its own package plus the shared submodule, verify its vendored
copies without a sibling provider checkout. When the provider file is present
the recorded hash is re-verified as well, so changing a provider without
updating the manifest fails loudly.
"""

import argparse
import hashlib
import json
import re
import sys
from pathlib import Path


def normalize(path):
    text = Path(path).read_text(encoding="utf-8")
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//.*", "", text)
    text = re.sub(r"\s+", " ", text)
    return text.strip()


def digest(text):
    return hashlib.sha256(text.encode("utf-8")).hexdigest()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", required=True)
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--quiet", action="store_true")
    args = parser.parse_args()
    root = Path(args.repo_root)
    manifest = json.loads(Path(args.manifest).read_text(encoding="utf-8"))
    failed = []
    for entry in manifest.get("protocols", []):
        provider_name = entry.get("provider", "")
        expected = entry.get("provider_sha256")
        provider = root / provider_name if provider_name else None

        if provider is not None and provider.is_file():
            current = digest(normalize(provider))
            if expected and current != expected:
                failed.append(
                    "provider changed: %s (%s != %s); update the manifest"
                    % (provider, current[:16], expected[:16]))
            expected = current
        elif not expected:
            failed.append(
                "missing provider and no provider_sha256: %s" % (provider or "<unset>"))
            continue

        for consumer_name in entry.get("consumers", []):
            consumer = root / consumer_name
            if not consumer.is_file():
                failed.append(f"missing consumer: {consumer}")
            elif digest(normalize(consumer)) != expected:
                failed.append(f"protocol drift: {consumer} != {provider_name or expected[:16]}")
            elif not args.quiet:
                print(f"ok: {consumer}")
    if failed:
        for item in failed:
            print("FAIL:", item, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
