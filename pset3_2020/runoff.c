#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
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
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
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
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
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
bool vote(int voter, int rank, string name)
{
    // TODO
    //let's make a loop, so we can iterate all voters choices
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name)  == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    //First, need to check if the candidate is eliminated
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // we need two loops - one for every voter, second one for everytime we need to use another rank, if the candidate was eliminated
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                // BREAK! we need break out of the loop if this "if" happened
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // let's count half + 1 of the votes
    //(Notice: in c, when you divide int, you get whole numbers)
    // or I could just do coter_count/2 and then in the if statement votes should be > more than half, not more or even >=.
    int half_counts = (voter_count / 2) + 1;

    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[i].votes >= half_counts)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    // the MAX_VOTERS is the biggest number one candidate can have. Which means, we can iterate and find the min smaller than the max
    int min = MAX_VOTERS;

    for (int i = 0; i < candidate_count; i++)
    {
        // count minimum just for candidates, who are still in the race
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes <= min)
            {
                min = candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    //the tie could happen only if more than one candidate have the min a
    //nop. a tie happens only when all of the remaining candidates has the same amount of votes
    int tie_candidates = 0;
    int remaining_candidates = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        //count remaining candidates
        if (candidates[i].eliminated == false)
        {
            remaining_candidates++;
        }

        //check how many candidates has the minimum votes
        if (min == candidates[i].votes)
        {
            tie_candidates++;
        }
    }

    //if the remaining candidates count and the ones having a tie is the same number, it's a tie
    if (tie_candidates == remaining_candidates)
    {
        return true;
    }
    //printf("%d\n", tie_candidates);
    //printf("its a tie?");

    // okay, I don't know if this is correct. it might not be, as in theory i should find if every candidate is in the tie, but let's make eliminate function and then come back.
    // as this might work and might not work
    //yep, it should return true only if all candidates has the same votes

    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            if (candidates[i].eliminated == false)
            {
                candidates[i].eliminated = true;
                printf("%s\n", candidates[i].name);
            }
        }
    }

    return;
}
