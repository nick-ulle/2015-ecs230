#!/usr/bin/env Rscript
# Description:
#   An R script to generate plots of the data and fitted line. Each argument is
#   a filepath.
#
# Usage:
#   ./extract.r DATA FIT PLOT

library(ggplot2, quietly=TRUE)

main = function() {
    argv = commandArgs(trailingOnly=TRUE)

    if (length(argv) != 3) {
        cat("\nUsage:\n  ./extract.r DATA FIT PLOT\n\n")
        stop("Exactly 3 arguments requred.")
    }

    b = extract_coefficients(argv[2])
    degree = length(b)

    data = read.table(argv[1], skip=1, col.names=c("x", "y"))

    # Define polynomial.
    poly = function(x) {
        len = length(x)

        p = seq.int(0, degree - 1)
        p = matrix(p, len, degree, byrow=TRUE)

        x^p %*% b
    }

    # Make plot.
    theme_set(theme_bw())
    pdf(argv[3])
    plt = ggplot(data, aes(x=x, y=y)) + geom_point() +
        stat_function(fun=poly, n=1000)
    print(plt)
    dev.off()

    invisible()
}

extract_coefficients = function(filename)
    # Extract coefficients from `poly` program output.
{
    f = file(filename, "rt")
    text = readLines(f)
    close(f)

    end = length(text)

    # Find output coefficients b.
    b_start = grep("^b =", text) + 1
    if (length(b_start) == 0) {
        stop("Input file does not contain coefficients.")
    }

    # Take first contiguous block of numbers.
    b = as.numeric(text[b_start:end])
    end = match(NA, b) - 1
    b = b[1:end]
}

main()
