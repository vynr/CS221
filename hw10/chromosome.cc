/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  assert(is_valid());
  //trans people be like
}

bool Chromosome::is_valid() const {
  std::vector<unsigned> sorted;
  for(unsigned i = 0; i < order_.size(); i++) {
    sorted.push_back(i);
  }
  return std::is_permutation(order_.begin(), order_.end(), sorted.begin(), sorted.end());
  
}


//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome() {
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate() {
  std::uniform_int_distribution<int> dist(0,order_.size()-1);
  auto index1 = dist(generator_);
  auto index2 = dist(generator_);
  std::swap(order_[index1], order_[index2]);
  //swap em :)

  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*> Chromosome::recombine(const Chromosome* other) {
  std::uniform_int_distribution<int> dist(0,order_.size()-1);
  auto index1 = dist(generator_);
  auto index2 = dist(generator_);
  unsigned beginning;
  unsigned end;

  if(index1 > index2) {
    beginning = index2;
    end = index1;
  }
  else {
    beginning = index1;
    end = index2;
  }

  auto child1 = Chromosome::create_crossover_child(this, other, beginning, end);
  auto child2 = Chromosome::create_crossover_child(other, this, beginning, end);
  auto children = std::make_pair(child1, child2);
  
  assert(is_valid());
  assert(other->is_valid());

  return children;

  // Add your implementation here
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
        assert(j < p2->order_.size());
      }
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double Chromosome::get_fitness() const {
  double fitness = cities_ptr_->total_path_distance(order_);
  fitness += 1;
  fitness = 1/fitness;
  return fitness;
// fitness hobby lifestyle :thumbs up:
}


// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const {

  for(unsigned i = begin; i < end; i++) {
    if(order_[i] == value) {
      return true;
    }
  }
  return false;

}
