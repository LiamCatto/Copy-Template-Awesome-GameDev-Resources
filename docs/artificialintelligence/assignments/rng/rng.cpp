// add your imports here
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <unordered_map>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int LehmerRNG(unsigned int seed, int r1, int r2);
int main(){
  // code here
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;

  unsigned int currentResult, callNumber = 1, cycleCounter = 0;
  bool firstCycleFinished = false;
  std::unordered_map<int, unsigned int> lehmerStates;   // Call number, state
  std::cout << std::left;

  for(i = N; i >= 1; i--)
  {
    //Run the Lehmer number generator
    currentResult = LehmerRNG(seed, min, max);

    // Print result and call number
    std::cout << "Result: " << std::setw(4) << currentResult << "Call: " << callNumber << std::endl;

    // Measure the duration of each phase
    if (!firstCycleFinished) {
      for (int k = 0; k < lehmerStates.size(); k++)
      {
        if (lehmerStates[k] == currentResult) {
          firstCycleFinished = true;
          std::cout << std::endl << "First cycle finished."
                    << std::endl << "Cycle length: " << callNumber - k
                    << std::endl << "Transient length: " << k
                    << std::endl << std::endl;
          break;
        }
      }
    }

    // Store the result of this call
    lehmerStates[callNumber] = currentResult;

    // Prepare for next iteration
    callNumber++;
    seed++;
  }
}
//The purpose of this function is to take the number and xor shift it to output a pseudo-random number
unsigned int LehmerRNG(unsigned int seed, int r1, int r2)
{
  seed = 48271 * (seed % 0x7fffffff); // Produce a pseudo-random number
  seed = (seed % r2) + r1;            // Clamp the number between r1 and r2
  return seed;
}