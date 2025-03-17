#include "ladder.h"
#include <cstdlib>

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