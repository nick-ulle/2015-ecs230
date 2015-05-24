#!/usr/bin/env Rscript
#
# Script for producing nice timing plots.

library(ggplot2)
library(RColorBrewer)

main = function()
{
    data = load_data()

    means = aggregate_all(data, mean)
    sds = aggregate_all(data, sd)

    write_latex(means, 'tex/figures/means.tex')
    write_latex(sds, 'tex/figures/sds.tex')

    pdf('tex/figures/gflops.pdf')
    print(plot_timing(data))
    invisible(dev.off())
}

write_latex = function(data, path)
{
    data = format(data, digits=4, nsmall=4)
    write.table(data
        , path
        , quote=FALSE
        , sep=' & '
        , eol=' \\\\ \n'
        , row.names=FALSE
    )
}

aggregate_all = function(data, fun)
{
    by = colnames(data) %in% c('n', 'method')
    aggregate(data[!by], data[by], fun)
}

load_data = function()
{
    data1 = read.csv("output/task1.csv")
    data2 = read.csv("output/task2.csv")

    data = rbind(data1, data2)

    names(data)[names(data) == 'order'] = 'method'

    levels = c('dgemm', 'jki', 'kji', 'ijk', 'jik', 'ikj', 'kij')
    data$method = factor(data$method, levels=levels)

    return(data)
}

plot_timing = function(
    data
    , y='gflops_per_sec'
    , ylab="GFlops / Second"
    , errorbars=FALSE
)
{
    groups = list(data[['method']], data[['n']])

    m = aggregate(data[[y]], groups, mean)
    s = aggregate(data[[y]], groups, sd)
    names(m)[1:2] = names(s)[1:2] = c('method', 'n')
    
    merged = merge(m, s, by=c('method', 'n'))
    names(merged)[3:4] = c('m', 's')

    # Set up linetypes and palette.
    linetype = c('solid', 'solid', 'dotted', 'solid', 'dotted', 'solid'
        , 'dotdash')

    palette = brewer.pal(3, 'Set2')[c(1, 3, 3, 2, 2, 1, 1)]

    # Plot the timings.
    pl = ggplot(
        merged
        , aes(x=n, y=m, colour=method, linetype=method)
    ) +
        geom_line() +
        geom_point() +
        labs(x="Matrix Dimension", y=ylab) +
        scale_linetype_manual('Method', values=linetype) +
        scale_color_manual('Method', values=palette)

    # Error bars are sometimes too narrow to be useful.
    if (errorbars)
        pl = pl + geom_errorbar(n, width=2 * s)

    pl
}

main()

