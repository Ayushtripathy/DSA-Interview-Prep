// Valid Palindrome
// T.C - O(N)  S.C - O(1)
bool isPalindrome(string s) {
    int left = 0, right = s.length()-1;
    while(left < right){
        if(!isalnum(s[left])) left++;//Not a char
        else if(!isalnum(s[right])) right--;//Not a char
        //If the chars are not equal
        else if(tolower(s[left]) != tolower(s[right])) return false;
        else {// If chars are equal
            left++;
            right--;
        }
    }
    return true;//Is palindrome
}


// Valid Anagrams
// T.C - O(N)  S.C - O(1)
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    
    int counts[26] = {0};//Store the freq of chars
    for (int i = 0; i < s.length(); i++) { 
        counts[s[i] - 'a']++;//Add the freq of str1
        counts[t[i] - 'a']--;//Remove the freq of str2
    }

    for (int i = 0; i < 26; i++){
        //Anagrams should have equal freq of chars
        if (counts[i]) return false;//Chars remain in array
    }
    return true;//Is anagram(no char remains in array)
}


// String to Integer(atoi)
// T.C - O()  S.C - O()
int myAtoi(string s){

}

// Reverse Words in a string
//T.C - O(N)  S.C - O(N)
string reverseWords(string s) {        
    vector<string> vec;
    stringstream ss(s);
    string word;
        
    while(ss >> word) vec.push_back(word);
        
    string res = "";

    for(int i=vec.size()-1;i>=0;i--) res += vec[i] + ' ';
        
    res.pop_back();
    return res;
}