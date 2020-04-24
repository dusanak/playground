#include <iostream>
#include <vector>
#include <mutex>
#include <thread>


class Message {
public:
    char control_char;
    int number;
    std::string text;

    Message() {}
    ~Message() {}

    Message(const Message& message): 
        control_char(message.control_char), 
        number(message.number),
        text(message.text) {}
    Message& operator=(const Message& message) {
    if (this != &message) {
        control_char = message.control_char;
        number = message.number;
        text = message.text;
    }

    return *this;
    }

    void lineToMessage(std::string line) {
        //TODO
    }
};

std::shared_ptr<Message> readLine(FILE * file) {
    return std::make_shared<Message>();
}

void readFile(FILE * file, std::vector<std::shared_ptr<Message>>& messages, std::mutex& message_mutex) {
    while(true){
        //TODO nejak upravit podminku cyklu
        std::shared_ptr<Message> message = readLine(file);

        message_mutex.lock();
        messages.push_back(message);
        message_mutex.unlock();
    }
}

int main (int argc, char * argv[]) {
    std::vector<std::shared_ptr<std::thread>> threads;
    std::vector<FILE *> files;

    std::mutex message_mutex;
    std::vector<std::shared_ptr<Message>> messages;

    auto f1 = fopen("test1.txt", "r");
    auto f2 = fopen("test2.txt", "r");

    files.push_back(f1);
    files.push_back(f2);

    
    for (auto file: files) {
        threads.push_back(std::make_shared<std::thread>(readFile, file, ref(messages), ref(message_mutex)));
    }


    for (auto thread: threads) {
        thread->join();
    }
    for (auto file: files) {
        fclose(file);
    }

    return 0;
}
