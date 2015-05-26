
# Assignment 3 README

The directory structure used for this assignment had to be flattened when 
uploading to SmartSite. The original directory structure, as assumed by the 
makefile, is:

```
./
    bin/
    output/
    scripts/
        extract.r
    src/
        error.c
        error.h
        main.c
        matrix.c
        matrix.h
    data.dat
    job.sh
    README.md
    makefile
```

With this structure in place, the `poly` program can be built using clang, 
provided BLAS and LAPACK are installed, by running `make`. Alternatively, the 
program can be built using icc on stampede by running `CC=icc make`.

The usage of `poly` is then

```
bin/poly DEGREE DATA
```

Output can be saved to a file using standard shell pipe commands such as `>`.
This output can then be scraped to produce a plot using

```
scripts/extract.r DATA FIT PLOT
```

provided R is installed.

As usual, please contact me if you would like a .tar.gz or read access to the 
assignment GitHub repository.
