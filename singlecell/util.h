
// #TODO# The Code You Will Need To Edit

/***************************************
*         AI Tool Disclosure:          *
****************************************/

/*
Used chatgpt for reminders on malloc syntax. Didn't use for pointer math
Used the VS code debugger
used chatgpt to look more into some cpp syntax that came up in helpers.h,
but i was pretty fine just writing it in C instead of using extra cpp features.
*/

//
// #TODO# 
//

#include "moves.h"
#include "helpers.h"

// Allocates memory using malloc for an array of characters
void allocate_memory(Character** characters, int N_CHARACTERS){
  //
  // #TODO# 
  // Hint: You've been passed in a pointer to the location
  //       where we want to have an array's worth of memory.
  //       If this is wrinkling your brain this stackoverflow
  //       post may have some very valuable advice:
  //       https://stackoverflow.com/questions/897366/how-do-pointer-to-pointers-work-in-c-and-when-might-you-use-them
  //

  //allocate for the array of pointers to struct Character
  *characters = (Character *)malloc(N_CHARACTERS*sizeof(characters));
  
  //allocate along characters pointer array to make space for each character
  for(int i=0;i<N_CHARACTERS;i++){
    characters[i] = (Character *) malloc(sizeof(Character));
  }
}

// Applies the given move to all characters
// Note: 0 = Up, 1 = Down, 2 = Left, 3 = Right
void apply_moves(Character* characters, int move){
  //

  for(int i=0;i<N_CHARACTERS;i++){
    if(move==0 && characters[i].y<xy_max){
      characters[i].y +=1;
    }
    else if(move==1 && characters[i].y>xy_min){
      characters[i].y  -=1;
    }
    else if(move==2 && characters[i].x>xy_min){
      characters[i].x -=1;
    }
    else if(move==3 && characters[i].x<xy_max){
      characters[i].x +=1;
    }
  }
  return;
}

// returns True if in collision
bool in_collision(Character& c1, Character& c2){
  //
  // #TODO#
  // hint: the euclidean_distance function will be helpful and don't
  //       forget characters are circles!
  //
  //ASSUMPTION: the (x,y) coordinaters of a character represents the centerpoint
  float distance = euclidean_distance(c1.x,c1.y,c2.x,c2.y);
  if((distance<(c1.size+c2.size))&&(c1.alive==1&&c2.alive==1)){
    return true;
  }

  return false;
}

// resolve a collision between two characters
void resolve_collision(Character& c1, Character& c2){
  //
  // #TODO#
  // hint: make sure to break ties correctly!
  //
  int c1_wins_tie=0;
  if(c1.size==c2.size){ //tie state
    if(c1.id<c2.id){
      c1_wins_tie=1;
    }
  }

  if(c1.size>c2.size||c1_wins_tie){ //c1 wins
    //grow c1 by c2
    c1.size+=c2.size;
    //remove c2
    c2.alive=0;

  }

  else{ //c2 wins
    c2.size +=c1.size;
    c1.alive=0;
  }

  return;
}

// check for and resolve all possible collisions
void check_resolve_all_collision(Character* characters){
  //
  // #TODO#
  // Hint: a modified version of the following code will be helpful
  //       when called correctly inside of some loops and conditionals
  //       if (in_collision(c1, c2)){resolve_collision(c1,c2);}
  //
  for(int i=0;i<N_CHARACTERS;i++){
    for(int j=i+1;j<N_CHARACTERS;j++){//won't overflow since if i=N_CHARACTERS-1,
                                      //j=N_CHARACTERS, loop doesnt run :)
      if(in_collision(characters[i],characters[j])){
        resolve_collision(characters[i],characters[j]);
      }
      if(characters[i].alive==0){//will occur if loses the collusion
        break;
      }
    }
  }
}