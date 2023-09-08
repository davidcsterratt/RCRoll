##' @title Rolling miniumum
##' @param x an object (representing a series of observations).
##' @param k integer width of the rolling window.
##' @param fill a three-component vector or list (recycled otherwise)
##'   providing filling values at the left/within/to the right of the
##'   data range. See the ‘fill’ argument of na.fill for details.
##' @param align character specifying whether the index of the result
##'   should be left- or right-aligned or centered (default) compared
##'   to the rolling window of observations.
##' @param ... Further arguments passed to methods.
##' @return An object of the same class as ‘x’ with the rolling min.
##' @author David C Sterratt
##' @useDynLib RCRoll
##' @export
rollmin <- function (x, k, fill = if (na.pad) NA, align = c("center",
    "left", "right"), ...)
{
  out <- .Call("C_rollmin", as.double(x), as.integer(k), PACKAGE="RCRoll")
  return(out)
}
