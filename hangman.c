#include <string.h>
#include "hangman-io.h"
#include "words.h"
#include "cs136.h"

//capitalize returns the capitalized char if the char is 
//not a capital letter. Else return the char. 
//Runtime: O(1)
static char capitalize (char a){ 
  if ((a >= 97) && (a <= 122)) { 
    return a - 32;
  } else { 
    return a;
  }
}

//exist returns true if the letter in question exists in the 
//used_letters array. It returns fales otherwise.
//runtime : O(n), n being the length of used_letters
static bool exist (char used_letters[], char letter){ 
  int len = strlen(used_letters);
  if ((letter <= 'z') && (letter >= 'a')){
  for (int i = 0; i < len; i++){ 
    if ((used_letters[i] == letter) ||
        ((used_letters[i] + 32) == letter)){ 
      return true ; 
    }
  }
  } else {
    for (int i = 0; i < len; i++){ 
    if ((used_letters[i] == letter) ||
        ((used_letters[i] - 32) == letter)){ 
      return true ; 
    }
  }
  }
      
  return false; 
}

//update_word returns true if the character c exists within the word
//effect : mutates word_tracker
//runtime: O(n), n being the length of word. 
static bool update_word(char word[], char word_tracker[], char c){
  int len = strlen(word);
  int counter = 0; 
  for (int i = 0; i < len; i++){ 
    if ((word[i] == c) || 
        (word[i] == (c- 32))){
      word_tracker[i] = word[i];
      counter++;
    }
  }
  if (counter == 0){ 
    return 0; 
  }else{ 
    return 1;
}
}

//
int main(void) {
  while(1){
    printf(enter_game_number, max_words);
    int num = 0;
    scanf(" %d", &num);
    //making sure its a valid number
    if ((num < 1) || (num > max_words)){ 
      printf(invalid_game_number);
    } 
    else if ((num >= 1) && (num <= max_words)){
      int strike_counter = 0;
      int letter_counter = 0;
      //tracking all the used chars
      char used_letters[101] = {42,42,42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,
                           42,42,42,42,42,42,42,42,42,42,'\0'};
  
      const char *p = get_word(num);
      char word[51]; 
      strcpy(word, p); //create word  
      char word_tracker[51];
      strcpy(word_tracker, p);//create word_tracker
      for(int i = 0; i < strlen(word); i++){ //convert tracker to *** format
        if (word_tracker[i] != 32) { 
          word_tracker[i] = 42; 
        } else { 
          word_tracker[i] = 32;
      }
      }
      print_hangman(0); //print initial hangman 0 
        printf(letter_prompt);
        printf("%s\n", word_tracker);
      while(strike_counter < 6){
        char input; 
        scanf(" %c", &input);
        //if the character is not a letter
         if ((input < 65) || (input > 122) ||
                ((input > 90) && (input < 97))) { 
          printf(not_a_letter, input);
          print_hangman(strike_counter);
          printf(letter_prompt);
          printf("%s\n", word_tracker);
        //if the character was already used, case insensitive
        }else if (exist(used_letters, input) == 1) { 
          printf(already_guessed_letter, capitalize(input)); 
          print_hangman(strike_counter);
          printf(letter_prompt);
          printf("%s\n", word_tracker);
          
        }   
        //if the character is not in the word 
        else if (update_word(word, word_tracker, input) == 0) { 
          printf(not_in_word, capitalize(input));
          strike_counter++; 
          //if the game is over
          if (strike_counter == 6) {
            print_hangman(strike_counter);
            printf(game_over, word);
            break;
          }
          printf(not_last_guess,6 - strike_counter);
          print_hangman(strike_counter);
          used_letters[letter_counter] = input; 
          letter_counter++;
          printf(letter_prompt);
          printf("%s\n", word_tracker);
        }  
        //if the character is in the word 
        else if (update_word(word, word_tracker, input) == 1){ 
          if (strcmp(word,word_tracker) == 0) {  //when we win
          printf(congratulations, word); 
          break;
        }
           print_hangman(strike_counter); //print hang
           printf(letter_prompt); //print message
           printf("%s\n", word_tracker); //print word 
           used_letters[letter_counter] = input; 
           letter_counter++;
          
      }
}
      //if we win/lose 
      while((strike_counter == 6) || (strcmp(word,word_tracker) == 0)){
        printf(play_again);

        char restart; 
        scanf(" %c", &restart);
        //restart = read_char(false);
        if ((restart == 'Y') || (restart == 'y')) { 
          num=0;
          break; 
          
        } else if  ((restart == 'N') ||  (restart == 'n')){ 
          return 0;
        }else if ((restart != 'n') && (restart != 'N') &&(restart != 'y') &&(restart != 'Y')){ 
          printf(invalid_play_again_response);
        }
      }
} 
  }
}



  
