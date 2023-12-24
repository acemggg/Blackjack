#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int drawnCards[13][4] = {0};

typedef struct{
    char playerName[255];
    int playerScore;
} player;

void error(){
	system("cls");
    printf("Game encountered an error\n");
}

int isCardDrawn(int x, int y){
    return drawnCards[x - 2][y];
}

void markCardAsDrawn(int x, int y){
    drawnCards[x - 2][y] = 1;
}

void cards(int x){
    char *card[8] = {"Two", "Three", "Four", "Five", 
					"Six", "Seven", "Eight", "Nine"};
    char *specialCard[4] = {"Ten", "Jack", "Queen", "King"};
    char *suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    int index, suit;
    index = x - 2;
    suit = rand() % 4;
    
    while(isCardDrawn(x, suit)) suit = rand() % 4;
    
    markCardAsDrawn(x, suit);
    if(index == 9 || index == -1) 
		printf("Ace of %s. ", suits[suit]);
    
    else if(index == 8){
    	index = rand() % 4;
    	printf("%s of %s. ", specialCard[index], suits[suit]);
	}
	
	else if(index < 8) printf("%s of %s. ", card[index], suits[suit]);
}

void rules(){
	system("cls");
	puts("Rules:");
	puts("1. Each player is dealt with a card and has the option to draw as many additional cards as they desire.");
	puts("2. If the total value of their cards exceeds 21, they will bust and lose the game.");
	puts("3. The player with the highest value wins the game.");
	puts("4. Jack, Queen, and King have the same exact value, which is 10.");
	puts("5. Ace can have a value of either 1 or 11, depending on which value benefits the player more.");
//	puts("6. Spades > Hearts > Diamonds > Clubs.");
	printf("\n"); puts("Go to main menu (Enter): "); 
	printf(">> "); getchar(); system("cls"); main();
}

void clearHistory(){
    system("cls");
    FILE *history = fopen("history.txt", "w");

		printf("History cleared successfully.\n");
	
    fclose(history);
    
    printf("\n");
    puts("Go to main menu (Enter): ");
    printf(">> ");
    getchar();
    system("cls");
    main();
}

void printHistory(){
    system("cls");
    char text[1000];

    FILE *history = fopen("history.txt", "r");	    
    
    puts("+-------------------------------+");
    puts("|            History            |");
    puts("+-------------------------------+\n");
    while(fgets(text, sizeof(text), history) != NULL)
        printf("%s", text);

    printf("1. Clear History\n");
    printf("2. Go to main menu\n");
    printf(">> ");
    int choice;
    scanf("%d", &choice); getchar();

    switch(choice){
    case 1:
        clearHistory();
        break;
    case 2:
        system("cls");
        main();
        break;
    default:
        error();
        break;
    }

    fclose(history);
}


//Sorting

void swapPlayers(player *a, player *b){
    player temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(player players[], int n){
	int i, j;
    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(players[j].playerScore < players[j + 1].playerScore) 
				swapPlayers(&players[j], &players[j + 1]);
        }
    }
}

//Sorting end


