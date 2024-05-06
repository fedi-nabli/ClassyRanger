#include <iostream>

#include "BaseClassifier.h"

using namespace ClassyRanger;

int main()
{
  BaseClassifier bs;
  bs.fit("../data/features.txt", "../data/labels.txt");
  bs.shape();
  bs.head();
  return 0;
}