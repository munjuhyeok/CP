#include <iostream>
#include <string>
#include <utility>
#include <set>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <numeric>

/* =======START OF PRIME-RELATED HELPERS======= */
/*
 * The code snippet below AS A WHOLE does the primality
 * test and integer factorization. Feel free to move the
 * code to somewhere more appropriate to get your codes
 * more structured.
 *
 * You don't have to understand the implementation of it.
 * But if you're curious, refer to the sieve of Eratosthenes
 *
 * If you want to just use it, use the following 2 functions.
 *
 * 1) bool is_prime(int num):
 *     * `num` should satisfy 1 <= num <= 999999
 *     - returns true if `num` is a prime number
 *     - returns false otherwise (1 is not a prime number)
 *
 * 2) std::multiset<int> factorize(int num):
 *     * `num` should satisfy 1 <= num <= 999999
 *     - returns the result of factorization of `num`
 *         ex ) num = 24 --> result = { 2, 2, 2, 3 }
 *     - if `num` is 1, it returns { 1 }
 */

const int PRIME_TEST_LIMIT = 999999;
int sieve_of_eratosthenes[PRIME_TEST_LIMIT + 1];
bool sieve_calculated = false;

void make_sieve() {
    sieve_of_eratosthenes[0] = -1;
    sieve_of_eratosthenes[1] = -1;
    for(int i=2; i<=PRIME_TEST_LIMIT; i++) {
        sieve_of_eratosthenes[i] = i;
    }
    for(int i=2; i*i<=PRIME_TEST_LIMIT; i++) {
        if(sieve_of_eratosthenes[i] == i) {
            for(int j=i*i; j<=PRIME_TEST_LIMIT; j+=i) {
                sieve_of_eratosthenes[j] = i;
            }
        }
    }
    sieve_calculated = true;
}

bool is_prime(int num) {
    if (!sieve_calculated) {
        make_sieve();
    }
    return sieve_of_eratosthenes[num] == num;
}

std::multiset<int> factorize(int num) {
    if (!sieve_calculated) {
        make_sieve();
    }
    std::multiset<int> result;
    while(num > 1) {
        result.insert(sieve_of_eratosthenes[num]);
        num /= sieve_of_eratosthenes[num];
    }
    if(result.empty()) {
        result.insert(1);
    }
    return result;
}

/* =======END OF PRIME-RELATED HELPERS======= */

/* =======START OF std::string LITERALS======= */
/* Use this code snippet if you want */

const std::string MAXIMIZE_GAIN = "Maximize-Gain";
const std::string MINIMIZE_LOSS = "Minimize-Loss";
const std::string MINIMIZE_REGRET = "Minimize-Regret";

/* =======END OF std::string LITERALS======= */


/* =======START OF TODOs======= */

std::pair<int, int> number_fight(int a, int b) {
    // TODO 2-1
    std::pair<int, int> result;
    std::multiset<int> fa = factorize(a);
    std::multiset<int> fb = factorize(b);
    std::set<int> intersection;
    std::set_intersection(fa.begin(), fa.end(), fb.begin(), fb.end(), std::inserter(intersection, intersection.begin()));

    for (int i:intersection){
        a = a/i;
        b = b/i;
    }
    return std::pair<int, int>(a,b);
}

std::pair<int, int> number_vs_number(int a, int b) {
    // TODO 2-2
    // if index is 0, chooses to fight, if 1, chooses not to fight. first axis is A, second axis is B. Each element is expected outcome pair (A,B).
    std::pair<int, int> outcome[2][2];
    outcome[0][0] = number_fight(a,b);
    outcome[1][1] = std::make_pair(a,b);
    int damage_a = a - outcome[0][0].first;
    int damage_b = b - outcome[0][0].second;
    if(a%7 == 0){
        int outcome_b = std::max(1,(int)(b-floor(damage_a/2)));
        outcome[1][0] = std::make_pair(a-floor(damage_a/2), outcome_b);
    }else{
        outcome[1][0] = std::make_pair(a-damage_a, b);
    }
    if(b%7 == 0){
        int outcome_a = std::max(1,(int)(a-floor(damage_b/2)));
        outcome[0][1] = std::make_pair(outcome_a, b-floor(damage_b/2));
    }else{
        outcome[0][1] = std::make_pair(a, b-damage_b);
    }

    bool a_will_fight;
    bool a_will_fight1 = outcome[0][0].first >= outcome[1][0].first; //when b chooses to fight
    bool a_will_fight2 = outcome[0][1].first >= outcome[1][1].first; //when b chooses not to fight
    if(a_will_fight1 && a_will_fight2){
        a_will_fight = true;
    }else if(!a_will_fight1 && !a_will_fight2){
        a_will_fight = false;
    }else if(a<b){
        a_will_fight = true;
    }else{
        a_will_fight = false;
    }

    bool b_will_fight;
    bool b_will_fight1 = outcome[0][0].second >= outcome[0][1].second;
    bool b_will_fight2 = outcome[1][0].second >= outcome[1][1].second;
    if(b_will_fight1 && b_will_fight2){
        b_will_fight = true;
    }else if(!b_will_fight1 && !b_will_fight2){
        b_will_fight = false;
    }else if(a>b){
        b_will_fight = true;
    }else{
        b_will_fight = false;
    }
    int index_a = a_will_fight?0:1;
    int index_b = b_will_fight?0:1;
    return outcome[index_a][index_b];
}

