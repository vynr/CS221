#include "cities.hh"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>

// write operator (reading in, adding to) function outside cities class
// operator wil let us overhaul >> (means read in from a stream) for our own class
// write method in cities to add extra city to vector

std::istream& operator>> (std::istream& is, Cities& cities) {
    std::string x_char;
    std::string y_char;

    while (is >> x_char) {
        // add a city to cities for each input from istream
        is >> y_char;

        int x_int = std::stoi(x_char);
        int y_int = std::stoi(y_char);

        // std::cout<<x_int<<" "<<y_int<<"\n";
        Cities::coord_t new_city(x_int, y_int);
        cities.get_new_city(new_city);
    }
    return is;
}

void Cities::get_new_city(coord_t new_city) {
    cities_list_.push_back(new_city);

}

void Cities::write_to(std::ostream& os) {
    // smile :)
    for (auto city : cities_list_) {
    os<<city.first;
    os<<"\t";
    os<<city.second;
    os<<"\n";
    }
}

std::ostream& operator<< (std::ostream& os, Cities& cities) {
    cities.write_to(os);
    return os;
}

double distance_to(Cities::coord_t city_1, Cities::coord_t city_2) {
    double x1 = city_1.first;
    double y1 = city_1.second;
    double x2 = city_2.first;
    double y2 = city_2.second;

    double len1 = x1 - x2;
    double len2 = y1 - y2;

    return std::hypot(len1, len2);
}

double Cities::total_path_distance(const permutation_t& ordering) const{
    auto prev = ordering.back();
    double total_dist = 0.0;
    for (auto curr : ordering) {
        // std::cout<<cities_list_[prev].first<<" "<<cities_list_[prev].second<<"\t"<<cities_list_[curr].first<<" "<<cities_list_[curr].second<<"\n";
        total_dist += distance_to(cities_list_[prev], cities_list_[curr]);
        prev = curr;
    }
    return total_dist;
}


Cities Cities::reorder(const permutation_t& ordering) const {
    Cities new_cities_list;
    for (auto index : ordering) {
        new_cities_list.get_new_city(cities_list_[index]);
        }
    return new_cities_list;
}

Cities::permutation_t Cities::random_permutation(size_t len) {
    Cities::permutation_t list (len);
    for (size_t counter = 0; counter < len; counter++) {
        list[counter] = counter;
    }
    std::random_shuffle(list.begin(), list.end());
    return list;
}

size_t Cities::get_size() {
    return cities_list_.size();
}

void Cities::print_shortest(permutation_t best_ordering) {
    for (auto curr : best_ordering) {
        std::cout<<cities_list_[curr].first<<" "<<cities_list_[curr].second<<"\n";
    }
}