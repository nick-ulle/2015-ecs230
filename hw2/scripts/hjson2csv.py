#!/usr/bin/env python3
# hjson2csv.py
#
# A simple HJSON to CSV converter.

import sys
import hjson
import itertools
import pandas as pd

def read_hjson(path):
    with open(path) as file:
        data = hjson.load(file)

    return data

if __name__ == '__main__':
    try:
        _, in_path, out_path = sys.argv
    except ValueError:
        print("Usage:")
        print("    hjson2csv.py source dest")
        sys.exit(1)

    data = read_hjson(in_path)

    # Chain the lists together.
    data = itertools.chain.from_iterable(data)

    data = pd.DataFrame.from_records(data)

    data.to_csv(out_path, index=False)
