#!/usr/bin/env python3
"""Check consumer copies of provider-owned protocol headers.

The manifest is intentionally explicit. Each entry names a canonical provider
header and zero or more consumer headers. The check compares normalized C
declarations (comments and whitespace removed), so comments may differ while
ABI drift fails.
"""

import argparse
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
        provider = root / entry["provider"]
        if not provider.is_file():
            failed.append(f"missing provider: {provider}")
            continue
        source = normalize(provider)
        for consumer_name in entry.get("consumers", []):
            consumer = root / consumer_name
            if not consumer.is_file():
                failed.append(f"missing consumer: {consumer}")
            elif normalize(consumer) != source:
                failed.append(f"protocol drift: {consumer} != {provider}")
            elif not args.quiet:
                print(f"ok: {consumer}")
    if failed:
        for item in failed:
            print("FAIL:", item, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
