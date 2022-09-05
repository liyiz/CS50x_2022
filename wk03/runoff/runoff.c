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

    // get array index of candidates based on name
    // where in candidates[n]? That's the value to put into preferences[voter][n]
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // printf("%s\n", candidates[i].name);
        int nameCheck = strcmp(name, candidates[i].name);
        // printf("%i\n", nameCheck);
        if (nameCheck == 0)
        {
            //i is the array index of the candidate
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // for each voter...
    for (int i = 0, n = voter_count; i < n; i++)
    {
        // i is the index for each voter.
        // j is for each voter's ranking of candidates
        // for each voter ranking...
        for (int j = 0, c = candidate_count; j < c; j++)
        {
            // printf("%i\n",preferences[i][j]);
            // identify and store the candidate's name via the int in preferences array
            int candidateArrInd = preferences[i][j];
            bool curCandidateStatus = candidates[candidateArrInd].eliminated;
            // check if candidate has been eliminated
            if (!curCandidateStatus)
            {
                candidates[candidateArrInd].votes++;
                // kick out of current loop (of voter's rankings)
                j = c;
            }
        }

    }

    // check if candidate is eliminated or not
    // if not eliminated, add count to votes
    // if eliminated pass vote to next candidate in voter's rankings
    // check if that candidate is eliminated or not

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // define the majority
    // remember integer tomfoolery
    int majority = (voter_count / 2) + 1;
    // printf("votes needed to win: %i\n", majority);

    // cycle through each candidate's vote counts and check for majority win
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // if there's no majority
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // arbitrarily start on the max possible votes
    int leastVotes = voter_count;

    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // but 0 means they're eliminated too?
        // so check if they're eliminated
        if (candidates[i].eliminated == false)
        {
            // check if the votes of current candidate is less than leastVotes
            if (candidates[i].votes < leastVotes)
            {
                leastVotes = candidates[i].votes;
            }
        }
    }
    // after looping through all candidates return the lowest votes
    // printf("least number of votes: %i\n", leastVotes);
    return leastVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // count candidates with min
    int candidatesWithMin = 0;
    int candidatesElim = 0;
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // check if they're eliminated
        if (candidates[i].eliminated == false)
        {
            // check if the votes of current candidate is less than leastVotes
            if (candidates[i].votes == min)
            {
                candidatesWithMin++;
            }
        }
        else
        {
            candidatesElim++;
        }
    }

    int elimsCheck = candidatesWithMin + candidatesElim;

    if (candidatesWithMin >= 2 && elimsCheck == candidate_count)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // check if they're eliminated
        if (candidates[i].eliminated == false)
        {
            // check if the votes of current candidate is less than leastVotes
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}