std::pair<std::multiset<int>, std::multiset<int>> player_battle(
    std::string type_a, std::multiset<int> a, std::string type_b, std::multiset<int> b
) {
    // TODO 2-3
    int n = a.size();
    int m = b.size();

    //numbers A and B have
    std::vector<int> a_vector(a.begin(), a.end());
    std::vector<int> b_vector(b.begin(), b.end());

    std::vector<int> max_loss_a(n,0);
    std::vector<int> min_loss_a(n,PRIME_TEST_LIMIT);
    std::vector<int> max_loss_b(m,0);
    std::vector<int> min_loss_b(m,PRIME_TEST_LIMIT);

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            std::pair<int,int> outcome = number_vs_number(a_vector[i],b_vector[j]);
            int loss_a = a_vector[i] - outcome.first;
            int loss_b = b_vector[j] - outcome.second;
            max_loss_a[i] = std::max(max_loss_a[i],loss_a);
            min_loss_a[i] = std::min(min_loss_a[i],loss_a);
            max_loss_b[j] = std::max(max_loss_b[j],loss_b);
            min_loss_b[j] = std::min(min_loss_b[j],loss_b);
        }
    }

    std::vector<int> max_regret_a(n,-PRIME_TEST_LIMIT);
    std::vector<int> max_regret_b(m,-PRIME_TEST_LIMIT);
    for(int i = 0; i<n; i++){
        std::vector<int> min_loss_except_ith_element = min_loss_a;
        min_loss_except_ith_element.erase(min_loss_except_ith_element.begin()+i);
        max_regret_a[i] = max_loss_a[i] - *std::min_element(min_loss_except_ith_element.begin(), min_loss_except_ith_element.end());
    }
    for(int i = 0; i<m; i++){
        std::vector<int> min_loss_except_ith_element = min_loss_b;
        min_loss_except_ith_element.erase(min_loss_except_ith_element.begin()+i);
        max_regret_b[i] = max_loss_b[i] - *std::min_element(min_loss_except_ith_element.begin(), min_loss_except_ith_element.end());
    }
    // which number to choose from a_vector, b_vector
    int index_a, index_b;

    if(type_a == MAXIMIZE_GAIN) {
        index_a = std::min_element(min_loss_a.begin(),min_loss_a.end()) - min_loss_a.begin();
    }else if(type_a == MINIMIZE_LOSS){
        index_a = std::min_element(max_loss_a.begin(),max_loss_a.end()) - max_loss_a.begin();
    }else if(type_a == MINIMIZE_REGRET) {
        index_a = std::min_element(max_regret_a.begin(),max_regret_a.end()) - max_regret_a.begin();
    }

    if(type_b == MAXIMIZE_GAIN) {
        index_b = std::min_element(min_loss_b.begin(),min_loss_b.end()) - min_loss_b.begin();
    }else if(type_b == MINIMIZE_LOSS){
        index_b = std::min_element(max_loss_b.begin(),max_loss_b.end()) - max_loss_b.begin();
    }else if(type_b == MINIMIZE_REGRET) {
        index_b = std::min_element(max_regret_b.begin(),max_regret_b.end()) - max_regret_b.begin();
    }

    int num_a = a_vector[index_a];
    int num_b = b_vector[index_b];

    std::pair<int,int> outcome = number_vs_number(num_a, num_b);

    num_a = outcome.first;
    num_b = outcome.second;

    a_vector[index_a] = num_a;
    b_vector[index_b] = num_b;

    a = std::multiset<int>(a_vector.begin(), a_vector.end());
    b = std::multiset<int>(b_vector.begin(), b_vector.end());

    return std::pair<std::multiset<int>, std::multiset<int>>(a,b);
}

