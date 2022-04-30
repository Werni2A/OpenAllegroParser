#! /usr/bin/env python3

import argparse
import os
import re
import subprocess
import sys
import tempfile
import time
from datetime import datetime
from pathlib import Path
from sys import platform
from typing import Optional


def clean_path(path: str) -> str:
    path = os.path.abspath(path)
    path = os.path.normpath(path)
    path = path.replace("\\", "/")
    return path


def create_scr_file(
    path_scr: str, path_pxml: str, version: Optional[str] = None
) -> None:
    """Create a script file for the padstack editor
    to export the currently opened padstack to an XML file.

    Args:
        path_scr (str): Path to padstack (*.pad) file
        path_pxml (str): Path where XML (*.pxml) file will be saved to
        version (str, optional): Version string that is included into
            the script as a comment.
    """

    # Files generated from the padstack editor use forward slashes in paths
    path_pxml = clean_path(path_pxml)
    path_scr = clean_path(path_scr)

    if version is None:
        # This is the padstack editor version that the
        # script is designed and tested against. Other
        # versions might require modifications to the script!
        version = "17.4 S012 (3898062) Windows SPB 64-bit Edition"

    now = datetime.now()
    date_time = now.strftime("%a %b %d %Y %H:%M:%S")

    scr_content = f"""# Padstack Editor script
#	file: {path_scr}
#	start time: {date_time}
#	Version: {version}

QtSignal MainWindow ExportXml triggered
QtSignal pseCheckBrowser Close clicked
QtFillin Yes
QtFillin {path_pxml}
QtFillin Save
QtFillin Yes
QtSignal MainWindow AQFileDialog finished 1
QtSignal MainWindow Exit triggered
"""

    with open(path_scr, "w") as file_scr:
        file_scr.write(scr_content)


def export_pad_to_xml(path_pad: str, path_pxml: str) -> None:
    """Export a padstack to an XML file.

    This will generate a padstack editor script that
    will be executed by the padstack editor.

    Args:
        path_pad (str): Path to padstack (*.pad) file
        path_pxml (str): Path to XML (*.pxml) file that will be created
    """

    path_pad = clean_path(path_pad)
    path_pxml = clean_path(path_pxml)

    path_scr = os.path.join(tempfile.gettempdir(), "pad_to_pxml.scr")
    path_scr = clean_path(path_scr)

    path_padstack_editor = r"C:\Cadence\SPB_17.4\tools\bin\padstack_editor.exe"
    path_padstack_editor = clean_path(path_padstack_editor)

    if not os.path.isfile(path_padstack_editor):
        print(
            f"Padstack editor was not found at {path_padstack_editor}, adjust this path!"
        )
        sys.exit(-1)

    print(f"Exporting {path_pad} to {path_pxml} with script {path_scr} ...")

    create_scr_file(path_scr, path_pxml)

    command = [
        path_padstack_editor,
        "-p",
        f"{os.path.dirname(path_pad)}",
        "-s",
        f"{path_scr}",
        f"{os.path.basename(path_pad)}",
    ]

    print(f'Executing: {" ".join(command)}')

    last_modified_pxml = None
    if os.path.exists(path_pxml):
        last_modified_pxml = os.stat(path_pxml).st_mtime

    # Start padstack editor and convert the *.pad to *.pxml
    proc = subprocess.run(command)

    curr_modified_pxml = None
    if os.path.exists(path_pxml):
        curr_modified_pxml = os.stat(path_pxml).st_mtime

    export_success = False

    if proc.returncode != 0:
        print(f"Executing padstack editor failed with return code {proc.returncode}")

    # Successfully created new pxml file
    if not last_modified_pxml and curr_modified_pxml:
        export_success = True

    # Successfully updated existing pxml file
    if curr_modified_pxml and last_modified_pxml:
        if curr_modified_pxml > last_modified_pxml:
            export_success = True

    if not export_success:
        print(f"Exporting {path_pxml} failed!")


parser = argparse.ArgumentParser()


parser.add_argument(
    "path", help="Path to `*.pad` file or folder containing them", type=str
)

parser.add_argument(
    "--pxml_suffix",
    help="Gets appended to the pxml file name",
    const="",
    nargs="?",
    type=str,
)

parser.add_argument(
    "--overwrite",
    help="Overwrite existing pxml files",
    const=False,
    nargs="?",
    type=bool,
)

args = parser.parse_args()

if __name__ == "__main__":

    if "win" not in platform:
        print(f"This tool runs only on Windows but your system is {platform}!")
        sys.exit(-1)

    if not os.path.exists(args.path):
        print(f"{args.path} does not exist!")
        sys.exit(-1)

    if not os.path.isdir(args.path) and not os.path.isfile(args.path):
        print(f"{args.path} needs to be a file or directory!")
        sys.exit(-1)

    path = clean_path(args.path)
    suffix = args.pxml_suffix if args.pxml_suffix else ""
    overwrite = args.overwrite if args.overwrite else False

    path_pads = []

    if os.path.isfile(path):
        path_pads = [path]

    if os.path.isdir(path):
        path_pads = [str(file_pad) for file_pad in Path(path).rglob("*.pad")]
        path_pads = sorted(path_pads)

    for path_pad in path_pads:

        path_pad = clean_path(path_pad)

        name_pad = re.sub(r"\.pad$", "", os.path.basename(path_pad))
        name_pxml = name_pad + suffix + ".pxml"

        path_pxml = os.path.join(os.path.dirname(path_pad), name_pxml)
        path_pxml = clean_path(path_pxml)

        if not overwrite and os.path.exists(path_pxml):
            print(
                f"pxml already exists, skipping export from `{path_pad}` to `{path_pxml}`."
            )
            continue

        print(f"Exporting `{path_pad}` to `{path_pxml}` ...")
        export_pad_to_xml(path_pad, path_pxml)

        # The padstack editor requires some time,
        # otherwise it might fail silently.
        time.sleep(1.5)
