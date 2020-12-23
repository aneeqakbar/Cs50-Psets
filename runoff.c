#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef enum
{
    false,
    true
} bool;

// Candidates have name, vote count, eliminated status
typedef struct
{
    char *name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[10];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Utilities
int stringlen(char *string);
bool stringcmp(char *string,char *string2);
char *tolower(char string[]);

// Function prototypes
bool vote(int voter, int rank, char *name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = tolower(argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %i: ", j + 1);
            char *name;
            scanf("%s", name);
            // Record vote, unless it's invalid
            if (!vote(i, j, tolower(name)))
            {
                printf("\033[0;31m \bInvalid vote.\033[0m\n");
                // return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            printf("\033[0;33m \bTied between: \033[0m");
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s ", candidates[i].name);
                }
            }
            printf("\n");
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);
        
        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (!stringcmp(candidates[i].name, name))
            {
                preferences[voter][rank] = 9;
                candidates[9].eliminated = true;
                candidates[9].name = "default";
                candidates[9].votes = 0;
            }
            else
            {
                preferences[voter][rank] = i;
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // printf("%i\n",voter_count);
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        int times = 0;
        while (times < candidate_count)
        {
            times++;
            int count = preferences[i][j];
            j++;
            if (!candidates[count].eliminated)
            {
                candidates[count].votes += 1;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        float remainder = ((float)candidates[i].votes / (float)voter_count);
        if (remainder >= 0.5)
        {
            printf("\033[0;32m \b%s\n\033[0m",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_vote = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min_vote)
        {
            min_vote = candidates[i].votes;
        }
    }    
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool not_tie = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes != min)
            {
                not_tie = true;
            }   
        }
    }
    if (!not_tie)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;   
            }
        }
    }
    return;
}

// Utilities

bool stringcmp(char *string, char *string2)
{
    int i = 0;
    bool r;
    while (string[i] == string2[i])
    {
        if (string[i] == '\0' || string2[i] == '\0')
        {
            break;
        }
        i++;
    }
    (string[i] == '\0' && string2[i] == '\0') ? (r = true) : (r = false);
    return r;
}

int stringlen(char *string)
{
    int i = 0;
    while (string[i] != '\000')
    {
        i++;
    }
    return i + 1;
}

char *tolower(char string[]){
    int lenght = stringlen(string);
    for (int i = 0; i < lenght; i++)
    {
        char letter = string[i];
        if (letter >= 65 && letter <= 90)
        {
            letter += 32;
            string[i] = letter;
        }
    }
    return string;
}
