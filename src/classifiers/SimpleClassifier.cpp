#include "SimpleClassifier.h"

namespace ClassyRanger
{
  SimpleClassifier::SimpleClassifier(std::string true_label_meaning, std::string false_label_meaning)
  {
    m_TrueLabelMeaning = true_label_meaning;
    m_FalseLabelMeaning = false_label_meaning;
    CV.set_binary(true);
    CV.set_caseSensitive(false);
    CV.set_includeStopwords(false);
  }

  SimpleClassifier::~SimpleClassifier()
  {
  }

  int SimpleClassifier::analyze(std::string sentence)
  {
    Corpus corpus;
    std::vector<std::string> processed_input;
    float weight = 0;

    processed_input = CV.build_sentence_vector(sentence);
    weight = get_weight(processed_input);

    if (weight == -1)
    {
      std::cout << "Sorry, not enough data for this input" << std::endl;
      return corpus.UNK;
    }
    else if (weight < 0.5)
    {
      std::cout << m_FalseLabelMeaning << std::endl;
      return corpus.NEG;
    }
    else if (weight > 0.5)
    {
      std::cout << m_TrueLabelMeaning << std::endl;
      return corpus.POS;
    }
    else
    {
      std::cout << "Netral" << std::endl;
      return corpus.NEU;
    }
  }

  float SimpleClassifier::get_weight(std::vector<std::string> sentence)
  {
    float count = 0;
    float num = 0;
    float sum = 0;

    std::vector<float> word_weights;
    unsigned int word_array_length = CV.get_word_array_size();

    for (std::string query_word : sentence)
    {
      for (unsigned int i = 0; i < word_array_length; i++)
      {
        if (query_word == CV.get_word(i))
        {
          for (auto sentence : CV.get_sentences())
          {
            if (CV.word_is_in_sentence(*sentence, i))
            {
              count++;
              num += sentence->label;
            }
          }

          float word_weight = num / count;
          word_weights.push_back(word_weight);
          count = 0;
          num = 0;
        }
      }
    }

    float found_occurences = (float)word_weights.size();
    if (!found_occurences)
    {
      return -1.0;
    }
    
    for (float word_weight : word_weights)
    {
      sum += word_weight;
    }

    return sum / found_occurences;
  }
}