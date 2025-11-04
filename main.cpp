//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0}; //freq[26] stores normalized letter counts

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");


    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies (do not change or edit)
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();
    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character (do not change or edit)
int createLeafNodes(int freq[]) { //demonstrates how characters with nonzero frequency are converted into nodes
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) { //if a letter is repeated
            charArr[nextFree] = 'a' + i; //automatically assigns letters in chronological order ('a' = 97 in ascii)
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    MinHeap heap; // 1. Create a MinHeap object.
    for (int i = 0; i < nextFree; ++i) { // 2. Push all leaf node indices into the heap.
        heap.push(i, weightArr);
    }
    if (heap.size == 0) return -1;
    while (heap.size > 1) {   // 3. While the heap size is greater than 1:
        int lindex = heap.pop(weightArr);   //    - Pop two smallest nodes
        int rindex = heap.pop(weightArr);   //    - Pop two smallest nodes
        int parent = nextFree;//    - Create a new parent node with combined weight
        nextFree++;
        charArr[parent] = '\0';
        leftArr[parent] = lindex;  //    - Set left/right pointers
        rightArr[parent] = rindex;  //    - Set left/right pointers
        weightArr[parent] = weightArr[lindex] + weightArr[rindex];
        heap.push(parent, weightArr);  //    - Push new parent index back into the heap
    }
    return heap.data[0]; // 4. Return the index of the last remaining node (root)
}

    // Step 4: Use an STL stack to generate codes
    void generateCodes(int root, string codes[]) {
    if (root == -1) return;
    if (leftArr[root] == -1 && rightArr[root] == -1) {
        if (charArr[root] >= 'a' && charArr[root] <= 'z') {
            codes[charArr[root] - 'a'] = "0";
        }
        return;
    }

    stack<pair<int, string>> s; //stack = node index, code path // Use stack<pair<int, string>> to simulate DFS traversal.
    s.push(pair<int, string>(root, "")); //adds the root node to the stack with no 0s or 1s read
    while (!s.empty()) { //while the stack is not empty, safety
        pair<int, string> pair = s.top(); //separates the pair into index int and string for binary
        s.pop(); //s.top() reads but does not remove
        int node = pair.first;
        string binary = pair.second;

        int left = leftArr[node]; //index of left child
        int right = rightArr[node]; //index of right child

        // Record code when a leaf node is reached.
        if (left == -1 && right == -1) { //if a leaf node is found
            if (charArr[node] >= 'a' and charArr[node] <= 'z') {
                if (binary.empty()) {
                    codes[charArr[node] - 'a'] = "0";
                }
                else {
                    codes[charArr[node] - 'a'] = binary;
                }
            }
        }
        else {
            if (right!= -1) {
                s.push(std::pair<int, std::string>(right, binary + "1"));
            }
            if (left != -1) {
                s.push(std::pair<int, std::string>(left, binary + "0"));
                //Left edge adds '0', right edge adds '1'.
            }
        }
    }
}
    // Step 5: Print table and encoded message
    void encodeMessage(const string& filename, string codes[]) {
        cout << "\nCharacter : Code\n";
        for (int i = 0; i < 26; ++i) {
            if (!codes[i].empty())
                cout << char('a' + i) << " : " << codes[i] << "\n";
        }

        cout << "\nEncoded message:\n";

        ifstream file(filename);
        char ch;
        while (file.get(ch)) {
            if (ch >= 'A' && ch <= 'Z')
                ch = ch - 'A' + 'a';
            if (ch >= 'a' && ch <= 'z')
                cout << codes[ch - 'a'];
        }
        cout << "\n";
        file.close();
    }
