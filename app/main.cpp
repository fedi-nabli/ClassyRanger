#include <iostream>

#include "classifiers/SimpleClassifier.h"

using namespace ClassyRanger;

int main()
{
  SimpleClassifier sc("positive", "negative");
  sc.fit("../data/features.txt", "../data/labels.txt");
  sc.shape();
  sc.head();

  sc.analyze("Amazing. Loved this place. I want to come again");
  return 0;
}