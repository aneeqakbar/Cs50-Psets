#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// Defines bool type
typedef enum
{
    false,
    true
} bool;

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Array of candidates
char *candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool circleChecker(int winner, int loser);
void print_winner(void);

// Utilities
bool stringcmp(char str1[], char str2[]);
int strlen(char string[]);
char *caseInsensitive(char string[]);

// Main code starts here
int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("\033[0;33m \bNumber of voters:\033[0m ");
    scanf("%i", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[30];
            printf("\033[0;34m \bRank %i:\033[0m ", j + 1);
            scanf("%s", &name);

            if (!vote(j, name, ranks))
            {
                printf("\033[1;31m \bInvalid vote.\033[0m\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, char *name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (stringcmp(caseInsensitive(name), caseInsensitive(candidates[i])))
        {
            // i is the index of candidate whos name is matched
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int rankedOverOthers[candidate_count]; //index of candidates which r greater than the candidate selected
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == ranks[j])
            {
                int g = 0;
                for (int k = j; k >= 0; k--)
                {
                    rankedOverOthers[g] = ranks[k];
                    g++;
                }
                break;
            }
        }
        //done getting index greater than candidate
        for (int h = 0; h < candidate_count; h++)
        {
            int match = 0;
            for (int v = 0; v < candidate_count; v++)
            {
                if (rankedOverOthers[v] == h)
                {
                    match++;
                }
            }
            if (match == 0)
            {
                preferences[i][h] += 1;
            }
            //print prefrences grid
            //printf("%i-", preferences[i][h]);
        }
        //printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int mainCandidate = preferences[i][j];
            int candidateToCmp = preferences[j][i];
            int product = mainCandidate - candidateToCmp;
            if (product > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
                // printf("difference--%i\n", mainCandidate - candidateToCmp);
            }
        }
    }
    //print unsorted pairs
    //     for (int i = 0; i < pair_count; i++)
    //     {
    //         printf("Winner:%i\n", pairs[i].winner);
    //         printf("Loser:%i\n", pairs[i].loser);
    //         printf("---------------\n");
    //     }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int pairInfo[pair_count][2]; // Stores index and Margin through which a pair win between each other;
    //make pairInfo
    for (int i = 0; i < pair_count; i++)
    {
        int mainCandidate = preferences[pairs[i].winner][pairs[i].loser];
        int candidateToCmp = preferences[pairs[i].loser][pairs[i].winner];

        pairInfo[i][0] = i;                              // index of pair
        pairInfo[i][1] = mainCandidate - candidateToCmp; // win margin
    }
    // sort PairInfo in respect to win margin
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (pairInfo[i][1] < pairInfo[j][1])
            {
                int temp[1][2];
                temp[0][0] = pairInfo[i][0];
                temp[0][1] = pairInfo[i][1];

                pairInfo[i][0] = pairInfo[j][0];
                pairInfo[i][1] = pairInfo[j][1];

                pairInfo[j][0] = temp[0][0];
                pairInfo[j][1] = temp[0][1];
            }
        }
    }
    pair pairSorted[MAX * (MAX - 1) / 2]; // Duplicate of pairs
    // add Pairs data into pairSorted in decending order using pairInfo
    for (int i = 0; i < pair_count; i++)
    {
        pairSorted[i].winner = pairs[pairInfo[i][0]].winner;
        pairSorted[i].loser = pairs[pairInfo[i][0]].loser;
    }
    // replace pairs with pairsSorted which is in decending order
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = pairSorted[i].winner;
        pairs[i].loser = pairSorted[i].loser;
    }
    // In this way we will get pairs sorted in decending order
        // print sorted winner and loser
    // for (int i = 0; i < pair_count; i++)
    // {
    //     int mainCandidate = preferences[pairs[i].winner][pairs[i].loser];
    //     int candidateToCmp = preferences[pairs[i].loser][pairs[i].winner];

    //     printf("Winner:%i\n", pairs[i].winner);
    //     printf("Loser:%i\n", pairs[i].loser);
    //     printf("difference--%i\n", mainCandidate - candidateToCmp);
    //     printf("---------------\n");
    // }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Check for circle and if there is no circle it will set locked pair to true
        if (!circleChecker(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    //Print locked grid
    //     for (int i = 0; i < candidate_count; i++)
    //     {
    //         for (int j = 0; j < candidate_count; j++)
    //         {
    //             printf("%i-", locked[i][j]);
    //         }
    //         printf("\n");
    //     }
    //     printf("!!!!!!!!!!!!Locked!!!!!!!!!!!!!\n");
    return;
}

//circle Checker function,Checks for circle
bool circleChecker(int winner, int loser)
{
    //if loser from bottom is beaten by this loser then return true
    if (loser == winner)
    {
        return true;
    }
    // check if loser have beaten winner at any point
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            // recursion effect here
            if (circleChecker(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool pointed = false;
        for (int j = 0; j < candidate_count; j++)
        {
            // if there is not pointer to [i]. "i is not beaten by anyone"
            if (locked[j][i]) // this will be true if i is beaten by someone else will return false
            {
                pointed = true;
            }
        }
        if (pointed == false) // if pointer is still false after the check then system will consider i as winner.
        {
            printf("\033[1;32m \bWinner: %s\033[0m\n", candidates[i]); // print name of candidate
            return;
        }
    }
    printf("No Winner\n"); // In any case if there's no winner then print "No winner"
    return;
}

// Utilities

bool stringcmp(char str1[], char str2[])
{
    bool r;
    int i = 0;
    while (str1[i] == str2[i])
    {
        if (str1[i] == '\000' || str2[i] == '\000')
        {
            break;
        }
        i++;
    }
    (str1[i] == '\000' && str2[i] == '\000') ? (r = true) : (r = false);

    return r;
}

int strlen(char string[])
{
    int i = 0;
    while (string[i] != '\000')
    {
        i++;
    }
    return i + 1;
}

char *caseInsensitive(char string[])
{
    int lenght = strlen(string);
    for (int i = 0; i < lenght; i++)
    {
        int letter = string[i];
        if (letter >= 97 && letter <= 122)
        {
            letter -= 32;
        }
        string[i] = letter;
    }
    return string;
}