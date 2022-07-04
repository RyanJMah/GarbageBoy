import os
import sys
import signal
import subprocess
from termcolor import cprint

EXECUTABLE_PATH = "./build/garbageboy"

TESTS_BASE_PATH = "./tests/gb-test-roms/cpu_instrs/individual"
TEST_ROMS = [
    os.path.join(TESTS_BASE_PATH, "01-special.gb"),
    os.path.join(TESTS_BASE_PATH, "02-interrupts.gb"),
    os.path.join(TESTS_BASE_PATH, "03-op sp,hl.gb"),
    os.path.join(TESTS_BASE_PATH, "04-op r,imm.gb"),
    os.path.join(TESTS_BASE_PATH, "05-op rp.gb"),
    os.path.join(TESTS_BASE_PATH, "06-ld r,r.gb"),
    os.path.join(TESTS_BASE_PATH, "07-jr,jp,call,ret,rst.gb"),
    os.path.join(TESTS_BASE_PATH, "08-misc instrs.gb"),
    os.path.join(TESTS_BASE_PATH, "09-op r,r.gb"),
    os.path.join(TESTS_BASE_PATH, "10-bit ops.gb"),
    os.path.join(TESTS_BASE_PATH, "11-op a,(hl).gb"),
]

def run_test(rom):
    cmd = [EXECUTABLE_PATH, "--headless", "--rom_path", rom]
    with subprocess.Popen(cmd, stdout=subprocess.PIPE, bufsize=0) as p:
        char = p.stdout.read(1)
        output = char.decode()
        while char != b'':
            output += char.decode()
            char = p.stdout.read(1)

            if "Passed" in output:
                p.kill()
                return True

            if "Failed" in output:
                p.kill()
                return False

def main():
    for rom in TEST_ROMS:
        test_name = os.path.basename(rom)
        passed = run_test(rom)
        if passed:
            cprint(f"{test_name}: PASSED!!!", "green")
        else:
            cprint(f"{test_name}: FAILED!!!", "red")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(1)

