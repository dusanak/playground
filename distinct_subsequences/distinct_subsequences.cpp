#include <iostream>
#include <vector>

class BigCounter {
    public:
    std::vector<u_int32_t> val;
    const u_int32_t base = 1000000;

    BigCounter() {
        val.push_back(0);
    }

    void Set(int i) {
        val.clear();
        while (i != 0) {
            val.push_back(i % base);
            i /= base;
        }
    }

    void Set(BigCounter big_counter) {
        val.clear();
        for (auto i: big_counter.val) {
            val.push_back(i);
        }
    }

    std::string Print() {
        std::string result = "";
        for (int i = val.size() - 1; i >= 0; i--) {
            if ((u_int32_t)i != (val.size() - 1)) {
                result += std::string((6 - std::to_string(val[i]).length()), '0');
            }

            result += std::to_string(val[i]);
        }
        return result;
    }

    void Add(BigCounter big_counter) {
        int carry = 0;
        size_t i;
        for (i = 0; i < big_counter.val.size(); i++) {
            if (val.size() == i) {
                val.push_back(0);
            }

            uint32_t result = val[i] + big_counter.val[i] + carry;
            val[i] = result % base;
            carry = result / base;
        }

        if ((i == val.size()) && (carry)) {
            val.push_back(0);
        }

        for (size_t j = i; j < val.size(); j++) {   
            uint32_t result = val[j] + carry;
            val[j] = result % base;
            carry = result / base;

            if ((val.size() == j + 1) && carry) {
                val.push_back(0);
            }
        }
    }

    void Increment() {
        int carry = 1;
        for (size_t i = 0; i < val.size(); i++) {   
            uint32_t result = val[i] + carry;
            val[i] = result % base;
            carry = result / base;

            if ((val.size() == i + 1) && carry) {
                val.push_back(0);
            }
        }
    }
};

void numberOfSubSeq(std::string & sequence, std::vector<std::pair<std::string, BigCounter>> & subsequences) {
    for (char i: sequence) {
        for (int j = subsequences.size() - 1; j >= 0 ; j--) {
            if (i == subsequences[j].first[j]) {
                if (j == 0) {
                    subsequences[j].second.Increment();
                } else {
                    subsequences[j].second.Add(subsequences[j - 1].second);
                }           
            }
        }
    }
}

std::string testCase(std::string & sequence, std::string & subsequence) {
    if (sequence.length() == 0 || subsequence.length() == 0) {
        return "-1";
    }

    std::vector<std::pair<std::string, BigCounter>> subsequences = std::vector<std::pair<std::string, BigCounter>>();

    std::string possible_subsequence = "";
    for (char i: subsequence) {
        possible_subsequence += i;
        subsequences.emplace_back(possible_subsequence, BigCounter());
    }

    numberOfSubSeq(sequence, subsequences);

    return subsequences[subsequences.size() - 1].second.Print();
}


int main() {
    unsigned int test_case_number = 0;
    std::cin >> test_case_number;

    std::vector<std::string> results;
    for (unsigned int i = 0; i < test_case_number; i++) {
        std::string sequence, subsequence;
        std::cin >> sequence;
        std::cin >> subsequence;

        results.push_back(testCase(sequence, subsequence));
    }

    for (std::string i: results) {
        std::cout << i << "\n";
    }
    std::cout << std::endl;
    
    return 1;
}