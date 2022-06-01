// Swap Two Numbers
void swap(int a,int b){
    a = a^b;
    b = a^b;
    a = a^b;
}


// Single Number
//T.C - O(N) S.C - O(1)
int singleNumberI(vector<int>& nums) {
    int xori = 0;
    for (int el: nums) xori ^= el;
    return xori;    
}
int singleNumberII(vector<int>& nums) {       
    int ones = 0;
    int twos = 0;
        
    for ( int i : nums ) {
        ones = (ones ^ i) & (~twos);
        twos = (twos ^ i) & (~ones);
    }
    return ones;
}
pair<int,int> singleNumberIII(vector<int>& nums) {
    int xori = 0;
    //Take xor of all nums so xor of two non repeated numbers will remain
    for(auto num : nums) xori ^= num;

    int count = 0;
    while(xori){//Get rightmost different bit
        if(xor&1) break;//Bit is set
        count++;//Gives the idx of rightmost set bit
        xori = xori >> 1;
    }

    //Segregate into two sets
    xor1 = 0,xor2 = 0;
    for(auto num : nums){
        //Check if bit at idx count is set or not
        if(num &(1<<count)) xor1 ^= num;
        else xor2 ^= num;//Keep xoring in both sets and the non repeating nums will remain
    }
    return {xor1,xor2};
}


// Print XOR of N elements
//T.C - O(1)  S.C - O(1)
void printXOR(int n){
    if(n%4 == 0) cout<<n<<endl;

    if(n%4 == 1) cout<<1<<endl;

    if(n%4 == 2) cout<<n+1<<endl;

    if(n%4 == 3) cout<<0<<endl;
}


// Check whether K-th bit is set or not
bool kBitIsSet(int N,int k){
    //Shift 1 to left by k steps as we need 1 at kth pos in mask
    mask = (1 << k);
    //This mask can have both T/F depending on whether thee req bit is set or not
    bool set = mask & N;
    return set;
}

// Set the kth bit
int setKthBit(int N,int k){
    //Shift 1 to left by k steps as we need 1 at kth pos in mask
    mask = (1 << k);
    //The mask has 1 so whether bit is set or not at kth pos doesn't matter 
    N = mask | N;
    return N;

    //For clearing the kth bit
    mask = ~(1 << k);
    N = N&mask;

    //Remove last set bit
    N = N & N-1;
}


// Power of 2
bool isPowerOfTwo(int n){
    if(n<=0) return false;
    //If n is power of two then n&n-1 will give 0
    return !(n&(n-1));
}


// Reverse bits
uint32_t reverseBits(uint32_t n){
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result <<= 1;
        result |= n & 1;
        n >>= 1;
    }
    return result;
}


// Find first set bit
//T.C - O(logN)  S.C - O(1)
int positionRightmostSetbit(int n){
  int p = 1;
  // Iterate till number>0
  while(n > 0){
    // Checking if last bit is set
    if(n&1) return p;
     
    // Increment position and right shift number
    p++;
    n = n>>1;
  }
  // set bit not found.
  return -1;
}


// Count total set bits
//T.C - O(MSB)  S.C - O(1)
int countSetBits(int n){
    int count = 0;
    while(n != 0){//Until all bits are exhausted
        //This will give 1 only when bit is set
        if(n & 1 == 1) count++;//Bit is set so inc count
        n >> 1;//Shift right to check for the rest of left bits

        //n = n&n-1; Optimized O(Set bits)
    }
    return count;
}


// Count the number of bits needed to be flipped to convert A to B.
int countBitsFlip(int a, int b){
    //For ex we have a = 10 and b = 20 so a = 01010 b = 10100
    //Xor a and b which gives 11110 now just count set bits
    //Flipping the set bits will give 0 which makes a and b same
    int xor = a^b;
    return countSetBits(xor);
}


// Toggle bits given range
//T.C - O(logN)  S.C - O(1)
int toggleBits(int n,int l, int r){
    int val = 0;
    int power = 0;
    int mask = 1;//Needed to AND
    int i = 1;
    //Include all rightmost bits as it is
    while(i < l){
        if(mask&n) val += pow(2,power);
        mask <<= 1;//left shift to check with other bits
        power += 1;
        ++i;
    }
    //Toggle bits in given range and include
    while(i<=r){
        if(!(mask&n)) val += pow(2,power);//Toggling bits
        mask <<= 1;//left shift to check with other bits
        power += 1;
        ++i;
    }
    //Include all leftmost bits as it is
    while(i<=10){
        if(mask&n) val += pow(2,power);
        mask<<= 1;//left shift to check with other bits
        power += 1;
        ++i;
    }
    return val;
}


