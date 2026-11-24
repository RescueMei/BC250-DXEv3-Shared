#!/usr/bin/env python3
"""Check the menu's VFR-safe config mirror against the shared ABI header.

The VFR compiler cannot consume the full shared header, so the menu carries a
mirror of the structs and enum-like constants it needs. This check parses both
files and fails on any layout or constant drift.
"""

import argparse
import re
import sys
from pathlib import Path

STRUCT_RE = re.compile(r"typedef\s+struct\s*\{(.*?)\}\s*(\w+)\s*;", re.S)
DEFINE_RE = re.compile(r"^\s*#define\s+(\w+)\s+(.+?)\s*$", re.M)


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"//.*", "", text)
    return text


def fields(body):
    out = []
    for decl in body.split(";"):
        decl = " ".join(decl.split())
        if not decl:
            continue
        match = re.match(r"(.+?)\s*(\w+)\s*(\[[^\]]*\])?$", decl)
        if not match:
            out.append(decl)
            continue
        ctype, name, dims = match.groups()
        ctype = " ".join(ctype.split())
        out.append((ctype, name, dims or ""))
    return out


def structs(text):
    result = {}
    for body, name in STRUCT_RE.findall(strip_comments(text)):
        result[name] = fields(body)
    return result


def constants(text):
    result = {}
    for name, value in DEFINE_RE.findall(strip_comments(text)):
        value = " ".join(value.split())
        value = re.sub(r"\(\s*", "(", value)
        value = re.sub(r"\s*\)", ")", value)
        result[name] = value.rstrip("uUlL")
    return result


def resolve(name, table, depth=0):
    value = table[name]
    if depth < 8 and re.fullmatch(r"\w+", value) and value in table:
        return resolve(value, table, depth + 1)
    return value


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--mirror", required=True)
    parser.add_argument("--shared", required=True)
    args = parser.parse_args()

    mirror_text = Path(args.mirror).read_text(encoding="utf-8")
    shared_text = Path(args.shared).read_text(encoding="utf-8")
    mirror_structs = structs(mirror_text)
    shared_structs = structs(shared_text)
    mirror_consts = constants(mirror_text)
    shared_consts = constants(shared_text)

    failed = []
    for name, mirror_fields in mirror_structs.items():
        if name not in shared_structs:
            failed.append("mirror struct not in shared header: %s" % name)
            continue
        if mirror_fields != shared_structs[name]:
            failed.append("struct drift: %s" % name)
        else:
            print("ok: struct %s" % name)

    for name, value in mirror_consts.items():
        if name not in shared_consts:
            # UI IDs and other local-only constants are allowed; only compare
            # names that the shared header defines.
            continue
        if resolve(name, mirror_consts) != resolve(name, shared_consts):
            failed.append("constant drift: %s (%s != %s)" % (
                name, resolve(name, mirror_consts), resolve(name, shared_consts)))
        else:
            print("ok: constant %s" % name)

    if failed:
        for item in failed:
            print("FAIL:", item, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
