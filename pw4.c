#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define col 7
#define row 6

// Function prototypes
void cleargrid(char martix[row][col]);
int getinput(char matrix[row][col],char m);
void move(char matrix[row][col], char m, int colm);
void printgrid(char matrix[row][col]);
int availablecolumn(char matrix[row][col], int colm);
bool checkalignment(char matrix[row][col],char m);
int randommove();
int smartmove(char matrix[row][col],char m);
int human();
void ai();
int aiaccomodation(char matrix[row][col]);
int aiaccomodation2(char matrix[row][col], char m);

// Main function
int main(){
    while(true) { // main game loop 
        printf("Do you want to play? (y/n): "); 
        char play;
        scanf(" %c",&play);
        if(tolower(play)=='y'){ //I added tolower in case if input is upper(both in "n" and "y")
            char answer;
            printf("Play against AI or player?(write '1' for 1 player, '2' for 2 players): ");
            scanf(" %c", &answer);
            // if else statement to decide whether it is a human-human game or ai-human game
            if (answer == '2') {
                printf("1st player is red(*), 2nd is yellow($) \n");
                human();
            } else if (answer == '1') {
                printf("Human player is yellow($), AI is red(*) \n");
                ai();
            } else {
                printf("Invalid input.\n");
            }
        }
        else if(tolower(play)=='n'){
            printf("Game over!\n");
            break;
        }
    }
    return 0;
}

// AI function
void ai() {
    char matrix[row][col]; 
    char m; 
    int player=-1;  // 1 and * for red; -1 and $ for yellow

    cleargrid(matrix);
    while(true) { // game loop
        if(player==1){
            m='*'; // AI player is red
            int nextcolm; 
            char k='$';
            /*in this if statement the goal of ai is to block the user if user has 2 or 3 allignment 
            when the user does not have allignment else if statements are used*/
            if (smartmove(matrix,k)!=0){
                nextcolm=smartmove(matrix,k);
                move(matrix, m, nextcolm); 
                //printf("%d\n",111);
            }
            else if(smartmove(matrix,m)!=0){
                nextcolm=smartmove(matrix,m); // if ai has allignment
                move(matrix, m, nextcolm);
                //printf("%d\n",2222);
            }
            else if(aiaccomodation(matrix)!=0){ 
                nextcolm=aiaccomodation(matrix); // if ai doesnt have allignment but has a move that can create allignment
                move(matrix, m, nextcolm);
                //printf("%d\n",333);
            }
            else if (aiaccomodation2(matrix,m)!=0){
                nextcolm=aiaccomodation2(matrix,m); // if ai doesnt have allignment but doen not have a move that can make allignment 
                move(matrix, m, nextcolm);
                //printf("%d\n",444);
            }
            else{
                nextcolm=randommove(); // if something goes wrong in previous if's 
                move(matrix, m, nextcolm);
                //printf("%d\n",555);
            }

            if (checkalignment(matrix,m)) { // checks winning or not
                printgrid(matrix); 
                printf("AI wins!\n");
                return;
            }
            player=(-1)*player; // changes player  
        }
        printgrid(matrix);
        if(player==-1){
            m='$'; // Human player is yellow
            printf("Random move offer: %d\n", randommove());
            printf("Smart move offer: %d\n",smartmove(matrix,m));
            printf("Enter column for your move, player yellow: ");
            int nextcolm;
            scanf("%d", &nextcolm); // gets move
            while (0>=nextcolm || nextcolm>7 || availablecolumn(matrix, nextcolm)!=1){ // checks move
                printf("Your move offer must be between 1 and 7!\n");
                printf("Enter column for your move, player yellow: ");
                scanf("%d", &nextcolm);
            }
            move(matrix, m, nextcolm); // does move
            if (checkalignment(matrix,m)) { // checks winning conditions
                printgrid(matrix); 
                printf("Player Yellow wins!\n");
                return;
            }
            player=(-1)*player; // changes player
        }
        printgrid(matrix);

    }
}

// Function to check if AI has a move that can create alignment
int aiaccomodation(char matrix[row][col]) {
    for(int i=row-1; i>=0; i--){
        for (int j=0; j<col; j++) {
            char k='$';
            if(matrix[i][j]==k && availablecolumn(matrix,j+1)==1 && j!=6){
                return j+2; 
            }
            else if(matrix[i][j]==' ' && availablecolumn(matrix,j) == 1 &&j!=6){
                return j+1; 
            }
        }
    }
    return 0;
}

// ai makes a move
int aiaccomodation2(char matrix[row][col], char m) {
    for (int j=0; j<col; j++) {
        for (int i=row-1; i>=0; i--) {
            if(matrix[i][j]==m){
                if(matrix[i][j-1]==' ' && j!=0 && availablecolumn(matrix,j-1)==1){
                    return j;
                }
                else if(matrix[i][j+1]==' '&& availablecolumn(matrix,j+1)==1&&j!=6){
                    return j+2;
                }
                else if(matrix[i-1][j]==' '&& availablecolumn(matrix,j)==1){
                    return j+1;
                }
            }
        }
    }
    int k=aiaccomodation(matrix); 
    return k;
}


