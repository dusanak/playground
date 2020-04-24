#include <iostream>
#include <vector>
#include <thread>


class Message {
    char control_char;
    int number;
    std::string text;
public:
    Message() {}
    void lineToMessage();
};

void readFile(FILE * file, const std::vector<std::shared_ptr<Message>>& messages) {
    std::cout << "test" << std::endl;
}

Message readLine() {
    return Message();
}

int main (int argc, char * argv[]) {
    std::vector<std::shared_ptr<std::thread>> threads;
    std::vector<FILE *> files;
    std::vector<std::shared_ptr<Message>> messages;

    auto f1 = fopen("test1.txt", "r");
    auto f2 = fopen("test2.txt", "r");

    files.push_back(f1);
    files.push_back(f2);

    
    for (auto file: files) {
        threads.push_back(std::make_shared<std::thread>(readFile, file, ref(messages)));
    }


    for (auto thread: threads) {
        thread->join();
    }
    for (auto file: files) {
        fclose(file);
    }

    return 0;
}
