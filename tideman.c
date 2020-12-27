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
void print_winner(void);
// Utilities
bool stringcmp(char str1[], char str2[]);

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
    printf("Number of voters: ");
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
            printf("Rank %i: ", j + 1);
            scanf("%s", &name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
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
        if (stringcmp(name, candidates[i]))
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
            printf("%i-", preferences[i][h]);
        }
        printf("\n");
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
            if (j != i)
            {
                if (mainCandidate != candidateToCmp)
                {
                    if (mainCandidate > candidateToCmp)
                    {
                        pairs[pair_count].winner = i;
                        pairs[pair_count].loser = j;
                        printf("difference--%i\n",mainCandidate - candidateToCmp);
                        pair_count++;
                    }
                    // else if (candidateToCmp > mainCandidate)
                    // {
                    //     pairs[pair_count].winner = j;
                    //     pairs[pair_count].loser = i;
                    // }
                    // pair_count++;
                }
            }
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner:%i\n", pairs[i].winner);
        printf("Loser:%i\n", pairs[i].loser);
        printf("---------------\n");
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int pairInfo[pair_count][2];
    for (int i = 0; i < pair_count; i++)
    {
        int mainCandidate = preferences[pairs[i].winner][pairs[i].loser];
        int candidateToCmp = preferences[pairs[i].loser][pairs[i].winner];

        pairInfo[i][0] = i;
        pairInfo[i][1] = mainCandidate - candidateToCmp;
    }
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (pairInfo[i][1] > pairInfo[j][1])
            {
                int temp[2] = {pairInfo[i][0], pairInfo[i][1]};
                pairInfo[i][0] = pairInfo[j][0];
                pairInfo[i][1] = pairInfo[j][1];

                pairInfo[j][0] = temp[0];
                pairInfo[j][1] = temp[1];
            }
        }
        printf("PairInfo[0]:%i\nPairInfo[1]:%i\n", pairInfo[i][0], pairInfo[i][1]);
        printf("00---------------00\n");
    }
    pair tem[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        tem[i].winner = pairs[i].winner;
        tem[i].loser = pairs[i].loser;

        pairs[i].winner = pairs[pairInfo[i][0]].winner;
        pairs[i].loser = pairs[pairInfo[i][0]].loser;

        pairs[pairInfo[i][0]].winner = tem[i].winner;
        pairs[pairInfo[i][0]].loser = tem[i].loser;
    }
    for (int i = 0; i < pair_count; i++)
    {
        int mainCandidate = preferences[pairs[i].winner][pairs[i].loser];
        int candidateToCmp = preferences[pairs[i].loser][pairs[i].winner];

        printf("winner:%i\nloser:%i\n", pairs[i].winner, pairs[i].loser);
        printf("difference--%i\n",mainCandidate - candidateToCmp);
        printf("----------------------------\n");
    }
    printf("%i\n", pair_count);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

// Utilities

bool stringcmp(char str1[], char str2[])
{
    int i = 0;
    while (str1[i] == str2[i])
    {
        if (str1[i] == '\000' || str2[i] == '\000')
        {
            break;
        }
        i++;
    }
    if (str1[i] == '\000' && str2[i] == '\000')
    {
        return true;
    }
    return false;
}