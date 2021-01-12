//
// Created by Bean Juice on 16/12/2020.
//

#ifndef SCHICTOOLS_CONTACTMAPS_H
#define SCHICTOOLS_CONTACTMAPS_H

#include <string>
#include "load_hic_file.h"
#include <vector>
#include<set>
#include <map>

using namespace std;

class scHiCs {
public:
    scHiCs(vector<string> list_of_files, string reference_genome, int resolution, bool
    adjust_resolution = true, bool sparse = false, string chromosomes = "all", string
           format = "customized", int keep_n_strata = 10, bool store_full_map = false,
           vector<string> operations = {}, int header = 0, int customized_format =
    0,
           double map_filter = 0., bool gzip = false,
           bool parallelize = false, int n_processes = 0

    );


private:
    vector<string> files, operations;
    string reference_genome, format;
    set<string> chromosomes;
    xt::xarray<int> contacts;
    xt::xarray<double> short_range, mitotic;
    map<string, xt::xarray<xt::xarray<double>>> strata;
    map<string, int> chromosome_lengths;
    int
            resolution, keep_n_strata, header, customized_format, n_processes,
            num_of_cells;
    bool
            adjust_resolution, sparse, store_full_map, gzip, parallelize;

};

#endif //SCHICTOOLS_CONTACTMAPS_H
