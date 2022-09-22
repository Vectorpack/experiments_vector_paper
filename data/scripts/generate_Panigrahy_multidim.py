import sys
from random import random, randint, choices, randrange
from math import floor

from instance import Instance

from pathlib import Path
# BASE_PATH points to the "data" folder
BASE_PATH = Path(__file__).resolve().parent.parent
#INSTANCES_PATH = BASE_PATH / "Panigrahy_instances_multidim"
INSTANCES_PATH = BASE_PATH / "Panigrahy_instances_TEST"

'''
Generation script for instances of Vector Packing Problem.
Instances are stored in files with the VBP format to be used by VP Solver
(https://github.com/fdabrandao/vpsolver)

These instances are generated randomly in 10 different classes in the same process
as described in the paper "Heuristics for Vector Bin Packing", by
Panigrahy et al., 2011.
'''

##########################################################
def generate_instance_ab(n, d, h, alpha, beta):
    # h is the bin capacity
    list_items = []
    range_size = range(alpha, beta+1)
    for i in range(n):
        sizes = choices(range_size, k=d)
        list_items.append(sizes)
    return Instance(d, list_items, h)

def generate_class(n, d, nb_instances, class_n, class_d):
    output_path = INSTANCES_PATH / class_n
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_ab(n, d, class_d["h"],
                                    class_d["alpha"], class_d["beta"])
        outfile = output_path / f"{class_n}_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)



##########################################################
def generate_instance_class7(n, d):
    range_size = range(20, 100)
    nb_full_pairs = int(floor(d/2))
    list_dims = []
    for i in range(nb_full_pairs):
        v1 = choices(range_size, k=n)
        v2 = list(map(lambda x: randint(x-10, x+10), v1))
        list_dims.append(v1)
        list_dims.append(v2)
    if (d%2) == 1:
        # Odd number of dimensions, need one more size
        list_dims.append(choices(range_size, k=n))
    list_items = list(zip(*list_dims))
    return Instance(d, list_items, 150)

def generate_class7(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class7"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_class7(n, d)
        outfile = output_path / f"class7_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)


##########################################################
def generate_instance_class8(n, d):
    range_size = range(20, 100)
    nb_full_pairs = int(floor(d/2))
    list_dims = []
    for i in range(nb_full_pairs):
        v1 = choices(range_size, k=n)
        v2 = list(map(lambda x: randint(110-x, 130-x), v1))
        list_dims.append(v1)
        list_dims.append(v2)
    if (d%2) == 1:
        # Odd number of dimensions, need one more size
        list_dims.append(choices(range_size, k=n))
    list_items = list(zip(*list_dims))
    return Instance(d, list_items, 150)

def generate_class8(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class8"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_class8(n, d)
        outfile = output_path / f"class8_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)


##########################################################
def generate_instance_class9(n, d):
    bin_capacity = 100
    list_items = []
    i = 0
    while i <= n:
        # Generate a list of sizes for the item
        list_bins = [0] * d
        for _ in range(2*d):
            x = randrange(d)
            list_bins[x] = list_bins[x] + 1

        s = randint(10, 40)
        sizes = [s*x+randint(0,1) for x in list_bins]
        if max(sizes) <= bin_capacity:
            # Keep this item
            list_items.append(sizes)
            i+=1

    return Instance(d, list_items, bin_capacity)

def generate_class9(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class9"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_class9(n, d)
        outfile = output_path / f"class9_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)



def main(argv):
    # [1000, 2500, 5000] Only for large instances, with d in [3, 5, 10] as well
    list_n = [2000, 5000]
    list_d = [3, 5, 10]

    # h is the bin capacity
    dict_classes = {
        "class1": {"h": 1000, "alpha": 100, "beta": 400},
        "class2": {"h": 1000, "alpha": 1, "beta": 1000},
        "class3": {"h": 1000, "alpha": 200, "beta": 800},
        "class4": {"h": 1000, "alpha": 50, "beta": 200},
        "class5": {"h": 1000, "alpha": 25, "beta": 100},
        "class6": {"h": 150, "alpha": 20, "beta": 100}
    }

    nb_instances = 5 # Nb of instances per configuration

    # Generate 6 first classes
    for class_i in range(1,7):
        for n in list_n:
            for d in list_d:
                class_n = f"class{class_i}"
                generate_class(n, d, nb_instances, class_n, dict_classes[class_n])
    #

    # Generate class 7
    for n in list_n:
        for d in list_d:
            generate_class7(n, d, nb_instances)
    #

    # Generate class 8
    for n in list_n:
        for d in list_d:
            generate_class8(n, d, nb_instances)
    #

    # Generate class 9
    for n in list_n:
        for d in list_d:
            generate_class9(n, d, nb_instances)
    #

if __name__ == '__main__':
    main(sys.argv)
