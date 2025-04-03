// library
#include <SFML/Graphics.hpp>
#include <cmath>
#include <numeric>


// main program
int main()
{
    // data
    int data[] = {1, 2, 3, 4};
    int data_n = sizeof(data) / sizeof(data[0]);
    int data_sum = std::accumulate(data, data + data_n, 0);

    // colors
    sf::Color colors[] = {
        sf::Color(153, 221, 255),
        sf::Color(102, 204, 255),
        sf::Color(51 , 187, 255),
        sf::Color(0  , 170, 255),
    };


    // create window
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Title", sf::State::Windowed, settings);

    // create sector of circle
    sf::ConvexShape sector;


    // while window is still open
    while (window.isOpen())
    {
        // handle events
        while (std::optional event = window.pollEvent())
        {
            // when close button is clicked
            if (event->is<sf::Event::Closed>())
            {
                // close window
                window.close();
            }
            // when window is resized
            else if (event->is<sf::Event::Resized>())
            {
                // update view
                sf::View view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
                window.setView(view);
            }
        }

        // size of window
        float window_w   = window.getView().getSize().x;
        float window_h   = window.getView().getSize().y;
        float window_min = std::min(window_w, window_h);

        // parameters
        float radius = 0.4f * window_min;
        float start  = -90.f;
        float step   = 5.f;

        // fill window with color
        window.clear(sf::Color(64, 64, 64));

        // draw
        for (int j = 0;  j < data_n;  j++)
        {
            float angle = data[j] * 360.f / data_sum;
            int   n     = std::ceil(angle / step) + 1;
            sector.setPointCount(n + 1);
            sector.setFillColor(colors[j]);
            sector.setPosition({window_w/2, window_h/2});
            for (int i = 0;  i < n - 1;  i++)
            {
                sector.setPoint(i, sf::Vector2f(radius, sf::degrees(start + i*step)));
            }
            sector.setPoint(n - 1, sf::Vector2f(radius, sf::degrees(start + angle)));
            sector.setPoint(n, {0.f, 0.f});
            window.draw(sector);

            // update start angle
            start += angle;
        }

        // display
        window.display();
    }

    
    // program end successfully
    return 0;
}