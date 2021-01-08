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
    // Iteração sobre o numero de candidatos existentes
    for (int h = 0; h < candidate_count; h++)
    {
        /* condicional para checar se a variável string name é igual a característica .name do candidate
        o qual está organizado dentro do array candidates*/
        if(strcmp(candidates[h].name, name) == 0)
        {
            /*caso a condicional for atendida o número que representa o nome do candidato
            dentro de candidate_count é atribuida ao rank da iteração*/
            preferences[voter][rank] = h;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    for (int b = 0; b < voter_count; b++)
    {
        for (int t = 0; t < candidate_count; t++)
        {
            if (candidates[t].eliminated == false && preferences[b][0] == t)
            {
                candidates[t].votes++;
                break;
            }

            else if (candidates[t].eliminated == true && preferences[b][0] == t)
            {
                bool vote_confirm = false;

                for (int q = 1; q < candidate_count; q++)
                {
                    if (vote_confirm == true)
                    {
                        break;
                    }

                    for (int j = 0; j < candidate_count; j++)
                    {
                        if (preferences[b][q] == j && candidates[j].eliminated == false)
                        {
                            candidates[j].votes++;
                            vote_confirm = true;
                            break;
                        }
                    }
                }
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
        if (candidates[i].eliminated == false && candidates[i].votes * 2 > voter_count)
        {
            printf("O vencedor dessa eleição foi %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false )
        {
            min = candidates[i].votes;
            break;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false && candidates[j].votes < min)
        {
            min = candidates[j].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int validos = 0;
    int ind = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if ( candidates[i].eliminated == false)
        {
            validos++;
        }
    }

    candidate possivel[validos];

    for (int t = 0; t < candidate_count; t++)
    {
        if (candidates[t].eliminated == false)
        {

            possivel[ind].name = candidates[t].name;
            possivel[ind].votes = candidates[t].votes;
            ind++;

        }
    }

    int empate = possivel[0].votes;

    for (int y = 0; y < validos; y++)
    {
        if (!(empate == possivel[y].votes))
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
