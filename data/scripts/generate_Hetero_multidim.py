import sys
import numpy as np
from random import choices, shuffle
from scipy.stats import norm
from math import floor, sqrt
from itertools import product

from instance import Instance

from pathlib import Path
# BASE_PATH points to the "data" folder
BASE_PATH = Path(__file__).resolve().parent.parent
#INSTANCES_PATH = BASE_PATH / "Hetero_instances_multidim"
INSTANCES_PATH = BASE_PATH / "Hetero_instances_large"

'''
Generation script for instances of Vector Packing Problem.
This is a new set of instances to explore more complex distributions.
'''


def generate_instance_class1(n, d):
    ''' First class generates items that are large in
    one dimension and small in other dimensions.
    Each dimension has n/d large items
    '''
    nb_items = int(floor(n/d))
    pad_items = int(n%d)
    list_items = []

    large_range = range(50, 101)
    small_range = range(0, 26)

    for i in range(1,d+1):
        if (i == d):
            nb_items += pad_items

        # Stores the list of item size in each dimension
        list_dims = [] # Must have d elements at the end
        for j in range(1,i):
            list_dims.append(choices(small_range, k=nb_items))
        list_dims.append(choices(large_range, k=nb_items))
        for j in range(i+1, d+1):
            list_dims.append(choices(small_range, k=nb_items))

        list_items.extend(list(zip(*list_dims)))

    return Instance(d, list_items, 100)


def generate_class1(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class1"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_class1(n, d)
        outfile = output_path / f"class1_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)



def pick_sizes_gaussian(n, mu, sigma):
    sizes = np.rint(norm.rvs(loc=mu, scale=sigma, size=n)).astype('int')
    for i in range(n):
        size = sizes[i]
        while (size < 0) or (size > 100):
            size = int(round(norm.rvs(loc=mu, scale=sigma)))
        sizes[i] = size
    return sizes

'''def pick_single_gaussian(mu, sigma):
    size = -1
    while (size < 0) or (size > 100):
        size = int(round(norm.rvs(loc=mu, scale=sigma)))
    return size'''

def generate_instance_gaussian(n, d, mu, sigma):
    list_dims = []
    for i in range(d):
        list_dims.append(pick_sizes_gaussian(n, mu, sigma))

    return Instance(d, list(zip(*list_dims)), 100)


'''
Classes 2 and 3 generate similar small items, with size picked
by gaussian distribution with different mean/sigma parameters.
'''
def generate_class2(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class2"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_gaussian(n, d, 20, 10)
        outfile = output_path / f"class2_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)


def generate_class3(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class3"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_instance_gaussian(n, d, 30, 15)
        outfile = output_path / f"class3_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)




def generate_class_bimodal(n, d, ratio_large, mean_large, mean_small, sigma):
    list_dims = []
    for i in range(d):
        # Number of items with large size in that dimension
        nb_large = int(round(norm.rvs(loc=int(n*ratio_large), scale=sqrt(n/4))))
        if (nb_large < 0):
            nb_large = 0
        if (nb_large > n):
            nb_large = n
        nb_small = n - nb_large

        sizes = list(pick_sizes_gaussian(nb_large, mean_large, sigma))
        sizes.extend(pick_sizes_gaussian(nb_small, mean_small, sigma))
        shuffle(sizes)
        list_dims.append(sizes)
    return Instance(d, list(zip(*list_dims)), 100)


'''
Classes 4 5 6 generate items with a sort of
bimodal gaussian distribution sizes
'''
def generate_class4(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class4"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_class_bimodal(n, d, 0.1, 70, 30, 15)
        outfile = output_path / f"class4_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)


def generate_class5(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class5"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_class_bimodal(n, d, 0.1, 80, 20, 10)
        outfile = output_path / f"class5_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)


def generate_class6(n, d, nb_instances):
    output_path = INSTANCES_PATH / "class6"
    output_path.mkdir(parents=True, exist_ok=True)

    for i in range(nb_instances):
        inst = generate_class_bimodal(n, d, 0.1, 70, 15, 10)
        outfile = output_path / f"class6_{n}_{d}_{i}.vbp"
        inst.write_to_file(outfile)




def main(argv):
    list_n = [2000, 5000]
    list_d = [3, 5, 10]

    nb_instances = 5 #10 # Nb of instances per configuration

    # Generate class 1
    for n, d in product(list_n, list_d):
        generate_class1(n, d, nb_instances)

    # Generate class 2
    for n, d in product(list_n, list_d):
        generate_class2(n, d, nb_instances)

    # Generate class 3
    for n, d in product(list_n, list_d):
        generate_class3(n, d, nb_instances)

    # Generate class 4
    for n, d in product(list_n, list_d):
        generate_class4(n, d, nb_instances)

    # Generate class 5
    for n, d in product(list_n, list_d):
        generate_class5(n, d, nb_instances)

    # Generate class 6
    for n, d in product(list_n, list_d):
        generate_class6(n, d, nb_instances)

if __name__ == '__main__':
    main(sys.argv)
