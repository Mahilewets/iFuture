#include <iostream>

#define max_n 20

bool is_even(int a)
{
    return (a % 2 == 0);
}

void search_A(int N, double p, double &probability_A_wins, int Sa, int Sb, double Pa, double Pb);
void search_B(int N, double p, double &probability_A_wins, int Sa, int Sb, double Pa, double Pb);

void search(int N, double p, double &probability_A_wins, int Sa, int Sb, double Pa, double Pb)
{
    if(N > max_n)
    {
        return;
    }

    if(N >= 10 && Sa > Sb)
    {
        probability_A_wins += p;
        return;
    }

    if(is_even(N))
    {
        search_A(N, p, probability_A_wins, Sa, Sb, Pa, Pb);
    }
    else
    {
        search_B(N, p, probability_A_wins, Sa, Sb, Pa, Pb);
    }
}

void search_A(int N, double p, double &probability_A_wins, int Sa, int Sb, double Pa, double Pb)
{
    double p_goal = p * Pa, p_not_goal = p * (1.0 - Pa);
    search(N + 1, p_goal, probability_A_wins, Sa + 1, Sb, Pa, Pb);
    search(N + 1, p_not_goal, probability_A_wins, Sa, Sb, Pa, Pb);
}

void search_B(int N, double p, double &probability_A_wins, int Sa, int Sb, double Pa, double Pb)
{
    double p_goal = p * Pb, p_not_goal = p * (1.0 - Pb);
    search(N + 1, p_goal, probability_A_wins, Sa, Sb + 1, Pa, Pb);
    search(N + 1, p_not_goal, probability_A_wins, Sa, Sb, Pa, Pb);
}


int main()
{
    double Pa, Pb;
    int N, Sa, Sb;

    std::cout << "Enter Pa: " << std::endl;
    std::cin >> Pa;

    std::cout << "Enter Pb: " << std::endl;
    std::cin >> Pb;

    std::cout << "Enter N: " << std::endl;
    std::cin >> N;

    std::cout << "Enter Sa: " << std::endl;
    std::cin >> Sa;

    std::cout << "Enter Sb: " << std::endl;
    std::cin >> Sb;

    double probability_A_wins = 0.0;

    search(N, 1.0, probability_A_wins, Sa, Sb, Pa, Pb);

    std::cout << "Probability A wins: " << probability_A_wins << std::endl;

    return 0;
}
