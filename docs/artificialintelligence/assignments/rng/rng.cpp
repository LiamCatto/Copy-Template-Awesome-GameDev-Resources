// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <cstdint>
#include <iomanip>
const std::string TEST_FOLDER = "\\tests\\";
unsigned int LehmerRNG(unsigned int seed, int r1, int r2);
int main(){
  // code here
  unsigned int seed, N, min, max;
  std::cin >> seed >> N >> min >> max;
  unsigned int i;

  unsigned int firstResult, currentResult, counter = 1, cycleCounter = 1;
  bool transientFinished = false;
  std::cout << std::left;

  for(i = N; i >= 1; i--)
  {
    //Run the Lehmer number generator
    currentResult = LehmerRNG(seed, min, max);

    // Print result and call number
    std::cout << "Result: " << std::setw(4) << currentResult << "Call: " << counter << std::endl;

    // Determine the length of each phase
    if (i == N) firstResult = currentResult;  // Store the initial result
    if (transientFinished)  // Begin recording the length of the cycle after the transient phase
    {
      cycleCounter++;
      if (currentResult == firstResult)
      {
        std::cout << "Cycle finished. Cycle length: " << cycleCounter - 1 << std::endl;
        return 0;
      }
    }
    if (currentResult == firstResult && i < N
        && !transientFinished)  // Measure the length of the transient phase
    {
      std::cout << "Transient phase finished. Transient length: " << counter - 1 << std::endl;
      transientFinished = true;
    }

    counter++;
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

// Note for me (Liam):
// I've been testing this code with the following input: 1 1000 0 99
// This leads to the following values:
// Initial result: 58
// Transient phase length: 99
// First reappearance of initial result: Call 100
// Cycle length: 99
// Second reappearance of initial result: Call 199

// Note for me (Liam):
// Not sure if I got the transient phase correct. Currently, I have the transient phase declared as
// complete once it loops for the first time. This understanding of the transient phase essentially
// makes it equivalent to the first cycle. However, it might actually be the series of results prior
// to when the program starts repeating. A possible distinction between the two methods might be
// that I have to wait until I see the code repeat AFTER the first reappearance of the first result.
// I could then measure the transient by counting the calls after the first repetition of the
// initial result and subtracting the current call count by that number. That number would also be
// the same as the cycle length. All in all, these two methods should result in the same lengths of
// the transient phase and the cycle (at least in this case since the transient appears to be the
// same series of results as the cycle).