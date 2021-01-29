//
// Created by Bean Juice on 06/01/2021.
//

#include <xtensor/xsort.hpp>
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"
#include "xtensor-blas/xlinalg.hpp"

using namespace std;

xt::xarray<double> PCA(xt::xarray<double> X, int dim = 2) {
    X = X - xt::mean(X, 0);
    xt::xarray<double> U, S, V;
    tie(U, S, V) = xt::linalg::svd(X, false, true);
    return xt::transpose(
            xt::linalg::dot(xt::view(V, xt::range(xt::placeholders::_, dim), xt::all()),
                            xt::transpose(X)));
}
