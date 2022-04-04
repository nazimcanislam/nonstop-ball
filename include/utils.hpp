#include <iostream>
#include <SFML/Graphics.hpp>

namespace utils
{
    /**
     * @brief Calculates and returns frame per seconds (fps).
     * @param clock Current clock object
     * @return float Frame per seconds (fps)
     */
    inline float getFrameRate(sf::Clock &clock)
    {
        // Get the elapsed time.
        sf::Time elapsed = clock.getElapsedTime();

        // Calculate frame per seconds and restart the clock.
        float fps = 1.0f / elapsed.asSeconds();
        clock.restart();

        // Return calculated FPS.
        return fps;
    }

    /**
     * @brief Outputs error message in red color.
     * @param message Message to output.
     */
    inline void errorOutput(std::string message)
    {
        std::cerr << "\033[1;31m" << message << "\033[0m" << std::endl;
    }
}
