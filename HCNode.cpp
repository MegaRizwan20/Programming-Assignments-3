/*
 * Author: Rizwan Khan
 * CSE100 Login: cs100sgv
 * PID: A12236946
 * Email: rikhan@ucsd.edu
 */

#include "HCNode.h"
#include <stdio.h>
#include <ctype.h>

using namespace std;

/* Compare this HCNode and other for priority ordering.
 * Smaller count means higher priority. Use node symbol
 * for deterministic tiebreaking
 */
bool HCNode::operator<(const HCNode& other) {

  // If counts are different, just compare counts
  if (count != other.count) return count > other.count;


  // Counts are equal. Use Symbol value to break tie.
  // (For this to work, internal HCNodes must have symb set.)
  return symbol < other.symbol;

}