// Swap all odd and even bits
// T.C - O(1)  S.C - O(1)
int swapEvenOddBits(int n){
    int oddMask = 0x55555555;
    int evenMask = 0xAAAAAAAA;

    preserveOdd = n&oddMask;
    preserveEven = n&evenMask;

    int makeOddEven = preserveOdd << 1;
    int makeEvenOdd = preserveEven >> 1;

    n = makeOddEven | makeEvenOdd;

    return n;
}


// Longest Consecutive 1’s
int maxConsecutiveOnes(int n){
    int count = 0;
    while(n != 0){
        //This operation reduces length of every seq of 1s by one
        n = (n&(n<<1));
        count++;
    }
    return count;
}


// Gray code
//T.C - O(2^N)  S.C - O(1)
vector<string> generate(int n){
    //We have to make 1 bit gray seq
    if(n == 1) return {"0","1"};

    vector<string>ans;
    vector<string>temp = generate(n-1);
    //Add 0 to prev computes bits
    for(auto bit : temp) ans.push_back("0" + bit);
    //Add 1 to prev computes bits from bottom
    for(int i = temp.size() - 1; i >= 0; i--) ans.push_back("1" + temp[i]);
    return ans;
}
vector<int> grayCode(int n) {
    vector<string>grayString = generate(n);
    vector<int>ans;

    for(auto it:grayString) ans.push_back(stoi(it,0,2));

    return ans;
}


// Flipping an Image
vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
    for (int i=0; i<image.size(); i++) {
        reverse(image[i].begin(), image[i].end());//Flip horizontally
        //Toggling the bits by taking xor
        for(int j = 0;j<image[i].size();j++) image[i][j] ^= 0x1;
    }
    return image;
}


// Binary Number with Alternating Bits
bool hasAlternatingBits(int n) {
    int lastBit = n%2;//Even gives 0 and odd gives 1
    n >>= 1;
    while(n > 0){
        int currBit = n % 2;
        if(currBit == lastBit) return false;//Adj are same
        lastBit = currBit;//Update last bit
        n >>= 1;
    }
    return true;
}


// Generate all subsets / Power Set
vector<int> generateSubsets(int arr[],int n){
    for(int num = 0; num <= (i<<n)-1;i++){
        vector<int>ds;
        for(int bit = 0; bit <= n-1 ;bit++){
            if(num & (1<<bit)) ds.push_back(arr[bit]);
        }
    }
    return ds;
}


//Number of Steps to Reduce a Number to Zero
int numberOfSteps (int num) {
    int count=0;
    while(num){
        if(num%2) --num;//If odd just reduce the num
        else num>>=1; // num=num/2
        ++count;
    }
    return count;
}

// Maximum Product of Word Lengths
// T.C - O(N*N) S.C - O(N)
bool checkCommon(bitset<26> &a, bitset<26> &b){ // function to check if two bitset are common
    for(int i=0;i<26;i++) if(a[i] && b[i]) return true; // if any of the bits are true, return true
    return false; // otherwise return false
}
int maxProduct(vector<string>& words) { // function to find the maximum product
    int n = words.size(); // number of words
    int ans=0; // initialize the answer
    vector<bitset<26>> chars(n); // vector of bitset

    for(int i=0;i<n;i++){ // iterate over all the words 

        // iterate over all the characters in the words[]
        for(auto &ch:words[i]) chars[i][ch-'a'] = 1; // set the bitset to 1

        for(int j=0;j<i;j++){ // iterate over all the words before the current word
            if(!checkCommon(chars[i],chars[j])){// if the two words are not common
                ans = max(ans, (int)words[i].size()*(int)words[j].size()); // update the answer
            } 
        }
    }
    return ans; // return the answer
}


// Divide two integers
//T.C - O(log(dividend))
int divide(int dividend, int divisor) {
    if(dividend == divisor) return 1;//Same number division
        
    bool isPositive = (dividend<0 == divisor<0);    // if both are of same sign, answer is positive
        
    unsigned int a = abs(dividend);
    unsigned int b = abs(divisor);
    unsigned int ans = 0;
        
    while(a >= b){  // while dividend is greater than or equal to divisor
        short q = 0;
        while(a > (b<<(q+1))) q++;//Keep increasing the power of 2(i.e q)
        ans += (1<<q);  // add the power of 2 found to the answer
        a = a - (b<<q);  // reduce the dividend by divisor * power of 2 found
    }
        
    // if ans cannot be stored in signed int
    if(ans == (1<<31) and isPositive) return INT_MAX;
    return isPositive ? ans : -ans;
}