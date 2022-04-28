/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>


// Representation of an ordering of cities
class Cities {
 public:

  Cities() = default;
  ~Cities() = default;
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  // An ordering of cities. Each value represents a unique index
  // into the current city ordering in some container.
  using permutation_t = std::vector<size_t>;

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  // fetches new city coords from istream and adds them to list of cities
  void get_new_city(coord_t new_city);

  // output a list of cities
  void write_to(std::ostream& os);

  permutation_t random_permutation(size_t len);

  size_t get_size();

  void print_shortest(permutation_t best_ordering);

  friend std::istream& operator>> (std::istream& is, Cities& cities);
  friend std::ostream& operator<< (std::ostream& os, Cities& cities);

 private:
  std::vector<coord_t> cities_list_;

};
