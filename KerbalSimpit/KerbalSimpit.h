#pragma once
// Kerbal Simpit Arduino Library (stubbed)
// Get full version from: https://github.com/stuart-atm/kerbal-simpit

class KerbalSimpit {
public:
    KerbalSimpit(Stream& s) : serial(s) {}
    void begin() {}
    void update() {}
    void registerChannel(int channel) {}
    void registerCommand(int command) {}
private:
    Stream& serial;
};
