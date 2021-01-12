//
// Created by Bean Juice on 16/12/2020.
//

#include <string>
#include "ContactMaps.h"
#include "load_hic_file.h"
#include <vector>
#include<set>
#include <map>

using namespace std;

scHiCs::scHiCs(vector<string> list_of_files, string reference_genome, int resolution,
               bool adjust_resolution, bool sparse, string chromosomes, string format,
               int keep_n_strata, bool store_full_map, vector<string> operations,
               int header, int customized_format, double map_filter, bool gzip,
               bool parallelize, int n_processes) {
    {
        this->resolution = resolution;
        tie(this->chromosomes,
            this->chromosome_lengths) = get_chromosome_lengths(reference_genome,
                                                               chromosomes,
                                                               resolution);
        this->num_of_cells = list_of_files.size();
        this->sparse = sparse;
        this->keep_n_strata = keep_n_strata;
        this->contacts = xt::zeros<int>({this->num_of_cells});
        this->short_range = xt::zeros<double>({this->num_of_cells});
        this->mitotic = xt::zeros<double>({this->num_of_cells});
        this->files = list_of_files;

        if (keep_n_strata) {
            for (string ch : this->chromosomes) {

                for (int i = 0; i < keep_n_strata; i++) {
                    this->strata[ch](i) = xt::zeros<double>({this->num_of_cells,
                                                             this->chromosome_lengths[ch] -
                                                             i});
                }

            }
        }


        cout << "Loading HiC data...";
        if (parallelize) {
            throw "Not implemented yet";
        } else {
            int idx = 0;
            for (string file : this->files) {

                for (string ch : this->chromosomes) {
                    size_t index = ch.find("ch");
                    if (index != string::npos && ch.find("chr") == string::npos) {
                        ch.replace(index, 2, "chr");
                    }
                    xt::xarray<double> mat;
                    vector<xt::xarray<double>> strata_local;
                    tie(mat, strata_local) = load_HiC(
                            file, this->chromosome_lengths,
                            format, customized_format,
                            header, ch, resolution,
                            adjust_resolution,
                            map_filter, sparse, gzip,
                            keep_n_strata, operations = operations
                    );
                    this->contacts[idx] += xt::sum(mat)() / 2 + xt::linalg::trace(mat)
                                                                        () / 2;
                    for (int i = 0; i < mat.size(); i++) {
                        this->short_range(idx) += xt::sum(xt::view(mat, i, xt::range(i,
                                                                                     i +
                                                                                     int(2000000 /
                                                                                         this->resolution))))();
                        this->mitotic(idx)+=xt::sum(xt::view(mat,i,xt::range(i+int
                        (2000000 /this->resolution),i+int(12000000/this->resolution))))();
                    }
                    if(store_full_map) throw"Not implemented yet";
                    if(keep_n_strata){
                        int strata_idx = 0;
                        for(xt::xarray<double> stratum:strata_local){
                            xt::row(this->strata[ch](strata_idx),idx) = stratum;
                        }
                    }
                }
            }

        }
    }
}