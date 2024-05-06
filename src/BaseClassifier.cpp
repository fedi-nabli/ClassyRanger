#include "BaseClassifier.h"

namespace ClassyRanger
{
  BaseClassifier::BaseClassifier()
  {
  }

  BaseClassifier::~BaseClassifier()
  {
  }

  void BaseClassifier::fit(std::string abs_filepath_to_features, std::string abs_filepath_to_labels)
  {
    CV.fit(abs_filepath_to_features, abs_filepath_to_labels);
  }

  void BaseClassifier::shape()
  {
    CV.shape();
  }

  void BaseClassifier::head()
  {
    CV.head();
  }
}