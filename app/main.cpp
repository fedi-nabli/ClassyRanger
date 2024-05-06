#include <iostream>

#include "classifiers/NaiveBayesClassifier.h"
#include "classifiers/SimpleClassifier.h"

using namespace ClassyRanger;

int main()
{
  SimpleClassifier sc("positive", "negative");
  sc.fit("../data/features.txt", "../data/labels.txt");
  sc.shape();
  sc.head();

  sc.analyze("I love this pet");
  return 0;
}