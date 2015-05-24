
---
title: ECS 230 Assignment 2
author: Nick Ulle
---
\captionsetup{width=0.75\textwidth}

# Naive Multiplication

Measurements for the naive matrix multiplication program were replicated 10
times for each combination of loop ordering and dimension
$n \in \{100, 200, 500, 1000, 2000\}$.
For $n = 5000$, only five measurements were made for order 'ijk' and three for
all other orders, because these alone took more than eight hours to complete.
Means and standard deviations for the resulting measurements are shown in 
Table 1 and Table 2, respectively.

According to the TACC Stampede User Guide, each Intel Xeon E5-2680 2.7 GHz
processor supports 8 floating-point operations per clock cycle. It follows that
the nominal theoretical peak performance is 21.6 GFlops. On average, the naive
matrix multiplication program achieved only 0.06--4.32 GFlops, which is very
poor in comparison. In fact, this is only 0.2--20\% of the peak performance.

Naive matrix multiplication worked best with loop orders 'jki' and 'kji'. Both
of these have the row index 'i' increasing the fastest. Consequently, columns
from $C$ and $A$ can be cached (good spatial locality), while the entry from
$B$ is constant over the innermost loop. On the other hand, the worst loop
orders had the column index 'j' increasing the fastest---which reflects the
fact that this arrangement is the least amenable to caching.

\begin{figure}[h]
    \centering
    \includegraphics[width=0.6\textwidth]{figures/gflops}
    \caption{
    Performance for matrix multiplication. Standard deviations are not shown 
    because they were several orders of magnitude smaller than the scale.
    }
\end{figure}

# DGEMM

Measurements for the DGEMM routine were replicated 10 times for all choices of
dimension. The DGEMM routine is clearly well-optimized, as its mean performance
ranged from 16.5--23.2 GFlops, with better performance for larger matrices.
This is somewhat surprising because the nominal theoretical peak is only 21.5
GFlops, but can be explained by the Intel Turbo Boost feature on Stampede's
Xeon processors. Turbo Boost allows the processors to gradually increase their
clock speed as high as 3.5 GHz when under load, provided electrical and
thermal constraints are met. For a 3.5 GHz processor, peak performance is 28
GFlops, and we see that all of the measurements were well within this maximum.

\begin{table}[p]
    \centering
    \begin{tabular}{rrrrrr}
    \toprule
    \input{figures/means}
    \bottomrule
    \end{tabular}
    \caption{Means for matrix multiplication measurements.}
    \label{tab:means}
\end{table}

\begin{table}[p]
    \centering
    \begin{tabular}{rrrrrr}
    \toprule
    \input{figures/sds}
    \bottomrule
    \end{tabular}
    \caption{Standard deviations for matrix multiplication measurements.}
    \label{tab:sds}
\end{table}
