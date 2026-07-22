#!/usr/bin/env python3
"""Run lightweight, dependency-free checks on human-written source files."""

import ast
import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from typing import Iterable


REPO_ROOT = Path(__file__).resolve().parents[1]
SOURCE_SUFFIXES = {
    ".c",
    ".cc",
    ".cpp",
    ".cxx",
    ".cff",
    ".csv",
    ".h",
    ".hh",
    ".hpp",
    ".launch",
    ".m",
    ".md",
    ".py",
    ".rviz",
    ".sh",
    ".txt",
    ".urdf",
    ".xml",
    ".yaml",
    ".yml",
}
C_CPP_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp"}
XML_SUFFIXES = {".launch", ".urdf", ".xml"}
FORBIDDEN_SUFFIXES = {".a", ".mat", ".mexmaci64", ".mexa64", ".mexw64", ".o", ".obj", ".pyc", ".slxc", ".so", ".zip"}
FORBIDDEN_DIRECTORIES = {"build", "codegen", "devel", "install", "log", "slprj"}
LEGACY_TOP_LEVEL = {
    "MultirotorSim_Vervoorst",
    "aerofoil_matlab",
    "cartpole_system",
    "csv",
    "quadcopter_simple",
    "robot",
    "robot_arm",
    "src",
}
PERSONAL_PATH = re.compile(r"/(?:home|Users)/divij(?:/|\b)")


def is_human_source(path: Path) -> bool:
    relative = path.relative_to(REPO_ROOT)
    return (
        (path.suffix in SOURCE_SUFFIXES or path.name == "CMakeLists.txt")
        and ".git" not in relative.parts
    )


def source_files() -> Iterable[Path]:
    for path in REPO_ROOT.rglob("*"):
        if path.is_file() and is_human_source(path):
            yield path


def main() -> int:
    forbidden_artifacts = []
    legacy_directories = []
    metadata_errors = []
    syntax_errors = []
    xml_errors = []
    personal_paths = []
    cpp_count = 0
    python_count = 0

    for legacy_name in sorted(LEGACY_TOP_LEVEL):
        if (REPO_ROOT / legacy_name).exists():
            legacy_directories.append(legacy_name)

    for path in REPO_ROOT.rglob("*"):
        if ".git" in path.relative_to(REPO_ROOT).parts:
            continue
        if path.is_dir():
            if path.name in FORBIDDEN_DIRECTORIES or path.name.endswith("_grt_rtw"):
                forbidden_artifacts.append(path)
            continue
        if path.suffix.lower() in FORBIDDEN_SUFFIXES:
            forbidden_artifacts.append(path)

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
        elif path.suffix in C_CPP_SUFFIXES:
            cpp_count += 1

        if path.suffix in XML_SUFFIXES or path.name == "package.xml":
            try:
                ET.fromstring(text)
            except ET.ParseError as error:
                xml_errors.append((path, str(error)))

        if path.name == "package.xml" and (
            "TODO@EMAIL.COM" in text
            or "<description>TODO</description>" in text
            or "<license>TODO</license>" in text
        ):
            metadata_errors.append(path)

    for path in forbidden_artifacts:
        print("forbidden artifact: {}".format(path.relative_to(REPO_ROOT)))
    for directory in legacy_directories:
        print("legacy top-level directory: {}".format(directory))
    for path in metadata_errors:
        print("incomplete package metadata: {}".format(path.relative_to(REPO_ROOT)))
    for path, line_number, message in syntax_errors:
        print("syntax error: {}:{}: {}".format(path.relative_to(REPO_ROOT), line_number, message))
    for path, message in xml_errors:
        print("XML error: {}: {}".format(path.relative_to(REPO_ROOT), message))
    for path, line_number in personal_paths:
        print("personal path: {}:{}".format(path.relative_to(REPO_ROOT), line_number))

    if forbidden_artifacts or legacy_directories or metadata_errors or syntax_errors or xml_errors or personal_paths:
        return 1

    print(
        "Repository checks passed ({} Python files parsed, {} C/C++ source/header files audited).".format(
            python_count,
            cpp_count,
        )
    )
    return 0


if __name__ == "__main__":
    sys.exit(main())
