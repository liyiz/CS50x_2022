#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // check name against existing names
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // printf("Candidate check: %s\n", candidates[i].name);
        // check if current candidate name matches input candidate name
        if (strcmp(name, candidates[i].name) == 0)
        {
            // increase vote count to the matching candidate
            candidates[i].votes++;
            return true;
        }
        // printf("%s has %i votes\n", candidates[i].name, candidates[i].votes);
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort candidates in order based on the number of votes they have

    int j = 0;
    // repeat for n-1 times
    while (j < candidate_count)
    {
        // cycle through all candidates comparing votes and sort
        for (int i = 0, n = candidate_count; i < n ; i++)
        {
            if (candidates[i + 1].votes < candidates[i].votes)
            {
                // save candidate from array in temp variables
                candidate swapLeft = candidates[i + 1];
                candidate swapRight = candidates[i];
                // swap candidate index positions in array
                candidates[i] = swapLeft;
                candidates[i + 1] = swapRight;
            }
        }
        j++;
    }

    // assume last indexed candidate is current winner because of bubble sort
    candidate currentWinner = candidates[candidate_count];
    // keep count of any tied candidates;
    int extraWinners = 0;
    // go through the candidates array again, but this time checking for ties
    for (int i = candidate_count; i > 0 ; i--)
    {
        if (currentWinner.votes == candidates[i].votes)
        {
            extraWinners++;
        }
        else
        {
            // kick out of this current loop if no one with tied result
            i = 0;
        }
    }

    for (int i = 0, n = extraWinners; i < n; i++)
    {
        printf("%s\n", candidates[candidate_count - i].name);
    }
    // printf("current winner: %s\n", candidates[candidate_count].name);
    return;
}