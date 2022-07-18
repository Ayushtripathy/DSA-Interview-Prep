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
// T.C - O(N)  S.C - O(1)
int myAtoi(string s){
    if(s.length() == 0) return 0;
    //Skip leading whitespaces
    int i=0;
    while(i < s.length() && s[i] == ' ') i++;
        
    s = s.substr(i);//Modify the input string
        
    int sign = +1;//Decides the sign of int
    long ans = 0;
        
    //If there is a negative sign in front
    if(s[0] == '-') sign = -1;
        
    int MAX = INT_MAX, MIN = INT_MIN;//Ques says to trim the ans
        
    //Determine the index from where to start -> 0 if no sign else 1
    i = (s[0] == '+' || s[0] == '-') ? 1 : 0;
        
    while(i < s.length()){
        if(s[0] == ' ' || !isdigit(s[i])) break;
        //Convert to int and manage the digit places
        ans = (ans*10 + (s[i] - '0'));
            
        //If out of bounds then return the max limits;
        if(sign == -1 && sign*ans < MIN) return MIN;
        if(sign == 1 && sign*ans > MAX) return MAX;
            
        i++;//Move i forward
    }
    return (int)(sign*ans);
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


// Knuth-Morris-Pratt Algorithm
//T.C - O(N + M)  S.C - O()
vector<int> lps(string p , int n){
    vector<int>pi(n,0);
    //Start from 1st idx as pi[0] = 0
    for(int i=1;i<n;i++){
        int j = pi[i-1];//Abtk kitne match kr lie the

        //Agr match ni hua to aur piche ja ke dekho
        while(j > 0 && s[i] != s[j]) j = pi[j-1];

        if(s[i] == s[j]) j++;//Char matches so increment j

        pi[i] = j;//Kitne match hue
    }
    return pi;
}
bool findPattern(string p, string s){
    int n = s.size();
    int m = p.size();

    vector<int>pi = lps(p,m);//Compute the lps table

    int i = 0;
    int j = 0;

    while(i < n){
        if(s[i] == p[j]){//Char matches
            i++;//Increment both
            j++;
        }
        //Pattern is exhausted so match found
        if(j >= m) return true;
        //str is not exhausted and the char don't match
        else if(i < n && s[i] != p[j]){
            if(j != 0) j = pi[j-1];//return to the prev repeated prefix in table
            else i++;
        }
    }
    return false;//No match found
}


// Count and Say
// T.C - O(N^2)  S.C - O(1)
string countAndSay(int n) {
    //Base cases
    if(n == 1) return "1";
    if(n == 2) return "11";

    string s = "11";//It's the ans string

    for(int i=3;i<=n;i++){
        string t = "";//Stores the curr iteration val
        s += '$';//Add delimiter(to count to last num)
        int count = 1;//At least 1 count will be there of num
        //s length will keep increasing
        for(int j=1;j<s.length();j++){
            if(s[j] != s[j-1]){
                t += to_string(count);//Count of num
                t += s[j-1];//Say the num
                count = 1;//Reset the count for new num
            }
            else count++;//Char is repeated so increment count
        }
        s = t;//Use s to calculate for next iteration
    }
    return s;
}