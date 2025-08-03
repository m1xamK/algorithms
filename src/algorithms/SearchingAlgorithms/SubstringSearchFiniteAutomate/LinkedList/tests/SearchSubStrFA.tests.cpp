#include "pch.h"

#define NO_OF_CHARS 256


int getNextState(std::string pat, int M, int currentState, int nextChar)
{
    if (currentState < M&& nextChar == pat[currentState])
        return currentState + 1;

    int nextState, i;

    for (nextState = currentState; nextState > 0; nextState--)
    {
        if (pat[nextState - 1] == nextChar)
        {
            for (i = 0; i < nextState - 1; i++)
                if (pat[i] != pat[currentState - nextState + 1 + i])
                    break;
            if (i == nextState - 1)
                return nextState;
        }
    }

    return 0;
}

void computeTF(std::string pat, int** TF)
{
    int patLen = pat.length();
    for (int state = 0; state <= patLen; ++state)
        for (int i = 0; i < NO_OF_CHARS; ++i)
            TF[state][i] = getNextState(pat, patLen, state, i);
}

std::vector<int> search(std::string pat, std::string txt)
{
    std::vector<int> res;
    const int patLen = pat.length();
    const int txtLen = txt.length();

    int** TF = new int* [patLen + 1];
    for (int i = 0; i < patLen + 1; ++i)
        TF[i]=new int[NO_OF_CHARS];
    computeTF(pat, TF);

    int state = 0;
    for (int i = 0; i < txtLen; i++)
    {
        state = TF[state][txt[i]];
        if (state == patLen)
        {
            std::cout << " Pattern found at index " << i - patLen + 1 << std::endl;
            res.push_back(i - patLen + 1);
        }
    }

    return res;
}
