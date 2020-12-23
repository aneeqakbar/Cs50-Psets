#include <stdio.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char *name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Define bool datatype (true & false)
typedef enum
{
    false,
    true
} bool;

// Utilities
bool strcmp(char *str1, char *str2);
int strlen(char *string);
char *tolower(char word[]);

// Function prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("\033[1;31m \bUsage: plurality [candidate ...] \033[0m\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("\033[1;31m \bMaximum number of candidates is %i \033[0m\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        int same_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (strcmp(candidates[i].name,candidates[j].name))
            {
                same_count++;
            }
            if (same_count > 1)
            {
                printf("\033[1;31m \bEach candidates should have different Names! \033[0m\n");
                return 3;
            }
        }
    }
    
    printf("Number of voters: ");
    int voter_count;
    scanf("%d", &voter_count);
    printf("\033[0;33m!!!------------------------------------!!!\033[0m\n");
    // int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        printf("Vote: ");
        char name[255];
        int scan = scanf("%s", &name);
        
        // string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("\033[0;31m \bInvalid vote. \033[0m\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    int i = 0, matched = 0, lenght = strlen(name);
    while (candidates[i].name != NULL)
    {
        if (strcmp(tolower(name),tolower(candidates[i].name)))
        {
            candidates[i].votes += 1;
            return true;
        }
        i++;
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    typedef struct
    {
        char *name;
        int votes;
    } winner;

    winner winners[MAX];

    int mostVotes = 0, w = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > mostVotes)
        {
            mostVotes = candidates[i].votes;
            winners[0].name = candidates[i].name;
            winners[0].votes = candidates[i].votes;
        }
        else if (candidates[i].votes == mostVotes)
        {
            w++;
            winners[w].name = candidates[i].name;
            winners[w].votes = candidates[i].votes;
        }
    }
    if (w >= 1)
    {
        for (int i = 0; i <= w; i++)
        {
            printf("\033[0;32m \b%s \033[0m\n", winners[i].name);
        }
    }
    else
    {
        printf("\033[0;32m \b%s \033[0m\n", winners[0].name);
    }
    return;
}

int strlen(char *string)
{
    int i = 0, lenght = 0;
    while (string[i] != '\000')
    {
        i++;
        lenght++;
    }
    return lenght;
}

char *tolower(char *word){
    int lenght = strlen(word);
    for (int i = 0; i < lenght; i++)
    {
        int letter = word[i];
        if (letter >= 65 && letter <= 90)
        {
            letter += 32;
            word[i] = letter;
        }
    }
    return word;
}

bool strcmp(char str1[], char str2[])
{
    int r, i = 0;
    while (str1[i] == str2[i])
    {
        if (str1[i] == '\000' || str2[i] == '\000')
        {
            break;
        }
        i++;
    }
    (str1[i] == '\0' && str2[i] == '\0') ? (r = true) : (r = false);
    return r;
}
