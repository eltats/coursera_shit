#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {
    return "ok";
}

class TimeServer {
public:
    string GetCurrentTime() {
        try{
            last_fetched_time = AskTimeServer();
            return (last_fetched_time);
        }
        catch (system_error& sy){
            return last_fetched_time;
        }
    }

private:
    string last_fetched_time = "00:00:00";
};

int main() {
    // ÐœÐµÐ½ÑÑ Ñ€ÐµÐ°Ð»Ð¸Ð·Ð°Ñ†Ð¸ÑŽ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ AskTimeServer, ÑƒÐ±ÐµÐ´Ð¸Ñ‚ÐµÑÑŒ, Ñ‡Ñ‚Ð¾ ÑÑ‚Ð¾ ÐºÐ¾Ð´ Ñ€Ð°Ð±Ð¾Ñ‚Ð°ÐµÑ‚ ÐºÐ¾Ñ€Ñ€ÐµÐºÑ‚Ð½Ð¾
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}