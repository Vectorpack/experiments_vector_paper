import sys
from random import randint
from math import floor
from itertools import product

from instance import Instance

from pathlib import Path
# BASE_PATH points to the "data" folder
BASE_PATH = Path(__file__).resolve().parent.parent
INSTANCES_PATH = BASE_PATH / "Triplet_instances_multidim"

'''
Generation script for triplet instances of Vector Packing Problem.
This is an extension of the generation method from
"A Hybrid Grouping Genetic Algorithm for Bin Packing", Falkenauer, 1996.

Another class of triplets was defined by Caprara and Toth, 2001,
"Lower bounds and algorithms for the 2-dimensional vector packing problem".

Another class of triplets is newly defined by Mommessin et al. 2022.
'''

def generate_Falkenauer_triplet_sizes():
    a = randint(38, 49)
    s = 100 - a
    b = randint(25, floor(s/2.0))
    c = 100 - a - b
    return (a,b,c)

def generate_Caprara_triplet_sizes():
    a = randint(25, 50)
    b = randint(25, 50)
    c = 100 - a - b
    return (a,b,c)

def generate_Mommessin_triplet_sizes():
    a = randint(1,50)
    b = randint(1,50)
    c = 100 - a - b
    return (a,b,c)


def generate_triplets(n, d, triplet_class):
    nb_triplets = int(n/3)
    list_items = []

    for tt in range(nb_triplets):
        list_triplet = []
        for dd in range(d):
            if triplet_class == "Falkenauer":
                tri = generate_Falkenauer_triplet_sizes()
            elif triplet_class == "Caprara":
                tri = generate_Caprara_triplet_sizes()
            elif triplet_class == "Mommessin":
                tri = generate_Mommessin_triplet_sizes()

            list_triplet.append(tri)
        (a,b,c) = list(zip(*list_triplet))
        list_items.append(a)
        list_items.append(b)
        list_items.append(c)

    return Instance(d, list_items, 100)


def main(argv):
    # [1000, 2500, 5000] Only for large instances, with d in [3, 5, 10] as well
    list_n = [60, 120, 249, 501]
    list_d = [3, 5, 10]

    nb_instances = 10

    classes = ["Falkenauer", "Caprara", "Mommessin"]

    for triplet_class in classes :
        out_path = INSTANCES_PATH / triplet_class
        out_path.mkdir(parents=True, exist_ok=True)
        
        for n, d, i in product(list_n, list_d, range(nb_instances)):
            inst = generate_triplets(n, d, triplet_class)
            outfile = out_path / f"class{triplet_class[0]}_{n}_{d}_{i}.vbp"
            inst.write_to_file(outfile)

if __name__ == '__main__':
    INSTANCES_PATH.mkdir(parents=True, exist_ok=True)
    main(sys.argv)
