#include <iostream>
#include <string>

using namespace std;

class bluetoothModule {
    private:
        string connectionStatus;

    public:
    //constructor
        bluetoothModule() {

        }
        //getters
        string getConnectionStatus() {
            return this->connectionStatus;
        }

        //setters
        void setConnectionStatus(string status) {
            this->connectionStatus = status;
        }

        void connectToDevice(string deviceID) {

        }

        void disconnectFromDevice() {
            
        }
};