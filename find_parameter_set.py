#!/usr/bin/env python3


import argparse
import os
import subprocess
import sys
from pathlib import Path
from typing import List, Tuple

# pip install colorama
from colorama import Fore, Style


class UnknownParameter:
    def __init__(self):
        self.bool0: bool = False
        self.bool1: bool = False
        self.bool2: bool = False
        self.int0: int = 0
        self.numUserLayers: int = 0  # @todo not required anymore
        self.additionalStr2: int = 0


def permute_unknown_parameters():

    param_set = UnknownParameter()

    for bool1 in [True, False]:
        param_set.bool1 = bool1

        for bool2 in [True, False]:
            param_set.bool2 = bool2

            for int0 in range(17):
                param_set.int0 = int0

                for additionalStr2 in range(45):
                    param_set.additionalStr2 = additionalStr2

                    yield param_set


def print_found(result: Tuple[str, str, bool]) -> None:
    print(Fore.GREEN)
    print("---------- Found valid Parameter Set -----------")
    print(result[1])
    print(Style.RESET_ALL)


def print_not_found(result: Tuple[str, str, bool]) -> None:
    print(Fore.RED)
    print("-------- No valid parameter set found! ---------")
    print(result[1])
    print(Style.RESET_ALL)


def print_result(result: Tuple[str, str, bool]) -> None:
    command = result[1]
    found_param_set = result[2]

    if found_param_set:
        print(Fore.GREEN, end="")
    else:
        print(Fore.RED, end="")

    print(command)
    print(Style.RESET_ALL, end="", flush=True)


parser = argparse.ArgumentParser()

parser.add_argument(
    "path", help="Path to `*.pad` file or folder containing them", type=str
)

args = parser.parse_args()


if __name__ == "__main__":

    if not os.path.exists(args.path):
        print(f"{args.path} does not exist!")
        sys.exit(-1)

    if not os.path.isdir(args.path) and not os.path.isfile(args.path):
        print(f"{args.path} needs to be a file or directory!")
        sys.exit(-1)

    path_pads = []

    if os.path.isfile(args.path):
        path_pads = [args.path]

    if os.path.isdir(args.path):
        path_pads = Path(args.path).rglob("*.pad")

    # List of tuples with pad path, command and whether
    # a working command was found
    results: List[Tuple[str, str, bool]] = []

    for path_pad in path_pads:
        path_pad = str(path_pad)
        print(f"Evaluate {path_pad}")

        cmd = ["./build/cli/OpenAllegroParser-cli", "-i", path_pad]

        found_param_set = False

        for param_set in permute_unknown_parameters():

            tmp_cmd = cmd.copy()

            if param_set.bool0:
                tmp_cmd += ["--bool0"]

            if param_set.bool1:
                tmp_cmd += ["--bool1"]

            if param_set.bool2:
                tmp_cmd += ["--bool2"]

            if param_set.int0 > 0:
                tmp_cmd += ["--int0", str(param_set.int0)]

            if param_set.numUserLayers > 0:
                tmp_cmd += ["--numUserLayers", str(param_set.numUserLayers)]

            if param_set.additionalStr2 > 0:
                tmp_cmd += ["--additionalStr2", str(param_set.additionalStr2)]

            # Shows progress
            print(".", end="", flush=True)

            proc = subprocess.run(tmp_cmd, capture_output=True)

            if proc.returncode == 0:
                found_param_set = True
                cmd = tmp_cmd.copy()
                break

        results += [(path_pad, " ".join(cmd), found_param_set)]

        if found_param_set:
            print_found(results[-1])
        else:
            print_not_found(results[-1])

    print()
    print("Summary:")

    for result in results:
        print_result(result)
