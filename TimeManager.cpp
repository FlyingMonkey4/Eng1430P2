#include "TimeManager.h"

namespace TimeManager {
    static unsigned long lastTime = 0;
    static float deltaTime = 0.0f;

    void update() {
        unsigned long now = millis();
        deltaTime = (now - lastTime) / 1000.0f;
        lastTime = now;
    }

    float getDeltaTime() {
        return deltaTime;
    }
}