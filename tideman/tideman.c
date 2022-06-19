#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
int pair_weight(int index);
void sort_pairs(void);
bool is_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
bool vote(int rank, string name, int ranks[])
{
    // TODO

    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Record rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO

    // Loop over all ranks (row)
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop over all candidates (column), exclude self
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Return the number of voters who prefer candidate i over candidate j in prefrences[i][j] by checking pair.
int pair_weight(int index)
{
    int w = pairs[index].winner;
    int l = pairs[index].loser;
    return preferences[w][l];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    // Search the unsorted part of the data to find the largest vale
    // Loop over all pairs
    for (int i = 0; i < pair_count; i++)
    {
        // largest value
        int max_w = pair_weight(i);

        // Index
        int max_i = i;

        // Loop over all candidates (Before i + 1 => unsorted part)
        for (int j = i + 1; j < pair_count; j++)
        {
            if (max_w < pair_weight(j))
            {
                max_w = pair_weight(j);
                max_i = j;
            }
        }
        // Swap the largest found value with the first element of the unsorted part
        pair temp = pairs[max_i];
        pairs[max_i] = pairs[i];
        pairs[i] = temp;
    }
    return;
}

// Check if it forms cycle
bool is_cycle(int winner, int loser)
{
    // Base case
    if (winner == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if loser is locked with a candidate
        if (locked[loser][i] && is_cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    // Loop over all pairs
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        if (!is_cycle(w, l))
        {
            locked[w][l] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    // Row
    for (int i = 0; i < candidate_count; i++)
    {
        // Identifier
        bool is_l = false;

        // Column
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_l = true;
                break;
            }
        }

        // No candidate wins candidate i
        if (!is_l)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