// Function for human vs. human gameplay
int human() {
    char matrix[row][col]; 
    char m; 
    int player=1;  // 1 and * for red; -1 and $ for yellow

    cleargrid(matrix);
    while(true){
        if(player==1){
            m='*';
            printf("Random move offer: %d\n", randommove());
            printf("Smart move offer: %d\n",smartmove(matrix,m));
            int nextcolm=getinput(matrix,m);
            while (0>=nextcolm || nextcolm>=8 || availablecolumn(matrix, nextcolm)!=1){
                printf("Your move offer must be between 1 and 7!\n");
                nextcolm=getinput(matrix,m);
            }
        
            move(matrix, m, nextcolm);
            if (checkalignment(matrix,m)) {
                printf("Player Red wins!\n");
                printgrid(matrix);
                return 0;
            }
            player=(-1)*player;
            
        }
        printgrid(matrix);
        if(player==-1){
            m='$';
            printf("Random move offer: %d\n", randommove());
            printf("Smart move offer: %d\n",smartmove(matrix,m));
            int nextcolm=getinput(matrix,m);
            while (0>=nextcolm || nextcolm>=8 || availablecolumn(matrix, nextcolm)!=1){
                printf("Your move offer must be between 1 and 7!\n");
                nextcolm=getinput(matrix,m);
            }
            move(matrix, m, nextcolm);
            if (checkalignment(matrix,m)) {
                printgrid(matrix);
                printf("Player Yellow wins!\n");//same here
                return 0;
            }
            player=(-1)*player;
        }
        printgrid(matrix);
    }
    return 0;
}

// Function to determine a smart move for the AI
int smartmove(char matrix[row][col], char m) { /* the goal of smart move is to show the longest allignmnt
                                                not blocking the opposite player*/

    int hexp = 0, vexp = 0, upexp = 0, downexp = 0;
    int hcol =0 , vcol=0, upcol=0 , downcol=0 ;
    // Check horizontally
    for (int i = row-1; i >= 0; i--) { // loop backwards
        for (int j = 0; j < col - 3; j++) { 
            if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i][j+1] && matrix[i][j] == matrix[i][j+2]) { // checks *** senario
                hexp = 1;
                if (matrix[i][j+3] == ' ' && j+3 < col) {
                    hcol = j+4; //printf("h1 %d\n", hcol);
                }
                else if (matrix[i][j-1] == ' ' && j-1 >= 0) {
                    hcol = j;  //printf("h2 %d\n", hcol);             
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i][j+1] && matrix[i][j]==matrix[i][j+3] ){// checks ** * senario
                hexp=1;
                if (matrix[i][j+2] == ' ') {
                    hcol = j+3; //printf("h3 %d\n", hcol);
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i][j+2] && matrix[i][j] == matrix[i][j+3]) { // checks * ** senario
                hexp=1;
                if (matrix[i][j+1] == ' ') {
                    hcol = j+2; //printf("h4 %d\n", hcol);
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i][j+1]) { // checkes ** senario
                hexp = 2;
                if (matrix[i][j+2] == ' ' && j+2 < col) {
                    hcol = j+3; //printf("h5 %d\n", hcol);
                }
                else if (matrix[i][j-1] == ' ' && j-1 >= 0) {
                    hcol = j; //printf("h6 %d\n", hcol);
                }
            }
        }
    }

    //printf("Horizontal: hexp=%d, hcol=%d\n", hexp, hcol);

    // Check vertically
    for (int j = 0; j < col-1; j++) {
        for (int i = row-1; i >=0; i--) {
            if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-1][j] && matrix[i][j] == matrix[i-2][j] ) {
                vexp = 1;
                if (matrix[i-3][j] == ' ') {
                    vcol = j+1; //printf("v1 %d", vcol);
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] == matrix[i-1][j]) {
                vexp = 2;
                if (matrix[i-2][j] == ' ') {
                    vcol = j+1; //printf("v2 %d", vcol);
                }
            }
        }
    }
       // printf("Vertical: vexp=%d, vcol=%d\n", vexp, vcol);

    // Check diagonally (bottom-left to top-right)
    for (int i = row-1; i >= 3; i--) {
        for (int j = 0; j < col - 3; j++) {
            if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-1][j+1] && matrix[i][j] == matrix[i-2][j+2]) {// checkes like horizontal (alignment of 3s then 2)
                upexp = 1;
                if (matrix[i-3][j+3] == ' ') {
                    upcol = j+4;
                }
                else if (matrix[i+1][j-1] == ' ') {
                    upcol = j;
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-1][j+1] && matrix[i][j]==matrix[i-3][j+3] ){
                upexp=1;
                if (matrix[i-2][j+2] == ' ') {
                    upcol = j+3;
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-2][j+2] && matrix[i][j] == matrix[i-3][j+3]) {
                upexp=1;
                if (matrix[i-1][j+1] == ' ') {
                    upcol = j+2;
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i+1][j-1]) {
                upexp = 2;
                if (matrix[i-1][j+1] == ' ') {
                    upcol = j+2;
                }
                else if (matrix[i+2][j-2] == ' ') {
                    upcol = j-1;
                }
            }
        }
    }

        //printf("Up diagonal: upexp=%d, upcol=%d\n", upexp, upcol);

    // Check diagonally (bottom-right to top-left)
    for (int i = row-1; i >= 0; i--) {
        for (int j = col - 1; j >= 0; j--) {
            if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-1][j-1] && matrix[i][j] == matrix[i-2][j-2]) {// checkes like horizontal (alignment of 3s then 2)
                downexp = 1;
                if (matrix[i-3][j-3] == ' ') {
                    downcol = j-2;
                }
                else if (matrix[i+1][j+1] == ' ') {
                    downcol = j+2;
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-1][j-1] && matrix[i][j]==matrix[i-3][j-3] ){
                downexp=1;
                if (matrix[i-2][j-2] == ' ') {
                    downcol = j-1;
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i-2][j-2] && matrix[i][j] == matrix[i-3][j-3]) {
                upexp=1;
                if (matrix[i-1][j-1] == ' ') {
                    upcol = j;
                }
            }
            else if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i+1][j+1]) {
                downexp = 2;
                if (matrix[i-1][j-1] == ' ') {
                    downcol = j-2;
                }
                else if (matrix[i+2][j+2] == ' ') {
                    downcol = j+3;
                }
            }
        }
    }

    //printf("Down diagonal: downexp=%d, downcol=%d\n", downexp, downcol);
    if (vexp==1) return vcol;
    else if (hexp==1) return hcol; 
    else if (upexp==1) return upcol;
    else if (downexp==1) return downcol;
    else if (vexp==2) return vcol;
    else if (hexp==2) return hcol;
    else if (upexp==2) return upcol;
    else if (downexp==2) return downcol;
    // If no smart move is found, return 0
    return 0;
}


