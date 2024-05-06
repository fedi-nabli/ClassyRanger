#pragma once

#include "Corpus.h"

#include <set>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace ClassyRanger
{
  struct Sentence
  {
    std::vector<int> sentence_array;
    int label;
  };

  class CountVectorizer
  {
    public:
      // ======================CONSTRUCTORS==============================|
      
      /**
       * @brief Default constructor has two options, one which takes no params,
       * which defaults to m_Binary=true, m_CaseSensitive=true, m_IncludeStopwords=true
       */
      CountVectorizer();

      // Add another which allows the user to choose their options
      CountVectorizer(bool binary, bool case_sensitive, bool include_stopwords);

      // Destructor
      ~CountVectorizer();

      // ======================USER INTERFACE FUNCTIONS==================|

      /**
       * @brief Fit will add additional (labeled) data to a CV object. User must
       * provide an absolute filepath to the features and an absolute filepath to
       * the labels.
       * 
       * @param abs_filepath_to_features 
       * @param abs_filepath_to_labels 
       */
      void fit(std::string abs_filepath_to_features, std::string abs_filepath_to_labels);
      /**
       * @brief Prints the dimensions of the CV object
       */
      void shape();
      /**
       * @brief Prints a dictionary-like representation of the CV object (first 10) 
       */
      void head();

      // ======================HELPERS===================================|

      // Checks if a word is in the sentence. Returns an integer casted bool
      int word_is_in_sentence(Sentence sentence, unsigned int idx);
      // Given a sentence, push_sentence_to_word_array will update the CV's m_WordArray
      // to incorporate newly discovered words.
      void push_sentence_to_word_array(std::vector<std::string> new_sentence_vector);
      // Given a sentence, return a fully constructed sentence object
      std::shared_ptr<Sentence> create_sentence_object(std::vector<std::string> new_sentence_vector, bool label);
      // Given a sentence, add the sentence to the CountVectorizer. Combines
      // build_sentence_vector, push_sentence_to_word_array and create_sentence_object
      // to accomplish this task
      void add_sentence(std::string new_sentence, bool label);
      
      // Checks if CV object already contains the word
      bool count_vectorizer_contains_words(std::string word_to_check);
      // Given a sentence, split the sentence into a vector of words
      // Punctuation should be it's own element
      std::vector<std::string> build_sentence_vector(std::string sentence);

    public:
      void set_binary(bool binary) { m_Binary = binary; }
      void set_caseSensitive(bool caseSensitive) { m_CaseSensitive = caseSensitive; }
      void set_includeStopwords(bool includeStopwords) { m_IncludeStopwords = includeStopwords; }

      inline std::string get_word(int idx) { return m_WordArray[idx]; }
      inline std::shared_ptr<Sentence> get_sentence(int idx) { return m_Sentences[idx]; }
      inline unsigned int get_word_array_size() { return m_WordArray.size(); }
      inline unsigned int get_sentence_count() { return m_Sentences.size(); }

    private:
      std::vector<std::string> m_WordArray;
      std::vector<std::shared_ptr<Sentence>> m_Sentences;
      bool m_Binary;
      bool m_CaseSensitive;
      bool m_IncludeStopwords;
  };
}