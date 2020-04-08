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
void sort_pairs(void);
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
        //it's a empty array for now

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
    //TODO
        for (int i = 0; i < candidate_count; i++)
        {
            if (strcmp(name, candidates[i])  == 0)
            {
                //ranks[i]++;
                // I might be stupid. int ranks[candidate_count] declares an array with the size of candidate count.
                // so if the preference is charlie, alice, bob, the ranks[] array suppose to be like this - ranks[2,0,1]
                // alright, so i is the index of candidate and rank is rank, so we need to put some numbers in array:
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = (i + 1); j < candidate_count; j++)
        {
                preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
    // these 3lines took me 4hours to figure it out. amazing.
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = (i + 1); j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {           
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

            if (preferences[j][i] > preferences[i][j])
            {           
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;             
                pair_count++;
            }
        }
    }
    
    return;
}

// I need new swap function for sorting
void swap(pair *xp, pair *yp)
{
    pair temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    
    // sort by selection sort.
    // TODO
    int max = 0;
    int max_index = 0;

    // i for every pair[i]
    for (int i = 0; i < pair_count; i++)
    {
        //j for every preferences[pairs[j].winner][pairs[j].loser]
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > max)
            {
                max = preferences[pairs[j].winner][pairs[j].loser];
                //those max index is the same as j.
                max_index = j;
            }
        }

        // swap from previous function
        swap(&pairs[max_index], &pairs[i]);
        // you need to degrade max to zero, as the loop with the j is not having the largest element anymore, because it's used already.
        max = 0;

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //wrong approach:
    for (int i = 0; i < pair_count; i++)
    {
        if (i == (pair_count - 1))
        {
            for (int j = 0; j < pair_count; j++)
            {
                if (locked[pairs[j].winner][pairs[j].loser] == false)
                {
                    //printf("ka cia turim? :D ");
                    locked[pairs[i].winner][pairs[i].loser] = true;
                    //printf("last pairs' edge: %d winner over %d loser, locked - %d\n", pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser]);
                }
            }
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //printf("%d winner over %d loser, locked - %d\n", pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser]);
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

