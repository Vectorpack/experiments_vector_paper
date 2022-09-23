import pandas as pd
import sys

def load_dataset(filename):
    return pd.read_csv(filename, sep='\t', index_col='instance_name', encoding='utf-8')


def merge_multidim_OPT(benchmark_name):
    df = load_dataset(f"{benchmark_name}_multidim.csv")
    dfo = load_dataset(f"{benchmark_name}_base_OPT.csv")
    df["OPT"] = dfo["OPT"]
    cols = list(df.columns)
    cols.insert(1, 'OPT')
    df.to_csv(f"{benchmark_name}_multidim_OPT.csv", sep='\t', columns=cols)


def merge_BPP_OPT(benchmark_name):
    map_sheets = {
        "Falkenauer": 0,
        "Scholl": 1,
        "Waescher": 2,
        "Schwerin": 3,
        "Hard28": 4,
        "Irnich": 8
        # Difficult instances are still open
        # (or maybe not, this is not clear)
    }

    dfopt = pd.read_excel("Solutions.xlsx", sheet_name = map_sheets[benchmark_name])
    dfopt.drop(["Best UB", "Status", "Selected"], axis=1, inplace=True, errors='ignore')
    dfopt["Name"] = dfopt["Name"].apply(lambda x: x.rstrip('.txt'))
    dfopt.set_index("Name", inplace=True)
    dfopt.rename(columns={'Best LB':'OPT'}, inplace=True)
    df1 = load_dataset(f"BPPLIB_{benchmark_name}_dim1.csv")
    df = df1.merge(dfopt, left_index=True, right_index=True)
    df.index.rename("instance_name", inplace=True)
    cols = list(df.columns)
    cols.remove("OPT")
    cols.insert(1, "OPT")
    df.to_csv(f"BPPLIB_{benchmark_name}_dim1_OPT.csv", sep='\t', columns=cols)


if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print(f"Usage: {sys.argv[0]} <Panigrahy|Hetero|<BPP_benchmark_name>")
        sys.exit(1)

    benchmark_name = sys.argv[1]

    if benchmark_name == "Panigrahy" or benchmark_name == "Hetero":
        merge_multidim_OPT(benchmark_name)
    elif benchmark_name == "BPP":
        l = ["Falkenauer", "Scholl", "Waescher",
             "Schwerin", "Hard28", "Irnich"]
        for b in l:
            merge_BPP_OPT(b)
    else:
        merge_BPP_OPT(benchmark_name)
