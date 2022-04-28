#include "cities.hh"
#include <limits>
#include <iomanip>
#include <fstream>

int main(int argc, char* argv[]) {
    //input cities file into a new cities object using ifstream
    if(argc != 2) {
        std::cout<<"damn";
        //if I don't do this I get a warning lol
    }
    Cities cities;
    std::ifstream is(argv[1], std::ifstream::in);
    is>>cities;

    //make a variable shortest_path that stores the shortest path found
    //hopefully no paths are higher than infinity :)
    double shortest_path = std::numeric_limits<double>::infinity();
    size_t size = cities.get_size();

    //make a while loop
    //while counter under 1 million
    //randomly scramble the cities using reorder method
    //if route shorter than current shortest_path, replace
    //print to terminal the current counter value, "\t", route distance
    //exit loop and return 0
    //smile :)

    Cities::permutation_t best_ordering;

    for (int counter = 0; counter < 1000000; counter++) {
        //rearrange cities
        Cities::permutation_t shuffle = cities.random_permutation(size);
        double dist = cities.total_path_distance(shuffle);
        //check if we've found a shorter path
        if (dist < shortest_path) {
            best_ordering = shuffle;
            cities.reorder(shuffle);
            shortest_path = dist;
            //round shortest_path to one decimal
            //please
            std::cout << std::fixed << std::showpoint;
            std::cout << std::setprecision(1); 
            std::cout << counter << "\t" << shortest_path << "\n";
            
        }
    }
    // cities.print_shortest(best_ordering);

return 0;
}