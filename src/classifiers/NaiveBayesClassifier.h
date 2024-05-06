#pragma once

#include "BaseClassifier.h"

#include <cmath>

namespace ClassyRanger
{
  class NaiveBayesClassifier : public BaseClassifier
  {
    public:
      NaiveBayesClassifier(std::string true_label_meaning, std::string false_label_meaning);
      ~NaiveBayesClassifier();

      int analyze(std::string sentence);

      int total_words();
      int total_words_of_type(bool label);
      float prob_of_type(bool label);
      int count_occurences(std::string word);
      int count_occurences_of_type(std::string, bool label);
      
      float get_weight(std::vector<std::string> sentence, bool label);
    
    private:
      float m_SmoothingParamM = 1.0f;
      float m_SmoothingParamP = 0.5f; 
  };
}