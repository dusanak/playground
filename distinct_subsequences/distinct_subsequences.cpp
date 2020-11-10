#include <iostream>
#include <vector>

int numberOfSubSeq(std::string & sequence, std::string & subsequence, unsigned int seq_pos, unsigned int sub_pos) {
    int counter = 0;
    for (unsigned int i = seq_pos; i < sequence.length(); i++) {
        if (sequence[i] == subsequence[sub_pos]) {
            if (sub_pos + 1 == subsequence.length()) {
                counter += 1;
            } else {
                counter += numberOfSubSeq(sequence, subsequence, i + 1, sub_pos + 1);
            }
        }
    }
    return counter;
}

int testCase(std::string & sequence, std::string & subsequence) {
    if (sequence.length() == 0 || subsequence.length() == 0) {
        return -1;
    }

    return numberOfSubSeq(sequence, subsequence, 0, 0);
}

int main() {
    unsigned int test_case_number = 0;
    std::cin >> test_case_number;

    std::vector<std::pair<std::string, std::string>> test_cases = std::vector<std::pair<std::string, std::string>>(test_case_number);
    for (unsigned int i = 0; i < test_case_number; i++) {
        std::string sequence, subsequence;
        std::cin >> sequence;
        std::cin >> subsequence;

        test_cases[i] = std::pair(sequence, subsequence);
    }

    for (auto i: test_cases) {
        std::cout << testCase(i.first, i.second) << std::endl;
    }
    
    return 1;
}