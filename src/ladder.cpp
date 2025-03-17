#include "ladder.h"
#include <cstdlib>
#include <cctype>
#include <algorithm>

void error(string word1, string word2, string msg){
    cout << msg << "words: " << word1 << ", " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length();
    int len2 = str2.length();

    if (abs(len1 - len2) > d) {
        return false;
    }

    int i = 0, j = 0;
    int differences = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            differences++;
            if (differences > d) {
                return false;
            }

            if (len1 > len2) {
                i++;
            } else if (len1 < len2) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }

    while (i < len1) {
        differences++;
        i++;
    }

    while (j < len2) {
        differences++;
        j++;
    }

    return differences <= d;
}


bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push(vector<string>{begin_word});
    set<string> visited;
    string lower_begin = begin_word;
    transform(lower_begin.begin(), lower_begin.end(), lower_begin.begin(), ::tolower);
    visited.insert(lower_begin);

    string lower_end = end_word;
    transform(lower_end.begin(), lower_end.end(), lower_end.begin(), ::tolower);

    //checks to see if first and last are the same
    if(lower_begin == lower_end) return vector<string>{};

    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        transform(last_word.begin(), last_word.end(), last_word.begin(), ::tolower);

        for(auto word: word_list){
            string lower_word = word;
            transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);

            if (is_adjacent(last_word, lower_word)){
                if (visited.find(lower_word) == visited.end()){
                    visited.insert(lower_word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(lower_word == lower_end) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    error(begin_word, end_word, "No ladder found!");
    return vector<string>{};
}

void load_words(set<string> & word_list, const string& file_name){
    string word;
    ifstream in(file_name);
    if (!in) {
        error("", "", "unable to find input file");
        return;
    }
    while(in >> word){
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    for(auto word: ladder){
        cout << "Word ladder found: " << word << " ";
    }
    cout << endl;
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "./src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
