// ============================================================
//  PROBLEM: Minimum Window Substring
//  Platform: LeetCode #76
//  Topic: Sliding Window / Strings
//  Difficulty: Hard
// ============================================================

// ------------------------------------------------------------
//  PROBLEM STATEMENT
// ------------------------------------------------------------
//  Given two strings s and t, return the minimum window
//  substring of s such that every character in t (including
//  duplicates) is included in the window.
//
//  If there is no such substring, return "".
//
//  Example 1:
//    Input : s = "ADOBECODEBANC", t = "ABC"
//    Output: "BANC"
//    Reason: "BANC" is the smallest window that has A, B, C
//
//  Example 2:
//    Input : s = "a", t = "a"
//    Output: "a"
//
//  Example 3:
//    Input : s = "a", t = "aa"
//    Output: ""
//    Reason: t has two 'a' but s has only one, so impossible
// ------------------------------------------------------------

// ------------------------------------------------------------
//  INTUITION — READ THIS FIRST
// ------------------------------------------------------------
//  Think of two pointers: LEFT and RIGHT, both starting at 0.
//
//  RIGHT keeps moving forward to EXPAND the window.
//  When the window has all characters of t,
//  LEFT moves forward to SHRINK the window.
//
//  Every time we have a valid window, we record it
//  if it is smaller than the best we have seen so far.
//
//  We use a frequency map (unordered_map) to track:
//    - How many of each character t needs (need[])
//    - How many the current window has (window[])
//    - A counter "formed" to know when all chars are satisfied
// ------------------------------------------------------------

// ------------------------------------------------------------
//  APPROACH: Sliding Window with Frequency Map
//  Time Complexity : O(|s| + |t|)
//  Space Complexity: O(|s| + |t|)
// ------------------------------------------------------------

// ------------------------------------------------------------
//  DRY RUN — trace through example manually
// ------------------------------------------------------------
//  s = "ADOBECODEBANC", t = "ABC"
//  need = {A:1, B:1, C:1}, required = 3
//
//  Step 1: right moves → window grows
//    right=0  window={A:1}          formed=1  (A satisfied)
//    right=1  window={A:1,D:1}      formed=1
//    right=2  window={A:1,D:1,O:1}  formed=1
//    right=3  window={...,B:1}      formed=2  (B satisfied)
//    right=4  window={...,E:1}      formed=2
//    right=5  window={...,C:1}      formed=3  ✅ valid window!
//    → window = "ADOBEC" (len=6), best = "ADOBEC"
//
//  Step 2: left moves → window shrinks
//    left=0  remove A → formed=2  (A no longer satisfied)
//    right keeps moving...
//    right=9  window has A again → formed=3 ✅
//    → window = "DOBECODEBA" — wait, shrink again
//    left shrinks to smallest valid → "BANC" (len=4)
//    best = "BANC" ✅ final answer
// ------------------------------------------------------------

#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

// ------------------------------------------------------------
//  SOLUTION FUNCTION
// ------------------------------------------------------------
string minWindow(string s, string t) {

    // Edge case: if t is longer than s, impossible
    if (s.empty() || t.empty() || t.size() > s.size()) return "";

    // Step 1: Build frequency map of what t needs
    unordered_map<char, int> need;
    for (char c : t) need[c]++;

    // Step 2: Sliding window variables
    unordered_map<char, int> window;  // current window character counts
    int left = 0;                     // left pointer
    int right = 0;                    // right pointer
    int formed = 0;                   // how many unique chars are satisfied
    int required = need.size();       // how many unique chars we need

    // Step 3: Track best result
    int bestLen = INT_MAX;
    int bestLeft = 0;

    // Step 4: Expand window by moving right
    while (right < s.size()) {

        char c = s[right];
        window[c]++;

        // Check if this character's count satisfies t's requirement
        if (need.count(c) && window[c] == need[c]) {
            formed++;
        }

        // Step 5: When window is valid, shrink from left
        while (formed == required) {

            // Update best result if this window is smaller
            int currLen = right - left + 1;
            if (currLen < bestLen) {
                bestLen = currLen;
                bestLeft = left;
            }

            // Remove leftmost character from window
            char leftChar = s[left];
            window[leftChar]--;
            if (need.count(leftChar) && window[leftChar] < need[leftChar]) {
                formed--;  // window is no longer valid
            }
            left++;  // shrink window
        }

        right++;  // expand window
    }

    // Step 6: Return result
    return bestLen == INT_MAX ? "" : s.substr(bestLeft, bestLen);
}

// ------------------------------------------------------------
//  COMMON MISTAKES TO AVOID
// ------------------------------------------------------------
//  ❌ Mistake 1: Using need.size() after modifying need map
//     → Calculate required = need.size() BEFORE the loop
//
//  ❌ Mistake 2: Checking formed == required only on expansion
//     → You must check it inside the shrink loop too
//
//  ❌ Mistake 3: Forgetting duplicates in t
//     → "formed" only increments when window[c] == need[c]
//        NOT just when window[c] >= 1
//
//  ❌ Mistake 4: Off-by-one in substr
//     → substr(bestLeft, bestLen) needs LENGTH not end index
// ------------------------------------------------------------

// ------------------------------------------------------------
//  VARIATIONS OF THIS PATTERN (practice these next)
// ------------------------------------------------------------
//  1. Longest Substring Without Repeating Characters (LC #3)
//  2. Longest Substring with At Most K Distinct Chars (LC #340)
//  3. Permutation in String (LC #567)
//  4. Find All Anagrams in a String (LC #438)
//  5. Fruits into Baskets (LC #904)
// ------------------------------------------------------------

// ------------------------------------------------------------
//  MAIN — test cases
// ------------------------------------------------------------
int main() {

    // Test 1: Standard case
    string s1 = "ADOBECODEBANC", t1 = "ABC";
    cout << "Test 1: " << minWindow(s1, t1) << endl;
    // Expected: BANC

    // Test 2: Exact match
    string s2 = "a", t2 = "a";
    cout << "Test 2: " << minWindow(s2, t2) << endl;
    // Expected: a

    // Test 3: Impossible case
    string s3 = "a", t3 = "aa";
    cout << "Test 3: " << minWindow(s3, t3) << endl;
    // Expected: (empty string)

    // Test 4: Duplicate characters in t
    string s4 = "AABBCC", t4 = "ABC";
    cout << "Test 4: " << minWindow(s4, t4) << endl;
    // Expected: AABB or ABBC or BBCC (any valid minimum)

    // Test 5: t longer than s
    string s5 = "AB", t5 = "ABC";
    cout << "Test 5: " << minWindow(s5, t5) << endl;
    // Expected: (empty string)

    return 0;
}

// ============================================================
//  SUMMARY CARD
// ============================================================
//
//  Pattern  : Sliding Window + Frequency Map
//  Pointers : left shrinks, right expands
//  Key var  : formed == required means valid window
//  Update   : record best only inside shrink loop
//
//  Time  : O(|s| + |t|)
//  Space : O(|s| + |t|)
//
// ============================================================