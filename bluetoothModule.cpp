#include <iostream>
#include <string>

using namespace std;

class BluetoothModule {
    private:
        string connectionStatus;

    public:
    //constructor
        BluetoothModule() {

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