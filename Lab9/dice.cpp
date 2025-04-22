#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class DICE {
public:
    DICE() {
        srand(time(nullptr));
    }

    int roll_one_dice(double upper_bound, const vector<int>& unavailable_numbers = {}) {
        if (upper_bound < 1) {
            cout << "Error: upper_bound must be at least 1." << endl;
            return -1;
        }

        int max = static_cast<int>(upper_bound);
        
        vector<int> available_numbers;
        for (int i = 1; i <= max; i++) {
            bool is_available = true;
            for (int unavailable : unavailable_numbers) {
                if (i == unavailable) {
                    is_available = false;
                    break;
                }
            }
            
            if (is_available) {
                available_numbers.push_back(i);
            }
        }
        
        if (available_numbers.empty()) {
            cout << "Error: No available numbers to roll." << endl;
            return -1;
        }
        
        int random_index = rand() % available_numbers.size();
        return available_numbers[random_index];
    }

    vector<int> roll_play_order(int num_players) {
        if (num_players <= 0) {
            cout << "Error: Number of players must be positive." << endl;
            return {};
        }
        
        int upper_bound = 100;
        if (num_players * 2 > upper_bound) {
            upper_bound = num_players * 2;
        }
        
        vector<int> player_rolls(num_players);
        vector<int> used_numbers;
        
        for (int i = 0; i < num_players; i++) {
            int roll = roll_one_dice(upper_bound, used_numbers);
            player_rolls[i] = roll;
            used_numbers.push_back(roll);
        }
        
        vector<int> player_order(num_players);
        for (int i = 0; i < num_players; i++) {
            player_order[i] = i;
        }
        
        for (int i = 0; i < num_players; i++) {
            for (int j = i + 1; j < num_players; j++) {
                if (player_rolls[player_order[i]] < player_rolls[player_order[j]]) {
                    int temp = player_order[i];
                    player_order[i] = player_order[j];
                    player_order[j] = temp;
                }
            }
        }
        
        return player_order;
    }
};