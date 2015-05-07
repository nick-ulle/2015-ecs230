#!/usr/bin/env python3

from pathlib import Path

import pandas as pd

source_dir = Path('output/')
data_dir = Path('data/')
tex_dir = Path('tex/tables/')

def main():
    for dir in (data_dir, tex_dir):
        dir.exists() or dir.mkdir()

    for file in source_dir.glob('*.out'):
        name = file.stem.partition('.')[0]
        data = load_data(file)
        data = pd.DataFrame(data)

        if name == 'timing1':
            columns = ['Command', 'Argument', 'Cycles', 'CPU', 'Real']
        else:
            columns = ['Command', 'Argument', 'Sqrt Cycles', 'Sum Cycles'
                       , 'Sum']

        data.columns = columns

        # Write data to a CSV and LaTeX.
        csv_path = data_dir / (name + '.csv')
        data.to_csv(str(csv_path), index=False)

        tex_path = tex_dir / (name + '.tex')
        with tex_path.open('w') as out:
            data.to_latex(out, index=False)

        print(data)

def load_data(path):
    data = []
    cmd = None

    with path.open() as file:
        for line in file:
            if line.startswith('Running'):
                # Get the command used.
                cmd = line.split('`')[1].split(' ')
                cmd[1] = int(cmd[1])

            elif line.startswith('Iteration'):
                # Extract numbers from the next 3 lines.
                values = cmd.copy()
                for _ in range(3):
                    line = file.readline()
                    value = next(s for s in line.split() if is_float(s))
                    values.append(float(value))
                data.append(values)

    return data

def is_float(s):
    # Check if a string can be converted to a float.
    try:
        float(s)
        return True
    except ValueError:
        return False

if __name__ == '__main__':
    main()

