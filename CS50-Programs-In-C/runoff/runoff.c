#include <cs50.h>
#include <stdio.h>
#include <string.h>
 
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
//Function prototypes
bool vote(int voter, int rank, char *name);
void tabulate();
bool print_winner();
int find_min();
bool is_tie(int min);
void eliminate(int min);
 
int preferences[MAX_VOTERS][MAX_CANDIDATES];
 
typedef struct
{
    char *name;
    int votes;
    bool eliminated;
}
candidate;
 
candidate candidates[MAX_CANDIDATES];
 
int voter_count;
int candidate_count;
 

 
int main(int argc, char *argv[])
{
    //Runoff Vote
    //Every voter ranks their preferences
    //if a candidate has a majority (more than half) of the ovtes,
    // they are the winner
    //otherwise, eliminate the candidate with the fewest votes
    //and re-run the election without them
 
    //Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate...]\n");
        return 1;
    }
 
    //Populate array of candidates
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
 
    //receive number of votes
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
 
    //keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        //query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            //record vote, unless it's invalid
            char *name = get_string("Rank %i: ", j + 1);
            if (!vote(i, j, name))
            {
                printf("Invalid vote\n");
            }
        }
        printf("\n");
    }
 
    // Keep holding runoffs untsil winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();
        // Check if election has been won
        if (print_winner())
        {
            break;
        }
 
        int min = find_min();
        if (is_tie(min))
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
        eliminate(min);
 
        // Eliminate last-place candidates
        // If tie, everyone wins
        // Eliminate anyone with minimum number of votes
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
    bool has_candidate = false;
    //Look for a candidate called name,
    //if candidate found, update preferences so that they are the voter's
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0) 
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
 
    //if no candidate found, dont update and return false
    return false;
}
 
// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //update vote counts for all non-eliminated candidates
    for (int i = 0; i < voter_count; i++)
    {
        //recall that each voter votes for their heighest preference
        for (int j = 0; j < candidate_count; j++)
        {
            //candidate who has not yet been eliminated.
            //only update vote who are still in the race
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }
    return;
}
 
// Print the winner of the election, if there is one
bool print_winner(void)
{
    //if any candidate has more ethan half the vote, print out their
    //their name and return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (voter_count / 2 < candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    //if nobody has won the election yet, return false
    return false;
}
 
// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //return the minimum number of votes of anyone still in the elction.
    //return candidates who has not been eliminated
    int min = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && min > candidates[i].votes)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}
 
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //accepts the minimum number of votes min as input.
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    //returns true if the election is tied between all remaining candidates
    //, and return false otherwise.
    return true;
}
 
// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    //eliminate anyone still in the race who has the min number of votes
    //if votes are the same, should eliminate two candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}


