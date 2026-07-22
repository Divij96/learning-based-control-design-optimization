#!/usr/bin/env python3
"""Run lightweight, dependency-free checks on human-written source files."""

import ast
import re
import sys
from pathlib import Path
from typing import Iterable


REPO_ROOT = Path(__file__).resolve().parents[1]
SOURCE_SUFFIXES = {".py", ".m", ".sh", ".xml", ".yaml", ".yml"}
EXCLUDED_PARTS = {".git", "build", "devel", "install", "log", "slprj", "codegen"}
PERSONAL_PATH = re.compile(r"/(?:home|Users)/divij(?:/|\b)")


def is_human_source(path: Path) -> bool:
    relative = path.relative_to(REPO_ROOT)
    return (
        path.suffix in SOURCE_SUFFIXES
        and not any(part in EXCLUDED_PARTS for part in relative.parts)
        and not any(part.endswith("_grt_rtw") for part in relative.parts)
    )


def source_files() -> Iterable[Path]:
    for path in REPO_ROOT.rglob("*"):
        if path.is_file() and is_human_source(path):
            yield path


def main() -> int:
    syntax_errors = []
    personal_paths = []
    python_count = 0

    for path in source_files():
        text = path.read_text(encoding="utf-8", errors="replace")
        for line_number, line in enumerate(text.splitlines(), start=1):
            if PERSONAL_PATH.search(line):
                personal_paths.append((path, line_number))

        if path.suffix == ".py":
            python_count += 1
            try:
                ast.parse(text, filename=str(path))
            except SyntaxError as error:
                syntax_errors.append((path, error.lineno or 0, error.msg))

    for path, line_number, message in syntax_errors:
        print("syntax error: {}:{}: {}".format(path.relative_to(REPO_ROOT), line_number, message))
    for path, line_number in personal_paths:
        print("personal path: {}:{}".format(path.relative_to(REPO_ROOT), line_number))

    if syntax_errors or personal_paths:
        return 1

    print("Repository checks passed ({} Python files parsed).".format(python_count))
    return 0


if __name__ == "__main__":
    sys.exit(main())
