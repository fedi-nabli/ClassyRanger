#include "CountVectorizer.h"

namespace ClassyRanger
{
  // ================================================================|
  // ======================CONSTRUCTORS==============================|
  // ================================================================|

  CountVectorizer::CountVectorizer()
  {
    m_Binary = true;
    m_CaseSensitive = true;
    m_IncludeStopwords = true;
  }

  CountVectorizer::CountVectorizer(bool binary, bool case_sensitive, bool include_stopwords)
  {
    m_Binary = binary;
    m_CaseSensitive = case_sensitive;
    m_IncludeStopwords = include_stopwords;
  }

  CountVectorizer::~CountVectorizer()
  {
  }

  // ===============================================================|
  // ======================USER INTERFACE FUNCTIONS=================|
  // ===============================================================|

  void CountVectorizer::fit(std::string abs_filepath_to_features, std::string abs_filepath_to_labels)
  {
    std::ifstream in;
    std::string feature_output;
    std::string label_output;
    std::vector<std::string> features;
    std::vector<bool> labels;

    in.open(abs_filepath_to_features);
    if (!in)
    {
      std::cout << "Error: Cannot open features file\n";
      std::exit(-1);
    }

    while (std::getline(in, feature_output))
    {
      features.push_back(feature_output);
    }
    
    in.close();

    in.open(abs_filepath_to_labels);
    if (!in)
    {
      std::cout << "Error: Cannot open labels file\n";
      std::exit(-1);
    }

    while (std::getline(in, label_output))
    {
      labels.push_back((bool)std::stoi(label_output));
    }

    in.close();

    unsigned int feature_size = features.size();
    if(feature_size != labels.size())
    {
      std::cout << "Error: Feature dimension is different from labels dimension\n";
      std::exit(-1);
    }

    for (unsigned int i = 0; i < feature_size; i++)
    {
      add_sentence(features[i], labels[i]);
    }
  }

  void CountVectorizer::shape()
  {
    unsigned int wordArraySize = get_word_array_size();
    unsigned int sentenceCount = get_sentence_count();
    std::cout << "------------------------------" << std::endl;
    std::cout << "Current CountVectorizer Shape:" << std::endl;
    std::cout << "Total unique words: " << std::to_string(wordArraySize) << std::endl;
    std::cout << "Documents in corpus: " << std::to_string(sentenceCount) << std::endl;
    std::cout << "------------------------------" << std::endl;
  }

  void CountVectorizer::head()
  {
    int count = 0;
    unsigned int wordArraySize = get_word_array_size();

    if (wordArraySize > 10)
    {
      wordArraySize = 10;
    }

    std::cout << "------------------------------" << std::endl;
    std::cout << "Current CountVectorizer Head:" << std::endl;
    for (unsigned int i = 0; i < wordArraySize; i++)
    {
      for (auto sentence : m_Sentences)
      {
        if (word_is_in_sentence(*sentence, i))
        {
          count++;
        }
      }

      std::cout << get_word(i) << ": " << count << std::endl;
      count = 0;
    }
    std::cout << "------------------------------" << std::endl;
  }

  // ===========================================================|
  // ======================HELPERS==============================|
  // ===========================================================|

  int CountVectorizer::word_is_in_sentence(Sentence sentence, unsigned int idx)
  {
    return (sentence.sentence_array.size() > idx && sentence.sentence_array[idx]);
  }

  void CountVectorizer::push_sentence_to_word_array(std::vector<std::string> new_sentence_vector)
  {
    for (std::string word : new_sentence_vector)
    {
      if (!count_vectorizer_contains_words(word))
      {
        m_WordArray.push_back(word);
      }
    }
  }

  std::shared_ptr<Sentence> CountVectorizer::create_sentence_object(std::vector<std::string> new_sentence_vector, bool label)
  {
    std::shared_ptr<Sentence> new_sentence(new Sentence);
    unsigned int wordArraySize = get_word_array_size();
    for (unsigned int i = 0; i < wordArraySize; i++)
    {
      int count = std::count(new_sentence_vector.begin(), new_sentence_vector.end(), m_WordArray[i]);
      if (count)
      {
        if (m_Binary)
        {
          new_sentence->sentence_array.push_back(1);
        }
        else
        {
          new_sentence->sentence_array.push_back(count);
        }
      }
      else
      {
        new_sentence->sentence_array.push_back(0);
      }
    }

    new_sentence->label = label;
    return new_sentence;
  }

  void CountVectorizer::add_sentence(std::string new_sentence, bool label)
  {
    std::vector<std::string> processedString;
    processedString = build_sentence_vector(new_sentence);
    push_sentence_to_word_array(processedString);
    std::shared_ptr<Sentence> sentenceObject = create_sentence_object(processedString, label);
    m_Sentences.push_back(sentenceObject);
  }

  bool CountVectorizer::count_vectorizer_contains_words(std::string word_to_check)
  {
    for (std::string word : m_WordArray)
    {
      if (word == word_to_check)
      {
        return true;
      }
    }

    return false;
  }

  std::vector<std::string> CountVectorizer::build_sentence_vector(std::string sentence)
  {
    Corpus corpus;
    std::string new_word = "";
    std::vector<std::string> return_vector;

    for (char x : sentence)
    {
      if (std::isupper(x) && !m_CaseSensitive)
      {
        x = std::tolower(x);
      }

      if (x == ' ')
      {
        if (!m_IncludeStopwords && corpus.stop_words.count(new_word))
        {
          new_word = "";
        }
        else
        {
          return_vector.push_back(new_word);
          new_word = "";
        }
      }
      else if (corpus.punctuations.count(x))
      {
        return_vector.push_back(new_word);
        std::string str(1, x);
        return_vector.push_back(str);
        new_word = "";
      }
      else
      {
        new_word = new_word + x;
      }
    }

    if (new_word != "")
    {
      return_vector.push_back(new_word);
    }

    return return_vector;
  }
}