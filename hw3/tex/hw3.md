
---
title: ECS 230 Assignment 3
author: Nick Ulle
---

The program `poly`, written in C, was used to fit polynomials to the provided
data, for degrees 3 through 10. Computed coefficients were screen-scraped from
the output of `poly` using an R script. The source code for both is included
with this report.

Fitted polynomials of degree 5 and degree 9 are shown in \autoref{fig:deg5} and
\autoref{fig:deg9}, respectively. Both are reasonably close to the data
points, and so are those for all other degrees below 10 (not shown). This
suggests the `poly` program computes the least-squares coefficients correctly.

On the other hand, the high-degree polynomials are not a "good" fit to the data
because they interpolate as many data points as possible, at the cost of
fitting the overall trend. In other words, they overfit---the signal in the
data gets obscured by the noise. The degree 9 polynomial is an extreme case of
this. Each data point is interpolated, but the polynomial has extreme
fluctuations. Unless the data has some context justifying a high-degree
polynomial fit, the best fits here are the simplest: linear, quadratic, or
cubic.

For degree 10 and higher, the model is underdetermined, so the matrix 
$A = X\T X$ doesn't have full rank. Thus $A$ is not positive definite, and
doesn't have a Cholesky decomposition. The LAPACK library's `dpotrf()` function
reports this through a status code, but runs the decomposition algorithm
anyways. Somewhat interesting is that using this "decomposition" as if it were
correct yields the same polynomial as for degree 9.

\begin{figure}
    \centering
    \includegraphics[width=0.65\textwidth]{figures/fit5}
    \caption{Fitted polynomial for degree 5.}
    \label{fig:deg5}
\end{figure}

\begin{figure}
    \centering
    \includegraphics[width=0.65\textwidth]{figures/fit9}
    \caption{Fitted polynomial for degree 9.}
    \label{fig:deg9}
\end{figure}

\clearpage
\begin{listing}[p]
    \centering
    \inputminted[linenos=false, frame=none, xleftmargin=0pt,
        fontsize=\footnotesize]{text}{../output/fit5.out}
    \caption{Output for degree 5.}
\end{listing}

\begin{listing}[p]
    \centering
    \inputminted[linenos=false, frame=none, xleftmargin=0pt,
        fontsize=\footnotesize]{text}{../output/fit9.out}
    \caption{Output for degree 9.}
\end{listing}

