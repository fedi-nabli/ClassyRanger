#include "NaiveBayesClassifier.h"

namespace ClassyRanger
{
  NaiveBayesClassifier::NaiveBayesClassifier(std::string true_label_meaning, std::string false_label_meaning)
  {
    m_TrueLabelMeaning = true_label_meaning;
    m_FalseLabelMeaning = false_label_meaning;
    CV.set_binary(false);
    CV.set_caseSensitive(false);
    CV.set_includeStopwords(false);
  }

  NaiveBayesClassifier::~NaiveBayesClassifier()
  {
  }

  int NaiveBayesClassifier::total_words()
  {
    int count = 0;
    for (auto sentence : CV.get_sentences())
    {
      for (auto _count : sentence->sentence_array)
      {
        count += _count;
      }
    }

    return count;
  }

  int NaiveBayesClassifier::total_words_of_type(bool label)
  {
    int count = 0;
    for (auto sentence : CV.get_sentences())
    {
      for (auto _count : sentence->sentence_array)
      {
        if (sentence->label == label)
        {
          count += _count;
        }
      }
    }

    return count;
  }

  float NaiveBayesClassifier::prob_of_type(bool label)
  {
    int total = total_words();
    int total_of_type = total_words_of_type(label);
    return (float)total_of_type / (float)total;
  }

  int NaiveBayesClassifier::count_occurences(std::string word)
  {
    int count = 0;
    unsigned int word_array_size = CV.get_word_array_size();

    for (unsigned int i = 0; i < word_array_size; i++)
    {
      if (CV.get_word(i) == word)
      {
        for (auto sentence : CV.get_sentences())
        {
          if (sentence->sentence_array.size() > i)
          {
            count += sentence->sentence_array[i];
          }
        }
      }
    }

    return count;
  }

  int NaiveBayesClassifier::count_occurences_of_type(std::string word, bool label)
  {
    int count = 0;
    unsigned int word_array_size = CV.get_word_array_size();

    for (unsigned int i = 0; i < word_array_size; i++)
    {
      if (CV.get_word(i) == word)
      {
        for (auto sentence : CV.get_sentences())
        {
          if (sentence->sentence_array.size() > i)
          {
            if (sentence->label == label)
            {
              count += sentence->sentence_array[i];
            }
          }
        }
      }
    }

    return count;
  }

  float NaiveBayesClassifier::get_weight(std::vector<std::string> sentence, bool label)
  {
    int _total_words_of_type = total_words_of_type(label);
    float mp = m_SmoothingParamM * m_SmoothingParamP;
    float m = m_SmoothingParamM;
    float weight = log(prob_of_type(label));

    for (auto word : sentence)
    {
      weight += log(((float)count_occurences_of_type(word, label) + mp) / ((float)_total_words_of_type + m));
    }

    return weight;
  }

  int NaiveBayesClassifier::analyze(std::string sentence)
  {
    Corpus corpus;
    std::vector<std::string> processed_input;
    processed_input = CV.build_sentence_vector(sentence);

    float true_weight = get_weight(processed_input, true);
    float false_weight = get_weight(processed_input, false);

    if (true_weight < false_weight)
    {
      std::cout << m_FalseLabelMeaning << std::endl;
      return corpus.NEG;
    }
    else if (true_weight > false_weight)
    {
      std::cout << m_TrueLabelMeaning << std::endl;
      return corpus.POS;
    }
    else
    {
      std::cout << "Neutral" << std::endl;
      return corpus.NEU;
    }
  }
}