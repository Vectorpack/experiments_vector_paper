import sys
#import os

from instance import Instance
from pathlib import Path
# BASE_PATH points to the "data" folder
BASE_PATH = Path(__file__).resolve().parent.parent
INPUT_PATH = BASE_PATH / "1dim/BPPLIB/original_benchmarks"
OUTPUT_PATH = BASE_PATH / "1dim/BPPLIB"
SIZE_PARENTS = len(INPUT_PATH.parts)

'''
Formating of the instances provided in the BPPLIB into the VBP format
used by the VPSolver.
BPPPLIB: http://or.dei.unibo.it/library/bpplib
VPSolver: https://github.com/fdabrandao/vpsolver
'''

def mytrim(line):
    return line.rstrip('\n').split(' ')

def load_instance(infile):
    with open(infile, 'r') as f:
        n = int(f.readline())
        C = int(f.readline())

        item_list = []
        for _ in range(n):
            item_list.append([int(f.readline())])

    return Instance(1, item_list, C)


def get_list_files(base_path, dir_name):
    path = base_path / dir_name
    list_files = []
    for d in path.iterdir():
        if d.is_dir():
            sublist = get_list_files(base_path, d.relative_to(base_path))
            list_files.extend(sublist)
        else:
            list_files.append(d.relative_to(base_path))

    list_files.sort()
    return list_files



def main(argv):
    benchmark_list = [
        "Difficult_Instances",
        "Falkenauer",
        "Hard28",
        "Irnich_BPP",
        "Scholl",
        "Schwerin",
        "Waescher"
    ]

    dict_instances = {}
    for s in benchmark_list:
        l = get_list_files(INPUT_PATH, s)
        dict_instances[s] = l

    for k,l in dict_instances.items():
        big_s = ""

        for infile in l:
            # Convert each instance into VBP format
            outf = infile.with_suffix(".vbp")
            outfile = OUTPUT_PATH / outf
            inst_name = infile.stem

            inst = load_instance(INPUT_PATH / infile)
            outfile.parent.mkdir(parents=True, exist_ok=True)
            inst.write_to_file(str(outfile))

            big_s += str(inst_name) + " " + str(outf) + "\n"

        # Write the list of instances for each benchmark
        list_file = OUTPUT_PATH / (k + "_list.txt")
        with open(list_file, 'w') as f:
            f.write(big_s)
            f.write('\n')




if __name__ == '__main__':
    main(sys.argv)
