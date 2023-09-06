#include <iostream>
#include <string>

using namespace std;

class AudioSystem {
    private:
        int currentVolume;
        string currentSong;
        string audioSource;

    public:
    //constructor
    AudioSystem(string source) {

    }
    //getters
        int getCurrentVolume() {
            return this->currentVolume;
        }

        string getCurrentSong() {
            return this->currentSong;
        }

        string getAudioSource() {
            return audioSource;
        }

    //setters
        //pass positive value to increase, negative to decrease volume
        void setCurrentVolume(int volume) {
            this->currentVolume += volume;
        }

        void setCurrentSong(string song) {
            this->currentSong = song;
        }

        void setAudioSource(string source) {
            this->audioSource = source;
        }
};