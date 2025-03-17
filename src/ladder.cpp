#include "ladder.h"
#include <cstdlib>
#include <cctype>
#include <algorithm>

void error(string word1, string word2, string msg){
    cout << msg << "words: " << word1 << ", " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.length();
    int len2 = str2.length();

    if(abs(len1 - len2) > d) return false;
    int i = 0, j = 0;
    int differences = 0;

    while(i < len1 && j < len2){
        if(str1[i] != str2[j]){
            ++differences;
            if(differences > d) return false;

            if(len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else {++i; ++j;}
        }
        else{
            ++i;
            ++j;
        }
    }

    differences += (len1 - i) + (len2 - j);
    return differences <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push(vector<string>{begin_word});
    set<string> visited;
    string lower = begin_word;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    visited.insert(lower);

    string lower_end = end_word;
    transform(lower_end.begin(), lower_end.end(), lower_end.begin(), ::tolower);


    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        transform(last_word.begin(), last_word.end(), last_word.begin(), ::tolower);

        for(auto word: word_list){
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (is_adjacent(last_word, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == lower_end) return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    error(begin_word, end_word, "No ladder found!");
    return vector<string>{};
}