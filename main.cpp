#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define max_n 20
#define penalti_num 10

bool is_even(int a)
{
    return (a % 2 == 0);
}

long long Cmb[max_n+1][max_n+1];

void init_cmb()
{
    //std::cout << "Combinations initialization" << std::endl;

    for(int i = 0; i <= max_n; ++i)
    {
        for(int j = 0; j <= max_n; ++j)
        {
            Cmb[i][j] = -1;
        }

        Cmb[i][1] = i;
        Cmb[i][i] = 1;
        Cmb[i][0] = 1;
    }

    //std::cout << "Combinations initialized" << std::endl;
}

long long get_cmb(int n, int k)
{
    //std::cout << "Get combinations: " << n << " " << k << std::endl;

    if(k < 0 || n < 0)
    {
        return 0;
    }

    if(k > n)
    {
        return 0;
    }

    if(k == n)
    {
        return 1;
    }

    if(k == 0)
    {
        return 1;
    }

    if(k == 1)
    {
        return n;
    }

    if(Cmb[n][k] != -1)
    {
        return Cmb[n][k];
    }
    else
    {
        return Cmb[n][k] = get_cmb(n-1, k-1) + get_cmb(n-1, k);
    }
}

double get_bernoulli_probability(int N, int K, double p)
{
    //std::cout << "Get Bernoulli probability: " << N << " " << K << " " << p << std::endl;

    if(N < 0 || K < 0 || p < 0)
    {
        return 0;
    }

    if(N < K)
    {
        return 0.0;
    }

    return get_cmb(N, K) * std::pow(p, K) * std::pow(1.0 - p, N - K);
}

int get_a_penalti(int N)
{
    if(is_even(N))
    {
        return N/2;
    }
    else
    {
        return N/2+1;
    }
}

int get_b_penalti(int N)
{
    return N/2;
}

int get_a_remaining_penalti(int N)
{
    return penalti_num/2 - get_a_penalti(N);
}

int get_b_remaining_penalti(int N)
{
    return penalti_num/2 - get_b_penalti(N);
}

double get_score_probability_first_10_hits(int N, int current_Sa, int current_Sb, int Sa, int Sb, double Pa, double Pb)
{
    //std::cout << "Get score probability first 10 hits" << std::endl;

    int Ka = Sa - current_Sa;
    int Kb = Sb - current_Sb;

    int Na = get_a_remaining_penalti(N);
    int Nb = get_b_remaining_penalti(N);

    if(Ka < 0 || Kb < 0 || Na < 0 || Nb < 0)
    {
        return 0;
    }

    if(Ka > Na || Kb > Nb)
    {
        return 0;
    }

    return get_bernoulli_probability(Na, Ka, Pa) * get_bernoulli_probability(Nb, Kb, Pb);
}

double get_draw_probability_first_10_hits(int N, int Sa, int Sb, double Pa, double Pb)
{
    //std::cout << "Get draw probability first 10 hits" << std::endl;

    double p = 0.0;
    for(int i = 0; i <= 5; ++i)
    {
        p += get_score_probability_first_10_hits(N, Sa, Sb, i, i, Pa, Pb);
    }

    return p;
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

    //std::cout << "Before combinations initialization" << std::endl;

    init_cmb();

    //std::cout << "After combinations initialization" << std::endl;

    double probability_draw_10_hits = get_draw_probability_first_10_hits(N, Sa, Sb, Pa, Pb);

    //std::cout << "Draw probability first 10 hits: " << probability_draw_10_hits << std::endl;

    //std::cout << "Calculate probability of win in first 10 hits" << std::endl;

    for(int current_Sa = 1; current_Sa <= penalti_num/2; ++current_Sa)
    {
        for(int current_Sb = 0; current_Sb < current_Sa; ++current_Sb)
        {
            probability_A_wins += get_score_probability_first_10_hits(N, Sa, Sb, current_Sa, current_Sb, Pa, Pb);
        }
    }
    double probability_draw = probability_draw_10_hits;

    for(int i = 0; i < 100000; ++i)
    {
        double prev_draw_probability = probability_draw;
        probability_draw = probability_draw * (Pa * Pb + (1.0 - Pa) * (1.0 - Pb));
        probability_A_wins += prev_draw_probability * Pa * (1.0 - Pb);
    }

    std::cout << "Probability A wins: " << probability_A_wins << std::endl;

    return 0;
}
