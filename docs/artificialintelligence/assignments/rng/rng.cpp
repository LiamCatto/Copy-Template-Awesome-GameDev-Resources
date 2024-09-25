// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int LehmerRNG(unsigned int seed, int r1, int r2);
int main(){
  // code here
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;
  for(i = N; i >= 1; i--)
  {
    //Run xor shift
    seed = LehmerRNG(seed, min, max);
  }
}
//The purpose of this function is to take the number and xor shift it to output a pseudo-random number
    unsigned int LehmerRNG(unsigned int seed, int r1, int r2)
{
  seed = 48271 * (seed % 0x7fffffff); // Produce a pseudo-random number
  seed = (seed % r2) + r1;            // Clamp the number between r1 and r2
  std::cout << seed << std::endl;     // Print the result to the console
  return seed;
}
