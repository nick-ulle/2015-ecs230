
---
title: ECS 230 Assignment 1
author: Nick Ulle
---

1.  Throughout this exercise, we use the induced norm with $p = \infty$.

    Since the relative error in $b$ is bounded by $\epsilon$, the theorem given 
    in gives the bound
    $$
    \frac{
        \norm{\delta x}
    }{
        \norm{x}
    }
    \leq
    \cond(A) \, \frac{
        \norm{\delta b}
    }{
        \norm{b}
    }
    <
    \cond(A) \, \epsilon
    $$
    on the relative error in $x$.
    We can compute the condition number using the formula $\cond(A) = \norm{A} 
    \cdot \norm{A^{-1}}$. First, using the fact that 
    $a(a - 2) - (a - 1)^2 = -1$,
    $$
    A^{-1}
    =
    \frac{
        1
    }{
        a(a - 2) - (a - 1)^2
    }
    \begin{bmatrix}
    a - 2 & 1 - a \\
    1 - a & a \\
    \end{bmatrix}
    =
    \begin{bmatrix}
    2 - a & a - 1 \\
    a - 1 & -a \\
    \end{bmatrix}.
    $$
    Then by definition and since $a > 2$,
    $$
    \begin{aligned}
    \norm{A}
    &=
    (a + a - 1) \vee (a - 1 + a - 2)
    \\ &=
    2a - 1.
    \end{aligned}
    $$
    Similarly,
    $$
    \begin{aligned}
    \norm{A^{-1}}
    &=
    (\abs{2 - a} + a - 1) \vee (a - 1 + \abs{-a})
    \\ &=
    (a - 2 + a - 1) \vee (a - 1 + a)
    \\ &=
    2a - 1.
    \end{aligned}
    $$
    Therefore the relative error in $x$ is bounded by
    $$
    \frac{
        \norm{\delta x}
    }{
        \norm{x}
    }
    <
    (2a - 1)^2 \epsilon.
    $$

2.  Tables of output from the timing programs are included at the end of this
    report.

    a)  The `clock()` function appears to have centisecond resolution on
        Stampede's hardware, which is quite bad. Moreover, its timings vary by
        a whole centisecond for the 5,000,000 and 10,000,000 runs. Based on
        these results, `clock()` is not a reliable timer.

        On the other hand, `gettimeofday()` appears to have microsecond
        resolution on Stampede's hardware. Its timings exhibit only small
        variations, regardless of the job size. The documentation warns that
        the resolution varies across hardware, but as long as we're only
        interested in timing operations on Stampede, this seems like a very
        good choice of timer.

        The mean time as measured by `gettimeofday()` for the 5,000,000 square
        root runs is $0.0403893$ seconds. These runs were used because they had
        the lowest variance. Based on this, it takes approximately $8.078
        \times 10^{-9}$ seconds to calculate a square root. The other runs give
        a similar figure.

    b)  The `rdtsc` assembly instruction returns the number of CPU cycles since
        the machine was booted. Since the nodes of Stampede have a clock rate
        of 2.7 GHz, we can use the number of CPU cycles to estimate the elapsed
        time by multiplying by $2.7 \times 10^{-9}$ seconds per cycle. This
        conversion factor suggests that the `rdtsc` instruction has nanosecond
        resolution. In general, the estimated times for all runs are similar to
        those produced by `gettimeofday()`.

        Based on the mean cycle counts for the summation, it takes
        approximately $21.8$ cycles (or 22 cycles) to compute a square root.
        The data shows that computing $\sqrt{10}$ alone takes more cycles than
        this, which can be attributed to one-time operations performed before
        and after the computation, such as memory manipulation. Presumably
        these are amortized in the summation by keeping the total in a register
        until finished. Converting this to seconds gives $8.076 \times 10^{-9}$
        seconds, which is very close to our previous estimate.

    c)  Allowing the compiler to optimize the code speeds the computation up by
        about 3 cycles per square root. This has a small but noticeable impact
        on the timings. More dramatically, the compiler notices that the value
        of $\sqrt{10}$ is constant, and folds the value into the code, so it
        uses 0 cycles at runtime. The conclusion we can draw here is that
        compiler optimizations should be left off when trying to get an
        accurate measurement of CPU cycles for a particular computation.

\begin{table}
\centering
\input{tables/timing1.tex}
\caption{Results for \texttt{timing1}.}
\end{table}

\begin{table}
\centering
\input{tables/timing2.tex}
\caption{Results for \texttt{timing2}, assuming a 2.7 GHz clock rate.}
\end{table}
