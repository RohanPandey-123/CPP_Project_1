#include <SFML/Graphics.hpp>
#include <deque>
#include <cstdlib>
#include <ctime>

using namespace sf;

int main() {
    const int width = 800, height = 600, box = 20;
    RenderWindow window(VideoMode(width, height), "Snake Game - SFML");
    window.setFramerateLimit(10);

    std::deque<Vector2i> snake = { {10, 10} };
    Vector2i direction(1, 0);
    Vector2i food(rand() % (width / box), rand() % (height / box));

    RectangleShape rect(Vector2f(box - 1, box - 1));
    rect.setFillColor(Color::Green);
    RectangleShape foodRect(Vector2f(box - 1, box - 1));
    foodRect.setFillColor(Color::Red);

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && direction.y != 1)
            direction = {0, -1};
        else if (Keyboard::isKeyPressed(Keyboard::S) && direction.y != -1)
            direction = {0, 1};
        else if (Keyboard::isKeyPressed(Keyboard::A) && direction.x != 1)
            direction = {-1, 0};
        else if (Keyboard::isKeyPressed(Keyboard::D) && direction.x != -1)
            direction = {1, 0};

        Vector2i head = snake.front() + direction;
        if (head.x < 0 || head.y < 0 || head.x >= width / box || head.y >= height / box)
            break;
        for (auto &s : snake)
            if (s == head)
                return 0;

        snake.push_front(head);
        if (head == food)
            food = { rand() % (width / box), rand() % (height / box) };
        else
            snake.pop_back();
        window.clear();
        for (auto &s : snake) {
            rect.setPosition(s.x * box, s.y * box);
            window.draw(rect);
        }
        foodRect.setPosition(food.x * box, food.y * box);
        window.draw(foodRect);
        window.display();
    }

    return 0;
}
