#include "search_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// This function should loop over the vocabulary (which contains num_words
// entries) and return the number of words in which that particular letter
// occurs. So if there are 15 words containing the letter 'x' for the particular
// vocabulary, then this function will return 15.
int score_letter(char letter, char **vocabulary, size_t num_words) {

    int count = 0;
    for(size_t i = 0; i < num_words; i++)
    {
        if(vocabulary[i] != NULL)
        {
            if(strchr(vocabulary[i], letter) != NULL)
            {
                count++;
            }
        }
    }

    return count;

}


int score_word(char *word, int *letter_scores) {

    int sum = 0;
    char compare[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',                        'o','p','q','r','s','t','u','v','w','x','y','z'};    

    for(int i = 0; i < 5; i++)
    {
        char temp = word[i];
        for(int j = 0; j < 26; j++)
        {
            if(temp == compare[j])
            {
                sum += letter_scores[j];
                compare[j] = '\0';
            }
        }
    }    
    

    return sum;

}

char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter *does not occur* in the secret word. So for any of the words
// in the vocabulary that do contain that letter, free their pointers and set
// the corresponding slot to NULL.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_gray(char letter, char **vocabulary,
                              size_t num_words) {

    int count = 0;
    for(size_t i = 0; i < num_words; i++)
    {
        if(vocabulary[i] != NULL)
        {
            if(strchr(vocabulary[i], letter) !=  NULL)
            {
                count++;
                free(vocabulary[i]);
                vocabulary[i] = NULL;
            }
        }
    }


    return count;

}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter occurs in the word, *but not at this particular position*.
// So remove any words that either don't contain the letter at all, or do
// contain it, but at the specified position.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary,
                                size_t num_words) {

    int count = 0;
    for(size_t i = 0; i < num_words; i++)
    {
        if(vocabulary[i] != NULL)
        {
            if(strchr(vocabulary[i], letter) == NULL)
            {
                count++;
                free(vocabulary[i]);
                vocabulary[i] = NULL;
            }
            else if(vocabulary[i][position] == letter)
            {
                count++;
                free(vocabulary[i]);
                vocabulary[i] = NULL;
            }
        }    
    }

    //END MY CODE
    return count;

}


// This function will filter down the vocabulary based on the knowledge that the
// specified letter *definitely* occurs as the specified position. So remove any
// word that does not contain, for the specified position, the specified letter.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_green(char letter, int position, char **vocabulary,
                               size_t num_words) {

    int count = 0;
    for(size_t i = 0; i < num_words; i++)
    {
        if(vocabulary[i] != NULL)
        {
            if(vocabulary[i][position] != letter)
            {
                count++;
                free(vocabulary[i]);
                vocabulary[i] = NULL;
            }
        }
    }

    //END MY CODE
    return count;

}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
