#pragma once

#include "CountVectorizer.h"

#include <iostream>

namespace ClassyRanger
{
  class BaseClassifier
  {
    public:
      BaseClassifier();
      ~BaseClassifier();

      void fit(std::string abs_filepath_to_features, std::string abs_filepath_to_labels);
      void shape();
      void head();

      CountVectorizer CV;

    public:
      inline std::string get_true_label() { return m_TrueLabelMeaning; }
      inline std::string get_false_label() { return m_FalseLabelMeaning; }
    
    protected:
      std::string m_TrueLabelMeaning;
      std::string m_FalseLabelMeaning;
  };
}