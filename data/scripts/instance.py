'''
Small class to write vector packing instances in the VBP format
as be used with the VP Solver (https://github.com/fdabrandao/vpsolver).

For a given instance, the file contains (values are separated by a space):
- one line for the dimension d
- one line for the list of bin capacity in each of the d dimensions
- one line for the number of items
- one line per item containing 
    the list of item size in each of the d dimensions
    followed by a 1, meaning that there is one item of that type
'''

class Instance:
    def __init__(self, d, items, h):
        self.dim = d
        self.n = len(items)
        self.item_list = items
        if isinstance(h, list):
            if len(h) == d:
                self.bin_cap = h
            else:
                print(f"ERROR: bin capacity should be a single value or a list of size {d}")
        else:
            # Only one bin capacity given
            self.bin_cap = [h]*d

    def write_to_file(self, filename):
        with open(filename, 'w') as f:
            f.write(f"{self.dim}\n{' '.join(map(str, self.bin_cap))}\n{self.n}\n")
            for item_sizes in self.item_list:
                f.write(f"{' '.join(map(str,item_sizes))} 1\n")
