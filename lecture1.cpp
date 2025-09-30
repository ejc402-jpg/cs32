#include <iostream> 
/*
Algorithm: set of instructions/steps that solves a particular problem
  ex. Word Guessing Game (assuming lexicographically sorted dictionary)
    1. Linear Search 
      O(n), depends a lot on luck --> average 50000 words in a 100000 dictionary
    2. Binary Search 
      O(log n), a lot more efficient --> average 17 words in a 100000 dictionary
Data Structure: a set of variable(s) that an algorithm uses to solve a problem
  ex. consider a data structure efficiently store millions of DNA sequences so they can be searched, each with ten bases (i.e. AGTCGATCGA)
    1. sorted array of strings
      drawbacks: array cannot be dynamically resized, adding or removing elements is extremely costly
    2. Trie data structure (retrive) 
      acts like a balance mobile, with branches from each base to next
      start with a bar with the four letters, add a hook to represent the first letter and add another bar as you go down
      an existing DNA sequence will have at most ten levels
Interface: a collection of simple functions, allowing any programmer to use your code
  ex.  */
    int main(){
      addSequence("TAGCTGATTA");
      if(findSequence("GGATGCTAGG") == true){
        std::cout << "This is a known DNA snippet!\n";
      } 
    }
/*
Abstract Data Types (ADT): a coordinated group of data structures, algorithms, and interface functions
  the data structures and algorithms are secret
  the ADT provides an interface (simple set of functions) to enable the rest of the program to use it 
  typically we build programs from collections of ADT's to solve different sub-problems
  in C++, we use classes
  ex. */
    class DNADatabase{
      public: 
        // interface functions go here
      private: 
        // secret algorithms go here
        // secret data structures go here
    };
    int main(){
      DNADatabase d; 

      d.addSequence("acgtagtcgat");
      d.addSequence("acgtagtcgat");

      std::string dna_seq;

      std::cout << "Enter a 10-base sequence: ";
      std::cin >> dna_seq; 
      if(d.findSequence(dna_seq) == true){
        std::cout << "This bacteria is known!";
      }
    }
/*
Object Oriented Programming: a programming model based on the ADT concept 
  programs are constructured from multiple self-contained classes that each hold data structures and algorithms, accessed using sets of interface functions
  classes interact with each other by only using publis interface functions, everything else if private 
  
*/