// Function to generate a random move
int randommove(){
    return rand() % 7 + 1;
}

// Function to get input from the player
int getinput(char matrix[row][col],char m){
    int nextmove;
    if(m=='*'){
        printf("Enter column for your move, player red: ");
    }
    else if(m=='$'){
        printf("Enter column for your move, player yellow: ");
    }
    
    scanf("%d",&nextmove);
    while (0>=nextmove || nextmove>=8 && availablecolumn(matrix, nextmove)!=1){
        printf("Your move offer must be between 1 and 7!\n");
        scanf("%d",&nextmove);
    }
    return nextmove;
}

// Function to check if there is alignment in the game matrix
bool checkalignment(char matrix[row][col], char m) {
    // Check horizontally
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (matrix[i][j] == m && matrix[i][j] != ' ' && matrix[i][j] == matrix[i][j+1] && matrix[i][j] == matrix[i][j+2] && matrix[i][j] == matrix[i][j+3]) {
                return true;
            }
        }
    }
    // Check vertically
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < row - 3; i++) {
            if (matrix[i][j] == m &&matrix[i][j] != ' ' && matrix[i][j] == matrix[i+1][j] && matrix[i][j] == matrix[i+2][j] && matrix[i][j] == matrix[i+3][j]) {
                return true;
            }
        }
    }
    // Check diagonally (bottom-left to top-right)
    for (int i = 0; i < row - 3; i++) {
        for (int j = 0; j < col - 3; j++) {
            if (matrix[i][j] == m &&matrix[i][j] != ' ' && matrix[i][j] == matrix[i+1][j+1] && matrix[i][j] == matrix[i+2][j+2] && matrix[i][j] == matrix[i+3][j+3]) {
                return true;
            }
        }
    }
    // Check diagonally (bottom-right to top-left)
    for (int i = 0; i < row - 3; i++) {
        for (int j = col - 1; j >= 3; j--) {
            if (matrix[i][j] == m &&matrix[i][j] != ' ' && matrix[i][j] == matrix[i+1][j-1] && matrix[i][j] == matrix[i+2][j-2] && matrix[i][j] == matrix[i+3][j-3]) {
                return true;
            }
        }
    }
    return false;
}

// Function to initialize the game matrix
void cleargrid(char matrix[row][col]){
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix[i][j]=' ';
        }
    }
}

// Function to print the game matrix
void printgrid(char matrix[row][col]){
    printf("   1 2 3 4 5 6 7\n");
    for(int i=0; i<row; i++){
        printf("%d ",6-i);
        for(int j=0; j<col; j++){
            printf(" %c",matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a column is available for a move
int availablecolumn(char matrix[row][col], int colm){
    if(matrix[0][colm-1]==' ') return 1;
    else return 0;
}

// Function to make a move in the game matrix
void move(char matrix[row][col], char m, int colm){
    for (int i=5;i>=0; --i){
        if(matrix[i][colm-1]==' '){
            matrix[i][colm-1]=m;
            break;
        }
    }
}