std::pair<std::multiset<int>, std::multiset<int>> player_vs_player(
    std::string type_a, std::multiset<int> a, std::string type_b, std::multiset<int> b
) {
    // TODO 2-4
    while (true){
        std::pair<std::multiset<int>, std::multiset<int>> outcome = player_battle(type_a,a,type_b,b);
        std::multiset<int> new_a = outcome.first;
        std::multiset<int> new_b = outcome.second;
        if(a == new_a && b == new_b){
            break;
        }
        a = new_a;
        b = new_b;
    }
    return std::pair<std::multiset<int>, std::multiset<int>>(a,b);
}

int tournament(std::vector<std::pair<std::string, std::multiset<int>>> players) {
    // TODO 2-5
    std::vector<int> survivors(players.size()); //ID of survivors, 0~players.size()
    std::iota(survivors.begin(), survivors.end(), 0);

    while(survivors.size() != 1) {
        int num_match = survivors.size() / 2;
        std::vector<int> losers;
        for (int i = 0; i < num_match; i++) {
            int id_a = survivors[2 * i];
            int id_b = survivors[2 * i + 1];

            std::string type_a = players[id_a].first;
            std::string type_b = players[id_b].first;
            std::multiset<int> a = players[id_a].second;
            std::multiset<int> b = players[id_b].second;
            std::pair<std::multiset<int>, std::multiset<int>> outcome = player_vs_player(type_a, a, type_b, b);

            std::multiset<int> new_a = outcome.first;
            std::multiset<int> new_b = outcome.second;

            int sum_a = std::accumulate(new_a.begin(), new_a.end(), 0);
            int sum_b = std::accumulate(new_b.begin(), new_b.end(), 0);

            if(sum_a<sum_b){
                losers.push_back(id_a);
            } else{
                losers.push_back(id_b);
            }
        }
        for(int id :losers){
            survivors.erase(std::remove(survivors.begin(), survivors.end(), id), survivors.end());
        }
    }
    return survivors[0];
}

int steady_winner(std::vector<std::pair<std::string, std::multiset<int>>> players) {
    // TODO 2-6
    std::vector<int> num_win(players.size()); //ID of survivors, 0~players.size()
    for(int i = 0; i<players.size(); i++){
        int winner = tournament(players);
        num_win[(winner+i)%players.size()]++;
        std::rotate(players.begin(),players.begin()+1,players.end());
    }
    return std::max_element(num_win.begin(), num_win.end()) - num_win.begin();
}

/* =======END OF TODOs======= */

/* =======START OF THE MAIN CODE======= */
/* Please do not modify the code below */

typedef std::pair<std::string, std::multiset<int>> player;

player scan_player() {
    std::multiset<int> numbers;
    std::string player_type; int size;
    std::cin >> player_type >> size;
    for(int i=0;i<size;i++) {
        int t; std::cin >> t; numbers.insert(t);
    }
    return make_pair(player_type, numbers);
}

void print_multiset(const std::multiset<int>& m) {
    for(int number : m) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

int main() {
    int question_number;
    std::cin >> question_number;
    if (question_number == 1) {
        int a, b;
        std::cin >> a >> b;
        std::tie(a, b) = number_fight(a, b);
        std::cout << a << " " << b << std::endl;
    } else if (question_number == 2) {
        int a, b;
        std::cin >> a >> b;
        std::tie(a, b) = number_vs_number(a, b);
        std::cout << a << " " << b << std::endl;
    } else if (question_number == 3 || question_number == 4) {
        auto a = scan_player();
        auto b = scan_player();
        std::multiset<int> a_, b_;
        if (question_number == 3) {
            tie(a_, b_) = player_battle(
                    a.first, a.second, b.first, b.second
            );
        } else {
            tie(a_, b_) = player_vs_player(
                    a.first, a.second, b.first, b.second
            );
        }
        print_multiset(a_);
        print_multiset(b_);
    } else if (question_number == 5 || question_number == 6) {
        int num_players;
        std::cin >> num_players;
        std::vector<player> players;
        for (int i = 0; i < num_players; i++) {
            players.push_back(scan_player());
        }
        int winner_id;
        if (question_number == 5) {
            winner_id = tournament(players);
        } else {
            winner_id = steady_winner(players);
        }
        std::cout << winner_id << std::endl;
    }
return 0;
}
/* =======END OF MAIN CODE======= */