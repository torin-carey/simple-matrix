#!/usr/bin/env Rscript

genmat <- function(n) {
	term <- c()
	for (i in 1:(n*n)) {
		term <- c(term, sample(-50:50, 1))
	}
	return (matrix(term, nrow=n))
}

pout <- function(n, mat) {
	str = "["
	for (i in 1:n) {
		for (j in 1:(n-1)) {
			str = paste(str, mat[i, j], ",", sep="")
		}
		if (i == n) {
			str = paste(str, mat[i, n], "]", sep="")
		} else {
			str = paste(str, mat[i, n], ";", sep="")
		}

	}
	cat(paste(str, " ", round(det(mat)), "\n", sep=""))
}

repgen <- function(n, N=100) {
	for (i in 1:N) {
		pout(n, genmat(n))
	}
}

repgen(2)
repgen(3, 75)
repgen(4, 50)