void winner(player players[], int num){
    int max = players[0].playerScore;
    int i;
    time_t t; time(&t);

    system("cls");
    printf("\n");

    puts("  ######     ###    ##     ## ########  #######  ##     ## ######## ########  ");
    puts("##    ##    ## ##   ###   ### ##       ##     ## ##     ## ##       ##     ## ");
    puts("##         ##   ##  #### #### ##       ##     ## ##     ## ##       ##     ## ");
    puts("##   #### ##     ## ## ### ## ######   ##     ## ##     ## ######   ########  ");
    puts("##    ##  ######### ##     ## ##       ##     ##  ##   ##  ##       ##   ##   ");
    puts("##    ##  ##     ## ##     ## ##       ##     ##   ## ##   ##       ##    ##  ");
    puts(" ######   ##     ## ##     ## ########  #######     ###    ######## ##     ## ");

    bubbleSort(players, num);
    	
    if(players[0].playerScore > players[1].playerScore){
    	printf("\n");
    	printf("%s wins with a score of %d!\n", players[0].playerName, players[0].playerScore);
    }
    
    else{
    	printf("\n");
    	puts("Draw!");
	} 
	
	int sum = 0; float average; float rawAverage; int n = num; 
	for(i = 0; i < num; i++){
		sum = sum + players[i].playerScore;
		if(players[i].playerScore == 0)
			n = n - 1;
	}
	average = (float)sum / n;
	rawAverage = (float)sum / num;

    printf("\nRanking:\n");
    for(i = 0; i < num; i++){
    	if(players[i].playerScore == 0)
    		printf("Rank %d: %s - BUSTED!\n", i + 1, players[i].playerName);
    	else
    		printf("Rank %d: %s - Score: %d\n", i + 1, players[i].playerName, players[i].playerScore);
	} 
	printf("\n"); printf("Average: %.2f\n", average);
	printf("Raw Average: %.2f\n", rawAverage);
	
	FILE *history = fopen("history.txt", "w");
	
		fprintf(history, "%s\n", ctime(&t));
	
		for(i = 0; i < num; i++){
			if(players[i].playerScore == 0)
    			fprintf(history, "Rank %d: %s - BUSTED!\n", i + 1, players[i].playerName);
    		else
    			fprintf(history, "Rank %d: %s - Score: %d\n", i + 1, players[i].playerName, players[i].playerScore);
		}
		
		fprintf(history, "\nAverage: %.2f\n", average);
		fprintf(history, "Raw Average: %.2f\n\n", rawAverage);
	
	fclose(history);
    
    printf("\n"); puts("Go to main menu (Enter): "); 
	printf(">> "); getchar(); system("cls"); main();
}

void game(int num){
    srand(time(0));
    player players[4];
    memset(drawnCards, 0, sizeof(drawnCards));
    int i;

    for(i = 0; i < num; i++){
        int hit = 0;
        int random;
        char draw;
        system("cls");
        puts("      |========|      ");
        printf("|-----|Player %d|-----|\n", i + 1);
        puts("      |========|      ");
        printf("\n");

        printf("Enter the name for Player %d: ", i + 1);
        scanf("%[^\n]", players[i].playerName); getchar(); printf("\n");

        while(hit <= 21){
            random = (rand() % (11 - 2 + 1)) + 2;

            if(random == 11){
                puts("You drew an Ace (1 or 11)");
                printf(">> ");
                scanf("%d", &random); getchar(); printf("\n");
                
                if(random != 1 && random != 11){
                    error(); 
					exit(1);
                }
                    
				else if(random > 21){
                    error(); 
					exit(1);
                }
            }

            hit = hit + random;

            if(hit <= 21)
                players[i].playerScore = hit;
           
			else if(hit > 21){
                puts("Busted! ");
                printf("Total value: %d\n", hit);
                players[i].playerScore = 0;
                puts("Enter to continue");
                printf(">> ");
                getchar();
                break;
            }
            
            cards(random);
            printf("Total value: %d\n", hit);

            printf("Hit or Stand (h/s): ");
            scanf(" %c", &draw);
            getchar();
            printf("\n");
            draw = tolower(draw);
            
            switch(draw){
                case 'h':
                    continue;
                    
                default:
    				break;
            }
            break;
        }
    }
    winner(players, num);
}

int main(){
    int num, option;

    printf("\n");
    puts("########  ##          ###     ######  ##    ##       ##    ###     ######  ##    ##");
    puts("##     ## ##         ## ##   ##    ## ##   ##        ##   ## ##   ##    ## ##   ##");
    puts("##     ## ##        ##   ##  ##       ##  ##         ##  ##   ##  ##       ##  ##");
    puts("########  ##       ##     ## ##       #####          ## ##     ## ##       #####");
    puts("##     ## ##       ######### ##       ##  ##   ##    ## ######### ##       ##  ##");
    puts("##     ## ##       ##     ## ##    ## ##   ##  ##    ## ##     ## ##    ## ##   ##");
    puts("########  ######## ##     ##  ######  ##    ##  ######  ##     ##  ######  ##    ##");
    printf("\n");
    puts("1. Rules");
    puts("2. Play");
    puts("3. History");
    puts("4. Exit");
    printf(">> ");

    scanf("%d", &option);
    getchar();
    
    switch(option){
        case 1:
            rules();
            break;
            
        case 2:
            printf("\nEnter the amount of players (2 - 4): ");
            scanf("%d", &num); getchar();

            if(num >= 2 && num <= 4) 
				game(num);
            
			else
                error();
            break;
            
        case 3:
        	printHistory();
        	break;
        	
        case 4:
        	exit(1);
        	
        default:
            error();
            break;
    }
    
    return 0;
}

