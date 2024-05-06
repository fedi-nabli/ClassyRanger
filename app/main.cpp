#include <iostream>

#include "CountVectorizer.h"

using namespace ClassyRanger;

int main()
{
  CountVectorizer cv;
  cv.fit("../data/features.txt", "../data/labels.txt");
  cv.shape();
  cv.head();
  return 0;
}