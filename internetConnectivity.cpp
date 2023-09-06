#include <iostream>
#include <string>

using namespace std;

class InternetConnectivity {
    private:
        string connectionStatus;

    public:
        //getters
        string getConnectionStatus(){
            return this->connectionStatus;
        }

        //setters
        void setConnectionStatus(string status){
            this->connectionStatus = status;
        }

        //functionality
        void connectToInternet(){
            
        }
};